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
#include <wrl/client.h>
#include "ShaderCompiler.hpp"
#include "../../../Exceptions/Windows/DirectXException.hpp"

#pragma comment(lib, "d3dcompiler.lib")

namespace Nene::Windows::Direct3D11::Shader
{
	std::vector<Byte> compile(const std::string& name, const std::string& entryPoint, const std::string& target, ByteArrayView source)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> binary;
		Microsoft::WRL::ComPtr<ID3DBlob> error;

		HRESULT hr = ::D3DCompile(
			source.data(),
			source.size(),
			name.c_str(),
			nullptr,
			nullptr,
			entryPoint.c_str(),
			target.c_str(),
			0,
			0,
			binary.GetAddressOf(),
			error.GetAddressOf());

		if (FAILED(hr))
		{
			const auto message = fmt::format(
				u8"Failed to compile shader.\n"
				u8"Name: {}\n"
				u8"Entry point: {}\n"
				u8"Target: {}",
				name,
				entryPoint,
				target);

			throw DirectXException { hr, message };
		}

		const auto begin = static_cast<const Byte*>(binary->GetBufferPointer());
		const auto end   = begin + binary->GetBufferSize();

		return std::vector<Byte>(begin, end);
	}
}

#endif
