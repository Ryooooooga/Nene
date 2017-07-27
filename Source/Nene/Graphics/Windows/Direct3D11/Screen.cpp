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
#include "../../../Exceptions/Windows/DirectXException.hpp"
#include "../../../Window/Windows/Window.hpp"
#include "Screen.hpp"

namespace Nene::Windows::Direct3D11
{
	Screen::Screen(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const std::shared_ptr<Window>& window, const Size2Di& size)
		: swapChain_()
		, window_(window)
	{
		assert(device);
		assert(window);

		// Get DXGI factory.
		Microsoft::WRL::ComPtr<IDXGIDevice>  dxgiDevice;
		Microsoft::WRL::ComPtr<IDXGIAdapter> dxgiAdapter;
		Microsoft::WRL::ComPtr<IDXGIFactory> dxgiFactory;

		throwIfFailed(
			device->QueryInterface(dxgiDevice.GetAddressOf()),
			u8"Failed to aquire DXGI device.");

		throwIfFailed(
			dxgiDevice->GetAdapter(dxgiAdapter.GetAddressOf()),
			u8"Failed to aquire DXGI adapter.");

		throwIfFailed(
			dxgiAdapter->GetParent(IID_IDXGIFactory, reinterpret_cast<void**>(dxgiFactory.GetAddressOf())),
			u8"Failed to aquire DXGI factory.");

		// Create swap chain.
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

		throwIfFailed(
			dxgiFactory->CreateSwapChain(device.Get(), &desc, swapChain_.GetAddressOf()),
			u8"Failed to create swap chain.");

		// Disable ALT+Enter.
		dxgiFactory->MakeWindowAssociation(desc.OutputWindow, DXGI_MWA_NO_ALT_ENTER);

		// Get back buffer.
		Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;

		throwIfFailed(
			swapChain_->GetBuffer(0, IID_ID3D11Texture2D, reinterpret_cast<void**>(backBuffer.GetAddressOf())),
			u8"Failed to get back buffer texture.");
	}
}

#endif
