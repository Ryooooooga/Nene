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

#include "VertexShader.hpp"
#include "ShaderCompiler.hpp"
#include "ShaderReflection.hpp"
#include "../../../Exceptions/Windows/DirectXException.hpp"

namespace Nene::Windows::Direct3D11
{
	VertexShader::VertexShader(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const std::string& name, const std::string& entryPoint, const std::string& target, ByteArrayView source)
		: device_(device)
		, shader_()
		, inputLayout_()
		, name_(name)
		, binary_()
	{
		assert(device);

		// Compile vertex shader.
		binary_ = Shader::compile(name_, entryPoint, target, source);

		HRESULT hr = device_->CreateVertexShader(
			binary_.data(),
			binary_.size(),
			nullptr,
			shader_.GetAddressOf());

		if (FAILED(hr))
		{
			const auto message = fmt::format(
				u8"Failed to create vertex shader.\n"
				u8"Name: {}\n"
				u8"Entry point: {}\n"
				u8"Target: {}",
				name,
				entryPoint,
				target);

			throw DirectXException { hr, message };
		}

		// Create input layout.
		inputLayout_ = Shader::createInputLayout(device_, name_, binary_);
	}

	ByteArrayView VertexShader::compiledBinary() const noexcept
	{
		return binary_;
	}

	const Microsoft::WRL::ComPtr<ID3D11VertexShader>& VertexShader::shader() const noexcept
	{
		return shader_;
	}

	const Microsoft::WRL::ComPtr<ID3D11InputLayout>& VertexShader::inputLayout() const noexcept
	{
		return inputLayout_;
	}
}

#endif
