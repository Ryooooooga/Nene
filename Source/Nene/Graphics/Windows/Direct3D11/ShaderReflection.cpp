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

#include <vector>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include "ShaderReflection.hpp"
#include "../../../Exceptions/Windows/DirectXException.hpp"

namespace Nene::Windows::Direct3D11::Shader
{
	namespace
	{
		DXGI_FORMAT dxgiFormat(D3D_REGISTER_COMPONENT_TYPE componentType, BYTE mask)
		{
			if (mask == 1)
			{
				// x
				switch (componentType)
				{
					case D3D_REGISTER_COMPONENT_UINT32: return DXGI_FORMAT_R32_UINT;
					case D3D_REGISTER_COMPONENT_SINT32: return DXGI_FORMAT_R32_SINT;
					case D3D_REGISTER_COMPONENT_FLOAT32: return DXGI_FORMAT_R32_FLOAT;
				}
			}
			if (mask <= 3)
			{
				// xy
				switch (componentType)
				{
					case D3D_REGISTER_COMPONENT_UINT32: return DXGI_FORMAT_R32G32_UINT;
					case D3D_REGISTER_COMPONENT_SINT32: return DXGI_FORMAT_R32G32_SINT;
					case D3D_REGISTER_COMPONENT_FLOAT32: return DXGI_FORMAT_R32G32_FLOAT;
				}
			}
			if (mask <= 7)
			{
				// xyz
				switch (componentType)
				{
					case D3D_REGISTER_COMPONENT_UINT32: return DXGI_FORMAT_R32G32B32_UINT;
					case D3D_REGISTER_COMPONENT_SINT32: return DXGI_FORMAT_R32G32B32_SINT;
					case D3D_REGISTER_COMPONENT_FLOAT32: return DXGI_FORMAT_R32G32B32_FLOAT;
				}
			}
			if (mask <= 15)
			{
				// xyzw
				switch (componentType)
				{
					case D3D_REGISTER_COMPONENT_UINT32: return DXGI_FORMAT_R32G32B32A32_UINT;
					case D3D_REGISTER_COMPONENT_SINT32: return DXGI_FORMAT_R32G32B32A32_SINT;
					case D3D_REGISTER_COMPONENT_FLOAT32: return DXGI_FORMAT_R32G32B32A32_FLOAT;
				}
			}

			return DXGI_FORMAT_UNKNOWN;
		}
	}

	Microsoft::WRL::ComPtr<ID3D11InputLayout> createInputLayout(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const std::string& name, ByteArrayView binary)
	{
		HRESULT hr;

		// Create shader reflection.
		Microsoft::WRL::ComPtr<ID3D11ShaderReflection> reflection;

		hr = ::D3DReflect(
			binary.data(),
			binary.size(),
			IID_ID3D11ShaderReflection,
			reinterpret_cast<void**>(reflection.GetAddressOf()));

		if (FAILED(hr))
		{
			const auto message = fmt::format(
				u8"Failed to create shader reflection.\n"
				u8"Name: {}",
				name);

			throw DirectXException { hr, message };
		}

		// Get shader description.
		D3D11_SHADER_DESC shaderDesc;
		hr = reflection->GetDesc(&shaderDesc);

		if (FAILED(hr))
		{
			const auto message = fmt::format(
				u8"Failed to get shader reflection description.\n"
				u8"Name: {}",
				name);

			throw DirectXException { hr, message };
		}

		// Get input layout elements.
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputElements(shaderDesc.InputParameters);

		for (UINT i = 0; i < shaderDesc.InputParameters; i++)
		{
			// Get input parameter description.
			D3D11_SIGNATURE_PARAMETER_DESC paramDesc;
			hr = reflection->GetInputParameterDesc(i, &paramDesc);

			if (FAILED(hr))
			{
				const auto message = fmt::format(
					u8"Failed to get shader input parameter description.\n"
					u8"Name: {}",
					name);

				throw DirectXException { hr, message };
			}

			inputElements[i].SemanticName         = paramDesc.SemanticName;
			inputElements[i].SemanticIndex        = paramDesc.SemanticIndex;
			inputElements[i].Format               = dxgiFormat(paramDesc.ComponentType, paramDesc.Mask);
			inputElements[i].InputSlot            = 0;
			inputElements[i].AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
			inputElements[i].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
			inputElements[i].InstanceDataStepRate = 0;
		}

		// Create input layout.
		Microsoft::WRL::ComPtr<ID3D11InputLayout> layout;

		hr = device->CreateInputLayout(
			inputElements.data(),
			static_cast<UINT>(inputElements.size()),
			binary.data(),
			binary.size(),
			layout.GetAddressOf());

		if (FAILED(hr))
		{
			const auto message = fmt::format(
				u8"Failed to create vertex shader input layout.\n"
				u8"Name: {}",
				name);

			throw DirectXException { hr, message };
		}

		return layout;
	}
}

#endif
