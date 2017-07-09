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

#ifndef INCLUDE_NENE_SIZE2D_HPP
#define INCLUDE_NENE_SIZE2D_HPP

#include <cstdint>

namespace Nene
{
	/**
	 * @brief      2D size.
	 *
	 * @tparam     T     Element type.
	 */
	template <typename T>
	class Size2D
	{
	public:
		T width, height;

		using value_type = T;
		using size_type  = Size2D<T>;

		/**
		 * @brief      Returns zero size.
		 *
		 * @return     Zero size.
		 */
		constexpr static Size2D zero() noexcept
		{
			return { 0, 0 };
		}

		/**
		 * @brief      Returns square size.
		 *
		 * @param[in]  size  The length of sides.
		 *
		 * @return     Square size.
		 */
		constexpr static Size2D square(T size) noexcept
		{
			return { size, size };
		}

		/**
		 * @brief      Default constructor.
		 */
		constexpr Size2D() noexcept =default;

		/**
		 * @brief      Copy constructor.
		 */
		constexpr Size2D(const Size2D&) noexcept =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  width   Initial `width` value.
		 * @param[in]  height  Initial `height` value.
		 */
		constexpr Size2D(T width, T height) noexcept
			: width(width), height(height) {}

		/**
		 * @brief      Destructor.
		 */
		~Size2D() =default;

		/**
		 * @brief      Calculates the scaled size.
		 *
		 * @param[in]  s     Scaling.
		 *
		 * @return     Scaled size.
		 */
		[[nodiscard]]
		constexpr Size2D scaled(T s) const noexcept
		{
			return scaled(s, s);
		}

		/**
		 * @brief      Calculates the scaled size.
		 *
		 * @param[in]  sx    X-axis scaling.
		 * @param[in]  sy    Y-axis scaling.
		 *
		 * @return     Scaled size.
		 */
		[[nodiscard]]
		constexpr Size2D scaled(T sx, T sy) const noexcept
		{
			return { width * sx, height * sy };
		}

		/**
		 * @brief      Sets the size value.
		 *
		 * @param[in]  _width   New width value.
		 * @param[in]  _height  New height value.
		 *
		 * @return     `*this`.
		 */
		constexpr Size2D& set(T _width, T _height) noexcept
		{
			width  = _width;
			height = _height;

			return *this;
		}

		/**
		 * @brief      Sets the size value.
		 *
		 * @param[in]  s     New size value.
		 *
		 * @return     `*this`.
		 */
		constexpr Size2D& set(const Size2D& s) noexcept
		{
			width  = v.width;
			height = v.height;

			return *this;
		}

		/**
		 * @brief      Scales the size.
		 *
		 * @param[in]  s     Scaling.
		 *
		 * @return     `*this`.
		 */
		constexpr Size2D& scale(T s) noexcept
		{
			return scale(s, s);
		}

		/**
		 * @brief      Scales the size.
		 *
		 * @param[in]  sx    X-axis scaling.
		 * @param[in]  sy    Y-axis scaling.
		 *
		 * @return     `*this`.
		 */
		constexpr Size2D& scale(T sx, T sy) noexcept
		{
			width  *= sx;
			height *= sy;

			return *this;
		}

		/**
		 * @brief      Binary operator `=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this = a`.
		 */
		constexpr Size2D& operator=(const Size2D& a) noexcept =default;

		/**
		 * @brief      Binary operator `*=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this *= a`.
		 */
		constexpr Size2D& operator*=(T a) noexcept
		{
			width  *= a;
			height *= a;

			return *this;
		}

		/**
		 * @brief      Binary operator `/=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this /= a`.
		 */
		constexpr Size2D& operator/=(T a) noexcept
		{
			width  /= a;
			height /= a;

			return *this;
		}
	};

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a * b`.
	 */
	template <typename T, typename U>
	[[nodiscard]]
	constexpr auto operator*(const Size2D<T>& a, U b) noexcept
		-> Size2D<decltype(a.width * b)>
	{
		return { a.width * b, a.height * b };
	}

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a * b`.
	 */
	template <typename T, typename U>
	[[nodiscard]]
	constexpr auto operator*(T a, const Size2D<U>& b) noexcept
		-> Size2D<decltype(a * b.width)>
	{
		return { a.width * b, a.height * b };
	}

	/**
	 * @brief      Binary operator `/`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a / b`.
	 */
	template <typename T, typename U>
	[[nodiscard]]
	constexpr auto operator/(const Size2D<T>& a, U b) noexcept
		-> Size2D<decltype(a.width / b)>
	{
		return { a.width / b, a.height / b };
	}

	/**
	 * @brief      Binary operator `==`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a == b`.
	 */
	template <typename T>
	[[nodiscard]]
	constexpr bool operator==(const Size2D<T>& a, const Size2D<T>& b) noexcept
	{
		return a.width == b.width && a.height == b.height;
	}

	/**
	 * @brief      Binary operator `!=`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a != b`.
	 */
	template <typename T>
	[[nodiscard]]
	constexpr bool operator!=(const Size2D<T>& a, const Size2D<T>& b) noexcept
	{
		return !(a == b);
	}

	using Size2Di = Size2D<std::int32_t>;
	using Size2Df = Size2D<float>;
	using Size2Dd = Size2D<double>;
}

#endif  // #ifndef INCLUDE_NENE_SIZE2D_HPP
