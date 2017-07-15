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
#include "Context.hpp"
#include "CommandList.hpp"
#include "DynamicTexture.hpp"
#include "IndexBuffer.hpp"
#include "PixelShader.hpp"
#include "SpriteBatch.hpp"
#include "VertexBuffer2D.hpp"
#include "VertexShader.hpp"
#include "../../../File.hpp"

namespace Nene::Windows::Direct3D11
{
	Context::Context(const Microsoft::WRL::ComPtr<ID3D11Device>& device)
		: device_(device)
		, immediateContext_()
		, commandList_()
		, spriteBatch_()
		, vertexBuffer_()
		, indexBuffer_()
		, vertexShaderShape_()
		, pixelShaderShape_()
		, renderTarget_()
		, vertexShader_()
		, pixelShader_()
		, primitiveTopology_(D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED)
	{
		assert(device);

		// Get immediate context.
		device_->GetImmediateContext(immediateContext_.GetAddressOf());

		commandList_       = std::make_unique<CommandList>();
		spriteBatch_       = std::make_unique<SpriteBatch>(device_);
		vertexBuffer_      = spriteBatch_->vertexBuffer();
		indexBuffer_       = spriteBatch_->indexBuffer();

		// Compile shaders.
		const auto shaderPath   = std::experimental::filesystem::u8path(u8"Assets/Shaders/Shader2D.hlsl");
		const auto shaderSource = File::read(shaderPath);

		vertexShaderShape_ = std::make_shared<VertexShader>(device_, shaderPath.u8string(), u8"VS_shape", shaderSource);
		pixelShaderShape_  = std::make_shared<PixelShader> (device_, shaderPath.u8string(), u8"PS_shape", shaderSource);
	}

	Context::~Context() =default;

	void Context::dispatch()
	{
		for (const auto& command : commandList_->buffer())
		{
			std::visit([this](auto&& command)
			{
				excuteCommand(command);
			}, command);
		}

		clear();
	}

	void Context::setBuffers()
	{
		const UINT stride = vertexBuffer_->stride();
		const UINT offset = 0;

		immediateContext_->IASetVertexBuffers(0, 1, vertexBuffer_->buffer().GetAddressOf(), &stride, &offset);
		immediateContext_->IASetIndexBuffer(indexBuffer_->buffer().Get(), DXGI_FORMAT_R32_UINT, 0);
	}

	void Context::clear()
	{
		renderTarget_.reset();
		vertexShader_.reset();
		pixelShader_.reset();

		primitiveTopology_ = D3D11_PRIMITIVE_TOPOLOGY_UNDEFINED;
	}

	void Context::excuteCommand([[maybe_unused]] const CommandNop& command)
	{
		// Do nothing.
	}

	void Context::excuteCommand(const CommandClearRenderTarget& command)
	{
		const FLOAT clearColor[4] =
		{
			command.color.red,
			command.color.green,
			command.color.blue,
			command.color.alpha,
		};

		immediateContext_->ClearRenderTargetView(command.target->renderTargetView().Get(), clearColor);
	}

	void Context::excuteCommand(const CommandSetRenderTarget& command)
	{
		ID3D11RenderTargetView* const renderTargets[] =
		{
			command.target->renderTargetView().Get(),
		};

		immediateContext_->OMSetRenderTargets(
			std::extent_v<decltype(renderTargets)>,
			renderTargets,
			nullptr);
	}

	void Context::excuteCommand(const CommandSetVertexShader& command)
	{
		immediateContext_->VSSetShader(command.shader->shader().Get(), nullptr, 0);
		immediateContext_->IASetInputLayout(command.shader->inputLayout().Get());
	}

	void Context::excuteCommand(const CommandSetPixelShader& command)
	{
		immediateContext_->PSSetShader(command.shader->shader().Get(), nullptr, 0);
	}

	void Context::excuteCommand(const CommandSetPrimitiveTopology& command)
	{
		immediateContext_->IASetPrimitiveTopology(command.topology);
	}

	void Context::excuteCommand(const CommandDraw& command)
	{
		immediateContext_->DrawIndexed(command.indexCount, command.indexOffset, 0);
	}
}

#endif
