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

#include <memory>
#include "../Rectangle.hpp"
#include "../Event/IEventObserver.hpp"
#include "WindowEvent.hpp"

namespace Nene
{
	// Forward declarations.
	class IMonitor;
	class IWindow;

	/**
	 * @brief      Window event observer type.
	 */
	using WindowEventObserver = IEventObserver<IWindow&, WindowEvent>;

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
		 * @brief      Adds an window event observer.
		 *
		 * @param[in]  observer  The weak pointer of the observer.
		 *
		 * @return     `*this`.
		 *
		 * @see        `Nene::EventObservable::addObserver()`.
		 */
		virtual IWindow& addObserver(const std::shared_ptr<WindowEventObserver>& observer) =0;

		/**
		 * @brief      Removes an window event observer.
		 *
		 * @param[in]  observer  The observer to remove.
		 *
		 * @return     `*this`.
		 *
		 * @see        `Nene::EventObservable::removeObserver()`.
		 */
		virtual IWindow& removeObserver(const std::shared_ptr<WindowEventObserver>& observer) =0;

		/**
		 * @brief      Process the window message.
		 *
		 * @return     `*this`.
		 */
		virtual IWindow& update() =0;

		/**
		 * @brief      Determines if the close button has just been clicked.
		 *
		 * @return     `true` if the window is closing, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool isClosing() const =0;

		/**
		 * @brief      Returns the window caption.
		 *
		 * @return     The window caption.
		 */
		[[nodiscard]]
		virtual std::string title() const =0;

		/**
		 * @brief      Returns the coordinate of the window client area.
		 *
		 * @return     The coordinate of the window client area.
		 */
		[[nodiscard]]
		virtual Rectanglei area() const =0;

		/**
		 * @brief      Returns the width of the window client area.
		 *
		 * @return     The width of the window client area.
		 */
		[[nodiscard]]
		virtual Int32 width() const =0;

		/**
		 * @brief      Returns the height of the window client area.
		 *
		 * @return     The height of the window client area.
		 */
		[[nodiscard]]
		virtual Int32 height() const =0;

		/**
		 * @brief      Returns the size of the window client area.
		 *
		 * @return     The size of the window client area.
		 */
		[[nodiscard]]
		virtual Size2Di size() const =0;

		/**
		 * @brief      Returns the coordinate of the window.
		 *
		 * @return     The coordinate of the window.
		 */
		[[nodiscard]]
		virtual Rectanglei frame() const =0;

		/**
		 * @brief      Returns the window position.
		 *
		 * @return     The window position.
		 */
		[[nodiscard]]
		virtual Vector2Di position() const =0;

		/**
		 * @brief      Returns the width of the window.
		 *
		 * @return     The width of the window.
		 */
		[[nodiscard]]
		virtual Int32 frameWidth() const =0;

		/**
		 * @brief      Returns the height of the window.
		 *
		 * @return     The height of the window.
		 */
		[[nodiscard]]
		virtual Int32 frameHeight() const =0;

		/**
		 * @brief      Returns the size of the window.
		 *
		 * @return     The size of the window.
		 */
		[[nodiscard]]
		virtual Size2Di frameSize() const =0;

		/**
		 * @brief      Determines if the window has maximize box.
		 *
		 * @return     `true` if the window has maximize box, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool hasMaximizeBox() const =0;

		/**
		 * @brief      Determines if the window has minimize box.
		 *
		 * @return     `true` if the window has minimize box, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool hasMinimizeBox() const =0;

		/**
		 * @brief      Determines if the window is resizable.
		 *
		 * @return     `true` if the window is resizable, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool isResizable() const =0;

		/**
		 * @brief      Determines if the window is visible.
		 *
		 * @return     `true` if the window is visible, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool isShown() const =0;

		/**
		 * @brief      Determines if the window is not visible.
		 *
		 * @return     `true` if the window is hidden, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool isHidden() const =0;

		/**
		 * @brief      Determines if the window is active.
		 *
		 * @return     `true` if the window is active, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool isActive() const =0;

		/**
		 * @brief      Determines if the window is maximized.
		 *
		 * @return     `true` if the window is maximized, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool isMaximized() const =0;

		/**
		 * @brief      Determines if the window is minimized.
		 *
		 * @return     `true` if the window is minimized, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool isMinimized() const =0;

		/**
		 * @brief      Determines if the window is fullscreen.
		 *
		 * @return     `true` if the window is fullscreen, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool isFullscreen() const =0;

		/**
		 * @brief      Returns the monitor.
		 *
		 * @return     The monitor for the fullscreen.
		 */
		[[nodiscard]]
		virtual const IMonitor& monitor() const =0;

		/**
		 * @brief      Sets the window caption.
		 *
		 * @param[in]  newTitle  The new window caption.
		 *
		 * @return     `*this`.
		 */
		virtual IWindow& title(const std::string& newTitle) =0;

		/**
		 * @brief      Sets the maximize box enabled flag.
		 *
		 * @param[in]  enabled  The maximize box enabled.
		 *
		 * @return     `*this`.
		 */
		virtual IWindow& maximizeBox(bool enabled) =0;

		/**
		 * @brief      Sets the minimize box enabled flag.
		 *
		 * @param[in]  enabled  The minimize box enabled.
		 *
		 * @return     `*this`.
		 */
		virtual IWindow& minimizeBox(bool enabled) =0;

		/**
		 * @brief      Sets the window resizability.
		 *
		 * @param[in]  enabled  The window resizability.
		 *
		 * @return     `*this`.
		 */
		virtual IWindow& resizable(bool enabled) =0;

		/**
		 * @brief      Displays the window.
		 *
		 * @param[in]  visibility  The window visibility.
		 *
		 * @return     `*this`.
		 */
		virtual IWindow& show(bool visibility) =0;

		/**
		 * @brief      Activates the window.
		 *
		 * @param[in]  activity  `true` if activate.
		 *
		 * @return     `*this`.
		 */
		virtual IWindow& activate(bool activity) =0;

		/**
		 * @brief      Maximizes the window.
		 *
		 * @return     `*this`.
		 */
		virtual IWindow& maximize() =0;

		/**
		 * @brief      Minimizes the window.
		 *
		 * @return     `*this`.
		 */
		virtual IWindow& minimize() =0;

		/**
		 * @brief      Sets window fullscreen.
		 *
		 * @param[in]  fullscreen  `true` if the window makes fullscreen.
		 *
		 * @return     `*this`.
		 */
		virtual IWindow& setFullscreen(bool fullscreen) =0;

		/**
		 * @brief      Sets the monitor for the fullscreen window.
		 *
		 * @param      newMonitor  Monitor to set. primary monitor if `newMonitor` is `nullptr`.
		 *
		 * @return     `*this`.
		 */
		virtual IWindow& monitor(std::unique_ptr<IMonitor>&& newMonitor) =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_WINDOW_IWINDOW_HPP
