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

#ifndef INCLUDE_NENE_WINDOW_IWINDOW_HPP
#define INCLUDE_NENE_WINDOW_IWINDOW_HPP

#include <optional>
#include <string>
#include "../Rectangle.hpp"

namespace Nene
{
	/**
	 * @brief      Window interface.
	 */
	class IWindow
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		IWindow() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IWindow() =default;

		/**
		 * @brief      Destroys the window.
		 */
		virtual void destroy() =0;

		/**
		 * @brief      Displays the window.
		 *
		 * @return     `true` if the window has successfully shown, `false`
		 *             otherwise.
		 */
		virtual bool show() =0;

		/**
		 * @brief      Hides the window.
		 *
		 * @return     `true` if the window has successfully hidden, `false`
		 *             otherwise.
		 */
		virtual bool hide() =0;

		/**
		 * @brief      Minimizes the window.
		 *
		 * @return     `true` if the window has successfully minimized, `false`
		 *             otherwise.
		 */
		virtual bool minimize() =0;

		/**
		 * @brief      Maximizes the window.
		 *
		 * @return     `true` if the window has successfully maximized, `false`
		 *             otherwise.
		 */
		virtual bool maximize() =0;

		/**
		 * @brief      Sets the title of the window.
		 *
		 * @param[in]  newTitle  The new window title.
		 *
		 * @return     `true` if set the window title successfully, `false`
		 *             otherwise.
		 */
		virtual bool title(const std::string& newTitle) =0;

		/**
		 * @brief      Processes the window messages.
		 *
		 * @return     `false` if the window has destroyed, `true` otherwise.
		 */
		virtual bool update() =0;

		/**
		 * @brief      Determins if the window is alive.
		 *
		 * @return     `true` if the window is alive, `false` otherwise.
		 */
		virtual bool isAlive() const noexcept =0;

		/**
		 * @brief      Determins if the window has been destoryed.
		 *
		 * @return     `true` if the window has already been destroyed, `false`
		 *             otherwise.
		 */
		virtual bool isDestroyed() const noexcept =0;

		/**
		 * @brief      Determins if the window has been shown.
		 *
		 * @return     `true` if the window is shown, `false` if not shown,
		 *             `nullopt` otherwise.
		 */
		virtual std::optional<bool> isShown() const noexcept =0;

		/**
		 * @brief      Determins if the window has been hidden.
		 *
		 * @return     `true` if the window is hidden, `false` if not hidden,
		 *             `nullopt` otherwise.
		 */
		virtual std::optional<bool> isHidden() const noexcept =0;

		/**
		 * @brief      Determins if the window has been minimized.
		 *
		 * @return     `true` if the window is minimized, `false` if not
		 *             minimized, `nullopt` otherwise.
		 */
		virtual std::optional<bool> isMinimized() const noexcept =0;

		/**
		 * @brief      Determins if the window has been maximized.
		 *
		 * @return     `true` if the window is maximized, `false` if not
		 *             maximized, `nullopt` otherwise.
		 */
		virtual std::optional<bool> isMaximized() const noexcept =0;

		/**
		 * @brief      Returns the title of the window.
		 *
		 * @return     The title of the window if succeeded, `nullopt`
		 *             otherwise.
		 */
		virtual std::optional<std::string> title() const noexcept =0;

		/**
		 * @brief      Returns the position of the window.
		 *
		 * @return     The position if succeeded, `nullopt` otherwise.
		 */
		virtual std::optional<Vector2Di> position() const noexcept =0;

		/**
		 * @brief      Returns the size of the window.
		 *
		 * @return     The size if succeeded, `nullopt` otherwise.
		 */
		virtual std::optional<Size2Di> size() const noexcept =0;

		/**
		 * @brief      Returns the frame coordinate of the window.
		 *
		 * @return     The frame coordinate if succeeded, `nullopt` otherwise.
		 */
		virtual std::optional<Rectanglei> frame() const noexcept =0;

		/**
		 * @brief      Returns the client area size of the window.
		 *
		 * @return     The client area size if succeeded, `nullopt`
		 *             otherwise.
		 */
		virtual std::optional<Size2Di> clientSize() const noexcept =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_WINDOW_IWINDOW_HPP
