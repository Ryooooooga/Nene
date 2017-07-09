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

#include "DynamicTexture.hpp"
#include "Texture.hpp"
#include "../../../Exceptions/Windows/DirectXException.hpp"

namespace Nene::Windows::Direct3D11
{
	DynamicTexture::DynamicTexture(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const Size2Di& size, PixelFormat format)
		: texture_()
		, renderTarget_()
	{
		assert(device);

		// Create texture.
		texture_ = std::make_unique<Texture>(device, size, format, true);

		// Create render target view.
		D3D11_TEXTURE2D_DESC texDesc;
		texture_->texture2D()->GetDesc(&texDesc);

		D3D11_RENDER_TARGET_VIEW_DESC rtvDesc = {};
		rtvDesc.Format = texDesc.Format;
		rtvDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2D;
		rtvDesc.Texture2D.MipSlice = 0;

		HRESULT hr = device->CreateRenderTargetView(
			texture_->texture2D().Get(),
			&rtvDesc,
			renderTarget_.GetAddressOf());

		if (FAILED(hr))
		{
			const auto message = fmt::format(
				u8"Failed to create Direct3D11 render target view from dynamic texture.\n"
				u8"Size: {}x{}\n",
				size.width,
				size.height);
			
			throw DirectXException { hr, message };
		}
	}

	DynamicTexture::~DynamicTexture() =default;

	const Size2Di& DynamicTexture::size() const noexcept
	{
		return texture_->size();
	}
}

#endif
