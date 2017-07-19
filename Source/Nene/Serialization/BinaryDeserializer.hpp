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

#ifndef INCLUDE_NENE_SERIALIZATION_BINARYDESERIALIZER_HPP
#define INCLUDE_NENE_SERIALIZATION_BINARYDESERIALIZER_HPP

#include <memory>
#include "../Endian.hpp"
#include "../Uncopyable.hpp"
#include "../Reader/IReader.hpp"

namespace Nene::Serialization
{
	/**
	 * @brief      Binary deserializer.
	 */
	class BinaryDeserializer final
		: private Uncopyable
	{
		std::unique_ptr<IReader> reader_;
		Endian::Order order_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param      reader  The input reader.
		 * @param[in]  endian  The serializer byte order.
		 */
		explicit BinaryDeserializer(std::unique_ptr<IReader>&& reader, Endian::Order byteOrder = Endian::Order::native) noexcept;

		/**
		 * @brief      Destructor.
		 */
		~BinaryDeserializer() =default;

		/**
		 * @brief      Returns the serializer byte order.
		 *
		 * @return     The serializer byte order.
		 */
		[[nodiscard]]
		Endian::Order byteOrder() const noexcept;

		/**
		 * @brief      Deserializes the data.
		 *
		 * @param      data  The data to read.
		 *
		 * @tparam     T     The data type.
		 *
		 * @return     `*this`.
		 */
		template <typename T>
		BinaryDeserializer& serialize(T& data);

		/**
		 * @brief      Reads the data.
		 *
		 * @param      data  The pointer to the data.
		 * @param[in]  size  The data size.
		 */
		void read(void* data, std::size_t size);
	};
}

#include "BinaryDeserializer.inl.hpp"

#endif  // #ifndef INCLUDE_NENE_SERIALIZATION_BINARYDESERIALIZER_HPP
