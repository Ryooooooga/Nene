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

#include <cstdio>
#include <libjpeg/jpeglib.h>
#include <libjpeg/jerror.h>
#include "../Platform.hpp"
#include "../Scope.hpp"
#include "../Reader/IReader.hpp"
#include "../Writer/IWriter.hpp"
#include "JpegImageFormat.hpp"
#include "JpegImageFormatException.hpp"

namespace Nene
{
	namespace
	{
		constexpr std::size_t outputBufferSize = 4096;

		struct DestinationMgr
		{
			jpeg_destination_mgr dest;
			IWriter* writer;
			JOCTET* buffer;
		};

		void outputMessage([[maybe_unused]] j_common_ptr cinfo)
		{
		}

		noreturn_t error(j_common_ptr cinfo)
		{
			// Get last error message.
			char buffer[JMSG_LENGTH_MAX];
			cinfo->err->format_message(cinfo, buffer);

			throw JpegImageFormatException { buffer };
		}

		void initDest(j_compress_ptr cinfo)
		{
			const auto dest = reinterpret_cast<DestinationMgr*>(cinfo->dest);

			dest->buffer = static_cast<JOCTET*>(cinfo->mem->alloc_small(
				reinterpret_cast<j_common_ptr>(cinfo), JPOOL_IMAGE, outputBufferSize * sizeof(JOCTET)));

			dest->dest.next_output_byte = dest->buffer;
			dest->dest.free_in_buffer   = outputBufferSize;
		}

		boolean outputBuffer(j_compress_ptr cinfo)
		{
			const auto dest = reinterpret_cast<DestinationMgr*>(cinfo->dest);
		
			// Write data.
			if (dest->writer->write(dest->buffer, outputBufferSize) != outputBufferSize)
			{
				cinfo->err->msg_code = JERR_FILE_WRITE;
				cinfo->err->error_exit(reinterpret_cast<j_common_ptr>(cinfo));
			}

			dest->dest.next_output_byte = dest->buffer;
			dest->dest.free_in_buffer   = outputBufferSize;

			return TRUE;
		}

		void termDest(j_compress_ptr cinfo)
		{
			const auto dest       = reinterpret_cast<DestinationMgr*>(cinfo->dest);
			const auto dataRemain = outputBufferSize - dest->dest.free_in_buffer;

			if (dataRemain > 0)
			{
				if (dest->writer->write(dest->buffer, dataRemain) != dataRemain)
				{
					cinfo->err->msg_code = JERR_FILE_WRITE;
					cinfo->err->error_exit(reinterpret_cast<j_common_ptr>(cinfo));
				}
			}
		}
	}

	JpegImageFormat::JpegImageFormat(std::string_view name)
		: name_(name) {}

	const std::string& JpegImageFormat::name() const noexcept
	{
		return name_;
	}

	ArrayView<std::experimental::filesystem::path> JpegImageFormat::possibleExtensions() const noexcept
	{
		static const std::experimental::filesystem::path extensions[] =
		{
			".jpg",
			".jpeg",
		};

		return extensions;
	}

	bool JpegImageFormat::isImageHeader(const std::array<Byte, 16>& header) const noexcept
	{
		constexpr Byte signature[2] = { 0xff, 0xd8 };

		return std::memcmp(header.data(), signature, sizeof(signature)) == 0;
	}

	Image JpegImageFormat::decode(IReader& reader)
	{
		return Image(100, 100);
	}

	void JpegImageFormat::encode(const Image& image, IWriter& writer)
	{
		encode(image, writer, 100);
	}

	void JpegImageFormat::encode(const Image& image, IWriter& writer, Int32 quality)
	{
		jpeg_compress_struct cinfo;
		jpeg_error_mgr err;

		// Set error handler.
		cinfo.err          = jpeg_std_error(&err);
		err.output_message = outputMessage;
		err.error_exit     = error;

		// Initialize compression struct.
		jpeg_create_compress(&cinfo);

		const auto _ = scopeExit([&]()
		{
			// Destroy compression struct.
			jpeg_destroy_compress(&cinfo);
		});

		// Set destination.
		const auto dest = static_cast<DestinationMgr*>(cinfo.mem->alloc_small(
			reinterpret_cast<j_common_ptr>(&cinfo), JPOOL_PERMANENT, sizeof(DestinationMgr)));

		cinfo.dest                     = &dest->dest;
		dest->dest.init_destination    = initDest;
		dest->dest.empty_output_buffer = outputBuffer;
		dest->dest.term_destination    = termDest;
		dest->writer                   = &writer;

		// Compress data.
		cinfo.image_width      = image.size().width;
		cinfo.image_height     = image.size().height;
		cinfo.in_color_space   = JCS_RGB;
		cinfo.input_components = 3;

		jpeg_set_defaults(&cinfo);
		jpeg_set_quality(&cinfo, std::clamp(quality, 0, 100), TRUE);

		// Start compress.
		jpeg_start_compress(&cinfo, TRUE);

		std::vector<JSAMPLE> line(cinfo.image_width * 3);

		for (std::size_t y = 0; y < cinfo.image_height; y++)
		{
			auto p = line.data();
		
			for (std::size_t x = 0; x < cinfo.image_width; x++)
			{
				const auto& c = image.data()[x + y*cinfo.image_width];

				p[x*3 + 0] = c.red;
				p[x*3 + 1] = c.green;
				p[x*3 + 2] = c.blue;
			}

			jpeg_write_scanlines(&cinfo, &p, 1);
		}

		// Finish compress.
		jpeg_finish_compress(&cinfo);
	}
}
