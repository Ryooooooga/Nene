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
#include "ImageFormatException.hpp"
#include "../Platform.hpp"
#include "../Reader/IReader.hpp"

namespace Nene
{
	namespace
	{
		void pngError([[maybe_unused]] ::png_structp png, ::png_const_charp message)
		{
			throw ImageFormatException { fmt::format(u8"PNG image format error\nDescription: {}", message) };
		}

		void pngWarning([[maybe_unused]] ::png_structp png, ::png_const_charp message)
		{
#ifdef NENE_DEBUG
			fprintf(stderr, "PNG warning: %s\n", message);
#endif
		}

		void pngReadData(::png_structp png, ::png_bytep buffer, ::png_size_t size)
		{
			const auto reader = static_cast<IReader*>(::png_get_io_ptr(png));

			reader->read(buffer, size);
		}
	}

	PngImageFormat::PngImageFormat(std::string_view name)
		: name_(name) {}

	const std::string& PngImageFormat::name() const noexcept
	{
		return name_;
	}

	bool PngImageFormat::isImageHeader(const std::array<Byte, 16>& header) const noexcept
	{
		constexpr Byte signature[8] = { 0x89, 0x50, 0x4e, 0x47, 0x0d, 0x0a, 0x1a, 0x0a };

		return std::memcmp(header.data(), signature, sizeof(signature)) == 0;
	}

	Image PngImageFormat::decode(IReader& reader)
	{
		// Initialize libpng.
		::png_structp png = ::png_create_read_struct(PNG_LIBPNG_VER_STRING, nullptr, pngError, pngWarning);

		if (!png)
		{
			throw EngineException { u8"Failed to create png read struct." };
		}

		::png_infop info = ::png_create_info_struct(png);

		if (!info)
		{
			::png_destroy_read_struct(&png, nullptr, nullptr);

			throw EngineException { u8"Failed to cerate png info struct." };
		}

		::png_set_read_fn(png, &reader, pngReadData);

		// Read information header.
		::png_read_info(png, info);

		::png_uint_32 width, height;
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
		Image image { { static_cast<Int32>(width), static_cast<Int32>(height) } };

		// Create list of row pointers.
		std::vector<::png_bytep> rows(height);

		for (png_uint_32 i = 0; i < height; i++)
		{
			rows[i] = image.dataPointerAsByte() + i * width * sizeof(Color4);
		}

		// Read pixels.
		::png_read_image(png, rows.data());
		::png_read_end(png, info);

		// Release objects.
		::png_destroy_read_struct(&png, &info, nullptr);

		return image;
	}
}
