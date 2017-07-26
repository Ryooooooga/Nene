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
#include "BmpImageFormat.hpp"
#include "BmpImageFormatException.hpp"
#include "../Platform.hpp"
#include "../Reader/IReader.hpp"
#include "../Serialization/BinaryDeserializer.hpp"
#include "../Serialization/BinarySerializer.hpp"
#include "../Writer/IWriter.hpp"

namespace Nene
{
	namespace
	{
		struct BITMAPFILEHEADER
		{
			UInt16 signature;
			UInt32 size;
			UInt16 reserved1;
			UInt16 reserved2;
			UInt32 offset;
		};

		struct BITMAPINFOHEADER
		{
			UInt32 headerSize;
			Int32  width;
			Int32  height;
			UInt16 bitPlanes;
			UInt16 bitCount;
			UInt32 compression;
			UInt32 sizeImage;
			Int32  xPixelPerMeter;
			Int32  yPixelPerMeter;
			UInt32 colorUsed;
			UInt32 colorImportant;
		};

		void load(Serialization::BinaryDeserializer& archive, BITMAPFILEHEADER& header)
		{
			archive
				.serialize(header.signature)
				.serialize(header.size)
				.serialize(header.reserved1)
				.serialize(header.reserved2)
				.serialize(header.offset)
			;
		}

		void save(Serialization::BinarySerializer& archive, const BITMAPFILEHEADER& header)
		{
			archive
				.serialize(header.signature)
				.serialize(header.size)
				.serialize(header.reserved1)
				.serialize(header.reserved2)
				.serialize(header.offset)
			;
		}

		void load(Serialization::BinaryDeserializer& archive, BITMAPINFOHEADER& header)
		{
			archive
				.serialize(header.headerSize)
				.serialize(header.width)
				.serialize(header.height)
				.serialize(header.bitPlanes)
				.serialize(header.bitCount)
				.serialize(header.compression)
				.serialize(header.sizeImage)
				.serialize(header.xPixelPerMeter)
				.serialize(header.yPixelPerMeter)
				.serialize(header.colorUsed)
				.serialize(header.colorImportant)
			;
		}

		void save(Serialization::BinarySerializer& archive, const BITMAPINFOHEADER& header)
		{
			archive
				.serialize(header.headerSize)
				.serialize(header.width)
				.serialize(header.height)
				.serialize(header.bitPlanes)
				.serialize(header.bitCount)
				.serialize(header.compression)
				.serialize(header.sizeImage)
				.serialize(header.xPixelPerMeter)
				.serialize(header.yPixelPerMeter)
				.serialize(header.colorUsed)
				.serialize(header.colorImportant)
			;
		}
	}

	BmpImageFormat::BmpImageFormat(std::string_view name)
		: name_(name) {}

	const std::string& BmpImageFormat::name() const noexcept
	{
		return name_;
	}

	ArrayView<std::experimental::filesystem::path> BmpImageFormat::possibleExtensions() const noexcept
	{
		static const std::experimental::filesystem::path extensions[] =
		{
			".bmp",
		};

		return extensions;
	}

	bool BmpImageFormat::isImageHeader(const std::array<Byte, 16>& header) const noexcept
	{
		constexpr Byte signature[2] =
		{
			byte(0x42), byte(0x4d),
		};

		return std::memcmp(header.data(), signature, sizeof(signature)) == 0;
	}

	Image BmpImageFormat::decode(IReader& reader)
	{
		Serialization::BinaryDeserializer archive { reader, Endian::Order::little };

		// Read file header.
		BITMAPFILEHEADER fileHeader;
		archive.serialize(fileHeader);

		if (fileHeader.signature != 0x4d42)
		{
			throw BmpImageFormatException { u8"Unknown bitmap file format." };
		}

		// Read information header.
		BITMAPINFOHEADER infoHeader;
		archive.serialize(infoHeader);

		if (infoHeader.headerSize != 40)
		{
			throw BmpImageFormatException { u8"Unknown bitmap file information header format." };
		}

		if (infoHeader.bitPlanes != 1)
		{
			throw BmpImageFormatException { u8"Unknown bitmap image format." };
		}

		if (infoHeader.compression != 0)
		{
			throw BmpImageFormatException { u8"Unsupported bitmap compression format." };
		}

		if (infoHeader.width <= 0)
		{
			throw BmpImageFormatException { u8"Invalid bitmap image size." };
		}

		// Read pixels.
		bool topDown = (infoHeader.height < 0);

		Size2Di size =
		{
			infoHeader.width,
			std::abs(infoHeader.height),
		};

		Image image { size };

		switch (infoHeader.bitCount)
		{
			case 24:
			{
				for (Int32 y = 0; y < size.height; y++)
				{
					for (Int32 x = 0; x < size.width; x++)
					{
						const std::size_t col = x;
						const std::size_t row = topDown ? y : size.height - y - 1;
						const std::size_t i   = x + col * size.width;

						archive
							.serialize(image.dataPointer()[i].blue)
							.serialize(image.dataPointer()[i].green)
							.serialize(image.dataPointer()[i].red)
						;

						image.dataPointer()[i].alpha = 255;
					}

					UInt32 pad;
					archive.read(&pad, size.width % 4);
				}

				break;
			}

			case 32:
			{
				for (Int32 y = 0; y < size.height; y++)
				{
					for (Int32 x = 0; x < size.width; x++)
					{
						const std::size_t col = x;
						const std::size_t row = topDown ? y : size.height - y - 1;
						const std::size_t i   = x + col * size.width;

						archive
							.serialize(image.dataPointer()[i].blue)
							.serialize(image.dataPointer()[i].green)
							.serialize(image.dataPointer()[i].red)
							.serialize(image.dataPointer()[i].alpha)
						;
					}
				}

				break;
			}

			default:
			{
				throw BmpImageFormatException { u8"Unsupported bitmap image format." };
			}
		}

		return image;
	}

	void BmpImageFormat::encode(const Image& image, IWriter& writer)
	{
		Serialization::BinarySerializer archive { writer, Endian::Order::little };

		archive.serialize(BITMAPFILEHEADER
		{
			/*.signature =*/0x4d42,
			/*.size      =*/static_cast<UInt32>(54 + 4 * image.size().area()),
			/*.reserved1 =*/0,
			/*.reserved2 =*/0,
			/*.offset    =*/54,
		});

		archive.serialize(BITMAPINFOHEADER
		{
			/*.headerSize     =*/40,
			/*.width          =*/image.width(),
			/*.height         =*/image.height(),
			/*.bitPlanes      =*/1,
			/*.bitCount       =*/32,
			/*.compression    =*/0,
			/*.sizeImage      =*/static_cast<UInt32>(4 * image.size().area()),
			/*.xPixelPerMeter =*/3780,
			/*.yPixelPerMeter =*/3780,
			/*.colorUsed      =*/0,
			/*.colorImportant =*/0,
		});

		for (Int32 y = image.height() - 1; y >= 0; y--)
		{
			for (Int32 x = 0; x < image.width(); x++)
			{
				const std::size_t i = static_cast<std::size_t>(x + y * image.width());

				archive
					.serialize(image.data()[i].blue)
					.serialize(image.data()[i].green)
					.serialize(image.data()[i].red)
					.serialize(image.data()[i].alpha)
				;
			}
		}
	}

	void BmpImageFormat::encode(const Image& image, IWriter& writer, [[maybe_unused]] Int32 quality)
	{
		encode(image, std::move(writer));
	}
}
