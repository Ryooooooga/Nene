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

#if defined(NENE_COMPILER_MSVC)
#  pragma comment(lib, "dxgi.lib")
#  pragma comment(lib, "dxguid.lib")
#  pragma comment(lib, "d3d11.lib")
#  pragma comment(lib, "d3dcompiler.lib")
#endif

#include <d3dcompiler.h>
#include "../../../Exceptions/Windows/DirectXException.hpp"
#include "../../../Window/Windows/Window.hpp"
#include "Context.hpp"
#include "DynamicTexture.hpp"
#include "Graphics.hpp"
#include "IndexBuffer.hpp"
#include "PixelShader.hpp"
#include "Screen.hpp"
#include "Texture.hpp"
#include "VertexBuffer.hpp"
#include "VertexShader.hpp"

namespace Nene::Windows::Direct3D11
{
	namespace
	{
		std::vector<Byte> compileShader(const std::string& sourceName, ByteArrayView shaderSource, const char* target, const std::string& entryPoint)
		{
			assert(target);

			UINT shaderFlags = D3D10_SHADER_ENABLE_STRICTNESS;
	#if defined(NENE_DEBUG)
			shaderFlags |= D3D10_SHADER_DEBUG;
			shaderFlags |= D3D10_SHADER_SKIP_OPTIMIZATION;
	#endif

			Microsoft::WRL::ComPtr<ID3DBlob> code;
			Microsoft::WRL::ComPtr<ID3DBlob> error;

			throwIfFailed(
				::D3DCompile(
					shaderSource.data(),
					shaderSource.size(),
					sourceName.c_str(),
					nullptr,
					nullptr,
					entryPoint.c_str(),
					target,
					shaderFlags,
					0,
					code.GetAddressOf(),
					error.GetAddressOf()),
				[&]()
				{
					return fmt::format(
						u8"Failed to compile shader.\n"
						u8"Name: {}\n"
						u8"Target: {}\n"
						u8"Entry point: {}\n"
						u8"Error: {}",
						sourceName,
						target,
						entryPoint,
						static_cast<const char*>(error->GetBufferPointer()));
				});

			const auto begin = static_cast<const Byte*>(code->GetBufferPointer());
			const auto end   = begin + code->GetBufferSize();

			return std::vector<Byte>(begin, end);
		}
	}

	Graphics::Graphics()
		: device_()
		, context_()
		, driverType_(D3D_DRIVER_TYPE_UNKNOWN)
		, featureLevel_()
	{
		// Create device.
		UINT creationFlags = 0;
#if defined(NENE_DEBUG)
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

		for (const auto driverType : driverTypes)
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
				nullptr);

			if (SUCCEEDED(hr))
			{
				driverType_ = driverType;

				break;
			}
		}

		throwIfFailed(hr, u8"Failed to create Direct3D11 device.");

		// Create context.
		context_ = std::make_shared<Context>(device_);
	}

	std::shared_ptr<IContext> Graphics::context()
	{
		return context_;
	}

	std::shared_ptr<IScreen> Graphics::screen(const std::shared_ptr<IWindow>& window)
	{
		assert(window);

		return screen(window, window->size());
	}

	std::shared_ptr<IScreen> Graphics::screen(const std::shared_ptr<IWindow>& window, const Size2Di& size)
	{
		assert(window);

		const auto window_Windows = std::dynamic_pointer_cast<Window>(window);

		return window_Windows
			? std::make_shared<Screen>(device_, window_Windows, size)
			: throw InvalidTypeException { u8"Argument must be a Windows API window." };
	}

	std::shared_ptr<ITypedVertexBuffer<Vertex2D>> Graphics::vertexBuffer2D(UInt32 capacity)
	{
		return std::make_shared<VertexBuffer<Vertex2D>>(device_, capacity);
	}

	std::shared_ptr<ITypedIndexBuffer<UInt32>> Graphics::indexBuffer(UInt32 capacity)
	{
		return std::make_shared<IndexBuffer<UInt32>>(device_, capacity);
	}

	std::vector<Byte> Graphics::compileVertexShader(const std::string& sourceName, ByteArrayView shaderSource, const std::string& entryPoint)
	{
		const char* target =
			featureLevel_ >= D3D_FEATURE_LEVEL_11_0 ? u8"vs_5_0" :
			featureLevel_ >= D3D_FEATURE_LEVEL_10_1 ? u8"vs_4_1" : u8"vs_4_0";

		return compileShader(sourceName, shaderSource, target, entryPoint);
	}

	std::vector<Byte> Graphics::compileVertexShader(const std::string& sourceName, std::string_view shaderSource, const std::string& entryPoint)
	{
		const auto source = ByteArrayView
		{
			reinterpret_cast<const Byte*>(shaderSource.data()),
			shaderSource.size(),
		};

		return compileVertexShader(sourceName, source, entryPoint);
	}

	std::shared_ptr<IVertexShader> Graphics::vertexShader(const std::string& sourceName, ByteArrayView shaderSource, const std::string& entryPoint)
	{
		return vertexShader(compileVertexShader(sourceName, shaderSource, entryPoint));
	}

	std::shared_ptr<IVertexShader> Graphics::vertexShader(const std::string& sourceName, std::string_view shaderSource, const std::string& entryPoint)
	{
		return vertexShader(compileVertexShader(sourceName, shaderSource, entryPoint));
	}

	std::shared_ptr<IVertexShader> Graphics::vertexShader(ByteArrayView compiledBinary)
	{
		return std::make_shared<VertexShader>(device_, compiledBinary);
	}

	std::vector<Byte> Graphics::compilePixelShader(const std::string& sourceName, ByteArrayView shaderSource, const std::string& entryPoint)
	{
		const char* target =
			featureLevel_ >= D3D_FEATURE_LEVEL_11_0 ? u8"ps_5_0" :
			featureLevel_ >= D3D_FEATURE_LEVEL_10_1 ? u8"ps_4_1" : u8"ps_4_0";

		return compileShader(sourceName, shaderSource, target, entryPoint);
	}

	std::vector<Byte> Graphics::compilePixelShader(const std::string& sourceName, std::string_view shaderSource, const std::string& entryPoint)
	{
		const auto source = ByteArrayView
		{
			reinterpret_cast<const Byte*>(shaderSource.data()),
			shaderSource.size(),
		};

		return compilePixelShader(sourceName, source, entryPoint);
	}

	std::shared_ptr<IPixelShader> Graphics::pixelShader(const std::string& sourceName, ByteArrayView shaderSource, const std::string& entryPoint)
	{
		return pixelShader(compilePixelShader(sourceName, shaderSource, entryPoint));
	}

	std::shared_ptr<IPixelShader> Graphics::pixelShader(const std::string& sourceName, std::string_view shaderSource, const std::string& entryPoint)
	{
		return pixelShader(compilePixelShader(sourceName, shaderSource, entryPoint));
	}

	std::shared_ptr<IPixelShader> Graphics::pixelShader(ByteArrayView compiledBinary)
	{
		return std::make_shared<PixelShader>(device_, compiledBinary);
	}

	std::shared_ptr<ITexture> Graphics::texture(const Image& image)
	{
		return std::make_shared<Texture>(device_, image, false);
	}

	std::shared_ptr<IDynamicTexture> Graphics::dynamicTexture(const Size2Di& size)
	{
		return std::make_shared<DynamicTexture>(device_, size);
	}

	std::shared_ptr<IDynamicTexture> Graphics::dynamicTexture(const Image& image)
	{
		return std::make_shared<DynamicTexture>(device_, image);
	}
}

#endif
