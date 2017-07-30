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
#include "FileWriter.hpp"
#include "../Platform.hpp"
#include "../Exceptions/FileException.hpp"

namespace Nene
{
	FileWriter::FileWriter(const std::experimental::filesystem::path& path)
		: path_(std::experimental::filesystem::absolute(path))
		, file_(nullptr, std::fclose)
	{
		// Open file.
		FILE* fp = nullptr;

#if defined(NENE_COMPILER_MSVC)
		if (_wfopen_s(&fp, path.c_str(), L"wb"))
#else
		if (!(fp = std::fopen(path.c_str(), "wb")))
#endif
		{
			throw FileException { fmt::format(u8"Could not open file '{}'.", path.u8string()) };
		}

		file_.reset(fp);
	}

	std::size_t FileWriter::size() const noexcept
	{
#if defined(NENE_COMPILER_MSVC)
		struct ::_stat64 stat;
		::_fstat64(::_fileno(file_.get()), &stat);
#else
		struct ::stat stat;
		::fstat(::_fileno(file_.get()), &stat);
#endif

		return static_cast<std::size_t>(stat.st_size);
	}

	std::size_t FileWriter::position() const noexcept
	{
#if defined(NENE_COMPILER_MSVC)
		return static_cast<std::size_t>(::_ftelli64(file_.get()));
#elif defined(NENE_COMPILER_GCC) || defined(NENE_COMPILER_CLANG)
		return static_cast<std::size_t>(::ftello64(file_.get()));
#else
		return static_cast<std::size_t>(std::ftell(file_.get()));
#endif
	}

	void FileWriter::position(std::size_t pos)
	{
#if defined(NENE_COMPILER_MSVC)
		::_fseeki64(file_.get(), static_cast<__int64>(pos), SEEK_SET);
#elif defined(NENE_COMPILER_GCC) || defined(NENE_COMPILER_CLANG)
		::fseeko64(file_.get(), static_cast<off64_t>(pos), SEEK_SET);
#else
		std::fseek(file_.get(), static_cast<long>(pos), SEEK_SET);
#endif
	}

	std::size_t FileWriter::write(const void* buffer, std::size_t size)
	{
		return std::fwrite(buffer, 1, size, file_.get());
	}

	std::experimental::filesystem::path FileWriter::path() const
	{
		return path_;
	}
}
