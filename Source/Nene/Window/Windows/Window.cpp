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

#include <fmt/ostream.h>
#include "../../Encoding.hpp"
#include "../../Exceptions/Windows/WindowsApiException.hpp"
#include "Window.hpp"

namespace Nene::Windows
{
	namespace
	{
		thread_local std::exception_ptr exception;
	}

	LRESULT CALLBACK Window::procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		const auto self = reinterpret_cast<Window*>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA));

		switch (msg)
		{
			case WM_CREATE:
			{
				const auto self = reinterpret_cast<LPCREATESTRUCTW>(lParam)->lpCreateParams;
				::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(self));

				return 0;
			}

			case WM_DESTROY:
			{
				if (self)
				{
					self->destroy();
				}
				
				return 0;
			}

			case WM_CLOSE:
			{
				if (self)
				{
					self->destroy();
				}

				return 0;
			}

			case WM_SETTEXT:
			{
				if (self)
				{
					const auto title = reinterpret_cast<const wchar_t*>(lParam);

					self->title_ = Encoding::toUtf8(title);
				}

				break;
			}

			case WM_SIZE:
			{
				if (self)
				{
					switch (wParam)
					{
						case SIZE_RESTORED:
						{
							const auto width  = static_cast<std::int32_t>((wParam >>  0) & 0xffff);
							const auto height = static_cast<std::int32_t>((wParam >> 16) & 0xffff);

							self->state_ = State::shown;
							self->client_.set(width, height);
							break;
						}

						case SIZE_MINIMIZED:
						{
							self->state_ = State::minimized;
							break;
						}

						case SIZE_MAXIMIZED:
						{
							self->state_ = State::maximized;
							break;
						}
					}

					break;
				}

				case WM_SHOWWINDOW:
				{
					if (self)
					{
						self->state_ = wParam ? State::shown : State::hidden;
					}

					break;
				}
			}
		}

		return ::DefWindowProcW(hWnd, msg, wParam, lParam);
	}

	Window::Window(const std::string& title, const Size2Di& size)
		: handle_    (nullptr)
		, state_     (State::hidden)
		, className_ ()
		, title_     (title)
		, client_    (size)
	{
		const auto wtitle = Encoding::toWide(title_);

		// Register window class.
		className_ = fmt::format(L"Nene:%08p:%s", static_cast<void*>(this), wtitle);

		::WNDCLASSEXW wc;
		wc.cbSize        = sizeof(wc);
		wc.style         = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc   = procedure;
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.hInstance     = ::GetModuleHandleW(nullptr);
		wc.hIcon         = nullptr;
		wc.hCursor       = ::LoadCursorW(nullptr, IDC_ARROW);
		wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
		wc.lpszMenuName  = nullptr;
		wc.lpszClassName = className_.c_str();
		wc.hIconSm       = nullptr;

		if (!::RegisterClassExW(&wc))
		{
			const auto errorCode = ::GetLastError();
			const auto message   = u8"Failed to register window class.";

			throw WindowsApiException { errorCode, message };
		}

		// Calculate window size.
		const DWORD style = WS_OVERLAPPEDWINDOW;
		
		::RECT rect = { 0, 0, static_cast<LONG>(size.width), static_cast<LONG>(size.height) };
		::AdjustWindowRectEx(&rect, style, FALSE, 0);

		// Create window.
		handle_ = ::CreateWindowExW(
			0,
			wc.lpszClassName,
			wtitle.c_str(),
			style,
			0,
			0,
			rect.right  - rect.left,
			rect.bottom - rect.top,
			nullptr,
			nullptr,
			wc.hInstance,
			this);

		if (!handle_)
		{
			const auto errorCode = ::GetLastError();
			const auto message   = u8"Failed to create window.";

			::UnregisterClassW(wc.lpszClassName, wc.hInstance);

			throw WindowsApiException { errorCode, message };
		}
	}

	Window::~Window()
	{
		destroy();
	}

	void Window::destroy()
	{
		state_ = State::destroyed;

		// Clear-and-minimize idiom.
		std::string {}.swap(title_);
		
		if (handle_)
		{
			::DestroyWindow(handle_);
			handle_ = nullptr;
		}

		if (!className_.empty())
		{
			::UnregisterClassW(className_.c_str(), ::GetModuleHandleW(nullptr));
			
			// Clear-and-minimize idiom.
			std::wstring {}.swap(className_);
		}
	}

	bool Window::show()
	{
		if (isDestroyed())
		{
			return false;
		}

		::ShowWindow(handle_, SW_SHOWNORMAL);

		return true;
	}

	bool Window::hide()
	{
		if (isDestroyed())
		{
			return false;
		}

		::ShowWindow(handle_, SW_HIDE);

		return true;
	}

	bool Window::minimize()
	{
		if (isDestroyed())
		{
			return false;
		}

		::ShowWindow(handle_, SW_MINIMIZE);

		return true;
	}

	bool Window::maximize()
	{
		if (isDestroyed())
		{
			return false;
		}

		::ShowWindow(handle_, SW_MAXIMIZE);

		return true;
	}

	bool Window::title(const std::string& newTitle)
	{
		if (isDestroyed())
		{
			return false;
		}

		title_ = newTitle;
		::SetWindowTextW(handle_, Encoding::toWide(title_).c_str());

		return true;
	}

	bool Window::update()
	{
		if (isDestroyed())
		{
			return false;
		}

		// Process message.
		::MSG msg;

		while (isAlive() && ::PeekMessageW(&msg, handle_, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessageW(&msg);

			if (exception)
			{
				auto ex = exception;
				exception = nullptr;

				std::rethrow_exception(ex);
			}
		}

		return isAlive();
	}

	bool Window::isAlive() const noexcept
	{
		return !isDestroyed();
	}

	bool Window::isDestroyed() const noexcept
	{
		return state_ == State::destroyed;
	}

	std::optional<bool> Window::isShown() const noexcept
	{
		if (state_ == State::destroyed)
		{
			return std::nullopt;
		}

		return state_ == State::shown;
	}

	std::optional<bool> Window::isHidden() const noexcept
	{
		if (state_ == State::destroyed)
		{
			return std::nullopt;
		}

		return state_ == State::hidden;
	}

	std::optional<bool> Window::isMinimized() const noexcept
	{
		if (state_ == State::destroyed)
		{
			return std::nullopt;
		}

		return state_ == State::minimized;
	}

	std::optional<bool> Window::isMaximized() const noexcept
	{
		if (state_ == State::destroyed)
		{
			return std::nullopt;
		}

		return state_ == State::maximized;
	}

	std::optional<std::string> Window::title() const noexcept
	{
		if (state_ == State::destroyed)
		{
			return std::nullopt;
		}

		return title_;
	}

	std::optional<Vector2Di> Window::position() const noexcept
	{
		if (state_ == State::destroyed || state_ == State::minimized)
		{
			return std::nullopt;
		}

		::RECT rect;
		::GetWindowRect(handle_, &rect);

		return Vector2Di
		{
			static_cast<std::int32_t>(rect.left ),
			static_cast<std::int32_t>(rect.top  ),
		};
	}

	std::optional<Size2Di> Window::size() const noexcept
	{
		if (state_ == State::destroyed || state_ == State::minimized)
		{
			return std::nullopt;
		}

		::RECT rect;
		::GetWindowRect(handle_, &rect);

		return Size2Di
		{
			static_cast<std::int32_t>(rect.left - rect.right  ),
			static_cast<std::int32_t>(rect.top  - rect.bottom ),
		};
	}

	std::optional<Rectanglei> Window::frame() const noexcept
	{
		if (state_ == State::destroyed || state_ == State::minimized)
		{
			return std::nullopt;
		}

		::RECT rect;
		::GetWindowRect(handle_, &rect);

		return Rectanglei
		{
			static_cast<std::int32_t>(rect.left   ),
			static_cast<std::int32_t>(rect.top    ),
			static_cast<std::int32_t>(rect.right  ),
			static_cast<std::int32_t>(rect.bottom ),
		};
	}

	std::optional<Size2Di> Window::clientSize() const noexcept
	{
		if (state_ == State::destroyed)
		{
			return std::nullopt;
		}

		return client_;
	}

	HWND Window::handle() const noexcept
	{
		return handle_;
	}
}

#endif
