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

#ifndef INCLUDE_NENE_SERIALIZATION_BINARYSERIALIZER_HPP
#define INCLUDE_NENE_SERIALIZATION_BINARYSERIALIZER_HPP

#include <memory>
#include "../Endian.hpp"
#include "../Uncopyable.hpp"
#include "../Writer/IWriter.hpp"

namespace Nene::Serialization
{
	/**
	 * @brief      Binary serializer.
	 */
	class BinarySerializer final
		: private Uncopyable
	{
		std::unique_ptr<IWriter> writer_;
		Endian::Order order_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param      writer  The output writer.
		 * @param[in]  endian  The serializer byte order.
		 */
		explicit BinarySerializer(std::unique_ptr<IWriter>&& writer, Endian::Order byteOrder = Endian::Order::native) noexcept;

		/**
		 * @brief      Destructor.
		 */
		~BinarySerializer() =default;

		/**
		 * @brief      Returns the serializer byte order.
		 *
		 * @return     The serializer byte order.
		 */
		[[nodiscard]]
		Endian::Order byteOrder() const noexcept;

		/**
		 * @brief      Serializes the data.
		 *
		 * @param      data  The data to write.
		 *
		 * @tparam     T     The data type.
		 *
		 * @return     `*this`.
		 */
		template <typename T>
		BinarySerializer& serialize(const T& data);

		/**
		 * @brief      Writes data.
		 *
		 * @param      data  The pointer to the data.
		 * @param[in]  size  The data size.
		 */
		void write(const void* data, std::size_t size);
	};
}

#include "BinarySerializer.inl.hpp"

#endif  // #ifndef INCLUDE_NENE_SERIALIZATION_BINARYSERIALIZER_HPP
