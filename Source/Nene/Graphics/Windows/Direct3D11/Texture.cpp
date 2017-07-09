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

#include "Texture.hpp"
#include "../../../Exceptions/Windows/DirectXException.hpp"

namespace Nene::Windows::Direct3D11
{
	namespace
	{
		// Converts pixel format to DXGI format.
		constexpr DXGI_FORMAT toDxgiFormat(PixelFormat format)
		{
			switch (format)
			{
				case PixelFormat::R8G8B8A8: return DXGI_FORMAT_R8G8B8A8_UNORM;

				default:
					assert(!"Unknown pixel format.");
					return DXGI_FORMAT_UNKNOWN;
			}
		}
	}

	Texture::Texture(const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texture)
		: device_()
		, texture_(texture)
		, shaderResource_()
		, size_()
	{
		assert(texture);

		HRESULT hr;

		// Get device.
		texture_->GetDevice(device_.GetAddressOf());

		// Get size.
		D3D11_TEXTURE2D_DESC texDesc;
		texture->GetDesc(&texDesc);

		size_.set(static_cast<Int32>(texDesc.Width), static_cast<Int32>(texDesc.Height));

		// Create shader resource view.
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format                    = srvDesc.Format;
		srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = texDesc.MipLevels - 1;
		srvDesc.Texture2D.MipLevels       = texDesc.MipLevels;

		hr = device_->CreateShaderResourceView(texture_.Get(), &srvDesc, shaderResource_.GetAddressOf());

		if (FAILED(hr))
		{
			throw DirectXException { hr, u8"Failed to create Direct3D11 shader resource view from texture2D." };
		}
	}

	Texture::Texture(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const Size2Di& size, PixelFormat format, bool dynamic)
		: device_(device)
		, texture_()
		, shaderResource_()
		, size_(size)
	{
		assert(device);

		HRESULT hr;

		// Create texture.
		D3D11_TEXTURE2D_DESC texDesc = {};
		texDesc.Width              = static_cast<UINT>(size_.width  );
		texDesc.Height             = static_cast<UINT>(size_.height );
		texDesc.MipLevels          = 1;
		texDesc.ArraySize          = 1;
		texDesc.Format             = toDxgiFormat(format);
		texDesc.SampleDesc.Count   = 1;
		texDesc.SampleDesc.Quality = 0;
		texDesc.Usage              = D3D11_USAGE_DEFAULT;
		texDesc.BindFlags          = (dynamic ? D3D11_BIND_RENDER_TARGET : 0) | D3D11_BIND_SHADER_RESOURCE;
		texDesc.CPUAccessFlags     = 0;
		texDesc.MiscFlags          = 0;

		hr = device_->CreateTexture2D(&texDesc, nullptr, texture_.GetAddressOf());

		if (FAILED(hr))
		{
			const auto message = fmt::format(
				u8"Failed to create Direct3D11 texture2D.\n"
				u8"Size: {}x{}\n"
				u8"Dynamic: {}",
				size.width,
				size.height,
				dynamic);

			throw DirectXException { hr, message };
		}

		// Create shader resource view.
		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc = {};
		srvDesc.Format                    = srvDesc.Format;
		srvDesc.ViewDimension             = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Texture2D.MostDetailedMip = texDesc.MipLevels - 1;
		srvDesc.Texture2D.MipLevels       = texDesc.MipLevels;

		hr = device_->CreateShaderResourceView(texture_.Get(), &srvDesc, shaderResource_.GetAddressOf());

		if (FAILED(hr))
		{
			throw DirectXException { hr, u8"Failed to create Direct3D11 shader resource view from texture2D." };
		}
	}

	const Size2Di& Texture::size() const noexcept
	{
		return size_;
	}

	const Microsoft::WRL::ComPtr<ID3D11Texture2D>& Texture::texture2D() const noexcept
	{
		return texture_;
	}

	const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& Texture::shaderResourceView() const noexcept
	{
		return shaderResource_;
	}
}

#endif
