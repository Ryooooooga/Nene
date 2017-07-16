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

#ifndef INCLUDE_NENE_ENDIAN_INL_HPP
#define INCLUDE_NENE_ENDIAN_INL_HPP

namespace Nene::Endian
{
	template <typename T>
	constexpr T reverse(T x) noexcept
	{
		static_assert(std::is_scalar_v<T>);

		Byte* p = static_cast<Byte*>(static_cast<void*>(&x));

		for (std::size_t i = 0; i < sizeof(T)/2; i++)
		{
			Byte tmp = p[sizeof(T)-i-1];
			p[sizeof(T)-i-1] = p[i];
			p[i] = tmp;
		}

		return x;
	}

	template <>
	constexpr UInt8 reverse(UInt8 x) noexcept
	{
		return x;
	}

	template <>
	constexpr UInt16 reverse(UInt16 x) noexcept
	{
#if defined(NENE_COMPILER_GCC) || defined(NENE_COMPILER_CLANG)
		return __builtin_bswap16(x);
#else
		x = ((x & 0xff00) >> 8) | ((x & 0x00ff) << 8);
		return x;
#endif
	}

	template <>
	constexpr UInt32 reverse(UInt32 x) noexcept
	{
#if defined(NENE_COMPILER_GCC) || defined(NENE_COMPILER_CLANG)
		return __builtin_bswap32(x);
#else
		x = ((x & 0xffff0000) >> 16) | ((x & 0x0000ffff) << 16);
		x = ((x & 0xff00ff00) >>  8) | ((x & 0x00ff00ff) <<  8);
		return x;
#endif
	}

	template <>
	constexpr UInt64 reverse(UInt64 x) noexcept
	{
#if defined(NENE_COMPILER_GCC) || defined(NENE_COMPILER_CLANG)
		return __builtin_bswap64(x);
#else
		x = ((x & 0xffffffff00000000) >> 32) | ((x & 0x00000000ffffffff) << 32);
		x = ((x & 0xffff0000ffff0000) >> 16) | ((x & 0x0000ffff0000ffff) << 16);
		x = ((x & 0xff00ff00ff00ff00) >>  8) | ((x & 0x00ff00ff00ff00ff) <<  8);
		return x;
#endif
	}

	template <>
	constexpr Int8 reverse(Int8 x) noexcept
	{
		return x;
	}

	template <>
	constexpr Int16 reverse(Int16 x) noexcept
	{
		return static_cast<Int16>(reverse(static_cast<UInt16>(x)));
	}

	template <>
	constexpr Int32 reverse(Int32 x) noexcept
	{
		return static_cast<Int32>(reverse(static_cast<UInt32>(x)));
	}

	template <>
	constexpr Int64 reverse(Int64 x) noexcept
	{
		return static_cast<Int64>(reverse(static_cast<UInt64>(x)));
	}

	template <>
	constexpr char reverse(char x) noexcept
	{
		return x;
	}

	template <>
	constexpr wchar_t reverse(wchar_t x) noexcept
	{
#if defined(NENE_OS_WINDOWS)
		return static_cast<wchar_t>(reverse(static_cast<UInt16>(x)));
#else
		return static_cast<wchar_t>(reverse(static_cast<UInt32>(x)));
#endif
	}

	template <>
	constexpr char16_t reverse(char16_t x) noexcept
	{
		return static_cast<char16_t>(reverse(static_cast<UInt16>(x)));
	}

	template <>
	constexpr char32_t reverse(char32_t x) noexcept
	{
		return static_cast<char32_t>(reverse(static_cast<UInt32>(x)));
	}

	template <typename T>
	constexpr T nativeToBig(T x) noexcept
	{
#if defined(NENE_LITTLE_ENDIAN)
		return reverse(x);
#else
		return x;
#endif
	}

	template <typename T>
	constexpr T nativeToLittle(T x) noexcept
	{
#if defined(NENE_LITTLE_ENDIAN)
		return x;
#else
		return reverse(x);
#endif
	}

	template <typename T>
	constexpr T bigToNative(T x) noexcept
	{
		return nativeToBig(x);
	}

	template <typename T>
	constexpr T littleToNative(T x) noexcept
	{
		return nativeToLittle(x);
	}
}

#endif  // #ifndef INCLUDE_NENE_ENDIAN_INL_HPP
