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

#ifndef INCLUDE_NENE_WRITER_FILEWRITER_HPP
#define INCLUDE_NENE_WRITER_FILEWRITER_HPP

#include <cstdio>
#include <memory>
#include <experimental/filesystem>
#include "../Uncopyable.hpp"
#include "IWriter.hpp"

namespace Nene
{
	/**
	 * @brief      File writer.
	 */
	class FileWriter final
		: public  IWriter
		, private Uncopyable
	{
		std::experimental::filesystem::path path_;
		std::unique_ptr<FILE, int(*)(FILE*)> file_;

	public:
		using path_type = std::experimental::filesystem::path;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  path  The file path to write.
		 */
		explicit FileWriter(const path_type& path);

		/**
		 * @brief      Destructor.
		 */
		~FileWriter() =default;

		/**
		 * @see        `Nene::IWriter::size()`.
		 */
		[[nodiscard]]
		std::size_t size() const noexcept override;

		/**
		 * @see        `Nene::IWriter::position()`.
		 */
		[[nodiscard]]
		std::size_t position() const noexcept override;

		/**
		 * @see        `Nene::IWriter::position()`.
		 */
		void position(std::size_t pos) override;

		/**
		 * @see        `Nene::IReader::write()`.
		 */
		std::size_t write(const void* buffer, std::size_t size) override;

		/**
		 * @brief      Returns the input file path.
		 *
		 * @return     The input file path.
		 */
		[[nodiscard]]
		path_type path() const;
	};
}

#endif  // #ifndef INCLUDE_NENE_WRITER_FILEWRITER_HPP
