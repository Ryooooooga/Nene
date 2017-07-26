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

#ifndef INCLUDE_NENE_MONITOR_WINDOWS_MONITOR_HPP
#define INCLUDE_NENE_MONITOR_WINDOWS_MONITOR_HPP

#include "../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <memory>
#include <vector>
#include <Windows.h>
#include "../../Uncopyable.hpp"
#include "../IMonitor.hpp"

namespace Nene::Windows
{
	/**
	 * @brief      Windows monitor implementation.
	 */
	class Monitor final
		: public  IMonitor
		, private Uncopyable
	{
		std::string device_;
		Rectanglei  area_;
		bool        primary_;

		static BOOL CALLBACK onEnumMonitor(HMONITOR hMonitor, HDC hDC, LPRECT lprcMonitor, LPARAM dwData);
		static BOOL CALLBACK onEnumMonitorPrimary(HMONITOR hMonitor, HDC hDC, LPRECT lprcMonitor, LPARAM dwData);

	public:
		/**
		 * @see        `Nene::Monitors::enumerate()`.
		 */
		static std::vector<std::unique_ptr<IMonitor>> enumerate();

		/**
		 * @see        `Nene::Monitors::primary()`.
		 */
		static std::unique_ptr<IMonitor> primary();

		/**
		 * @brief      Constructor
		 *
		 * @param      device   The monitor device name.
		 * @param[in]  area     The monitor coordinate.
		 * @param[in]  primary  Indicates the monitor is primary.
		 */
		explicit Monitor(std::string&& device, const Rectanglei& area, bool primary) noexcept
			: device_(std::move(device)), area_(area), primary_(primary) {}

		/**
		 * @brief      Destructor.
		 */
		~Monitor() =default;

		/**
		 * @see        `Nene::IMonitor::device()`.
		 */
		[[nodiscard]]
		std::string device() const noexcept override
		{
			return device_;
		}

		/**
		 * @see        `Nene::IMonitor::area()`.
		 */
		[[nodiscard]]
		Rectanglei area() const noexcept override
		{
			return area_;
		}

		/**
		 * @see        `Nene::IMonitor::position()`.
		 */
		[[nodiscard]]
		Vector2Di position() const noexcept override
		{
			return area_.position;
		}

		/**
		 * @see        `Nene::IMonitor::center()`.
		 */
		[[nodiscard]]
		Vector2Di center() const noexcept override
		{
			return area_.center();
		}

		/**
		 * @see        `Nene::IMonitor::width()`.
		 */
		[[nodiscard]]
		Int32 width() const noexcept override
		{
			return area_.width();
		}

		/**
		 * @see        `Nene::IMonitor::height()`.
		 */
		[[nodiscard]]
		Int32 height() const noexcept override
		{
			return area_.height();
		}

		/**
		 * @see        `Nene::IMonitor::size()`.
		 */
		[[nodiscard]]
		Size2Di size() const noexcept override
		{
			return area_.size;
		}

		/**
		 * @see        `Nene::IMonitor::isPrimary()`.
		 */
		[[nodiscard]]
		bool isPrimary() const noexcept override
		{
			return primary_;
		}
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_MONITOR_WINDOWS_MONITOR_HPP
