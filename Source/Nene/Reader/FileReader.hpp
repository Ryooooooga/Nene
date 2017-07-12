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

#ifndef INCLUDE_NENE_READER_FILEREADER_HPP
#define INCLUDE_NENE_READER_FILEREADER_HPP

#include <cstdio>
#include <filesystem>
#include <memory>
#include "../Uncopyable.hpp"
#include "IReader.hpp"

namespace Nene
{
	/**
	 * @brief      File reader.
	 */
	class FileReader final
		: public  IReader
		, private Uncopyable
	{
		std::experimental::filesystem::path path_;
		std::unique_ptr<FILE, int(*)(FILE*)> file_;
		std::size_t size_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  path  The file path to read.
		 */
		explicit FileReader(const std::experimental::filesystem::path& path);

		/**
		 * @brief      Destructor.
		 */
		~FileReader() =default;

		/**
		 * @see        `Nene::IReader::eof()`.
		 */
		[[nodiscard]]
		bool eof() const noexcept override;

		/**
		 * @see        `Nene::IReader::size()`.
		 */
		[[nodiscard]]
		std::size_t size() const noexcept override;

		/**
		 * @see        `Nene::IReader::position()`.
		 */
		[[nodiscard]]
		std::size_t position() const noexcept override;

		/**
		 * @see        `Nene::IReader::position()`.
		 */
		void position(std::size_t pos) override;

		/**
		 * @see        `Nene::IReader::read()`.
		 */
		std::size_t read(void* buffer, std::size_t size) override;

		/**
		 * @see        `Nene::IReader::peek()`.
		 */
		std::size_t peek(void* buffer, std::size_t size) override;

		/**
		 * @brief      Returns the input file path.
		 *
		 * @return     The input file path.
		 */
		[[nodiscard]]
		const std::experimental::filesystem::path& path() const noexcept;
	};
}

#endif  // #ifndef INCLUDE_NENE_READER_FILEREADER_HPP
