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
#include "Texture.hpp"

namespace Nene::Windows::Direct3D11
{
	Texture::Texture(const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texture)
		: texture_(texture)
		, shaderResource_()
	{
		assert(texture);

		// Get texture size.
		D3D11_TEXTURE2D_DESC texDesc;
		texture_->GetDesc(&texDesc);

		size_.width  = static_cast<Int32>(texDesc.Width);
		size_.width  = static_cast<Int32>(texDesc.Height);

		// Create shader resource view.
		Microsoft::WRL::ComPtr<ID3D11Device> device;
		texture_->GetDevice(device.GetAddressOf());

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format                    = texDesc.Format;
		srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = texDesc.MipLevels - 1;
		srvDesc.Texture2D.MipLevels       = texDesc.MipLevels;

		throwIfFailed(
			device->CreateShaderResourceView(texture_.Get(), &srvDesc, shaderResource_.GetAddressOf()),
			u8"Failed to create Direct3D11 shader resource view from texture2D.");
	}
}

#endif
