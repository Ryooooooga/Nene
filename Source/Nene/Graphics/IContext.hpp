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

#ifndef INCLUDE_NENE_GRAPHICS_ICONTEXT_HPP
#define INCLUDE_NENE_GRAPHICS_ICONTEXT_HPP

#include <memory>
#include "../ArrayView.hpp"
#include "../Vertex2D.hpp"
#include "../Geometry/Rectangle.hpp"

namespace Nene
{
	// Forward declarations.
	class IDynamicTexture;
	class IIndexBuffer;
	class IPixelShader;
	class IScreen;
	class ITexture;
	class IVertexBuffer;
	class IVertexShader;

	/**
	 * @brief      Graphics context interface.
	 */
	class IContext
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		IContext() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IContext() =default;

		/**
		 * @brief      Excutes all rendering commands.
		 *
		 * @return     `*this`.
		 */
		virtual IContext& flush() =0;

		/**
		 * @brief      Presents the screen.
		 *
		 * @param[in]  screen  The screen instance.
		 *
		 * @return     `*this`.
		 */
		virtual IContext& present(const std::shared_ptr<IScreen>& screen) =0;

		/**
		 * @brief      Sets the render target texture.
		 *
		 * @param[in]  newRenderTarget  The new render target.
		 *
		 * @return     `*this`.
		 */
		virtual IContext& renderTarget(const std::shared_ptr<IDynamicTexture>& newRenderTarget) =0;

		/**
		 * @brief      Clears the current render target.
		 *
		 * @param[in]  clearColor  The clear color.
		 *
		 * @return     `*this`.
		 */
		virtual IContext& clear(const Color4f& clearColor) =0;

		/**
		 * @brief      Sets the viewport.
		 *
		 * @param[in]  nextViewport  The viewport to set.
		 *
		 * @return     `*this`.
		 */
		virtual IContext& viewport(const Rectanglef& nextViewport) =0;

		/**
		 * @brief      Sets the current rendering texture.
		 *
		 * @param[in]  nextTexture  The next rendering texture.
		 *
		 * @return     `*this`.
		 */
		virtual IContext& texture(const std::shared_ptr<ITexture>& nextTexture) =0;

		/**
		 * @brief      Sets the current vertex shader.
		 *
		 * @param[in]  nextVertexShader  The vertex shader to set.
		 *
		 * @return     `*this`.
		 */
		virtual IContext& vertexShader(const std::shared_ptr<IVertexShader>& nextVertexShader) =0;

		/**
		 * @brief      Sets the current pixel shader.
		 *
		 * @param[in]  nextPixelShader  The pixel shader to set.
		 *
		 * @return     `*this`.
		 */
		virtual IContext& pixelShader(const std::shared_ptr<IPixelShader>& nextPixelShader) =0;

		/**
		 * @brief      Draw polygon.
		 *
		 * @param[in]  vertices  Vertices.
		 * @param[in]  indices   Indices.
		 *
		 * @return     `*this`.
		 */
		virtual IContext& draw(ArrayView<Vertex2D> vertices, ArrayView<UInt32> indices) =0;

		/**
		 * @brief      Returns the current render target texture.
		 *
		 * @return     The current render target texture.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IDynamicTexture> renderTarget() const =0;

		/**
		 * @brief      Returns the current viewport.
		 *
		 * @return     The current viewport.
		 */
		[[nodiscard]]
		virtual Rectanglef viewport() const =0;

		/**
		 * @brief      Returns the current rendering texture.
		 *
		 * @return     The current rendering texture.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<ITexture> texture() const =0;

		/**
		 * @brief      Returns the current vertex shader.
		 *
		 * @return     The current vertex shader.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IVertexShader> vertexShader() const =0;

		/**
		 * @brief      Returns the current pixel shader.
		 *
		 * @return     The current pixel shader.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IPixelShader> pixelShader() const =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_ICONTEXT_HPP
