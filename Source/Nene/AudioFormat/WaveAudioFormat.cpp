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
#include "WaveAudioFormat.hpp"
#include "WaveAudioFormatException.hpp"
#include "../Platform.hpp"
#include "../Reader/IReader.hpp"
#include "../Serialization/BinaryDeserializer.hpp"
#include "../Serialization/BinarySerializer.hpp"
#include "../Writer/IWriter.hpp"

namespace Nene
{
	namespace
	{
		struct RiffChunk
		{
			UInt32 chunkId;
			UInt32 chunkSize;
			UInt32 format;
		};

		struct ChunkHeader
		{
			UInt32 subchunkId;
			UInt32 subchunkSize;
		};

		struct FormatChunk
		{
			UInt16 audioFormat;
			UInt16 numChannels;
			UInt32 sampleRate;
			UInt32 byteRate;
			UInt16 blockAlign;
			UInt16 bitPerSample;
		};

		void load(Serialization::BinaryDeserializer& archive, RiffChunk& chunk)
		{
			archive
				.serialize(chunk.chunkId)
				.serialize(chunk.chunkSize)
				.serialize(chunk.format)
			;
		}

		void save(Serialization::BinarySerializer& archive, const RiffChunk& chunk)
		{
			archive
				.serialize(chunk.chunkId)
				.serialize(chunk.chunkSize)
				.serialize(chunk.format)
			;
		}

		void load(Serialization::BinaryDeserializer& archive, ChunkHeader& header)
		{
			archive
				.serialize(header.subchunkId)
				.serialize(header.subchunkSize)
			;
		}

		void save(Serialization::BinarySerializer& archive, const ChunkHeader& header)
		{
			archive
				.serialize(header.subchunkId)
				.serialize(header.subchunkSize)
			;
		}

		void load(Serialization::BinaryDeserializer& archive, FormatChunk& chunk)
		{
			archive
				.serialize(chunk.audioFormat)
				.serialize(chunk.numChannels)
				.serialize(chunk.sampleRate)
				.serialize(chunk.byteRate)
				.serialize(chunk.blockAlign)
				.serialize(chunk.bitPerSample)
			;
		}

		void save(Serialization::BinarySerializer& archive, const FormatChunk& chunk)
		{
			archive
				.serialize(chunk.audioFormat)
				.serialize(chunk.numChannels)
				.serialize(chunk.sampleRate)
				.serialize(chunk.byteRate)
				.serialize(chunk.blockAlign)
				.serialize(chunk.bitPerSample)
			;
		}
	}

	WaveAudioFormat::WaveAudioFormat(std::string_view name)
		: name_(name) {}

	const std::string& WaveAudioFormat::name() const noexcept
	{
		return name_;
	}

	ArrayView<IAudioFormat::path_type> WaveAudioFormat::possibleExtensions() const noexcept
	{
		static const path_type extensions[] =
		{
			".wav",
		};

		return extensions;
	}

	bool WaveAudioFormat::isAudioHeader(const std::array<Byte, 16>& header) const noexcept
	{
		constexpr Byte signatureRIFF[4] =
		{
			byte(0x52), byte(0x49), byte(0x46), byte(0x46),
		};

		constexpr Byte signatureWAVE[4] =
		{
			byte(0x57), byte(0x41), byte(0x56), byte(0x45),
		};

		return
			std::memcmp(header.data() + 0, signatureRIFF, sizeof(signatureRIFF)) == 0 &&
			std::memcmp(header.data() + 8, signatureWAVE, sizeof(signatureWAVE)) == 0;
	}

	Audio WaveAudioFormat::decode(IReader& reader)
	{
		Serialization::BinaryDeserializer archive { reader, Endian::Order::little };

		// Read RIFF chunk.
		RiffChunk riffChunk;
		archive.serialize(riffChunk);

		if (riffChunk.chunkId != 0x46464952)
		{
			throw WaveAudioFormatException { u8"File is not a RIFF format file." };
		}

		if (riffChunk.format != 0x45564157)
		{
			throw WaveAudioFormatException { u8"Unknown RIFF file format." };
		}

		// Read subchunks.
		std::vector<Byte> data;
		FormatChunk format = {};

		while (!reader.eof())
		{
			// Read subchunk header.
			ChunkHeader chunkHeader;
			archive.serialize(chunkHeader);

			if (chunkHeader.subchunkId == 0x20746d66)
			{
				// Format chunk.
				archive.serialize(format);

				if (format.audioFormat != 1)
				{
					throw WaveAudioFormatException { u8"Unsupported WAVE audio format." };
				}

				if ((format.numChannels != 1 && format.numChannels != 2) || (format.bitPerSample != 8 && format.bitPerSample != 16))
				{
					throw WaveAudioFormatException { u8"Unknown WAVE audio format." };
				}
			}
			else if (chunkHeader.subchunkId == 0x61746164)
			{
				// Data chunk.
				data.resize(chunkHeader.subchunkSize);

				archive.read(data.data(), chunkHeader.subchunkSize);
			}
			else
			{
				// Unknown chunk.
				reader.position(reader.position() + chunkHeader.subchunkSize);
			}
		}

		if (format.audioFormat == 0)
		{
			throw WaveAudioFormatException { u8"Missing format RIFF chunk in file." };
		}

		return Audio { format.numChannels, format.sampleRate, format.bitPerSample, data };
	}

	void WaveAudioFormat::encode(const Audio& audio, IWriter& writer)
	{
		Serialization::BinarySerializer archive { writer, Endian::Order::little };

		archive.serialize(RiffChunk
		{
			/*.chunkId   = */0x46464952,
			/*.chunkSize = */static_cast<UInt32>(audio.sizeBytes() + 36 - 8),
			/*.format    = */0x45564157,
		});

		archive.serialize(ChunkHeader
		{
			/*.subchunkId   = */0x20746d66,
			/*.subchunkSize = */16,
		});

		archive.serialize(FormatChunk
		{
			/*.audioFormat  = */1,
			/*.numChannels  = */static_cast<UInt16>(audio.channels()),
			/*.sampleRate   = */audio.samplingRate(),
			/*.byteRate     = */audio.samplingRate() * audio.channels() * audio.bitRate() / 8,
			/*.blockAlign   = */static_cast<UInt16>(audio.channels() * audio.bitRate() / 8),
			/*.bitPerSample = */static_cast<UInt16>(audio.bitRate()),
		});

		archive.serialize(ChunkHeader
		{
			/*.subchunkId   = */0x61746164,
			/*.subchunkSize = */static_cast<UInt32>(audio.sizeBytes()),
		});

		writer.write(audio.data().data(), audio.data().size());
	}

	void WaveAudioFormat::encode(const Audio& audio, IWriter& writer, [[maybe_unused]] Int32 quality)
	{
		encode(audio, writer);
	}
}
