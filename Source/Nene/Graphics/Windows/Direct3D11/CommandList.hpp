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

#ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_COMMANDLIST_HPP
#define INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_COMMANDLIST_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include <variant>
#include "../../../ArrayView.hpp"
#include "../../../Color.hpp"
#include "../../../Uncopyable.hpp"

namespace Nene::Windows::Direct3D11
{
	// Forward declarations.
	class DynamicTexture;
	class IndexBuffer;
	class PixelShader;
	class VertexBuffer;
	class VertexShader;

	struct CommandNop
	{
	};

	struct CommandClearRenderTarget
	{
		std::shared_ptr<DynamicTexture> target;
		Color4f color;
	};

	struct CommandSetRenderTarget
	{
		std::shared_ptr<DynamicTexture> target;
	};

	struct CommandSetVertexShader
	{
		std::shared_ptr<VertexShader> shader;
	};

	struct CommandSetPixelShader
	{
		std::shared_ptr<PixelShader> shader;
	};

	struct CommandSetVertexBuffer
	{
		std::shared_ptr<VertexBuffer> buffer;
	};

	struct CommandSetIndexBuffer
	{
		std::shared_ptr<IndexBuffer> buffer;
	};

	struct CommandDraw
	{
		std::size_t indexOffset;
		std::size_t indexCount;
	};

	using Command = std::variant
	<
		CommandClearRenderTarget,
		CommandSetRenderTarget,
		CommandSetVertexShader,
		CommandSetPixelShader,
		CommandSetVertexBuffer,
		CommandSetIndexBuffer,
		CommandDraw,
		CommandNop
	>;

	/**
	 * @brief      Rendering command buffer.
	 */
	class CommandList final
		: private Uncopyable
	{
		std::vector<Command> buffer_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  initialBufferSize  The initial rendering command buffer size.
		 */
		explicit CommandList(std::size_t initialBufferSize = 1024)
			: buffer_(initialBufferSize) {}

		/**
		 * @brief      Destructor.
		 */
		~CommandList() =default;

		/**
		 * @brief      Adds the rendering command.
		 *
		 * @param      command  The rendering command.
		 */
		void addCommand(Command&& command)
		{
			buffer_.emplace_back(std::move(command));
		}

		void addClearRenderTargetCommand(const std::shared_ptr<DynamicTexture>& renderTarget, const Color4f& clearColor)
		{
			addCommand(
				CommandClearRenderTarget
				{
					renderTarget,
					clearColor,
				}
			);
		}

		void addSetRenderTargetCommand(const std::shared_ptr<DynamicTexture>& renderTarget)
		{
			addCommand(
				CommandSetRenderTarget
				{
					renderTarget,
				}
			);
		}

		void addSetVertexShaderCommand(const std::shared_ptr<VertexShader>& shader)
		{
			addCommand(
				CommandSetVertexShader
				{
					shader,
				}
			);
		}

		void addSetPixelShaderCommand(const std::shared_ptr<PixelShader>& shader)
		{
			addCommand(
				CommandSetPixelShader
				{
					shader,
				}
			);
		}

		void addSetVertexBufferCommand(const std::shared_ptr<VertexBuffer>& buffer)
		{
			addCommand(
				CommandSetVertexBuffer
				{
					buffer,
				}
			);
		}

		void addSetIndexBufferCommand(const std::shared_ptr<IndexBuffer>& buffer)
		{
			addCommand(
				CommandSetIndexBuffer
				{
					buffer,
				}
			);
		}

		void addDraw(std::size_t indexOffset, std::size_t indexCount)
		{
			addCommand(
				CommandDraw
				{
					indexOffset,
					indexCount,
				}
			);
		}

		/**
		 * @brief      Returns the command list.
		 *
		 * @return     The command list buffer.
		 */
		[[nodiscard]]
		ArrayView<Command> buffer() const noexcept
		{
			return buffer_;
		}
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_COMMANDLIST_HPP
