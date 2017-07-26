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
#include "MessageDialog.hpp"

namespace Nene::Windows
{
	namespace
	{
		MessageDialogButton showDialog(std::string_view title, std::string_view message, MessageDialogType type, MessageDialogIcon icon, const std::shared_ptr<const IWindow>& parent)
		{
			// TODO: owner window.
			//const auto owner = std::dynamic_pointer_cast<const Windows::Window>(parent);
			//const HWND hWnd  = owner ? owner->handle() : nullptr;
			const HWND hWnd  = nullptr;

			UINT uType = 0;

			switch (type)
			{
				case MessageDialogType::ok:
					uType |= MB_OK;
					break;

				case MessageDialogType::okCancel:
					uType |= MB_OKCANCEL;
					break;

				case MessageDialogType::yesNo:
					uType |= MB_YESNO;
					break;

				case MessageDialogType::yesNoCancel:
					uType |= MB_YESNOCANCEL;
					break;

				default:
					assert(!"Unknown dialog type");
					break;
			}

			switch (icon)
			{
				case MessageDialogIcon::normal:
					uType |= 0;
					break;

				case MessageDialogIcon::info:
					uType |= MB_ICONINFORMATION;
					break;

				case MessageDialogIcon::question:
					uType |= MB_ICONQUESTION;
					break;

				case MessageDialogIcon::warning:
					uType |= MB_ICONWARNING;
					break;

				case MessageDialogIcon::error:
					uType |= MB_ICONERROR;
					break;

				default:
					assert(!"Unknown dialog icon");
					break;
			}

			const auto button = ::MessageBoxW(
				hWnd,
				Encoding::toWide(message).c_str(),
				Encoding::toWide(title).c_str(),
				uType);

			switch (button)
			{
				case IDOK:
					return MessageDialogButton::ok;

				case IDCANCEL:
					return MessageDialogButton::cancel;

				case IDYES:
					return MessageDialogButton::yes;

				case IDNO:
					return MessageDialogButton::no;

				default:
					return MessageDialogButton::none;
			}
		}
	}

	MessageDialogButton MessageDialog::show(const std::shared_ptr<const IWindow>& parent) const
	{
		return showDialog(title_, message_, type_, icon_, parent);
	}

	std::future<MessageDialogButton> MessageDialog::showAsync(const std::shared_ptr<const IWindow>& parent) const
	{
		return std::async(showDialog, title_, message_, type_, icon_, parent);
	}
}

#endif
