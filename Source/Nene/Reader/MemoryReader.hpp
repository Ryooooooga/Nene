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

#ifndef INCLUDE_NENE_READER_MEMORYREADER_HPP
#define INCLUDE_NENE_READER_MEMORYREADER_HPP

#include <algorithm>
#include <vector>
#include "../Types.hpp"
#include "../Uncopyable.hpp"
#include "IReader.hpp"

namespace Nene
{
	/**
	 * @brief      Memory reader.
	 */
	class MemoryReader final
		: public  IReader
		, private Uncopyable
	{
		std::vector<UInt8> data_;
		std::size_t        pos_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  data  The memory data.
		 */
		explicit MemoryReader(ArrayView<UInt8> data)
			: data_ (data.to_vector())
			, pos_  (0) {}

		/**
		 * @brief      Destructor.
		 */
		~MemoryReader() =default;

		/**
		 * @see        `Nene::IReader::eof()`.
		 */
		[[nodiscard]]
		bool eof() const noexcept override
		{
			return pos_ >= data_.size();
		}

		/**
		 * @see        `Nene::IReader::size()`.
		 */
		[[nodiscard]]
		std::size_t size() const noexcept override
		{
			return data_.size();
		}

		/**
		 * @see        `Nene::IReader::position()`.
		 */
		[[nodiscard]]
		std::size_t position() const noexcept override
		{
			return pos_;
		}

		/**
		 * @see        `Nene::IReader::position()`.
		 */
		void position(std::size_t pos) override
		{
			pos_ = (std::min)(pos, data_.size());
		}

		/**
		 * @see        `Nene::IReader::read()`.
		 */
		std::size_t read(void* buffer, std::size_t size) override
		{
			const auto sizeToRead = (std::min)(size, data_.size() - pos_);

			// Copy data.
			std::memcpy(buffer, data_.data(), sizeToRead);

			pos_ += sizeToRead;

			return sizeToRead;
		}

		/**
		 * @see        `Nene::IReader::peek()`.
		 */
		std::size_t peek(void* buffer, std::size_t size) override
		{
			const auto sizeToPeek = (std::min)(size, data_.size() - pos_);

			// Copy data.
			std::memcpy(buffer, data_.data(), sizeToPeek);

			return sizeToPeek;
		}

		/**
		 * @brief      Returns the memory data.
		 *
		 * @return     The memory data of the memory reader.
		 */
		[[nodiscard]]
		ArrayView<UInt8> data() const noexcept
		{
			return data_;
		}
	};
}

#endif  // #ifndef INCLUDE_NENE_READER_MEMORYREADER_HPP
