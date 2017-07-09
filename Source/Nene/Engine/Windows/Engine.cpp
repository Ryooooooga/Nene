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

#include "Engine.hpp"
#include "../../Graphics/Windows/Direct3D11/Graphics.hpp"
#include "../../Logger/FileLogger.hpp"
#include "../../Window/Windows/Window.hpp"

namespace Nene::Windows
{
	Engine::Engine()
		: logger_   ()
		, graphics_ ()
	{
		logger_   = std::make_shared<FileLogger>("log.txt");
		graphics_ = std::make_shared<Direct3D11::Graphics>();
	}

	const std::shared_ptr<Logger>& Engine::logger() const noexcept
	{
		return logger_;
	}

	const std::shared_ptr<IGraphics>& Engine::graphics() const noexcept
	{
		return graphics_;
	}

	std::shared_ptr<IWindow> Engine::window(const std::string& title, const Size2Di& size)
	{
		return std::make_shared<Window>(title, size);
	}
}

#endif
