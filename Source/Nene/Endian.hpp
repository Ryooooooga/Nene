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

#ifndef INCLUDE_NENE_ENDIAN_HPP
#define INCLUDE_NENE_ENDIAN_HPP

#include <type_traits>
#include "Platform.hpp"
#include "Types.hpp"

#if defined(NENE_OS_WINDOWS)
#  define NENE_LITTLE_ENDIAN
#elif defined(NENE_COMPILER_GCC) || defined(NENE_COMPILER_CLANG)
#  if   (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
#    define NENE_LITTLE_ENDIAN
#  elif (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
#    define NENE_BIG_ENDIAN
#  endif
#endif

#if !defined(NENE_LITTLE_ENDIAN) && !defined(NENE_BIG_ENDIAN)
#  define NENE_ENDIAN_UNSUPPORTED
#endif

namespace Nene::Endian
{
	/**
	 * @brief      Byte orders
	 */
	enum class Order: Int32
	{
		big,
		little,

#if   defined(NENE_BIG_ENDIAN)
		native = big,
#elif defined(NENE_LITTLE_ENDIAN)
		native = little,
#endif
	};

	/**
	 * @brief      Reverses bytes order.
	 *
	 * @param[in]  x     The data to swap bytes order.
	 *
	 * @tparam     T     The scalar type.
	 *
	 * @return     The data reversed.
	 */
	template <typename T>
	constexpr T reverse(T x) noexcept;

	/**
	 * @brief      Converts values between native and big endian byte order.
	 *
	 * @param[in]  x     The native byte order value.
	 *
	 * @tparam     T     The scalar type.
	 *
	 * @return     The big endian value.
	 */
	template <typename T>
	constexpr T nativeToBig(T x) noexcept;

	/**
	 * @brief      Converts values between native and little endian byte order.
	 *
	 * @param[in]  x     The native byte order value.
	 *
	 * @tparam     T     The scalar type.
	 *
	 * @return     The little endian value.
	 */
	template <typename T>
	constexpr T nativeToLittle(T x) noexcept;

	/**
	 * @brief      Converts values between native and big endian byte order.
	 *
	 * @param[in]  x     The big endian byte order value.
	 *
	 * @tparam     T     The scalar type.
	 *
	 * @return     The native endian value.
	 */
	template <typename T>
	constexpr T bigToNative(T x) noexcept;

	/**
	 * @brief      Converts values between native and little endian byte order.
	 *
	 * @param[in]  x     The little endian byte order value.
	 *
	 * @tparam     T     The scalar type.
	 *
	 * @return     The native endian value.
	 */
	template <typename T>
	constexpr T littleToNative(T x) noexcept;
}

#include "Endian.inl.hpp"

#endif  // #ifndef INCLUDE_NENE_ENDIAN_HPP
