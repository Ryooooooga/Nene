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

#ifndef INCLUDE_NENE_EXCEPTIONS_WINDOWS_DIRECTXEXCEPTION_HPP
#define INCLUDE_NENE_EXCEPTIONS_WINDOWS_DIRECTXEXCEPTION_HPP

#include "../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include <functional>
#include "WindowsApiException.hpp"

namespace Nene::Windows
{
	/**
	 * @brief      Exception for signaling DirectX errors.
	 */
	class DirectXException
		: public WindowsApiException
	{
	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  errorCode  Error code.
		 * @param[in]  message    Error message.
		 */
		explicit DirectXException(HRESULT errorCode, std::string_view message)
			: WindowsApiException(static_cast<DWORD>(errorCode), message) {}

		/**
		 * @brief      Destructor.
		 */
		virtual ~DirectXException() =default;
	};

	/**
	 * @brief      Throws error when the given code represents error.
	 *
	 * @param[in]  result        The result code.
	 * @param[in]  errorMessage  The error message or generator function.
	 */
	inline void throwIfFailed(HRESULT result, std::string_view errorMessage)
	{
		if (FAILED(result))
		{
			throw DirectXException { result, errorMessage };
		}
	}

	inline void throwIfFailed(HRESULT result, const std::function<std::string()>& errorMessage)
	{
		if (FAILED(result))
		{
			throw DirectXException { result, errorMessage() };
		}
	}
}

#endif

#endif  // #ifndef INCLUDE_NENE_EXCEPTIONS_WINDOWS_DIRECTXEXCEPTION_HPP

