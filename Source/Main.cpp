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

#include "Nene/Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <crtdbg.h>
#include <Windows.h>
#include "Nene/Console.hpp"
#include "Nene/Pallet.hpp"
#include "Nene/Dialog/MessageDialog.hpp"
#include "Nene/Window/Windows/Window.hpp"
#include "Nene/Graphics/IContext.hpp"
#include "Nene/Graphics/IScreen.hpp"
#include "Nene/Graphics/Windows/Direct3D11/Graphics.hpp"

#include "Nene/File.hpp"

int WINAPI wWinMain([[maybe_unused]] HINSTANCE hInstance, [[maybe_unused]] HINSTANCE hPrevInstance, [[maybe_unused]] LPWSTR lpCmdLine, [[maybe_unused]] int nCmdShow)
{
#ifdef NENE_DEBUG
	::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	try
	{
		using namespace Nene;
		using namespace Nene::Windows;

		Console::show();

		auto window1      = std::make_shared<Window>(u8"ねねっち", Size2Di {640, 480});
		auto window2      = std::make_shared<Window>(u8"あおっち", Size2Di {640, 480});
		auto graphics     = std::make_unique<Direct3D11::Graphics>();
		auto context      = graphics->context();
		auto screen1      = graphics->screen(window1);
		auto screen2      = graphics->screen(window2);
		auto path         = std::experimental::filesystem::u8path(u8"Assets/Shaders/Shader2D.hlsl");
		auto source       = File::read(path);
		auto vertexShader = graphics->vertexShader(path.u8string(), source, u8"VS_shape");
		auto pixelShader  = graphics->pixelShader(path.u8string(), source, u8"PS_shape");

		window1->show(true);
		window2->show(true);

		Vertex2D v[3] =
		{
			{ {0.f, 0.f}, 0xffff0000, {0.f, 0.f} },
			{ {1.f, 0.f}, 0xff00ff00, {0.f, 0.f} },
			{ {0.f, 1.f}, 0xff0000ff, {0.f, 0.f} },
		};

		UInt32 i[3] =
		{
			0, 2, 1
		};

		context->viewport({ 0.f, 0.f, 320.f, 480.f });

		while (!window1->update().isClosing() && !window2->update().isClosing())
		{
			context->renderTarget(screen1->renderTarget());
			context->clear(0xffff0000);

			context->vertexShader(vertexShader);
			context->pixelShader(pixelShader);

			context->draw(v, i);

			context->present(screen1);

			context->renderTarget(screen2->renderTarget());
			context->clear(0xff0000ff);

			context->vertexShader(vertexShader);
			context->pixelShader(pixelShader);

			context->draw(v, i);

			context->present(screen2);
		}
		
		return 0;
	}
	catch (const std::exception& e)
	{
		Nene::messageDialog(typeid(e).name(), e.what())
			->icon(Nene::MessageDialogIcon::error)
			.show();

		return -1;
	}
}

#endif
