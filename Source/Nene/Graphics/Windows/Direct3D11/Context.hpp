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

#include <memory>
#include <d3d11.h>
#include <wrl/client.h>
#include "../../../Uncopyable.hpp"

namespace Nene::Windows::Direct3D11
{
	// Forward declarations.
	struct CommandNop;
	struct CommandClearRenderTarget;
	struct CommandSetRenderTarget;
	struct CommandSetVertexShader;
	struct CommandSetPixelShader;
	struct CommandSetPrimitiveTopology;
	struct CommandDraw;

	class CommandList;
	class DynamicTexture;
	class IndexBuffer;
	class PixelShader;
	class SpriteBatch;
	class VertexBuffer2D;
	class VertexShader;

	/**
	 * @brief      Direct3D11 rendering context.
	 */
	class Context final
		: private Uncopyable
	{
		Microsoft::WRL::ComPtr<ID3D11Device>        device_;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> immediateContext_;

		std::unique_ptr<CommandList>    commandList_;
		std::unique_ptr<SpriteBatch>    spriteBatch_;

		std::shared_ptr<VertexBuffer2D> vertexBuffer_;
		std::shared_ptr<IndexBuffer>    indexBuffer_;
		std::shared_ptr<VertexShader>   vertexShaderShape_;
		std::shared_ptr<PixelShader>    pixelShaderShape_;

		std::shared_ptr<DynamicTexture> renderTarget_;
		std::shared_ptr<VertexShader>   vertexShader_;
		std::shared_ptr<PixelShader>    pixelShader_;

		D3D11_PRIMITIVE_TOPOLOGY primitiveTopology_;

		void setBuffers();
		void clear();

		void excuteCommand(const CommandNop&                  command);
		void excuteCommand(const CommandClearRenderTarget&    command);
		void excuteCommand(const CommandSetRenderTarget&      command);
		void excuteCommand(const CommandSetVertexShader&      command);
		void excuteCommand(const CommandSetPixelShader&       command);
		void excuteCommand(const CommandSetPrimitiveTopology& command);
		void excuteCommand(const CommandDraw&                 command);

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
		 * @brief      Dispatches the rendering commands.
		 */
		void dispatch();
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_CONTEXT_HPP
