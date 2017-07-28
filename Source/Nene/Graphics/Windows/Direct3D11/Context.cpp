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
#include "../../../Exceptions/InvalidTypeException.hpp"
#include "Context.hpp"
#include "DynamicTexture.hpp"
#include "Screen.hpp"

namespace Nene::Windows::Direct3D11
{
	Context::Context(const Microsoft::WRL::ComPtr<ID3D11Device>& device)
		: immediateContext_()
	{
		assert(device);

		device->GetImmediateContext(immediateContext_.GetAddressOf());
	}

	Context& Context::flush()
	{

		return *this;
	}

	Context& Context::present(const std::shared_ptr<IScreen>& screen)
	{
		const auto screen_Direct3D11 = std::dynamic_pointer_cast<Screen>(screen);

		// Type check.
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

	Context& Context::clear(const std::shared_ptr<IDynamicTexture>& texture, const Color4f& clearColor)
	{
		const auto texture_Direct3D11 = std::dynamic_pointer_cast<DynamicTexture>(texture);

		// Type check.
		if (!texture_Direct3D11)
		{
			throw InvalidTypeException { u8"Argument must be a Direct3D11 dynamic texture." };
		}

		// Clear texture.
		// TODO: prototype.
		const FLOAT color[4] = { clearColor.red, clearColor.green, clearColor.blue, clearColor.alpha };

		immediateContext_->ClearRenderTargetView(texture_Direct3D11->renderTargetView().Get(), color);

		return *this;
	}
}

#endif
