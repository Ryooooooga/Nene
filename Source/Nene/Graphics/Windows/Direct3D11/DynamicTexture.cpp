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

#include "DynamicTexture.hpp"
#include "Texture.hpp"
#include "../../../Exceptions/Windows/DirectXException.hpp"

namespace Nene::Windows::Direct3D11
{
	DynamicTexture::DynamicTexture(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const Size2Di& size, PixelFormat format)
		: texture_()
	{
		assert(device);

		// Create texture.
		texture_ = std::make_unique<Texture>(device, size, format);
	}

	DynamicTexture::~DynamicTexture() =default;

	const Size2Di& DynamicTexture::size() const noexcept
	{
		return texture_->size();
	}
}

#endif
