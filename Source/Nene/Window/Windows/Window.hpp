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

#ifndef INCLUDE_NENE_WINDOW_WINDOWS_WINDOW_HPP
#define INCLUDE_NENE_WINDOW_WINDOWS_WINDOW_HPP

#include "../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include "../../Uncopyable.hpp"
#include "../../Event/EventObservable.hpp"
#include "../IWindow.hpp"

namespace Nene::Windows
{
	/**
	 * @brief      Windows API window implementation.
	 */
	class Window final
		: public  IWindow
		, private Uncopyable
	{
		enum State
		{
			normal, maximized, minimized,
		};

		EventObservable<IWindow&, WindowEvent> event_;
		std::unique_ptr<IMonitor> monitor_;
		std::wstring className_;
		std::string  title_;
		Rectanglei   frame_;
		Rectanglei   client_;
		Rectanglei   frameWindowed_;
		State        state_;
		HWND         handle_;
		DWORD        style_;
		DWORD        styleWindowed_;
		bool         hidden_;
		bool         fullscreen_;
		bool         closing_;

		// Window procedure.
		static LRESULT CALLBACK procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  title  The caption of the window.
		 * @param[in]  size   The window client area size.
		 */
		explicit Window(std::string_view title, const Size2Di& size);

		/**
		 * @brief      Destructor.
		 */
		~Window();

		/**
		 * @see        `Nene::IWindow::addObserver()`.
		 */
		Window& addObserver(const std::shared_ptr<WindowEventObserver>& observer) override;

		/**
		 * @see        `Nene::IWindow::removeObserver()`.
		 */
		Window& removeObserver(const std::shared_ptr<WindowEventObserver>& observer) override;

		/**
		 * @see        `Nene::IWindow::update()`.
		 */
		Window& update() override;

		/**
		 * @see        `Nene::IWindow::isClosing()`.
		 */
		[[nodiscard]]
		bool isClosing() const override;

		/**
		 * @see        `Nene::IWindow::title()`.
		 */
		[[nodiscard]]
		std::string title() const override;

		/**
		 * @see        `Nene::IWindow::area()`.
		 */
		[[nodiscard]]
		Rectanglei area() const override;

		/**
		 * @see        `Nene::IWindow::width()`.
		 */
		[[nodiscard]]
		Int32 width() const override;

		/**
		 * @see        `Nene::IWindow::height()`.
		 */
		[[nodiscard]]
		Int32 height() const override;

		/**
		 * @see        `Nene::IWindow::size()`.
		 */
		[[nodiscard]]
		Size2Di size() const override;

		/**
		 * @see        `Nene::IWindow::frame()`.
		 */
		[[nodiscard]]
		Rectanglei frame() const override;

		/**
		 * @see        `Nene::IWindow::position()`.
		 */
		[[nodiscard]]
		Vector2Di position() const override;

		/**
		 * @see        `Nene::IWindow::frameWidth()`.
		 */
		[[nodiscard]]
		Int32 frameWidth() const override;

		/**
		 * @see        `Nene::IWindow::frameHeight()`.
		 */
		[[nodiscard]]
		Int32 frameHeight() const override;

		/**
		 * @see        `Nene::IWindow::frameSize()`.
		 */
		[[nodiscard]]
		Size2Di frameSize() const override;

		/**
		 * @see        `Nene::IWindow::monitor()`.
		 */
		[[nodiscard]]
		const IMonitor& monitor() const override;

		/**
		 * @see        `Nene::IWindow::hasMaximizeBox()`.
		 */
		[[nodiscard]]
		bool hasMaximizeBox() const override;

		/**
		 * @see        `Nene::IWindow::hasMinimizeBox()`.
		 */
		[[nodiscard]]
		bool hasMinimizeBox() const override;

		/**
		 * @see        `Nene::IWindow::isResizable()`.
		 */
		[[nodiscard]]
		bool isResizable() const override;

		/**
		 * @see        `Nene::IWindow::isShown()`.
		 */
		[[nodiscard]]
		bool isShown() const override;

		/**
		 * @see        `Nene::IWindow::isHidden()`.
		 */
		[[nodiscard]]
		bool isHidden() const override;

		/**
		 * @see        `Nene::IWindow::isActive()`.
		 */
		[[nodiscard]]
		bool isActive() const override;

		/**
		 * @see        `Nene::IWindow::isMaximized()`.
		 */
		[[nodiscard]]
		bool isMaximized() const override;

		/**
		 * @see        `Nene::IWindow::isMinimized()`.
		 */
		[[nodiscard]]
		bool isMinimized() const override;

		/**
		 * @see        `Nene::IWindow::isFullscreen()`.
		 */
		[[nodiscard]]
		bool isFullscreen() const override;

		/**
		 * @see        `Nene::IWindow::title()`.
		 */
		Window& title(const std::string& newTitle) override;

		/**
		 * @see        `Nene::IWindow::maximizeBox()`.
		 */
		Window& maximizeBox(bool enabled) override;

		/**
		 * @see        `Nene::IWindow::minimizeBox()`.
		 */
		Window& minimizeBox(bool enabled) override;

		/**
		 * @see        `Nene::IWindow::resizable()`.
		 */
		Window& resizable(bool enabled) override;

		/**
		 * @see        `Nene::IWindow::show()`.
		 */
		Window& show(bool visibility) override;

		/**
		 * @see        `Nene::IWindow::activate()`.
		 */
		Window& activate(bool activity) override;

		/**
		 * @see        `Nene::IWindow::maximize()`.
		 */
		Window& maximize() override;

		/**
		 * @see        `Nene::IWindow::minimize()`.
		 */
		Window& minimize() override;

		/**
		 * @see        `Nene::IWindow::setFullscreen()`.
		 */
		Window& setFullscreen(bool fullscreen) override;

		/**
		 * @see        `Nene::IWindow::monitor()`.
		 */
		Window& monitor(std::unique_ptr<IMonitor>&& newMonitor) override;

		/**
		 * @brief      Returns the window handle.
		 *
		 * @return     The window handle.
		 */
		[[nodiscard]]
		HWND handle() const noexcept;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_WINDOW_WINDOWS_WINDOW_HPP
