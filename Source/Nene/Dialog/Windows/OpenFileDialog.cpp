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

#include <Windows.h>
#include <commdlg.h>
#include "../../Encoding.hpp"
#include "../../Window/Windows/Window.hpp"
#include "OpenFileDialog.hpp"

namespace Nene::Windows
{
	namespace
	{
		constexpr DWORD bufferSize = 4096;
	}

	std::vector<IFileDialog::path_type> OpenFileDialog::show(const std::shared_ptr<IWindow>& owner)
	{
		const auto owner_Windows = std::dynamic_pointer_cast<Window>(owner);
		const auto hWndOwner     = owner_Windows ? owner_Windows->handle() : nullptr;
		const auto title         = title_ ? std::make_optional(Encoding::toWide(*title_)) : std::nullopt;

		// Join filter.
		std::wstring filter;

		for (const auto& x : filters_)
		{
			filter += Encoding::toWide(x.description);
			filter += L'\0';
			filter += x.filter.native();
			filter += L'\0';
		}

		// Show dialog.
		std::wstring buffer = filename_.native();
		buffer.resize(bufferSize);

		UINT flags = 0;
		flags |= OFN_EXPLORER;
		flags |= OFN_NOCHANGEDIR;
		flags |= multiselect_ ? OFN_ALLOWMULTISELECT : 0;
		flags |= fileExists_  ? OFN_FILEMUSTEXIST    : 0;

		OPENFILENAMEW ofn = {};
		ofn.lStructSize     = sizeof(ofn);
		ofn.hwndOwner       = hWndOwner;
		ofn.hInstance       = nullptr;
		ofn.lpstrFilter     = filter.c_str();
		ofn.nFilterIndex    = static_cast<DWORD>(filterIndex_ + 1);
		ofn.lpstrFile       = buffer.data();
		ofn.nMaxFile        = bufferSize;
		ofn.lpstrInitialDir = directory_.c_str();
		ofn.lpstrTitle      = title ? title->c_str() : nullptr;
		ofn.Flags           = flags;

		if (!::GetOpenFileNameW(&ofn))
		{
			return {};
		}

		// Parse result.
		const auto dir = path_type { ofn.lpstrFile, ofn.lpstrFile + ofn.nFileOffset - 1 };

		std::vector<path_type> files;

		for (LPCWSTR p = ofn.lpstrFile + ofn.nFileOffset; *p; p += ::wcslen(p) + 1)
		{
			files.emplace_back(dir / p);
		}

		// Set state.
		directory_   = dir;
		filename_    = files.front().filename();
		filterIndex_ = ofn.nFilterIndex - 1;

		return files;
	}
}

#endif
