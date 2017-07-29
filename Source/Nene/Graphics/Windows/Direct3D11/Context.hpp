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

#ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_CONTEXT_HPP
#define INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_CONTEXT_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <d3d11.h>
#include <wrl/client.h>
#include "../../../Uncopyable.hpp"
#include "../../IContext.hpp"

namespace Nene::Windows::Direct3D11
{
	// Forward declarations.
	struct CommandSetRenderTarget;
	struct CommandClearRenderTarget;
	struct CommandSetViewport;
	struct CommandSetVertexShader;
	struct CommandSetPixelShader;
	struct CommandDraw;
	struct CommandNop;

	class CommandList;
	class DynamicTexture;
	class PixelShader;
	class SpriteBatch;
	class VertexShader;

	/**
	 * @brief      Direct3D11 graphics context.
	 */
	class Context final
		: public  IContext
		, private Uncopyable
	{
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediateContext_;

		std::unique_ptr<CommandList>    commandList_;
		std::unique_ptr<SpriteBatch>    spriteBatch_;

		std::shared_ptr<DynamicTexture> renderTarget_;
		std::shared_ptr<VertexShader>   vertexShader_;
		std::shared_ptr<PixelShader>    pixelShader_;

		Rectanglef viewport_;

		void executeCommand(const CommandSetRenderTarget&   command);
		void executeCommand(const CommandClearRenderTarget& command);
		void executeCommand(const CommandSetViewport&       command);
		void executeCommand(const CommandSetVertexShader&   command);
		void executeCommand(const CommandSetPixelShader&    command);
		void executeCommand(const CommandDraw&              command);
		void executeCommand(const CommandNop&               command);

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  device  Direct3D11 device.
		 */
		explicit Context(const Microsoft::WRL::ComPtr<ID3D11Device>& device);

		/**
		 * @brief      Destructor.
		 */
		~Context();

		/**
		 * @see        `Nene::IContext::flush()`.
		 */
		Context& flush() override;

		/**
		 * @see        `Nene::IContext::present()`.
		 */
		Context& present(const std::shared_ptr<IScreen>& screen) override;

		/**
		 * @see        `Nene::IContext::renderTarget()`.
		 */
		Context& renderTarget(const std::shared_ptr<IDynamicTexture>& nextRenderTarget) override;

		/**
		 * @see        `Nene::IContext::viewport()`.
		 */
		Context& viewport(const Rectanglef& nextViewport) override;

		/**
		 * @see        `Nene::IContext::clear()`.
		 */
		Context& clear(const Color4f& clearColor) override;

		/**
		 * @see        `Nene::IContext::vertexShader()`.
		 */
		Context& vertexShader(const std::shared_ptr<IVertexShader>& nextVertexShader) override;

		/**
		 * @see        `Nene::IContext::pixelShader()`.
		 */
		Context& pixelShader(const std::shared_ptr<IPixelShader>& nextPixelShader) override;

		/**
		 * @see        `Nene::IContext::draw()`.
		 */
		Context& draw(ArrayView<Vertex2D> vertices, ArrayView<UInt32> indices) override;

		/**
		 * @see        `Nene::IContext::renderTarget()`.
		 */
		[[nodiscard]]
		std::shared_ptr<IDynamicTexture> renderTarget() const noexcept override;


		/**
		 * @see        `Nene::IContext::viewport()`.
		 */
		[[nodiscard]]
		Rectanglef viewport() const noexcept override;

		/**
		 * @see        `Nene::IContext::vertexShader()`.
		 */
		[[nodiscard]]
		std::shared_ptr<IVertexShader> vertexShader() const noexcept override;

		/**
		 * @see        `Nene::IContext::pixelShader()`.
		 */
		[[nodiscard]]
		std::shared_ptr<IPixelShader> pixelShader() const noexcept override;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_CONTEXT_HPP
