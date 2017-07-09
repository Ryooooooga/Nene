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

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "dxgi.lib")

#include "Graphics.hpp"
#include "Monitor.hpp"
#include "../../../Exceptions/Windows/DirectXException.hpp"

namespace Nene::Windows::Direct3D11
{
	Graphics::Graphics()
		: device_()
		, immediateContext_()
		, adapter_()
		, factory_()
		, driverType_()
		, featureLevel_()
	{
		// Create device.
		UINT creationFlags = 0;
#ifdef NENE_DEBUG
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

		for (const auto& driverType : driverTypes)
		{
			hr = ::D3D11CreateDevice(
				nullptr,
				driverType,
				nullptr,
				creationFlags,
				featureLevels,
				std::extent_v<decltype(featureLevels)>,
				D3D11_SDK_VERSION,
				device_.GetAddressOf(),
				&featureLevel_,
				immediateContext_.GetAddressOf());

			if (SUCCEEDED(hr))
			{
				driverType_ = driverType;
				break;
			}
		}

		if (FAILED(hr))
		{
			throw DirectXException { hr, u8"Failed to create Direct3D11 device." };
		}

		// Get DXGI device.
		Microsoft::WRL::ComPtr<IDXGIDevice> dxgiDevice;
		
		hr = device_->QueryInterface(dxgiDevice.GetAddressOf());

		if (FAILED(hr))
		{
			throw DirectXException { hr, u8"Failed to aquire DXGI device." };
		}

		// Get DXGI adapter.
		hr = dxgiDevice->GetAdapter(adapter_.GetAddressOf());

		if (FAILED(hr))
		{
			throw DirectXException { hr, u8"Failed to aquire DXGI adapter." };
		}

		// Get DXGI factory.
		hr = adapter_->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(factory_.GetAddressOf()));

		if (FAILED(hr))
		{
			throw DirectXException { hr, u8"Failed to aquire DXGI factory." };
		}
	}

	std::vector<std::shared_ptr<IMonitor>> Graphics::monitors() const
	{
		std::vector<std::shared_ptr<IMonitor>> monitors;
		Microsoft::WRL::ComPtr<IDXGIOutput> output;

		for (UINT i = 0; SUCCEEDED(adapter_->EnumOutputs(i, output.ReleaseAndGetAddressOf())); i++)
		{
			monitors.emplace_back(std::make_shared<Monitor>(output));
		}

		return monitors;
	}
}

#endif
