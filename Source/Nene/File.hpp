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

#ifndef INCLUDE_NENE_FILE_HPP
#define INCLUDE_NENE_FILE_HPP

#include <experimental/filesystem>
#include "ArrayView.hpp"

namespace Nene::File
{
	/**
	 * @brief      Reads whole file at once.
	 *
	 * @param[in]  path  The file path to read.
	 *
	 * @return     Entire contents of the file.
	 */
	std::vector<Byte> read(const std::experimental::filesystem::path& path);

	/**
	 * @brief      Writes byte array to a file.
	 *
	 * @param[in]  path  The file path to write or create.
	 * @param[in]  data  The file contents to write.
	 */
	void write(const std::experimental::filesystem::path& path, ArrayView<Byte> data);
}

#endif  // #ifndef INCLUDE_NENE_FILE_HPP
