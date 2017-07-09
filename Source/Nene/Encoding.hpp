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

#ifndef INCLUDE_NENE_ENCODING_HPP
#define INCLUDE_NENE_ENCODING_HPP

#include <string_view>

namespace Nene::Encoding
{
	/**
	 * @brief      Encodes UTF-8 characters to UTF-8 characters. (Does nothing.)
	 *
	 * @param[in]  utf8  UTF-8 encoded string.
	 *
	 * @return     UTF-8 encoded string.
	 */
	[[nodiscard]]
	std::string toUtf8(std::string_view utf8);

	/**
	 * @brief      Encodes UTF-16 characters to UTF-8 characters.
	 *
	 * @param[in]  utf16  UTF-16 encoded string.
	 *
	 * @return     UTF-8 encoded string.
	 */
	[[nodiscard]]
	std::string toUtf8(std::u16string_view utf16);

	/**
	 * @brief      Encodes UTF-32 characters to UTF-8 characters.
	 *
	 * @param[in]  utf32  UTF-32 encoded string.
	 *
	 * @return     UTF-8 encoded string.
	 */
	[[nodiscard]]
	std::string toUtf8(std::u32string_view utf32);

	/**
	 * @brief      Encodes wide characters to UTF-8 characters.
	 *
	 * @param[in]  wide  Wide character string.
	 *
	 * @return     UTF-8 encoded string.
	 */
	[[nodiscard]]
	std::string toUtf8(std::wstring_view wide);

	/**
	 * @brief      Encodes UTF-8 characters to UTF-16 characters.
	 *
	 * @param[in]  utf8  UTF-8 encoded string.
	 *
	 * @return     UTF-16 encoded string.
	 */
	[[nodiscard]]
	std::u16string toUtf16(std::string_view utf8);

	/**
	 * @brief      Encodes UTF-16 characters to UTF-16 characters. (Does nothing.)
	 *
	 * @param[in]  utf16  UTF-16 encoded string.
	 *
	 * @return     UTF-16 encoded string.
	 */
	[[nodiscard]]
	std::u16string toUtf16(std::u16string_view utf16);

	/**
	 * @brief      Encodes UTF-32 characters to UTF-16 characters.
	 *
	 * @param[in]  utf32  UTF-32 encoded string.
	 *
	 * @return     UTF-16 encoded string.
	 */
	[[nodiscard]]
	std::u16string toUtf16(std::u32string_view utf32);

	/**
	 * @brief      Encodes wide characters to UTF-16 characters.
	 *
	 * @param[in]  wide  Wide character string.
	 *
	 * @return     UTF-16 encoded string.
	 */
	[[nodiscard]]
	std::u16string toUtf16(std::wstring_view wide);

	/**
	 * @brief      Encodes UTF-8 characters to UTF-32 characters.
	 *
	 * @param[in]  utf8  UTF-8 encoded string.
	 *
	 * @return     UTF-32 encoded string.
	 */
	[[nodiscard]]
	std::u32string toUtf32(std::string_view utf8);

	/**
	 * @brief      Encodes UTF-16 characters to UTF-32 characters.
	 *
	 * @param[in]  utf16  UTF-16 encoded string.
	 *
	 * @return     UTF-32 encoded string.
	 */
	[[nodiscard]]
	std::u32string toUtf32(std::u16string_view utf16);

	/**
	 * @brief      Encodes UTF-32 characters to UTF-32 characters. (Does nothing.)
	 *
	 * @param[in]  utf32  UTF-32 encoded string.
	 *
	 * @return     UTF-32 encoded string.
	 */
	[[nodiscard]]
	std::u32string toUtf32(std::u32string_view utf32);

	/**
	 * @brief      Encodes wide characters to UTF-32 characters.
	 *
	 * @param[in]  wide  Wide character string.
	 *
	 * @return     UTF-32 encoded string.
	 */
	[[nodiscard]]
	std::u32string toUtf32(std::wstring_view wide);

	/**
	 * @brief      Encodes UTF-8 characters to wide characters.
	 *
	 * @param[in]  utf8  UTF-8 encoded string.
	 *
	 * @return     Wide character string.
	 */
	[[nodiscard]]
	std::wstring toWide(std::string_view utf8);

	/**
	 * @brief      Encodes UTF-16 characters to wide characters.
	 *
	 * @param[in]  utf16  UTF-16 encoded string.
	 *
	 * @return     Wide character string.
	 */
	[[nodiscard]]
	std::wstring toWide(std::u16string_view utf16);

	/**
	 * @brief      Encodes UTF-32 characters to wide characters.
	 *
	 * @param[in]  utf32  UTF-32 encoded string.
	 *
	 * @return     Wide character string.
	 */
	[[nodiscard]]
	std::wstring toWide(std::u32string_view utf32);

	/**
	 * @brief      Encodes wide characters to wide characters. (Does nothing.)
	 *
	 * @param[in]  wide  Wide character string.
	 *
	 * @return     Wide character string.
	 */
	[[nodiscard]]
	std::wstring toWide(std::wstring_view wide);
}

#endif  // #ifndef INCLUDE_NENE_ENCODING_HPP
