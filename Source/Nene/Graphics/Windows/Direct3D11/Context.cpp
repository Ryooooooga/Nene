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

#include <cassert>
#include "CommandList.hpp"
#include "Context.hpp"
#include "DynamicTexture.hpp"
#include "IndexBuffer.hpp"
#include "PixelShader.hpp"
#include "Screen.hpp"
#include "SpriteBatch.hpp"
#include "VertexBuffer.hpp"
#include "VertexShader.hpp"

namespace Nene::Windows::Direct3D11
{
	Context::Context(const Microsoft::WRL::ComPtr<ID3D11Device>& device)
		: immediateContext_ ()
		, commandList_      ()
		, spriteBatch_      ()
		, renderTarget_     ()
		, texture_          ()
		, vertexShader_     ()
		, pixelShader_      ()
		, viewport_         ()
	{
		assert(device);

		// Get context.
		device->GetImmediateContext(immediateContext_.GetAddressOf());

		// Create resources.
		commandList_ = std::make_unique<CommandList>();
		spriteBatch_ = std::make_unique<SpriteBatch>(immediateContext_);

		assert(spriteBatch_);
	}

	Context::~Context() =default;

	void Context::executeCommand(const CommandSetRenderTarget& command)
	{
		ID3D11RenderTargetView* const renderTargetViews[1] =
		{
			command.renderTarget.Get(),
		};

		immediateContext_->OMSetRenderTargets(
			std::extent_v<decltype(renderTargetViews)>,
			renderTargetViews,
			nullptr);
	}

	void Context::executeCommand(const CommandClearRenderTarget& command)
	{
		const FLOAT color[4] =
		{
			command.clearColor.red,
			command.clearColor.green,
			command.clearColor.blue,
			command.clearColor.alpha,
		};

		immediateContext_->ClearRenderTargetView(command.renderTarget.Get(), color);
	}

	void Context::executeCommand(const CommandSetViewport& command)
	{
		D3D11_VIEWPORT viewports[1] =
		{
			{
				/*.TopLeftX = */command.viewport.position.x,
				/*.TopLeftY = */command.viewport.position.y,
				/*.Width    = */command.viewport.size.width,
				/*.Height   = */command.viewport.size.height,
				/*.MinDepth = */0.f,
				/*.MaxDepth = */1.f,
			}
		};

		immediateContext_->RSSetViewports(std::extent_v<decltype(viewports)>, viewports);
	}

	void Context::executeCommand(const CommandSetTexture& command)
	{
		ID3D11ShaderResourceView* shaderResources[] =
		{
			command.shaderResource.Get(),
		};

		immediateContext_->PSGetShaderResources(0, std::extent_v<decltype(shaderResources)>, shaderResources);
	}

	void Context::executeCommand(const CommandSetVertexShader& command)
	{
		immediateContext_->VSSetShader(command.vertexShader.Get(), nullptr, 0);
		immediateContext_->IASetInputLayout(command.inputLayout.Get());
	}

	void Context::executeCommand(const CommandSetPixelShader& command)
	{
		immediateContext_->PSSetShader(command.pixelShader.Get(), nullptr, 0);
	}

	void Context::executeCommand(const CommandDraw& command)
	{
		immediateContext_->DrawIndexed(command.indexCount, command.indexOffset, 0);
	}

	void Context::executeCommand([[maybe_unused]] const CommandNop& command)
	{
	}

	Context& Context::flush()
	{
		// Update batch.
		spriteBatch_->updateBuffers(0, 0);

		// Set buffers.
		UINT stride = spriteBatch_->vertexBuffer()->byteStride();
		UINT offset = 0;

		immediateContext_->IASetVertexBuffers(0, 1, spriteBatch_->vertexBuffer()->vertexBuffer().GetAddressOf(), &stride, &offset);
		immediateContext_->IASetIndexBuffer(spriteBatch_->indexBuffer()->indexBuffer().Get(), spriteBatch_->indexBuffer()->format(), 0);

		// Initialize context state.
		immediateContext_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		// Execute command
		for (const auto& command : commandList_->commands())
		{
			std::visit([this](const auto& command)
			{
				executeCommand(command);
			}, command);
		}

		// Clear command list.
		commandList_->clear();

		// Clear sprite batch.
		spriteBatch_->clear();

		// Clear state.
		viewport(viewport_);

		if (renderTarget_)
		{
			renderTarget(std::exchange(renderTarget_, nullptr));
		}

		if (vertexShader_)
		{
			vertexShader(std::exchange(vertexShader_, nullptr));
		}

		if (pixelShader_)
		{
			pixelShader(std::exchange(pixelShader_, nullptr));
		}

		return *this;
	}

	Context& Context::present(const std::shared_ptr<IScreen>& screen)
	{
		// Type check.
		const auto screen_Direct3D11 = std::dynamic_pointer_cast<Screen>(screen);

		if (!screen_Direct3D11)
		{
			throw InvalidTypeException { u8"Argument must be a Direct3D11 screen." };
		}

		// Flush command buffer.
		flush();

		// Present screen.
		screen_Direct3D11->swapChain()->Present(1, 0);

		return *this;
	}

	Context& Context::renderTarget(const std::shared_ptr<IDynamicTexture>& nextRenderTarget)
	{
		// Type check.
		const auto renderTarget_Direct3D11 = std::dynamic_pointer_cast<DynamicTexture>(nextRenderTarget);

		if (!renderTarget_Direct3D11)
		{
			throw InvalidTypeException { u8"Argument must be a Direct3D11 dynamic texture." };
		}

		if (renderTarget_Direct3D11 == renderTarget_)
		{
			return *this;
		}

		// Push command.
		commandList_->overwriteLastOrPush(CommandSetRenderTarget
		{
			renderTarget_Direct3D11->renderTargetView(),
		});

		renderTarget_ = renderTarget_Direct3D11;

		return *this;
	}

	Context& Context::clear(const Color4f& clearColor)
	{
		if (!renderTarget_)
		{
			throw EngineException { u8"Render target has not been set." };
		}

		// Clear texture.
		commandList_->overwriteLastOrPush(CommandClearRenderTarget
		{
			renderTarget_->renderTargetView(),
			clearColor,
		});

		return *this;
	}

	Context& Context::viewport(const Rectanglef& viewport)
	{
		commandList_->overwriteLastOrPush(CommandSetViewport
		{
			viewport,
		});

		viewport_ = viewport;

		return *this;
	}

	Context& Context::texture(const std::shared_ptr<ITexture>& nextTexture)
	{
		// Type check.
		const auto texture_Direct3D11 = std::dynamic_pointer_cast<TextureBase>(nextTexture);

		if (!texture_Direct3D11)
		{
			throw InvalidTypeException { u8"Argument must be a Direct3D11 texture type." };
		}

		if (texture_Direct3D11 == texture_)
		{
			return *this;
		}

		// Push command.
		commandList_->overwriteLastOrPush(CommandSetTexture
		{
			texture_Direct3D11->shaderResourceView(),
		});

		texture_ = texture_Direct3D11;

		return *this;
	}

	Context& Context::vertexShader(const std::shared_ptr<IVertexShader>& nextVertexShader)
	{
		// Type check.
		const auto vertexShader_Direct3D11 = std::dynamic_pointer_cast<VertexShader>(nextVertexShader);

		if (!vertexShader_Direct3D11)
		{
			throw InvalidTypeException { u8"Argument must be a Direct3D11 vertex shader." };
		}

		if (vertexShader_Direct3D11 == vertexShader_)
		{
			return *this;
		}

		// Push command.
		commandList_->overwriteLastOrPush(CommandSetVertexShader
		{
			vertexShader_Direct3D11->vertexShader(),
			vertexShader_Direct3D11->inputLayout(),
		});

		vertexShader_ = vertexShader_Direct3D11;

		return *this;
	}

	Context& Context::pixelShader(const std::shared_ptr<IPixelShader>& nextPixelShader)
	{
		// Type check.
		const auto pixelShader_Direct3D11 = std::dynamic_pointer_cast<PixelShader>(nextPixelShader);

		if (!pixelShader_Direct3D11)
		{
			throw InvalidTypeException { u8"Argument must be a Direct3D11 pixel shader." };
		}

		if (pixelShader_Direct3D11 == pixelShader_)
		{
			return *this;
		}

		// Push command.
		commandList_->overwriteLastOrPush(CommandSetPixelShader
		{
			pixelShader_Direct3D11->pixelShader(),
		});

		pixelShader_ = pixelShader_Direct3D11;

		return *this;
	}

	Context& Context::draw(ArrayView<Vertex2D> vertices, ArrayView<UInt32> indices)
	{
		Vertex2D* vertexBuffer;
		UInt32*   indexBuffer;
		UInt32    indexOffset;

		if (vertices.size() > (std::numeric_limits<UInt32>::max)() || indices.size() > (std::numeric_limits<UInt32>::max)())
		{
			return *this;
		}

		UInt32 numVertices = static_cast<UInt32>(vertices.size());
		UInt32 numIndices  = static_cast<UInt32>(indices.size());

		if (!spriteBatch_->nextBuffer(vertexBuffer, indexBuffer, indexOffset, numVertices, numIndices))
		{
			return *this;
		}

		for (const auto& vertex : vertices)
		{
			*(vertexBuffer++) = vertex;
		}

		for (const auto index : indices)
		{
			*(indexBuffer++) = index + indexOffset;
		}

		commandList_->push(CommandDraw
		{
			spriteBatch_->indexPos() - numIndices,
			numIndices,
		});

		return *this;
	}

	std::shared_ptr<IDynamicTexture> Context::renderTarget() const
	{
		return renderTarget_;
	}

	Rectanglef Context::viewport() const
	{
		return viewport_;
	}

	std::shared_ptr<ITexture> Context::texture() const
	{
		return texture_;
	}

	std::shared_ptr<IVertexShader> Context::vertexShader() const
	{
		return vertexShader_;
	}

	std::shared_ptr<IPixelShader> Context::pixelShader() const
	{
		return pixelShader_;
	}
}

#endif
