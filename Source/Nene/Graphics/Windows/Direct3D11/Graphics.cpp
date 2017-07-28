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

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#if defined(NENE_COMPILER_MSVC)
#  pragma comment(lib, "dxgi.lib")
#  pragma comment(lib, "dxguid.lib")
#  pragma comment(lib, "d3d11.lib")
#  pragma comment(lib, "d3dcompiler.lib")
#endif

#include "../../../Exceptions/Windows/DirectXException.hpp"
#include "../../../Window/Windows/Window.hpp"
#include "Graphics.hpp"
#include "IndexBuffer.hpp"
#include "Screen.hpp"
#include "Texture.hpp"
#include "VertexBuffer.hpp"

namespace Nene::Windows::Direct3D11
{
	Graphics::Graphics()
		: device_()
		, immediateContext_()
		, driverType_(D3D_DRIVER_TYPE_UNKNOWN)
	{
		// Create device.
		UINT creationFlags = 0;
#if defined(NENE_DEBUG)
		creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

		constexpr D3D_DRIVER_TYPE driverTypes[] =
		{
			D3D_DRIVER_TYPE_HARDWARE,
			D3D_DRIVER_TYPE_WARP,
			D3D_DRIVER_TYPE_REFERENCE,
		};

		constexpr D3D_FEATURE_LEVEL featureLevels[] =
		{
			D3D_FEATURE_LEVEL_11_0,
			D3D_FEATURE_LEVEL_10_1,
			D3D_FEATURE_LEVEL_10_0,
		};

		HRESULT hr;

		for (const auto driverType : driverTypes)
		{
			D3D_FEATURE_LEVEL featureLevel;

			hr = ::D3D11CreateDevice(
				nullptr,
				driverType,
				nullptr,
				creationFlags,
				featureLevels,
				std::extent_v<decltype(featureLevels)>,
				D3D11_SDK_VERSION,
				device_.GetAddressOf(),
				&featureLevel,
				immediateContext_.GetAddressOf());

			if (SUCCEEDED(hr))
			{
				driverType_ = driverType;

				break;
			}
		}

		throwIfFailed(hr, u8"Failed to create Direct3D11 device.");
	}

	std::shared_ptr<IScreen> Graphics::screen(const std::shared_ptr<IWindow>& window)
	{
		assert(window);

		return screen(window, window->size());
	}

	std::shared_ptr<IScreen> Graphics::screen(const std::shared_ptr<IWindow>& window, const Size2Di& size)
	{
		assert(window);

		const auto window_Windows = std::dynamic_pointer_cast<Window>(window);

		return window_Windows
			? std::make_shared<Screen>(device_, window_Windows, size)
			: throw EngineException { u8"Window must be a Windows API window." };
	}

	std::shared_ptr<IVertexBuffer<Vertex2D>> Graphics::vertexBuffer2D(UInt32 capacity)
	{
		return std::make_shared<VertexBuffer<Vertex2D>>(device_, capacity);
	}

	std::shared_ptr<IIndexBuffer<UInt32>> Graphics::indexBuffer(UInt32 capacity)
	{
		return std::make_shared<IndexBuffer<UInt32>>(device_, capacity);
	}

	std::shared_ptr<ITexture> Graphics::texture(const Image& image)
	{
		return std::make_shared<Texture>(device_, image, false);
	}
}

#endif
