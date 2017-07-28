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

#ifndef INCLUDE_NENE_COLOR_HPP
#define INCLUDE_NENE_COLOR_HPP

#include "Types.hpp"

namespace Nene
{
	// Forward declarations.
	class Color4;
	class Color4f;

	/**
	 * @brief      Integer RGBA color.
	 */
	class Color4
	{
	public:
		UInt8 red, green, blue, alpha;

		/**
		 * @brief      Returns gray scaled color.
		 *
		 * @param[in]  gray   Gray scale.
		 * @param[in]  alpha  Alpha.
		 *
		 * @return     Gray color.
		 */
		[[nodiscard]]
		constexpr static Color4 gray(UInt8 gray, UInt8 alpha = 255) noexcept;

		/**
		 * @brief      Default constructor.
		 */
		constexpr Color4() noexcept =default;

		/**
		 * @brief      Copy constructor.
		 */
		constexpr Color4(const Color4&) noexcept =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  red
		 * @param[in]  green
		 * @param[in]  blue
		 * @param[in]  alpha
		 */
		constexpr Color4(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha = 255) noexcept;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color  Color code (0xAARRGGBB style).
		 */
		constexpr Color4(UInt32 color) noexcept;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color  Color code (0xRRGGBB style).
		 * @param[in]  alpha  Initial `alpha` value.
		 */
		constexpr Color4(UInt32 color, UInt8 alpha) noexcept;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color
		 * @param[in]  alpha
		 */
		constexpr Color4(const Color4& color, UInt8 alpha) noexcept;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color
		 * @param[in]  alpha
		 */
		constexpr Color4(const Color4f& color) noexcept;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color
		 * @param[in]  alpha
		 */
		constexpr Color4(const Color4f& color, UInt8 alpha) noexcept;

		/**
		 * @brief      Destructor.
		 */
		~Color4() =default;

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  _red
		 * @param[in]  _green
		 * @param[in]  _blue
		 * @param[in]  _alpha
		 *
		 * @return     `*this`.
		 */
		constexpr Color4& set(UInt8 _red, UInt8 _green, UInt8 _blue, UInt8 _alpha = 255) noexcept;

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  color
		 *
		 * @return     `*this`.
		 */
		constexpr Color4& set(const Color4& color) noexcept;

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  color
		 * @param[in]  _alpha
		 *
		 * @return     `*this`.
		 */
		constexpr Color4& set(const Color4& color, UInt8 _alpha) noexcept;

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  color
		 *
		 * @return     `*this`.
		 */
		constexpr Color4& set(const Color4f& color) noexcept;

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  color
		 * @param[in]  _alpha
		 *
		 * @return     `*this`.
		 */
		constexpr Color4& set(const Color4f& color, UInt8 _alpha) noexcept;

		/**
		 * @brief      Unary operator `~`.
		 *
		 * @return     `~(*this)`.
		 */
		[[nodiscard]]
		constexpr Color4 operator~() const noexcept;

		/**
		 * @brief      Binary operator `=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this = a`.
		 */
		constexpr Color4& operator=(const Color4& a) noexcept =default;

		/**
		 * @brief      Binary operator `+=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this += a`.
		 */
		constexpr Color4& operator+=(const Color4& a) noexcept;

		/**
		 * @brief      Binary operator `-=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this -= a`.
		 */
		constexpr Color4& operator-=(const Color4& a) noexcept;

		/**
		 * @brief      Binary operator `*=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this *= a`.
		 */
		constexpr Color4& operator*=(UInt8 a) noexcept;

		/**
		 * @brief      Binary operator `*=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this *= a`.
		 */
		constexpr Color4& operator*=(const Color4& a) noexcept;

		/**
		 * @brief      Binary operator `/=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this /= a`.
		 */
		constexpr Color4& operator/=(UInt8 a) noexcept;
	};

	/**
	 * @brief      Binary operator `+`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a + b`.
	 */
	[[nodiscard]]
	constexpr Color4 operator+(const Color4& a, const Color4& b) noexcept;

	/**
	 * @brief      Binary operator `-`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a - b`.
	 */
	[[nodiscard]]
	constexpr Color4 operator-(const Color4& a, const Color4& b) noexcept;

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a * b`.
	 */
	[[nodiscard]]
	constexpr Color4 operator*(const Color4& a, UInt8 b) noexcept;

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a * b`.
	 */
	[[nodiscard]]
	constexpr Color4 operator*(UInt8 a, const Color4& b) noexcept;

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a * b`.
	 */
	[[nodiscard]]
	constexpr Color4 operator*(const Color4& a, const Color4& b) noexcept;

	/**
	 * @brief      Binary operator `/`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a / b`.
	 */
	[[nodiscard]]
	constexpr Color4 operator/(const Color4& a, UInt8 b) noexcept;

	/**
	 * @brief      Float RGBA color.
	 */
	class Color4f
	{
	public:
		Float32 red, green, blue, alpha;

		/**
		 * @brief      Returns gray scaled color.
		 *
		 * @param[in]  gray   Gray scale.
		 * @param[in]  alpha  Alpha.
		 *
		 * @return     Gray color.
		 */
		[[nodiscard]]
		constexpr static Color4f gray(Float32 gray, Float32 alpha = 1.f) noexcept;

		/**
		 * @brief      Default constructor.
		 */
		constexpr Color4f() noexcept =default;

		/**
		 * @brief      Copy constructor.
		 */
		constexpr Color4f(const Color4f&) noexcept =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  red
		 * @param[in]  green
		 * @param[in]  blue
		 * @param[in]  alpha
		 */
		constexpr Color4f(Float32 red, Float32 green, Float32 blue, Float32 alpha = 1.f) noexcept;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color  Color code (0xAARRGGBB style).
		 */
		constexpr Color4f(UInt32 color) noexcept;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color  Color code (0xRRGGBB style).
		 * @param[in]  alpha  Initial `alpha` value.
		 */
		constexpr Color4f(UInt32 color, Float32 alpha) noexcept;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color
		 * @param[in]  alpha
		 */
		constexpr Color4f(const Color4& color) noexcept;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color
		 * @param[in]  alpha
		 */
		constexpr Color4f(const Color4& color, Float32 alpha) noexcept;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color
		 * @param[in]  alpha
		 */
		constexpr Color4f(const Color4f& color, Float32 alpha) noexcept;

		/**
		 * @brief      Destructor.
		 */
		~Color4f() =default;

		/**
		 * @brief      Clamps the values within range of `0` to `1`.
		 *
		 * @return     The clamped values.
		 */
		[[nodiscard]]
		constexpr Color4f saturated() const noexcept;

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  _red
		 * @param[in]  _green
		 * @param[in]  _blue
		 * @param[in]  _alpha
		 *
		 * @return     `*this`.
		 */
		constexpr Color4f& set(Float32 _red, Float32 _green, Float32 _blue, Float32 _alpha = 1.f) noexcept;

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  color
		 *
		 * @return     `*this`.
		 */
		constexpr Color4f& set(const Color4& color) noexcept;

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  color
		 * @param[in]  _alpha
		 *
		 * @return     `*this`.
		 */
		constexpr Color4f& set(const Color4& color, Float32 _alpha) noexcept;

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  color
		 *
		 * @return     `*this`.
		 */
		constexpr Color4f& set(const Color4f& color) noexcept;

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  color
		 * @param[in]  _alpha
		 *
		 * @return     `*this`.
		 */
		constexpr Color4f& set(const Color4f& color, Float32 _alpha) noexcept;

		/**
		 * @brief      Clamps the values within range of `0` to `1`.
		 *
		 * @return     `*this`.
		 */
		constexpr Color4f& saturate() noexcept;

		/**
		 * @brief      Unary operator `+`.
		 *
		 * @return     `+(*this)`.
		 */
		[[nodiscard]]
		constexpr Color4f operator+() const noexcept;

		/**
		 * @brief      Unary operator `-`.
		 *
		 * @return     `-(*this)`.
		 */
		[[nodiscard]]
		constexpr Color4f operator-() const noexcept;

		/**
		 * @brief      Unary operator `~`.
		 *
		 * @return     `~(*this)`.
		 */
		[[nodiscard]]
		constexpr Color4f operator~() const noexcept;

		/**
		 * @brief      Binary operator `=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this = a`.
		 */
		constexpr Color4f& operator=(const Color4f& a) noexcept =default;

		/**
		 * @brief      Binary operator `+=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this += a`.
		 */
		constexpr Color4f& operator+=(const Color4f& a) noexcept;

		/**
		 * @brief      Binary operator `-=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this -= a`.
		 */
		constexpr Color4f& operator-=(const Color4f& a) noexcept;

		/**
		 * @brief      Binary operator `*=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this *= a`.
		 */
		constexpr Color4f& operator*=(Float32 a) noexcept;

		/**
		 * @brief      Binary operator `*=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this *= a`.
		 */
		constexpr Color4f& operator*=(const Color4f& a) noexcept;

		/**
		 * @brief      Binary operator `/=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this /= a`.
		 */
		constexpr Color4f& operator/=(Float32 a) noexcept;
	};

	/**
	 * @brief      Binary operator `+`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a + b`.
	 */
	[[nodiscard]]
	constexpr Color4f operator+(const Color4f& a, const Color4f& b) noexcept;

	/**
	 * @brief      Binary operator `-`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a - b`.
	 */
	[[nodiscard]]
	constexpr Color4f operator-(const Color4f& a, const Color4f& b) noexcept;

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a * b`.
	 */
	[[nodiscard]]
	constexpr Color4f operator*(const Color4f& a, Float32 b) noexcept;

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a * b`.
	 */
	[[nodiscard]]
	constexpr Color4f operator*(Float32 a, const Color4f& b) noexcept;

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a * b`.
	 */
	[[nodiscard]]
	constexpr Color4f operator*(const Color4f& a, const Color4f& b) noexcept;

	/**
	 * @brief      Binary operator `/`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a / b`.
	 */
	[[nodiscard]]
	constexpr Color4f operator/(const Color4f& a, Float32 b) noexcept;
}

#include "Color.inl.hpp"

#endif  // #ifndef INCLUDE_NENE_COLOR_HPP
