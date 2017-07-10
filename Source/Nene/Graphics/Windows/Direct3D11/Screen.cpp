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

#include <cassert>
#include "Screen.hpp"
#include "DynamicTexture.hpp"
#include "../../../Exceptions/Windows/DirectXException.hpp"
#include "../../../Window/Windows/Window.hpp"

namespace Nene::Windows::Direct3D11
{
	Screen::Screen(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const Microsoft::WRL::ComPtr<IDXGIAdapter>& adapter, const std::shared_ptr<Window>& window)
		: device_(device)
		, swapChain_()
		, window_(window)
		, texture_()
	{
		assert(device);
		assert(adapter);
		assert(window);

		HRESULT hr;

		// Get DXGI factory.
		Microsoft::WRL::ComPtr<IDXGIFactory> factory;

		hr = adapter->GetParent(
			__uuidof(IDXGIFactory),
			reinterpret_cast<void**>(factory.GetAddressOf()));

		if (FAILED(hr))
		{
			throw DirectXException { hr, u8"Failed to aquire DXGI factory." };
		}

		// Create swap chain.
		const auto size = window->clientSize().value();

		DXGI_SWAP_CHAIN_DESC desc = {};
		desc.BufferDesc.Width                   = static_cast<UINT>(size.width);
		desc.BufferDesc.Height                  = static_cast<UINT>(size.height);
		desc.BufferDesc.RefreshRate.Numerator   = 60;
		desc.BufferDesc.RefreshRate.Denominator = 1;
		desc.BufferDesc.Format                  = DXGI_FORMAT_R8G8B8A8_UNORM;
		desc.BufferDesc.ScanlineOrdering        = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		desc.BufferDesc.Scaling                 = DXGI_MODE_SCALING_CENTERED;
		desc.SampleDesc.Count                   = 1;
		desc.SampleDesc.Quality                 = 0;
		desc.BufferUsage                        = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
		desc.BufferCount                        = 1;
		desc.OutputWindow                       = window_->handle();
		desc.Windowed                           = TRUE;
		desc.SwapEffect                         = DXGI_SWAP_EFFECT_DISCARD;
		desc.Flags                              = 0;

		hr = factory->CreateSwapChain(
			device_.Get(),
			&desc,
			swapChain_.GetAddressOf());

		if (FAILED(hr))
		{
			throw DirectXException { hr, u8"Failed to create swap chain." };
		}

		// Get back buffer texture.
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;

		hr = swapChain_->GetBuffer(
			0,
			__uuidof(ID3D11Texture2D),
			reinterpret_cast<void**>(backBuffer.GetAddressOf()));

		if (FAILED(hr))
		{
			throw DirectXException { hr, u8"Failed to get back buffer texture." };
		}

		// Create render target.
		texture_ = std::make_shared<DynamicTexture>(backBuffer);
	}

	const Size2Di& Screen::size() const noexcept
	{
		return texture_->size();
	}
}

#endif
