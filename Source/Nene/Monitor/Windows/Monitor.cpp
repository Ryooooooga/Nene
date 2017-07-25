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

#include "../../Encoding.hpp"
#include "../../Exceptions/Windows/WindowsApiException.hpp"
#include "Monitor.hpp"

namespace Nene::Windows
{
	BOOL CALLBACK Monitor::onEnumMonitor(HMONITOR hMonitor, [[maybe_unused]] HDC hDC, [[maybe_unused]] LPRECT lprcMonitor, LPARAM dwData)
	{
		MONITORINFOEXW info = {};
		info.cbSize = sizeof(info);

		if (::GetMonitorInfoW(hMonitor, &info))
		{
			auto monitor = std::make_unique<Monitor>(
				Encoding::toUtf8(info.szDevice),
				Rectanglei { info.rcMonitor.left, info.rcMonitor.top, info.rcMonitor.right, info.rcMonitor.bottom },
				!!(info.dwFlags & MONITORINFOF_PRIMARY));

			const auto monitors = reinterpret_cast<std::vector<std::unique_ptr<IMonitor>>*>(dwData);
			monitors->emplace_back(std::move(monitor));
		}

		return TRUE;
	}

	BOOL CALLBACK Monitor::onEnumMonitorPrimary(HMONITOR hMonitor, [[maybe_unused]] HDC hDC, [[maybe_unused]] LPRECT lprcMonitor, LPARAM dwData)
	{
		MONITORINFOEXW info = {};
		info.cbSize = sizeof(info);

		if (::GetMonitorInfoW(hMonitor, &info) && info.dwFlags & MONITORINFOF_PRIMARY)
		{
			auto monitor = std::make_unique<Monitor>(
				Encoding::toUtf8(info.szDevice),
				Rectanglei { info.rcMonitor.left, info.rcMonitor.top, info.rcMonitor.right, info.rcMonitor.bottom },
				!!(info.dwFlags & MONITORINFOF_PRIMARY));

			const auto primary = reinterpret_cast<std::unique_ptr<IMonitor>*>(dwData);
			*primary = std::move(monitor);

			return FALSE;
		}

		return TRUE;
	}

	std::vector<std::unique_ptr<IMonitor>> Monitor::enumerate()
	{
		std::vector<std::unique_ptr<IMonitor>> monitors;
		monitors.reserve(2);

		::EnumDisplayMonitors(
			nullptr,
			nullptr,
			onEnumMonitor,
			reinterpret_cast<LPARAM>(&monitors));

		return monitors;
	}

	std::unique_ptr<IMonitor> Monitor::primary()
	{
		std::unique_ptr<IMonitor> monitor;

		::EnumDisplayMonitors(
			nullptr,
			nullptr,
			onEnumMonitorPrimary,
			reinterpret_cast<LPARAM>(&monitor));

		if (!monitor)
		{
			throw WindowsApiException { ::GetLastError(), u8"Failed to get primary monitor information." };
		}

		return monitor;
	}
}

#endif
