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

#ifndef INCLUDE_NENE_WRITER_MEMORYWRITER_HPP
#define INCLUDE_NENE_WRITER_MEMORYWRITER_HPP

#include <algorithm>
#include <vector>
#include "../Types.hpp"
#include "../Uncopyable.hpp"
#include "IWriter.hpp"

namespace Nene
{
	/**
	 * @brief      Memory writer.
	 */
	class MemoryWriter final
		: public  IWriter
		, private Uncopyable
	{
		std::vector<Byte> data_;
		std::size_t       pos_;

	public:
		/**
		 * @brief      Constructor.
		 */
		explicit MemoryWriter()
			: data_ ()
			, pos_  (0) {}

		/**
		 * @brief      Destructor.
		 */
		~MemoryWriter() =default;

		/**
		 * @see        `Nene::IWriter::size()`.
		 */
		[[nodiscard]]
		std::size_t size() const noexcept override
		{
			return data_.size();
		}

		/**
		 * @see        `Nene::IWriter::position()`.
		 */
		[[nodiscard]]
		std::size_t position() const noexcept override
		{
			return pos_;
		}

		/**
		 * @see        `Nene::IWriter::position()`.
		 */
		void position(std::size_t pos) override
		{
			pos_ = (std::min)(pos, data_.size());
		}

		/**
		 * @see        `Nene::IReader::write()`.
		 */
		std::size_t write(const void* buffer, std::size_t size) override
		{
			const auto requiredSize = pos_ + size;

			if (requiredSize > data_.size())
			{
				data_.reserve(data_.size() * 2);
				data_.resize(requiredSize);
			}

			// Copy data.
			std::memcpy(data_.data() + pos_, buffer, size);

			pos_ += size;

			return size;
		}

		/**
		 * @brief      Returns the data.
		 *
		 * @return     The data written.
		 */
		[[nodiscard]]
		ByteArrayView data() const noexcept
		{
			return data_;
		}
	};
}

#endif  // #ifndef INCLUDE_NENE_WRITER_MEMORYWRITER_HPP
