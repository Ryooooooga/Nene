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

#ifndef INCLUDE_NENE_MONITOR_MONITOR_HPP
#define INCLUDE_NENE_MONITOR_MONITOR_HPP

#include <vector>
#include <string>
#include "../Rectangle.hpp"
#include "../Uncopyable.hpp"

namespace Nene
{
	/**
	 * @brief      Monitor information.
	 */
	class Monitor final
	{
		std::string device_;
		Rectanglei  area_;
		bool        primary_;

	public:

		/**
		 * @brief      Enumerates monitors.
		 *
		 * @return     List of monitors.
		 */
		static std::vector<Monitor> enumerate();

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  device     The device name.
		 * @param[in]  area       The monitor coordinate.
		 * @param[in]  isPrimary  Indicates if the monitor is primary.
		 */
		explicit Monitor(const std::string& device, const Rectanglei& area, bool isPrimary) noexcept
			: device_(std::move(device)), area_(area), primary_(isPrimary) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  device     The device name.
		 * @param[in]  area       The monitor coordinate.
		 * @param[in]  isPrimary  Indicates if the monitor is primary.
		 */
		explicit Monitor(std::string&& device, const Rectanglei& area, bool isPrimary) noexcept
			: device_(std::move(device)), area_(area), primary_(isPrimary) {}

		/**
		 * @brief      Copy constructor.
		 */
		Monitor(const Monitor&) =delete;

		/**
		 * @brief      Move constructor.
		 */
		Monitor(Monitor&&) =default;

		/**
		 * @brief      Copy operator `=`.
		 */
		Monitor& operator=(const Monitor&) =delete;

		/**
		 * @brief      Move operator `=`.
		 */
		Monitor& operator=(Monitor&&) =default;

		/**
		 * @brief      Destructor.
		 */
		~Monitor() =default;

		/**
		 * @brief      Returns the device name of the monitor being used.
		 *
		 * @return     The device name of the monitor being used.
		 */
		[[nodiscard]]
		const std::string& device() const noexcept
		{
			return device_;
		}

		/**
		 * @brief      Returns the screen area.
		 *
		 * @return     The screen area.
		 */
		[[nodiscard]]
		const Rectanglei& area() const noexcept
		{
			return area_;
		}

		/**
		 * @brief      Returns the top left coordinate of the monitor.
		 *
		 * @return     The top left coordiante.
		 */
		[[nodiscard]]
		const Vector2Di& position() const noexcept
		{
			return area_.position;
		}

		/**
		 * @brief      Returns the size of the monitor.
		 *
		 * @return     The size of the monitor.
		 */
		[[nodiscard]]
		const Size2Di& size() const noexcept
		{
			return area_.size;
		}

		/**
		 * @brief      Determines if the monitor is the primary monitor.
		 *
		 * @return     `true` if the primary monitor, `false` otherwise.
		 */
		[[nodiscard]]
		bool isPrimary() const noexcept
		{
			return primary_;
		}
	};
}

#endif  // #ifndef INCLUDE_NENE_MONITOR_MONITOR_HPP
