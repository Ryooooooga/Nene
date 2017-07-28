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

#ifndef INCLUDE_NENE_GRAPHICS_IGRAPHICS_HPP
#define INCLUDE_NENE_GRAPHICS_IGRAPHICS_HPP

#include <memory>
#include <string_view>
#include "../ArrayView.hpp"
#include "../Size2D.hpp"
#include "../Vertex2D.hpp"

namespace Nene
{
	// Forward declarations.
	class Image;
	class IContext;
	class IDynamicTexture;
	class IPixelShader;
	class IScreen;
	class ITexture;
	class IVertexShader;
	class IWindow;

	template <typename Index>
	class ITypedIndexBuffer;
	template <typename Vertex>
	class ITypedVertexBuffer;

	/**
	 * @brief      Graphics interface.
	 */
	class IGraphics
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		IGraphics() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IGraphics() =default;

		/**
		 * @brief      Returns graphics context.
		 *
		 * @return     Graphics context.
		 */
		virtual std::shared_ptr<IContext> context() =0;

		/**
		 * @brief      Creates the screen instance.
		 *
		 * @param[in]  window  The render target window.
		 *
		 * @return     The screen instance.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IScreen> screen(const std::shared_ptr<IWindow>& window) =0;

		/**
		 * @brief      Creates the screen instance.
		 *
		 * @param[in]  window  The render target window.
		 * @param[in]  size    The size of the screen.
		 *
		 * @return     The screen instance.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IScreen> screen(const std::shared_ptr<IWindow>& window, const Size2Di& size) =0;

		/**
		 * @brief      Creates the 2D vertex buffer instance.
		 *
		 * @param[in]  capacity  Capacity of the vertex buffer.
		 *
		 * @return     The vertex buffer instance.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<ITypedVertexBuffer<Vertex2D>> vertexBuffer2D(UInt32 capacity) =0;

		/**
		 * @brief      Creates the index buffer instance.
		 *
		 * @param[in]  capacity  Capacity of the index buffer.
		 *
		 * @return     The index buffer instance.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<ITypedIndexBuffer<UInt32>> indexBuffer(UInt32 capacity) =0;

		/**
		 * @brief      Compiles the vertex shader and returns the compiled shader binary.
		 *
		 * @param[in]  sourceName    The shader source name.
		 * @param[in]  shaderSource  The shader source.
		 * @param[in]  entryPoint    The entry point (for HLSL only).
		 *
		 * @return     Compiled vertex shader binary.
		 */
		[[nodiscard]]
		virtual std::vector<Byte> compileVertexShader(const std::string& sourceName, ByteArrayView shaderSource, const std::string& entryPoint = u8"main") =0;

		[[nodiscard]]
		virtual std::vector<Byte> compileVertexShader(const std::string& sourceName, std::string_view shaderSource, const std::string& entryPoint = u8"main") =0;

		/**
		 * @brief      Creates the vertex shader object.
		 *
		 * @param[in]  sourceName    The shader source name.
		 * @param[in]  shaderSource  The shader source.
		 * @param[in]  entryPoint    The entry point (for HLSL only).
		 *
		 * @return     The vertex shader object.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IVertexShader> vertexShader(const std::string& sourceName, ByteArrayView shaderSource, const std::string& entryPoint = u8"main") =0;

		[[nodiscard]]
		virtual std::shared_ptr<IVertexShader> vertexShader(const std::string& sourceName, std::string_view shaderSource, const std::string& entryPoint = u8"main") =0;

		/**
		 * @brief      Creates the vertex shader object from compiled shader binary.
		 *
		 * @param[in]  compiledBinary  The compiled shader binary.
		 *
		 * @return     The vertex shader object.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IVertexShader> vertexShader(ByteArrayView compiledBinary) =0;

		/**
		 * @brief      Compiles the pixel shader and returns the compiled shader binary.
		 *
		 * @param[in]  sourceName    The shader source name.
		 * @param[in]  shaderSource  The shader source.
		 * @param[in]  entryPoint    The entry point (for HLSL only).
		 *
		 * @return     Compiled pixel shader binary.
		 */
		[[nodiscard]]
		virtual std::vector<Byte> compilePixelShader(const std::string& sourceName, ByteArrayView shaderSource, const std::string& entryPoint = u8"main") =0;

		[[nodiscard]]
		virtual std::vector<Byte> compilePixelShader(const std::string& sourceName, std::string_view shaderSource, const std::string& entryPoint = u8"main") =0;

		/**
		 * @brief      Creates the pixel shader object.
		 *
		 * @param[in]  sourceName    The shader source name.
		 * @param[in]  shaderSource  The shader source.
		 * @param[in]  entryPoint    The entry point (for HLSL only).
		 *
		 * @return     The pixel shader object.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IPixelShader> pixelShader(const std::string& sourceName, ByteArrayView shaderSource, const std::string& entryPoint = u8"main") =0;

		[[nodiscard]]
		virtual std::shared_ptr<IPixelShader> pixelShader(const std::string& sourceName, std::string_view shaderSource, const std::string& entryPoint = u8"main") =0;

		/**
		 * @brief      Creates the pixel shader object from compiled shader binary.
		 *
		 * @param[in]  compiledBinary  The compiled shader binary.
		 *
		 * @return     The pixel shader object.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IPixelShader> pixelShader(ByteArrayView compiledBinary) =0;

		/**
		 * @brief      Creates the texture from images.
		 *
		 * @param[in]  image  The source image.
		 *
		 * @return     The texture instance.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<ITexture> texture(const Image& image) =0;

		/**
		 * @brief      Creates the empty dynamic texture.
		 *
		 * @param[in]  size  The texture size.
		 *
		 * @return     The dynamic texture instance.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IDynamicTexture> dynamicTexture(const Size2Di& size) =0;

		/**
		 * @brief      Creates the dynamic texture from images.
		 *
		 * @param[in]  image  The source image.
		 *
		 * @return     The dynamic texture instance.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IDynamicTexture> dynamicTexture(const Image& image) =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_IGRAPHICS_HPP
