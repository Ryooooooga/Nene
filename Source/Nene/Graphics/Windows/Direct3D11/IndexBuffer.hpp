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

#ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_INDEXBUFFER_HPP
#define INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_INDEXBUFFER_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include <memory>
#include "../../../Uncopyable.hpp"
#include "../../IIndexBuffer.hpp"
#include "Detail/Buffer.hpp"

namespace Nene::Windows::Direct3D11
{
	/**
	 * @brief      Direct3D11 index buffer implementation base.
	 */
	class IndexBufferBase
		: private Uncopyable
	{
	protected:
		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer_;
		UInt32 capacity_;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  device      Direct3D11 device.
		 * @param[in]  byteStride  Byte size of the index type.
		 * @param[in]  capacity    The capacity of the index buffer.
		 */
		explicit IndexBufferBase(const Microsoft::WRL::ComPtr<ID3D11Device>& device, UINT byteStride, UInt32 capacity)
			: buffer_(Detail::createBuffer(device, D3D11_BIND_INDEX_BUFFER, byteStride, capacity))
			, capacity_(capacity) {}

	public:
		/**
		 * @brief      Destructor.
		 */
		virtual ~IndexBufferBase() =default;

		/**
		 * @brief      Returns Direct3D11 index buffer.
		 *
		 * @return     Direct3D11 index buffer.
		 */
		[[nodiscard]]
		Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer() const noexcept
		{
			return buffer_;
		}
	};

	/**
	 * @brief      Direct3D11 index buffer implementation.
	 *
	 * @tparam     Index  Index type.
	 */
	template <typename Index>
	class IndexBuffer final
		: public ITypedIndexBuffer<Index>
		, public IndexBufferBase
	{
	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  device    Direct3D11 device.
		 * @param[in]  capacity  The capacity of the index buffer.
		 */
		explicit IndexBuffer(const Microsoft::WRL::ComPtr<ID3D11Device>& device, UInt32 capacity)
			: IndexBufferBase(device, sizeof(Index), capacity) {}

		/**
		 * @brief      Destructor.
		 */
		~IndexBuffer() =default;

		/**
		 * @see        `Nene::IIndexBuffer::size()`.
		 */
		[[nodiscard]]
		UInt32 size() const noexcept override
		{
			return capacity_;
		}

		/**
		 * @see        `Nene::IIndexBuffer::byteStride()`.
		 */
		[[nodiscard]]
		UInt32 byteStride() const noexcept override
		{
			return sizeof(Index);
		}
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_INDEXBUFFER_HPP

