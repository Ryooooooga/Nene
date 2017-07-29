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

#ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_SPRITEBATCH_HPP
#define INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_SPRITEBATCH_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <cassert>
#include <vector>
#include <d3d11.h>
#include <wrl/client.h>
#include "../../../Vertex2D.hpp"

namespace Nene::Windows::Direct3D11
{
	// Forward declarations.
	template <typename Vertex>
	class VertexBuffer;

	template <typename Index>
	class IndexBuffer;

	/**
	 * @brief      Direct3D sprite batch.
	 */
	class SpriteBatch final
		: private Uncopyable
	{
		std::shared_ptr<VertexBuffer<Vertex2D>> vertexBuffer_;
		std::shared_ptr<IndexBuffer<UInt32>>    indexBuffer_;

		std::vector<Vertex2D> vertices_;
		std::vector<UInt32>   indices_;

		UInt32 vertexPos_;
		UInt32 indexPos_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 */
		explicit SpriteBatch(const Microsoft::WRL::ComPtr<ID3D11Device>& device);

		/**
		 * @brief      Destructor.
		 */
		~SpriteBatch() =default;

		/**
		 * @brief      Get next buffer pointers.
		 *
		 * @param      vertices     Reference to the next vertex buffer pointer.
		 * @param      indices      Reference to the next index buffer pointer.
		 * @param      indexOffset  Reference to the index offset.
		 * @param[in]  vertexCount  Number of vertices to secure.
		 * @param[in]  indexCount   Number of indices to secure.
		 *
		 * @return     `true` if succeeded, `false` otherwise.
		 */
		bool nextBuffer(Vertex2D*& vertices, UInt32*& indices, UInt32& indexOffset, UInt32 vertexCount, UInt32 indexCount);

		/**
		 * @brief      Returns the vertex buffer.
		 *
		 * @return     The vertex buffer.
		 */
		[[nodiscard]]
		std::shared_ptr<VertexBuffer<Vertex2D>> vertexBuffer() const noexcept
		{
			return vertexBuffer_;
		}

		/**
		 * @brief      Returns the index buffer.
		 *
		 * @return     The index buffer.
		 */
		[[nodiscard]]
		std::shared_ptr<IndexBuffer<UInt32>> indexBuffer() const noexcept
		{
			return indexBuffer_;
		}
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_SPRITEBATCH_HPP
