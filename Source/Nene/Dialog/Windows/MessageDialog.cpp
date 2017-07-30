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

#include "../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <cassert>
#include <Windows.h>
#include "../../Encoding.hpp"
#include "../../Window/Windows/Window.hpp"
#include "MessageDialog.hpp"

namespace Nene::Windows
{
	IMessageDialog::Button MessageDialog::show(const std::shared_ptr<const IWindow>& owner) const
	{
		const auto owner_Windows = std::dynamic_pointer_cast<const Windows::Window>(owner);
		const HWND hWndOwner     = owner_Windows ? owner_Windows->handle() : nullptr;

		UINT uType = 0;

		switch (type_)
		{
		case Type::ok:
			uType |= MB_OK;
			break;

		case Type::okCancel:
			uType |= MB_OKCANCEL;
			break;

		case Type::yesNo:
			uType |= MB_YESNO;
			break;

		case Type::yesNoCancel:
			uType |= MB_YESNOCANCEL;
			break;

		default:
			assert(!"Unknown dialog type");
			break;
		}

		switch (icon_)
		{
		case Icon::normal:
			uType |= 0;
			break;

		case Icon::info:
			uType |= MB_ICONINFORMATION;
			break;

		case Icon::question:
			uType |= MB_ICONQUESTION;
			break;

		case Icon::warning:
			uType |= MB_ICONWARNING;
			break;

		case Icon::error:
			uType |= MB_ICONERROR;
			break;

		default:
			assert(!"Unknown dialog icon");
			break;
		}

		const auto button = ::MessageBoxW(
			hWndOwner,
			Encoding::toWide(message_).c_str(),
			Encoding::toWide(title_).c_str(),
			uType);

		switch (button)
		{
		case IDOK:
			return Button::ok;

		case IDCANCEL:
			return Button::cancel;

		case IDYES:
			return Button::yes;

		case IDNO:
			return Button::no;

		default:
			return Button::none;
		}
	}
}

#endif
