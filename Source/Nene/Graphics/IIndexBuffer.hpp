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

#ifndef INCLUDE_NENE_GRAPHICS_IINDEXBUFFER_HPP
#define INCLUDE_NENE_GRAPHICS_IINDEXBUFFER_HPP

#include <type_traits>
#include "../Types.hpp"

namespace Nene
{
	/**
	 * @brief      Index buffer interface.
	 */
	class IIndexBuffer
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		IIndexBuffer() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IIndexBuffer() =default;

		/**
		 * @brief      Returns number of indices the index buffer can containts.
		 *
		 * @return     Capacity of the index buffer.
		 */
		[[nodiscard]]
		virtual UInt32 size() const noexcept =0;

		/**
		 * @brief      Returns byte width of the index type.
		 *
		 * @return     Byte width of the index type.
		 */
		[[nodiscard]]
		virtual UInt32 byteStride() const noexcept =0;
	};

	/**
	 * @brief      Index buffer interface with index type.
	 *
	 * @tparam     Index  Index type.
	 */
	template <typename Index>
	class ITypedIndexBuffer
		: public IIndexBuffer
	{
		static_assert(std::is_unsigned_v<Index>);

	public:
		using index_type = Index;

		/**
		 * @brief      Constructor.
		 */
		ITypedIndexBuffer() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~ITypedIndexBuffer() =default;
	};

	using IIndexBufferUInt16 = ITypedIndexBuffer<UInt16>;
	using IIndexBufferUInt32 = ITypedIndexBuffer<UInt32>;
}

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_IINDEXBUFFER_HPP
