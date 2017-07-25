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

#include <Windows.h>
#include "../../Encoding.hpp"
#include "../Monitor.hpp"

namespace Nene
{
	namespace
	{
		BOOL CALLBACK onEnumMonitor(HMONITOR hMonitor, [[maybe_unused]] HDC hDC, [[maybe_unused]] LPRECT lprcMonitor, LPARAM dwData)
		{
			const auto monitors = reinterpret_cast<std::vector<Monitor>*>(dwData);

			// Get monitor information.
			MONITORINFOEXW info = {};
			info.cbSize = sizeof(info);

			::GetMonitorInfoW(hMonitor, &info);

			monitors->emplace_back(
				Encoding::toUtf8(info.szDevice),
				Rectanglei
				{
					static_cast<Int32>(info.rcMonitor.left   ),
					static_cast<Int32>(info.rcMonitor.top    ),
					static_cast<Int32>(info.rcMonitor.right  ),
					static_cast<Int32>(info.rcMonitor.bottom ),
				},
				!!(info.dwFlags & MONITORINFOF_PRIMARY));

			return TRUE;
		}
	}

	std::vector<Monitor> Monitor::enumerate()
	{
		std::vector<Monitor> monitors;
		monitors.reserve(2);

		::EnumDisplayMonitors(
			nullptr,
			nullptr,
			onEnumMonitor,
			reinterpret_cast<LPARAM>(&monitors));

		return monitors;
	}
}

#endif
