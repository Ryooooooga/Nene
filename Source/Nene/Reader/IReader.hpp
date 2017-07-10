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

#ifndef INCLUDE_NENE_READER_IREADER_HPP
#define INCLUDE_NENE_READER_IREADER_HPP

namespace Nene
{
	/**
	 * @brief      Reader interface.
	 */
	class IReader
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		IReader() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IReader() =default;

		/**
		 * @brief      Determins if the reader is already reached EOF.
		 *
		 * @return     `true` if already reached EOF, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool eof() const noexcept =0;

		/**
		 * @brief      Returns the data size.
		 *
		 * @return     The data size of the reader.
		 */
		[[nodiscard]]
		virtual std::size_t size() const noexcept =0;

		/**
		 * @brief      Returns the current reading position.
		 *
		 * @return     The current reading position of the reader.
		 */
		[[nodiscard]]
		virtual std::size_t position() const noexcept =0;

		/**
		 * @brief      Sets the current reading position.
		 *
		 * @param[in]  pos   The position to move.
		 */
		virtual void position(std::size_t pos) =0;

		/**
		 * @brief      Reads the data.
		 *
		 * @param      buffer  Pointer to the data buffer.
		 * @param[in]  size    The size to read in bytes.
		 *
		 * @return     Bytes of the data read.
		 */
		virtual std::size_t read(void* buffer, std::size_t size) =0;

		/**
		 * @brief      Peeks the data.
		 *
		 * @param      buffer  Pointer to the data buffer.
		 * @param[in]  size    The size to peek in bytes.
		 *
		 * @return     Bytes of the data peeked.
		 */
		virtual std::size_t peek(void* buffer, std::size_t size) =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_READER_IREADER_HPP
