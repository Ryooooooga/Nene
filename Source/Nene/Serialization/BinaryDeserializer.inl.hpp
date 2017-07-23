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

#ifndef INCLUDE_NENE_SERIALIZATION_BINARYDESERIALIZER_INL_HPP
#define INCLUDE_NENE_SERIALIZATION_BINARYDESERIALIZER_INL_HPP

#include <cassert>
#include "Access.hpp"
#include "SerializationException.hpp"

namespace Nene::Serialization
{
	inline BinaryDeserializer::BinaryDeserializer(IReader& reader, Endian::Order byteOrder) noexcept
		: reader_(reader), order_(byteOrder) {}

	inline Endian::Order BinaryDeserializer::byteOrder() const noexcept
	{
		return order_;
	}

	template <typename T>
	inline BinaryDeserializer& BinaryDeserializer::serialize(T& data)
	{
		Access<BinaryDeserializer, std::remove_cv_t<std::remove_reference_t<T>>>::accessLoad(*this, data);

		return *this;
	}

	inline void BinaryDeserializer::read(void* data, std::size_t size)
	{
		if (reader_.read(data, size) != size)
		{
			throw SerializationException { u8"Deserialization failed." };
		}

		// Swap byte order.
		if (order_ != Endian::Order::native)
		{
			Byte* p = static_cast<Byte*>(data);

			for (std::size_t i = 0; i < size/2; i++)
			{
				std::swap(p[i], p[size-i-1]);
			}
		}
	}

	inline void load(BinaryDeserializer& archive, char& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, char16_t& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, char32_t& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, wchar_t& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, UInt8& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, UInt16& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, UInt32& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, UInt64& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, Int8& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, Int16& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, Int32& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, Int64& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, Float32& data)
	{
		archive.read(&data, sizeof(data));
	}

	inline void load(BinaryDeserializer& archive, Float64& data)
	{
		archive.read(&data, sizeof(data));
	}
}

#endif  // #ifndef INCLUDE_NENE_SERIALIZATION_BINARYDESERIALIZER_INL_HPP
