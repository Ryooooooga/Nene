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

#ifndef INCLUDE_NENE_AUDIOFORMAT_IAUDIOFORMAT_HPP
#define INCLUDE_NENE_AUDIOFORMAT_IAUDIOFORMAT_HPP

#include <experimental/filesystem>
#include "../Audio.hpp"

namespace Nene
{
	// Forward declarations.
	class IReader;
	class IWriter;

	/**
	 * @brief      Audio format interface.
	 */
	class IAudioFormat
	{
	public:
		using path_type = std::experimental::filesystem::path;

		/**
		 * @brief      Constructor.
		 */
		explicit IAudioFormat() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IAudioFormat() =default;

		/**
		 * @brief      Returns the name of the audio format.
		 *
		 * @return     The name of the audio format.
		 */
		[[nodiscard]]
		virtual const std::string& name() const noexcept =0;

		/**
		 * @brief      Returns the list of possible extensions of the audio format.
		 *
		 * @return     The list of possible extensions of the audio format.
		 */
		[[nodiscard]]
		virtual ArrayView<path_type> possibleExtensions() const noexcept =0;

		/**
		 * @brief      Determines if the given data is an audio header.
		 *
		 * @param[in]  header  The header byte data.
		 *
		 * @return     `true` if `header` seems the audio header supported,
		 *             `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool isAudioHeader(const std::array<Byte, 16>& header) const noexcept =0;

		/**
		 * @brief      Constructs a audio from a reader.
		 *
		 * @param      reader  The audio data reader.
		 *
		 * @return     The audio from `reader`.
		 */
		[[nodiscard]]
		virtual Audio decode(IReader& reader) =0;

		/**
		 * @brief      Writes a audio to a writer.
		 *
		 * @param[in]  audio   The audio data to write.
		 * @param      writer  The audio data writer.
		 */
		virtual void encode(const Audio& audio, IWriter& writer) =0;

		/**
		 * @brief      Writes a audio to a writer.
		 *
		 * @param[in]  audio    The audio data to write.
		 * @param      writer   The audio data writer.
		 * @param[in]  quality  The audio quality.
		 */
		virtual void encode(const Audio& audio, IWriter& writer, Int32 quality) =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_AUDIOFORMAT_IAUDIOFORMAT_HPP
