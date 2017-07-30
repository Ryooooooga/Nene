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

#ifndef INCLUDE_COM_WINDOWS_COMMANAGER_HPP
#define INCLUDE_COM_WINDOWS_COMMANAGER_HPP

#include "../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <wrl/client.h>
#include "../../Exceptions/Windows/WindowsApiException.hpp"
#include "../../Uncopyable.hpp"

namespace Nene::Windows
{
	/**
	 * @brief      Windows COM manager.
	 */
	class ComManager final
		: private Uncopyable
	{
		explicit ComManager();

	public:
		/**
		 * @brief      Destructor.
		 */
		~ComManager();

		/**
		 * @brief      Creates the single instance.
		 *
		 * @return     Singleton instance.
		 */
		static ComManager& create();

		/**
		 * @brief      Destroys the single instance.
		 */
		static void destroy();

		/**
		 * @brief      Returns the single instance.
		 *
		 * @return     Singleton instance.
		 */
		[[nodiscard]]
		static ComManager& instance();

		/**
		 * @brief      Creates the COM object instance.
		 *
		 * @param[in]  classId  Target class id.
		 *
		 * @tparam     T        Interface type to create.
		 *
		 * @return     COM object.
		 */
		template <typename T>
		[[nodiscard]]
		Microsoft::WRL::ComPtr<T> createInstance(REFCLSID classId)
		{
			Microsoft::WRL::ComPtr<T> x;

			const HRESULT hr = ::CoCreateInstance(
				classId, nullptr, CLSCTX_ALL, __uuidof(T), reinterpret_cast<void**>(x.GetAddressOf()));

			if (FAILED(hr))
			{
				throw WindowsApiException { static_cast<DWORD>(hr), u8"Failed to create COM instance." };
			}

			return x;
		}
	};
}

#endif

#endif  // #ifndef INCLUDE_COM_WINDOWS_COMMANAGER_HPP
