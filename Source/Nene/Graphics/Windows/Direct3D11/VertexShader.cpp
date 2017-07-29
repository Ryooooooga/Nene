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

#include <d3dcompiler.h>
#include "VertexShader.hpp"
#include "../../../Exceptions/Windows/DirectXException.hpp"

namespace Nene::Windows::Direct3D11
{
	VertexShader::VertexShader(const Microsoft::WRL::ComPtr<ID3D11Device>& device, ByteArrayView compiledBinary)
		: shader_()
		, layout_()
	{
		assert(device);

		// Create shader object.
		throwIfFailed(
			device->CreateVertexShader(
				compiledBinary.data(),
				compiledBinary.size(),
				nullptr,
				shader_.GetAddressOf()),
			u8"Failed to create Direct3D11 vertex shader.");

		// Create shader reflection.
		Microsoft::WRL::ComPtr<ID3D11ShaderReflection> reflection;

		throwIfFailed(
			::D3DReflect(
				compiledBinary.data(),
				compiledBinary.size(),
				IID_ID3D11ShaderReflection,
				reinterpret_cast<void**>(reflection.GetAddressOf())),
			u8"Failed to create Direct3D11 shader reflection");

		// Get shader reflection.
		D3D11_SHADER_DESC shaderDesc;

		throwIfFailed(
			reflection->GetDesc(&shaderDesc),
			u8"Failed to get Direct3D11 shader reflection description");

		// Get input layout elements.
		std::vector<D3D11_INPUT_ELEMENT_DESC> inputElements(shaderDesc.InputParameters);

		for (UINT i = 0; i < shaderDesc.InputParameters; i++)
		{
			// Get input parameter description.
			D3D11_SIGNATURE_PARAMETER_DESC paramDesc;

			throwIfFailed(
				reflection->GetInputParameterDesc(i, &paramDesc),
				u8"Failed to get Direct3D11 shader input parameter description.");

			// Get DXGI format.
			DXGI_FORMAT format = DXGI_FORMAT_UNKNOWN;

			if (paramDesc.Mask <= 0b0001)
			{
				// 4byte.
				switch (paramDesc.ComponentType)
				{
					case D3D_REGISTER_COMPONENT_UINT32:
						format = DXGI_FORMAT_R32_UINT;
						break;

					case D3D_REGISTER_COMPONENT_SINT32:
						format = DXGI_FORMAT_R32_SINT;
						break;

					case D3D_REGISTER_COMPONENT_FLOAT32:
						format = DXGI_FORMAT_R32_FLOAT;
						break;
				}
			}
			else if (paramDesc.Mask <= 0b0011)
			{
				// 8byte.
				switch (paramDesc.ComponentType)
				{
					case D3D_REGISTER_COMPONENT_UINT32:
						format = DXGI_FORMAT_R32G32_UINT;
						break;

					case D3D_REGISTER_COMPONENT_SINT32:
						format = DXGI_FORMAT_R32G32_SINT;
						break;

					case D3D_REGISTER_COMPONENT_FLOAT32:
						format = DXGI_FORMAT_R32G32_FLOAT;
						break;
				}
			}
			else if (paramDesc.Mask <= 0b0111)
			{
				// 12byte.
				switch (paramDesc.ComponentType)
				{
					case D3D_REGISTER_COMPONENT_UINT32:
						format = DXGI_FORMAT_R32G32B32_UINT;
						break;

					case D3D_REGISTER_COMPONENT_SINT32:
						format = DXGI_FORMAT_R32G32B32_SINT;
						break;

					case D3D_REGISTER_COMPONENT_FLOAT32:
						format = DXGI_FORMAT_R32G32B32_FLOAT;
						break;
				}
			}
			else if (paramDesc.Mask <= 0b1111)
			{
				// 12byte.
				switch (paramDesc.ComponentType)
				{
					case D3D_REGISTER_COMPONENT_UINT32:
						format = DXGI_FORMAT_R32G32B32A32_UINT;
						break;

					case D3D_REGISTER_COMPONENT_SINT32:
						format = DXGI_FORMAT_R32G32B32A32_SINT;
						break;

					case D3D_REGISTER_COMPONENT_FLOAT32:
						format = DXGI_FORMAT_R32G32B32A32_FLOAT;
						break;
				}
			}

			// Construct input element description.
			inputElements[i].SemanticName         = paramDesc.SemanticName;
			inputElements[i].SemanticIndex        = paramDesc.SemanticIndex;
			inputElements[i].Format               = format;
			inputElements[i].InputSlot            = 0;
			inputElements[i].AlignedByteOffset    = D3D11_APPEND_ALIGNED_ELEMENT;
			inputElements[i].InputSlotClass       = D3D11_INPUT_PER_VERTEX_DATA;
			inputElements[i].InstanceDataStepRate = 0;
		}

		// Create input layout.
		throwIfFailed(
			device->CreateInputLayout(
				inputElements.data(),
				shaderDesc.InputParameters,
				compiledBinary.data(),
				compiledBinary.size(),
				layout_.GetAddressOf()),
			u8"Failed to create Direct3D11 shader input layout.");
	}
}

#endif
