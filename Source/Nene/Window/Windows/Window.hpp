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
		EventObservable<IWindow&, WindowEvent> event_;
		std::wstring className_;
		HWND  handle_;
		DWORD style_;
		bool  closing_;

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
		bool isClosing() const override;

		/**
		 * @see        `Nene::IWindow::title()`.
		 */
		std::string title() const override;

		/**
		 * @see        `Nene::IWindow::title()`.
		 */
		Window& title(const std::string& newTitle) override;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_WINDOW_WINDOWS_WINDOW_HPP
