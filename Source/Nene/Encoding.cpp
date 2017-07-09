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

#include <boost/locale/encoding_utf.hpp>
#include "Encoding.hpp"

namespace Nene::Encoding
{
	std::string toUtf8(std::string_view utf8)
	{
		return static_cast<std::string>(utf8);
	}

	std::string toUtf8(std::u16string_view utf16)
	{
		return boost::locale::conv::utf_to_utf<char>(utf16.data(), utf16.data() + utf16.size(), boost::locale::conv::method_type::stop);
	}

	std::string toUtf8(std::u32string_view utf32)
	{
		return boost::locale::conv::utf_to_utf<char>(utf32.data(), utf32.data() + utf32.size(), boost::locale::conv::method_type::stop);
	}

	std::string toUtf8(std::wstring_view wide)
	{
		return boost::locale::conv::utf_to_utf<char>(wide.data(), wide.data() + wide.size(), boost::locale::conv::method_type::stop);
	}

	std::u16string toUtf16(std::string_view utf8)
	{
		return boost::locale::conv::utf_to_utf<char16_t>(utf8.data(), utf8.data() + utf8.size(), boost::locale::conv::method_type::stop);
	}

	std::u16string toUtf16(std::u16string_view utf16)
	{
		return static_cast<std::u16string>(utf16);
	}

	std::u16string toUtf16(std::u32string_view utf32)
	{
		return boost::locale::conv::utf_to_utf<char16_t>(utf32.data(), utf32.data() + utf32.size(), boost::locale::conv::method_type::stop);
	}

	std::u16string toUtf16(std::wstring_view wide)
	{
		return boost::locale::conv::utf_to_utf<char16_t>(wide.data(), wide.data() + wide.size(), boost::locale::conv::method_type::stop);
	}

	std::u32string toUtf32(std::string_view utf8)
	{
		return boost::locale::conv::utf_to_utf<char32_t>(utf8.data(), utf8.data() + utf8.size(), boost::locale::conv::method_type::stop);
	}

	std::u32string toUtf32(std::u16string_view utf16)
	{
		return boost::locale::conv::utf_to_utf<char32_t>(utf16.data(), utf16.data() + utf16.size(), boost::locale::conv::method_type::stop);
	}

	std::u32string toUtf32(std::u32string_view utf32)
	{
		return static_cast<std::u32string>(utf32);
	}

	std::u32string toUtf32(std::wstring_view wide)
	{
		return boost::locale::conv::utf_to_utf<char32_t>(wide.data(), wide.data() + wide.size(), boost::locale::conv::method_type::stop);
	}

	std::wstring toWide(std::string_view utf8)
	{
		return boost::locale::conv::utf_to_utf<wchar_t>(utf8.data(), utf8.data() + utf8.size(), boost::locale::conv::method_type::stop);
	}

	std::wstring toWide(std::u16string_view utf16)
	{
		return boost::locale::conv::utf_to_utf<wchar_t>(utf16.data(), utf16.data() + utf16.size(), boost::locale::conv::method_type::stop);
	}

	std::wstring toWide(std::u32string_view utf32)
	{
		return boost::locale::conv::utf_to_utf<wchar_t>(utf32.data(), utf32.data() + utf32.size(), boost::locale::conv::method_type::stop);
	}

	std::wstring toWide(std::wstring_view wide)
	{
		return static_cast<std::wstring>(wide);
	}
}
