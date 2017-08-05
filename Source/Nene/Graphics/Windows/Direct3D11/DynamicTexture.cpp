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

#include "../../../Exceptions/Windows/DirectXException.hpp"
#include "DynamicTexture.hpp"
#include "Texture.hpp"

namespace Nene::Windows::Direct3D11
{
	namespace
	{
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> createRenderTargetView(const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texture)
		{
			D3D11_TEXTURE2D_DESC texDesc;
			texture->GetDesc(&texDesc);

			D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
			rtvDesc.Format             = texDesc.Format;
			rtvDesc.ViewDimension      = D3D11_RTV_DIMENSION_TEXTURE2D;
			rtvDesc.Texture2D.MipSlice = 0;

			Microsoft::WRL::ComPtr<ID3D11Device> device;
			texture->GetDevice(device.GetAddressOf());

			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget;

			throwIfFailed(
				device->CreateRenderTargetView(texture.Get(), &rtvDesc, renderTarget.GetAddressOf()),
				u8"Failed to create Direct3D11 render target view from a dynamic texture");

			return renderTarget;
		}
	}

	DynamicTexture::DynamicTexture(const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texture)
		: TextureBase(texture)
		, renderTarget_(createRenderTargetView(texture2D())) {}

	DynamicTexture::DynamicTexture(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const Size2Di& size)
		: TextureBase(device, size, true)
		, renderTarget_(createRenderTargetView(texture2D())) {}

	DynamicTexture::DynamicTexture(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const Image& image)
		: TextureBase(device, image, true)
		, renderTarget_(createRenderTargetView(texture2D())) {}
}

#endif
