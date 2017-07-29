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
#include "VertexBuffer.hpp"

namespace Nene::Windows::Direct3D11
{
	namespace
	{
		constexpr UInt32 vertexBufferSize = 4096;
		constexpr UInt32 indexBufferSize  = 4096 * 2;

		constexpr UInt32 maxNumVertices   = vertexBufferSize * 1;
		constexpr UInt32 maxNumIndices    = indexBufferSize  * 1;
	}

	SpriteBatch::SpriteBatch(const Microsoft::WRL::ComPtr<ID3D11Device>& device)
		: vertexBuffer_ (std::make_shared<VertexBuffer<Vertex2D>>(device, vertexBufferSize))
		, indexBuffer_  (std::make_shared<IndexBuffer<UInt32>>(device, indexBufferSize))
		, vertices_     (vertexBufferSize)
		, indices_      (indexBufferSize)
		, vertexPos_    (0)
		, indexPos_     (0)
	{
	}

	bool SpriteBatch::nextBuffer(Vertex2D*& vertices, UInt32*& indices, UInt32& indexOffset, UInt32 vertexCount, UInt32 indexCount)
	{
		if (vertexCount >= vertices_.size() - vertexPos_ || indexCount >= indices_.size() - indexPos_)
		{
			return false;
		}

		vertices    = vertices_.data() + vertexPos_;
		indices     = indices_ .data() + indexPos_;
		indexOffset = vertexPos_;

		vertexPos_ += vertexCount;
		indexPos_  += indexCount;

		return true;
	}
}

#endif
