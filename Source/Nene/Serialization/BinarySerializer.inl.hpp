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

#ifndef INCLUDE_NENE_SERIALIZATION_BINARYSERIALIZER_INL_HPP
#define INCLUDE_NENE_SERIALIZATION_BINARYSERIALIZER_INL_HPP

#include <cassert>
#include "Access.hpp"
#include "SerializationException.hpp"

namespace Nene::Serialization
{
	inline BinarySerializer::BinarySerializer(IWriter& writer, Endian::Order byteOrder) noexcept
		: writer_(writer), order_(byteOrder) {}

	inline Endian::Order BinarySerializer::byteOrder() const noexcept
	{
		return order_;
	}

	template <typename T>
	inline BinarySerializer& BinarySerializer::serialize(const T& data)
	{
		Access<BinarySerializer, std::remove_cv_t<std::remove_reference_t<T>>>::accessSave(*this, data);

		return *this;
	}

	inline void BinarySerializer::write(const void* data, std::size_t size)
	{
		const Byte* p = static_cast<const Byte*>(data);
		std::size_t sizeWritten = 0;

		for (std::size_t i = 0; i < size; i++)
		{

			if (order_ == Endian::Order::native)
			{
				sizeWritten += writer_.write(p + i, 1);
			}
			else
			{
				sizeWritten += writer_.write(p - size - i - 1, 1);
			}
		}

		if (sizeWritten != size)
		{
			throw SerializationException { u8"Serialization failed." };
		}
	}

	inline void save(BinarySerializer& archive, const char& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const char16_t& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const char32_t& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const wchar_t& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const UInt8& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const UInt16& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const UInt32& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const UInt64& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const Int8& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const Int16& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const Int32& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const Int64& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const Float32& data)
	{
		archive.write(&data, sizeof(data));
	}

	inline void save(BinarySerializer& archive, const Float64& data)
	{
		archive.write(&data, sizeof(data));
	}
}

#endif  // #ifndef INCLUDE_NENE_SERIALIZATION_BINARYSERIALIZER_INL_HPP
