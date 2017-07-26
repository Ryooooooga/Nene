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
		, className_()
		, handle_()
		, style_(WS_OVERLAPPEDWINDOW)
		, closing_(false)
	{
		assert(size.width  >= 0);
		assert(size.height >= 0);

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
		const auto monitor = Monitor::primary();

		RECT rect =
		{
			static_cast<LONG>(monitor->center().x - (size.width  + 1) / 2),
			static_cast<LONG>(monitor->center().y - (size.height + 1) / 2),
			static_cast<LONG>(monitor->center().x + (size.width  + 0) / 2),
			static_cast<LONG>(monitor->center().y + (size.height + 0) / 2),
		};

		::AdjustWindowRect(&rect, style_, FALSE);

		// Create window.
		handle_ = ::CreateWindowExW(
			0,
			wc.lpszClassName,
			Encoding::toWide(title).c_str(),
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

		::ShowWindow(handle_, SW_SHOWNORMAL);
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

	std::string Window::title() const
	{
		int size = ::GetWindowTextLengthW(handle_);
		std::vector<wchar_t> text(size + 1);

		::GetWindowTextW(handle_, text.data(), size + 1);

		return Encoding::toUtf8(std::wstring_view { text.data(), text.size() - 1 });
	}

	Window& Window::title(const std::string& newTitle)
	{
		::SetWindowTextW(handle_, Encoding::toWide(newTitle).c_str());

		return *this;
	}
}

#endif
