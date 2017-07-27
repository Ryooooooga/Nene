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
	namespace
	{
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> createShaderResourceView(const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texture)
		{
			assert(texture);

			Microsoft::WRL::ComPtr<ID3D11Device> device;
			Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResource;

			D3D11_TEXTURE2D_DESC texDesc;
			texture->GetDesc(&texDesc);
			texture->GetDevice(device.GetAddressOf());

			D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
			srvDesc.Format                    = texDesc.Format;
			srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
			srvDesc.Texture2D.MostDetailedMip = texDesc.MipLevels - 1;
			srvDesc.Texture2D.MipLevels       = texDesc.MipLevels;


			throwIfFailed(
				device->CreateShaderResourceView(texture.Get(), &srvDesc, shaderResource.GetAddressOf()),
				u8"Failed to create Direct3D11 shader resource view from texture2D.");

			return shaderResource;
		}
	}

	Texture::Texture(const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texture)
		: texture_(texture)
		, shaderResource_()
		, size_()
	{
		assert(texture);

		// Get texture size.
		D3D11_TEXTURE2D_DESC texDesc;
		texture_->GetDesc(&texDesc);

		size_.width  = static_cast<Int32>(texDesc.Width);
		size_.width  = static_cast<Int32>(texDesc.Height);

		// Create shader resource view.
		shaderResource_ = createShaderResourceView(texture_);
	}

	Texture::Texture(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const Image& image, bool dynamic)
		: texture_()
		, shaderResource_()
		, size_(image.size())
	{
		assert(device);

		// Create texture.
		UINT bindFlags = 0;
		bindFlags |= D3D11_BIND_SHADER_RESOURCE;
		bindFlags |= dynamic ? D3D11_BIND_RENDER_TARGET : 0;

		D3D11_TEXTURE2D_DESC texDesc = {};
		texDesc.Width              = static_cast<UINT>(size_.width);
		texDesc.Height             = static_cast<UINT>(size_.height);
		texDesc.MipLevels          = 1;
		texDesc.ArraySize          = 1;
		texDesc.Format             = DXGI_FORMAT_R8G8B8A8_UNORM;
		texDesc.SampleDesc.Count   = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage              = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags          = bindFlags;
		texDesc.CPUAccessFlags     = 0;
		texDesc.MiscFlags          = 0;

		D3D11_SUBRESOURCE_DATA subresource = {};
		subresource.pSysMem          = image.dataPointer();
		subresource.SysMemPitch      = size_.width * sizeof(Color4);
		subresource.SysMemSlicePitch = 0;

		throwIfFailed(
			device->CreateTexture2D(&texDesc, &subresource, texture_.GetAddressOf()),
			u8"Failed to create Direct3D11 texture2D.");

		// Create shader resource view.
		shaderResource_ = createShaderResourceView(texture_);
	}
}

#endif
