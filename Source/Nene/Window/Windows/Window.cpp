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
#include "../../Monitor.hpp"
#include "../../Scope.hpp"
#include "../../Exceptions/Windows/WindowsApiException.hpp"
#include "Window.hpp"

namespace Nene::Windows
{
	namespace
	{
		thread_local std::exception_ptr exception;

		Rectanglei frameRect(HWND hWnd)
		{
			RECT rect = {};
			::GetWindowRect(hWnd, &rect);

			return
			{
				static_cast<Int32>(rect.left   ),
				static_cast<Int32>(rect.top    ),
				static_cast<Int32>(rect.right  ),
				static_cast<Int32>(rect.bottom ),
			};
		}

		Rectanglei clientRect(HWND hWnd)
		{
			POINT pos = { 0, 0 };
			RECT rect = {};
			::ClientToScreen(hWnd, &pos);
			::GetClientRect(hWnd, &rect);

			return
			{
				{
					static_cast<Int32>(pos.x),
					static_cast<Int32>(pos.y),
				},
				{
					static_cast<Int32>(rect.right),
					static_cast<Int32>(rect.bottom),
				},
			};
		}
	}

	LRESULT CALLBACK Window::procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	try
	{
		// Get instance pointer from the window handle.
		const auto self = reinterpret_cast<Window*>(::GetWindowLongPtrW(hWnd, GWLP_USERDATA));

		switch (msg)
		{
			case WM_CREATE:
			{
				const auto param  = reinterpret_cast<LPCREATESTRUCTW>(lParam);
				const auto window = static_cast<Window*>(param->lpCreateParams);

				::SetWindowLongPtrW(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(window));

				return 0;
			}

			case WM_DESTROY:
			{
				return 0;
			}

			case WM_CLOSE:
			{
				if (self)
				{
					self->closing_ = true;

					self->event_.notify(*self, WindowEvent::closing);
				}

				return 0;
			}

			case WM_PAINT:
			{
				PAINTSTRUCT ps;
				::BeginPaint(hWnd, &ps);
				::EndPaint(hWnd, &ps);

				return 0;
			}

			case WM_SIZE:
			{
				if (self)
				{
					if (wParam == SIZE_RESTORED)
					{
						self->frame_  = frameRect(hWnd);
						self->client_ = clientRect(hWnd);
						self->state_  = State::normal;

						self->event_.notify(*self, WindowEvent::sized);
					}
					else if (wParam == SIZE_MINIMIZED)
					{
						self->state_ = State::minimized;

						self->event_.notify(*self, WindowEvent::minimized);
					}
					else if (wParam == SIZE_MAXIMIZED)
					{
						self->frame_  = frameRect(hWnd);
						self->client_ = clientRect(hWnd);
						self->state_  = State::maximized;

						self->event_.notify(*self, WindowEvent::sized);
						self->event_.notify(*self, WindowEvent::maximized);
					}

				}

				return 0;
			}

			case WM_SHOWWINDOW:
			{
				if (self)
				{
					self->hidden_ = !wParam;
				}

				return 0;
			}

			case WM_STYLECHANGED:
			{
				if (self)
				{
					self->style_ = reinterpret_cast<const STYLESTRUCT*>(lParam)->styleNew;
				}

				return 0;
			}

			case WM_MOVE:
			{
				if (self)
				{
					const Int16 x = static_cast<Int16>(LOWORD(lParam));

					if (x > -32000)
					{
						// Not minimized.
						self->frame_  = frameRect(hWnd);
						self->client_ = clientRect(hWnd);
						self->event_.notify(*self, WindowEvent::moved);
					}
				}

				return 0;
			}

			case WM_SETTEXT:
			{
				self->title_ = Encoding::toUtf8(reinterpret_cast<LPCWSTR>(lParam));

				break;
			}
		}

		return ::DefWindowProcW(hWnd, msg, wParam, lParam);
	}
	catch (...)
	{
		exception = std::current_exception();

		return 0;
	}

	Window::Window(std::string_view title, const Size2Di& size)
		: event_()
		, monitor_()
		, className_()
		, title_(title)
		, client_()
		, frame_()
		, frameWindowed_()
		, handle_()
		, style_(WS_OVERLAPPEDWINDOW)
		, styleWindowed_()
		, state_(State::normal)
		, hidden_(true)
		, fullscreen_(false)
		, closing_(false)
	{
		assert(size.width  >= 0);
		assert(size.height >= 0);

		// Get primary monitor.
		monitor_ = Monitor::primary();

		// Register class.
		className_ = fmt::format(L"Nene:{}", static_cast<const void*>(this));

		WNDCLASSEXW wc;
		wc.cbSize        = sizeof(wc);
		wc.style         = CS_HREDRAW | CS_VREDRAW;
		wc.lpfnWndProc   = procedure;
		wc.cbClsExtra    = 0;
		wc.cbWndExtra    = 0;
		wc.hInstance     = ::GetModuleHandleW(nullptr);
		wc.hIcon         = ::LoadIconW(nullptr, IDI_APPLICATION);
		wc.hCursor       = ::LoadCursorW(nullptr, IDC_ARROW);
		wc.hbrBackground = static_cast<HBRUSH>(::GetStockObject(WHITE_BRUSH));
		wc.lpszMenuName  = nullptr;
		wc.lpszClassName = className_.c_str();
		wc.hIconSm       = ::LoadIconW(nullptr, IDI_APPLICATION);

		if (!::RegisterClassExW(&wc))
		{
			throw WindowsApiException { ::GetLastError(), u8"Failed to register window class." };
		}

		[[maybe_unused]] const auto _ = scopeFailure([&]()
		{
			// Unregister class on error.
			::UnregisterClassW(wc.lpszClassName, wc.hInstance);
		});

		// Compute window size.
		RECT rect =
		{
			static_cast<LONG>(monitor_->center().x - (size.width  + 1) / 2),
			static_cast<LONG>(monitor_->center().y - (size.height + 1) / 2),
			static_cast<LONG>(monitor_->center().x + (size.width  + 0) / 2),
			static_cast<LONG>(monitor_->center().y + (size.height + 0) / 2),
		};

		::AdjustWindowRect(&rect, style_, FALSE);

		// Create window.
		handle_ = ::CreateWindowExW(
			0,
			wc.lpszClassName,
			Encoding::toWide(title_).c_str(),
			style_,
			rect.left,
			rect.top,
			rect.right - rect.left,
			rect.bottom - rect.top,
			nullptr,
			nullptr,
			wc.hInstance,
			this);

		if (!handle_)
		{
			throw WindowsApiException { ::GetLastError(), u8"Faild to create window." };
		}

		frame_  = frameRect(handle_);
		client_ = clientRect(handle_);

		activate(true);
	}

	Window::~Window()
	{
		if (handle_)
		{
			::DestroyWindow(std::exchange(handle_, nullptr));
		}

		if (!className_.empty())
		{
			::UnregisterClassW(className_.c_str(), ::GetModuleHandleW(nullptr));
		}
	}

	Window& Window::addObserver(const std::shared_ptr<WindowEventObserver>& observer)
	{
		event_.addObserver(observer);

		return *this;
	}

	Window& Window::removeObserver(const std::shared_ptr<WindowEventObserver>& observer)
	{
		event_.removeObserver(observer);

		return *this;
	}

	Window& Window::update()
	{
		closing_ = false;

		MSG msg;

		while (::PeekMessageW(&msg, handle_, 0, 0, PM_REMOVE))
		{
			::TranslateMessage(&msg);
			::DispatchMessageW(&msg);

			if (exception)
			{
				std::rethrow_exception(std::exchange(exception, nullptr));
			}
		}

		return *this;
	}

	bool Window::isClosing() const
	{
		return closing_;
	}

	Rectanglei Window::area() const
	{
		return client_;
	}

	Vector2Di Window::position() const
	{
		return client_.position;
	}

	Int32 Window::width() const
	{
		return client_.width();
	}

	Int32 Window::height() const
	{
		return client_.height();
	}

	Size2Di Window::size() const
	{
		return client_.size;
	}

	Rectanglei Window::frame() const
	{
		return frame_;
	}

	Vector2Di Window::framePosition() const
	{
		return frame_.position;
	}

	Int32 Window::frameWidth() const
	{
		return frame_.width();
	}

	Int32 Window::frameHeight() const
	{
		return frame_.height();
	}

	Size2Di Window::frameSize() const
	{
		return frame_.size;
	}

	bool Window::hasMaximizeBox() const
	{
		return !!((fullscreen_ ? styleWindowed_ : style_) & WS_MAXIMIZEBOX);
	}

	bool Window::hasMinimizeBox() const
	{
		return !!((fullscreen_ ? styleWindowed_ : style_) & WS_MINIMIZEBOX);
	}

	bool Window::isResizable() const
	{
		return !!((fullscreen_ ? styleWindowed_ : style_) & WS_THICKFRAME);
	}

	bool Window::isShown() const
	{
		return !isHidden();
	}

	bool Window::isHidden() const
	{
		return hidden_;
	}

	bool Window::isActive() const
	{
		return handle_ == ::GetActiveWindow();
	}

	bool Window::isMaximized() const
	{
		return state_ == State::maximized;
	}

	bool Window::isMinimized() const
	{
		return state_ == State::minimized;
	}

	std::string Window::title() const
	{
		return title_;
	}

	bool Window::isFullscreen() const
	{
		return fullscreen_;
	}

	const IMonitor& Window::monitor() const
	{
		return *monitor_;
	}

	Window& Window::title(const std::string& newTitle)
	{
		::SetWindowTextW(handle_, Encoding::toWide(newTitle).c_str());

		return *this;
	}

	Window& Window::area(const Rectanglei& newClientArea)
	{
		RECT rect =
		{
			static_cast<LONG>(newClientArea.position.x),
			static_cast<LONG>(newClientArea.position.y),
			static_cast<LONG>(newClientArea.size.width),
			static_cast<LONG>(newClientArea.size.height),
		};

		if (fullscreen_)
		{
			::AdjustWindowRect(&rect, styleWindowed_, false);

			frameWindowed_.position.x  = static_cast<Int32>(rect.left);
			frameWindowed_.position.y  = static_cast<Int32>(rect.top);
			frameWindowed_.size.width  = static_cast<Int32>(rect.right - rect.left);
			frameWindowed_.size.height = static_cast<Int32>(rect.bottom - rect.top);
		}
		else
		{
			::AdjustWindowRect(&rect, style_, false);

			::SetWindowPos(
				handle_,
				nullptr,
				rect.left,
				rect.top,
				rect.right - rect.left,
				rect.bottom - rect.top,
				SWP_NOACTIVATE | SWP_NOZORDER);
		}

		return *this;
	}

	Window& Window::size(const Size2Di& newSize)
	{
		RECT rect =
		{
			0,
			0,
			static_cast<LONG>(newSize.width),
			static_cast<LONG>(newSize.height),
		};

		if (fullscreen_)
		{
			::AdjustWindowRect(&rect, styleWindowed_, false);

			frameWindowed_.size.width  = static_cast<Int32>(rect.right - rect.left);
			frameWindowed_.size.height = static_cast<Int32>(rect.bottom - rect.top);
		}
		else
		{
			::AdjustWindowRect(&rect, style_, false);

			::SetWindowPos(
				handle_,
				nullptr,
				0,
				0,
				rect.right - rect.left,
				rect.bottom - rect.top,
				SWP_NOACTIVATE | SWP_NOMOVE | SWP_NOZORDER);
		}

		return *this;
	}

	Window& Window::maximizeBox(bool enabled)
	{
		if (fullscreen_)
		{
			styleWindowed_ &= ~WS_MAXIMIZEBOX;
			styleWindowed_ |= enabled ? WS_MAXIMIZEBOX : 0;

			return *this;
		}

		if (hasMaximizeBox() != enabled)
		{
			UINT flags = 0;
			flags |= SWP_NOMOVE;
			flags |= SWP_NOSIZE;
			flags |= SWP_NOACTIVATE;
			flags |= SWP_NOZORDER;
			flags |= SWP_FRAMECHANGED;
			flags |= isShown() ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;

			::SetWindowLongPtrW(handle_, GWL_STYLE, style_ ^ WS_MAXIMIZEBOX);
			::SetWindowPos(handle_, nullptr, 0, 0, 0, 0,  flags);
		}

		return *this;
	}

	Window& Window::minimizeBox(bool enabled)
	{
		if (fullscreen_)
		{
			styleWindowed_ &= ~WS_MINIMIZEBOX;
			styleWindowed_ |= enabled ? WS_MINIMIZEBOX : 0;

			return *this;
		}

		if (hasMinimizeBox() != enabled)
		{
			UINT flags = 0;
			flags |= SWP_NOMOVE;
			flags |= SWP_NOSIZE;
			flags |= SWP_NOACTIVATE;
			flags |= SWP_NOZORDER;
			flags |= SWP_FRAMECHANGED;
			flags |= isShown() ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;

			::SetWindowLongPtrW(handle_, GWL_STYLE, style_ ^ WS_MINIMIZEBOX);
			::SetWindowPos(handle_, nullptr, 0, 0, 0, 0,  flags);
		}

		return *this;
	}

	Window& Window::resizable(bool enabled)
	{
		if (fullscreen_)
		{
			styleWindowed_ &= ~WS_THICKFRAME;
			styleWindowed_ |= enabled ? WS_THICKFRAME : 0;

			return *this;
		}

		if (isResizable() != enabled)
		{
			UINT flags = 0;
			flags |= SWP_NOMOVE;
			flags |= SWP_NOSIZE;
			flags |= SWP_NOACTIVATE;
			flags |= SWP_NOZORDER;
			flags |= SWP_FRAMECHANGED;
			flags |= isShown() ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;

			::SetWindowLongPtrW(handle_, GWL_STYLE, style_ ^ WS_THICKFRAME);
			::SetWindowPos(handle_, nullptr, 0, 0, 0, 0,  flags);
		}

		return *this;
	}

	Window& Window::show(bool visibility)
	{
		if (visibility == isShown())
		{
			return *this;
		}

		if (visibility)
		{
			// Show window.
			if (fullscreen_)
			{
				::ShowWindow(handle_, SW_SHOWNA);

				return *this;
			}

			switch (state_)
			{
				case State::normal:
					::ShowWindow(handle_, SW_SHOWNA);
					break;

				case State::maximized:
					::ShowWindow(handle_, SW_SHOWNA);
					::ShowWindow(handle_, SW_MAXIMIZE);
					break;

				case State::minimized:
					::ShowWindow(handle_, SW_SHOWNA);
					::ShowWindow(handle_, SW_MINIMIZE);
					break;
			}
		}
		else
		{
			// Hide window.
			::ShowWindow(handle_, SW_HIDE);
		}

		return *this;
	}

	Window& Window::activate(bool activity)
	{
		::SetActiveWindow(activity ? handle_ : nullptr);

		return *this;
	}

	Window& Window::maximize()
	{
		if (state_ == State::maximized)
		{
			return *this;
		}

		if (!hidden_)
		{
			::ShowWindow(handle_, SW_MAXIMIZE);
		}
		else
		{
			state_ = State::maximized;
		}

		return *this;
	}

	Window& Window::minimize()
	{
		if (state_ == State::minimized)
		{
			return *this;
		}

		if (!hidden_)
		{
			::ShowWindow(handle_, SW_MINIMIZE);
		}
		else
		{
			state_ = State::minimized;
		}

		return *this;
	}

	Window& Window::setFullscreen(bool fullscreen)
	{
		if (fullscreen_ == fullscreen)
		{
			return *this;
		}

		if (fullscreen)
		{
			fullscreen_ = true;

			// Save window state.
			frameWindowed_ = frame_;
			styleWindowed_ = style_;

			UINT flags = 0;
			flags |= SWP_FRAMECHANGED;
			flags |= isShown() ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;

			::SetWindowLongPtrW(handle_, GWL_STYLE, WS_OVERLAPPED);
			::SetWindowPos(handle_, HWND_TOP, monitor_->position().x, monitor_->position().y, monitor_->width(), monitor_->height(), flags);
		}
		else
		{
			fullscreen_ = false;

			// Restore window state.
			UINT flags = 0;
			flags |= SWP_FRAMECHANGED;
			flags |= isShown() ? SWP_SHOWWINDOW : SWP_HIDEWINDOW;

			::SetWindowLongPtrW(handle_, GWL_STYLE, styleWindowed_);
			::SetWindowPos(handle_, HWND_TOP, frameWindowed_.position.x, frameWindowed_.position.y, frameWindowed_.width(), frameWindowed_.height(), flags);
		}

		return *this;
	}

	Window& Window::monitor(std::unique_ptr<IMonitor>&& monitor)
	{
		monitor_ = monitor ? std::move(monitor) : Monitor::primary();

		return *this;
	}

	HWND Window::handle() const noexcept
	{
		return handle_;
	}
}

#endif
