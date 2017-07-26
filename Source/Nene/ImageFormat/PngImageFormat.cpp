//=============================================================================
// Copyright (c) 2017 Ryooooooga
// https://github.com/Ryooooooga
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to whom
// the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
// DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
// OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//=============================================================================

#include <fmt/ostream.h>
#include <libpng/png.h>
#include "PngImageFormat.hpp"
#include "PngImageFormatException.hpp"
#include "../Platform.hpp"
#include "../Scope.hpp"
#include "../Reader/IReader.hpp"
#include "../Writer/IWriter.hpp"

namespace Nene
{
	namespace
	{
		void error([[maybe_unused]] ::png_structp png, ::png_const_charp message)
		{
			throw PngImageFormatException { fmt::format(u8"PNG image format error\nDescription: {}", message) };
		}

		void warning([[maybe_unused]] ::png_structp png, ::png_const_charp message)
		{
#ifdef NENE_DEBUG
			fprintf(stderr, "PNG warning: %s\n", message);
#endif
		}

		void readData(::png_structp png, ::png_bytep buffer, ::png_size_t size)
		{
			const auto reader = static_cast<IReader*>(::png_get_io_ptr(png));

			reader->read(buffer, size);
		}

		void writeData(::png_structp png, ::png_bytep buffer, ::png_size_t size)
		{
			const auto writer = static_cast<IWriter*>(::png_get_io_ptr(png));

			writer->write(buffer, size);
		}
	}

	PngImageFormat::PngImageFormat(std::string_view name)
		: name_(name) {}

	const std::string& PngImageFormat::name() const noexcept
	{
		return name_;
	}

	ArrayView<std::experimental::filesystem::path> PngImageFormat::possibleExtensions() const noexcept
	{
		static const std::experimental::filesystem::path extensions[] =
		{
			".png",
		};

		return extensions;
	}

	bool PngImageFormat::isImageHeader(const std::array<Byte, 16>& header) const noexcept
	{
		constexpr Byte signature[8] =
		{
			byte(0x89), byte(0x50), byte(0x4e), byte(0x47),
			byte(0x0d), byte(0x0a), byte(0x1a), byte(0x0a),
		};

		return std::memcmp(header.data(), signature, sizeof(signature)) == 0;
	}

	Image PngImageFormat::decode(IReader& reader)
	{
		png_structp png  = nullptr;
		png_infop   info = nullptr;

		// Release objects.
		[[maybe_unused]] const auto _ = scopeExit([&]()
		{
			::png_destroy_read_struct(&png, &info, nullptr);
		});

		// Initialize libpng.
		if (!(png = ::png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, error, warning)))
		{
			throw EngineException { u8"Failed to create png read struct." };
		}

		if (!(info = ::png_create_info_struct(png)))
		{
			throw EngineException { u8"Failed to cerate png info struct." };
		}

		// Set callback.
		::png_set_read_fn(png, &reader, readData);

		// Read information header.
		::png_read_info(png, info);

		png_uint_32 width, height;
		int bitDepth, colorType, interlaceType;

		::png_get_IHDR(png, info, &width, &height, &bitDepth, &colorType, &interlaceType, nullptr, nullptr);

		// Expand element into 8bit.
		::png_set_packing(png);

		if (colorType == PNG_COLOR_TYPE_PALETTE)
		{
			// Convert palette image into rgb image.
			::png_set_palette_to_rgb(png);
		}

		if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
		{
			// Convert (1/2/4)bit gray scale image into 8bit gray scale image.
			::png_set_expand_gray_1_2_4_to_8(png);
		}

		if (::png_get_valid(png, info, PNG_INFO_tRNS))
		{
			// Convert tRNS chunk into alpha channel.
			::png_set_tRNS_to_alpha(png);
		}

		if (bitDepth == 16)
		{
			// Narrow element into 8bit.
			::png_set_scale_16(png);
		}

		if (colorType == PNG_COLOR_TYPE_GRAY || colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
		{
			// Convert gray scale into rgb.
			::png_set_gray_to_rgb(png);
		}

		if (interlaceType != PNG_INTERLACE_NONE)
		{
			// Handling image interlace.
			::png_set_interlace_handling(png);
		}

		// Add alpha.
		::png_set_add_alpha(png, 0xff, PNG_FILLER_AFTER);

		// Set gamma.
		double gamma;

		if (::png_get_gAMA(png, info, &gamma))
		{
			// Windows screen gamma.
			constexpr double screenGamma = 2.2;

			::png_set_gamma(png, screenGamma, gamma);
		}

		// Update information.
		::png_read_update_info(png, info);

		// Create image buffer.
		Image image { static_cast<Int32>(width), static_cast<Int32>(height) };

		// Create list of row pointers.
		std::vector<::png_bytep> rows(height);

		for (png_uint_32 i = 0; i < height; i++)
		{
			rows[i] = reinterpret_cast<png_bytep>(image.dataBytes()) + i * width * sizeof(Color4);
		}

		::png_read_image(png, rows.data());
		::png_read_end(png, info);

		return image;
	}

	void PngImageFormat::encode(const Image& image, IWriter& writer)
	{
		png_structp png  = nullptr;
		png_infop   info = nullptr;

		try
		{
			// Initialize libpng.
			if (!(png = ::png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, error, warning)))
			{
				throw EngineException { u8"Failed to create png write struct." };
			}

			if (!(info = ::png_create_info_struct(png)))
			{
				throw EngineException { u8"Failed to cerate png info struct." };
			}

			// Set callback.
			::png_set_write_fn(png, &writer, writeData, nullptr);


			// Set information header.
			const auto width           = static_cast<png_uint_32>(image.width()  );
			const auto height          = static_cast<png_uint_32>(image.height() );
			const int  bitDepth        = 8;
			const int  colorType       = PNG_COLOR_TYPE_RGBA;
			const int  interlaceType   = PNG_INTERLACE_NONE;
			const int  compressionType = PNG_COMPRESSION_TYPE_DEFAULT;
			const int  filterType      = PNG_FILTER_TYPE_DEFAULT;

			::png_set_IHDR(png, info, width, height, bitDepth, colorType, interlaceType, compressionType, filterType);

			// Write information header.
			::png_write_info(png, info);

			// Write image data.
			png_const_bytep data = reinterpret_cast<png_const_bytep>(image.dataBytes());

			for (png_uint_32 y = 0; y < height; y++)
			{
				::png_write_row(png, data);

				data += width * sizeof(Color4);
			}

			::png_write_end(png, info);

			// Release objects.
			::png_destroy_write_struct(&png, &info);
		}
		catch (...)
		{
			// Release objects.
			::png_destroy_write_struct(&png, &info);

			throw;
		}
	}

	void PngImageFormat::encode(const Image& image, IWriter& writer, [[maybe_unused]] Int32 quality)
	{
		encode(image, writer);
	}
}
