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

#include <Windows.h>
#include "../../Uncopyable.hpp"
#include "../IWindow.hpp"

namespace Nene::Windows
{
	/**
	 * @brief      Windows API window implementation.
	 */
	class Window
		: public  IWindow
		, private Uncopyable
	{
		enum class State
		{
			shown,
			hidden,
			maximized,
			minimized,
			destroyed,
		};

		HWND         handle_;
		State        state_;
		std::wstring className_;
		std::string  title_;
		Size2Di      client_;

		static LRESULT CALLBACK procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  title  The title of the window.
		 * @param[in]  size   The client area size of the window.
		 */
		explicit Window(const std::string& title, const Size2Di& size);

		/**
		 * @brief      Destructor.
		 */
		virtual ~Window();

		/**
		 * @see        `Nene::IWindow::destroy()`.
		 */
		void destroy() override;

		/**
		 * @see        `Nene::IWindow::show()`.
		 */
		bool show() override;

		/**
		 * @see        `Nene::IWindow::hide()`.
		 */
		bool hide() override;

		/**
		 * @see        `Nene::IWindow::minimize()`.
		 */
		bool minimize() override;

		/**
		 * @see        `Nene::IWindow::maximize()`.
		 */
		bool maximize() override;

		/**
		 * @see        `Nene::IWindow::title()`.
		 */
		bool title(const std::string& newTitle) override;

		/**
		 * @see        `Nene::IWindow::update()`.
		 */
		bool update() override;

		/**
		 * @see        `Nene::IWindow::isAlive()`.
		 */
		bool isAlive() const noexcept override;

		/**
		 * @see        `Nene::IWindow::isDestroyed()`.
		 */
		bool isDestroyed() const noexcept override;

		/**
		 * @see        `Nene::IWindow::isShown()`.
		 */
		std::optional<bool> isShown() const noexcept override;

		/**
		 * @see        `Nene::IWindow::isHidden()`.
		 */
		std::optional<bool> isHidden() const noexcept override;

		/**
		 * @see        `Nene::IWindow::isMinimized()`.
		 */
		std::optional<bool> isMinimized() const noexcept override;

		/**
		 * @see        `Nene::IWindow::isMaximized()`.
		 */
		std::optional<bool> isMaximized() const noexcept override;

		/**
		 * @see        `Nene::IWindow::title()`.
		 */
		std::optional<std::string> title() const noexcept override;

		/**
		 * @see        `Nene::IWindow::position()`.
		 */
		std::optional<Vector2Di> position() const noexcept override;

		/**
		 * @see        `Nene::IWindow::size()`.
		 */
		std::optional<Size2Di> size() const noexcept override;

		/**
		 * @see        `Nene::IWindow::frame()`.
		 */
		std::optional<Rectanglei> frame() const noexcept override;

		/**
		 * @see        `Nene::IWindow::clientSize()`.
		 */
		std::optional<Size2Di> clientSize() const noexcept override;

		/**
		 * @brief      Returns the Windows API handle of the window.
		 *
		 * @return     The window handle if the window is alive, `nullptr`
		 *             otherwise.
		 */
		HWND handle() const noexcept;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_WINDOW_WINDOWS_WINDOW_HPP
