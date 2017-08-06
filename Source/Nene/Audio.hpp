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

#ifndef INCLUDE_NENE_AUDIO_HPP
#define INCLUDE_NENE_AUDIO_HPP

#include "ArrayView.hpp"

namespace Nene
{
	/**
	 * @brief      Audio file information.
	 */
	class Audio
	{
		std::vector<Byte> data_;
		UInt32            channels_;
		UInt32            samplingRate_;
		UInt32            bitRate_;

	public:
		/**
		 * @brief      Default constructor.
		 */
		Audio() =delete;

		/**
		 * @brief      Copy constructor.
		 */
		Audio(const Audio&) =delete;

		/**
		 * @brief      Move constructor.
		 */
		Audio(Audio&&) =default;

		explicit Audio(UInt32 channels, UInt32 samplingRate, UInt32 bitRate, ByteArrayView data)
			: data_(data.to_vector())
			, channels_(channels)
			, samplingRate_(samplingRate)
			, bitRate_(bitRate)
		{
			assert(channels == 1 || channels == 2);
			assert(samplingRate > 0);
			assert(bitRate == 8 || bitRate == 16);
		}

		/**
		 * @brief      Destructor.
		 */
		~Audio() =default;

		/**
		 * @brief      Copy operator `=`.
		 */
		Audio& operator=(const Audio&) =delete;

		/**
		 * @brief      Move operator `=`.
		 */
		Audio& operator=(Audio&&) =default;

		/**
		 * @brief      Returns the audio data.
		 *
		 * @return     The PCM audio data.
		 */
		[[nodiscard]]
		ByteArrayView data() const noexcept
		{
			return data_;
		}

		/**
		 * @brief      Returns number of channels.
		 *
		 * @return     Number of audio channels.
		 */
		[[nodiscard]]
		UInt32 channels() const noexcept
		{
			return channels_;
		}

		/**
		 * @brief      Returns the audio sampling rate.
		 *
		 * @return     The audio sampling rate.
		 */
		[[nodiscard]]
		UInt32 samplingRate() const noexcept
		{
			return samplingRate_;
		}

		/**
		 * @brief      Returns the data bit rate.
		 *
		 * @return     The bit rate of the audio data.
		 */
		[[nodiscard]]
		UInt32 bitRate() const noexcept
		{
			return bitRate_;
		}

		/**
		 * @brief      Returns bytes size of the audio data.
		 *
		 * @return     Bytes size of the audio data.
		 */
		[[nodiscard]]
		std::size_t sizeBytes() const noexcept
		{
			return data_.size();
		}

		/**
		 * @brief      Creates the new audio data from the audio.
		 *
		 * @return     Copy of the audio data.
		 */
		[[nodiscard]]
		Audio clone() const noexcept
		{
			return Audio { channels_, samplingRate_, bitRate_, data_ };
		}
	};
}

#endif  // #ifndef INCLUDE_NENE_AUDIO_HPP
