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

#ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_GRAPHICS_HPP
#define INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_GRAPHICS_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <d3d11.h>
#include <wrl/client.h>
#include "../../../Uncopyable.hpp"
#include "../../IGraphics.hpp"

namespace Nene::Windows::Direct3D11
{
	// Forward declarations.
	class Context;

	/**
	 * @brief      Direct3D11 graphics implementation.
	 */
	class Graphics final
		: public  IGraphics
		, private Uncopyable
	{
		Microsoft::WRL::ComPtr<ID3D11Device> device_;

		std::unique_ptr<Context> context_;

		D3D_DRIVER_TYPE   driverType_;
		D3D_FEATURE_LEVEL featureLevel_;

	public:
		/**
		 * @brief      Constructor.
		 */
		explicit Graphics();

		/**
		 * @brief      Destructor.
		 */
		~Graphics();

		/**
		 * @see        `Nene::IGraphics::screen()`.
		 */
		[[nodiscard]]
		std::shared_ptr<IScreen> screen(const std::shared_ptr<IWindow>& window) override;

		/**
		 * @see        `Nene::IGraphics::screen()`.
		 */
		[[nodiscard]]
		std::shared_ptr<IScreen> screen(const std::shared_ptr<IWindow>& window, const Size2Di& size) override;

		/**
		 * @see        `Nene::IGraphics::vertexBuffer2D()`.
		 */
		[[nodiscard]]
		std::shared_ptr<IVertexBuffer<Vertex2D>> vertexBuffer2D(UInt32 capacity) override;

		/**
		 * @see        `Nene::IGraphics::indexBuffer()`.
		 */
		[[nodiscard]]
		std::shared_ptr<IIndexBuffer<UInt32>> indexBuffer(UInt32 capacity) override;

		/**
		 * @see        `Nene::IGraphics::compileVertexShader()`.
		 */
		[[nodiscard]]
		std::vector<Byte> compileVertexShader(const std::string& sourceName, ByteArrayView shaderSource, const std::string& entryPoint = u8"main") override;

		[[nodiscard]]
		std::vector<Byte> compileVertexShader(const std::string& sourceName, std::string_view shaderSource, const std::string& entryPoint = u8"main") override;

		/**
		 * @see        `Nene::IGraphics::compilePixelShader()`.
		 */
		[[nodiscard]]
		std::vector<Byte> compilePixelShader(const std::string& sourceName, ByteArrayView shaderSource, const std::string& entryPoint = u8"main") override;

		[[nodiscard]]
		std::vector<Byte> compilePixelShader(const std::string& sourceName, std::string_view shaderSource, const std::string& entryPoint = u8"main") override;

		/**
		 * @see        `Nene::IGraphics::texture()`.
		 */
		[[nodiscard]]
		std::shared_ptr<ITexture> texture(const Image& image) override;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_GRAPHICS_HPP
