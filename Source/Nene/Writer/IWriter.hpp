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

#ifndef INCLUDE_NENE_WRITER_IWRITER_HPP
#define INCLUDE_NENE_WRITER_IWRITER_HPP

namespace Nene
{
	/**
	 * @brief      Writer interface.
	 */
	class IWriter
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		IWriter() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IWriter() =default;

		/**
		 * @brief      Returns the data size.
		 *
		 * @return     The data size of the writer.
		 */
		[[nodiscard]]
		virtual std::size_t size() const noexcept =0;

		/**
		 * @brief      Returns the current writing position.
		 *
		 * @return     The current writing position of the reader.
		 */
		[[nodiscard]]
		virtual std::size_t position() const noexcept =0;

		/**
		 * @brief      Sets the current writing position.
		 *
		 * @param[in]  pos   The position to move.
		 */
		virtual void position(std::size_t pos) =0;

		/**
		 * @brief      Writes the data.
		 *
		 * @param      buffer  Pointer to the data buffer.
		 * @param[in]  size    The size to write in bytes.
		 *
		 * @return     Bytes of the data written.
		 */
		virtual std::size_t write(const void* buffer, std::size_t size) =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_WRITER_IWRITER_HPP
