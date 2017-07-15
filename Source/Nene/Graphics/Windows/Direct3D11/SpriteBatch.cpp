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

#include "IndexBuffer.hpp"
#include "SpriteBatch.hpp"
#include "VertexBuffer2D.hpp"

namespace Nene::Windows::Direct3D11
{
	namespace
	{
		constexpr UInt32 initialVertexCount   = 4096;
		constexpr UInt32 initialIndexCount    = 4096 * 2;

		constexpr UInt32 vertexBufferCapacity = 65536;
		constexpr UInt32 indexBufferCapacity  = 65536 * 2;
	}

	SpriteBatch::SpriteBatch(const Microsoft::WRL::ComPtr<ID3D11Device>& device)
		: vertexBuffer_()
		, indexBuffer_()
		, vertices_(initialVertexCount)
		, indices_(initialIndexCount)
		, vertexWritePos_(0)
		, indexWritePos_(0)
	{
		assert(device);

		vertexBuffer_ = std::make_shared<VertexBuffer2D>(device, vertexBufferCapacity);
		indexBuffer_  = std::make_shared<IndexBuffer>(device, indexBufferCapacity);
	}
}

#endif
