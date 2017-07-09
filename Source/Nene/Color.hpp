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

#include <algorithm>
#include "Types.hpp"

namespace Nene
{
	/**
	 * @brief      Color.
	 */
	class Color
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
		constexpr static Color gray(Float32 gray, Float32 alpha = 1.f) noexcept
		{
			return { gray, gray, gray, alpha };
		}

		/**
		 * @brief      Default constructor.
		 */
		constexpr Color() noexcept =default;

		/**
		 * @brief      Copy constructor.
		 */
		constexpr Color(const Color&) noexcept =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  red    Initial `red` value.
		 * @param[in]  green  Initial `green` value.
		 * @param[in]  blue   Initial `blue` value.
		 * @param[in]  alpha  Initial `alpha` value.
		 */
		constexpr Color(Float32 red, Float32 green, Float32 blue, Float32 alpha = 1.f) noexcept
			: red(red), green(green), blue(blue), alpha(alpha) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color  Color code (0xAARRGGBB style).
		 */
		constexpr Color(UInt32 color) noexcept
			: red  (((color >> 16) & 0xff) / 255.f)
			, green(((color >>  8) & 0xff) / 255.f)
			, blue (((color >>  0) & 0xff) / 255.f)
			, alpha(((color >> 24) & 0xff) / 255.f) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color  Color code (0xRRGGBB style).
		 * @param[in]  alpha  Initial `alpha` value.
		 */
		constexpr Color(UInt32 color, Float32 alpha) noexcept
			: red  (((color >> 16) & 0xff) / 255.f)
			, green(((color >>  8) & 0xff) / 255.f)
			, blue (((color >>  0) & 0xff) / 255.f)
			, alpha(alpha) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  color  Color.
		 * @param[in]  alpha  Initial `alpha` value.
		 */
		constexpr Color(const Color& color, Float32 alpha) noexcept
			: red(color.red), green(color.green), blue(color.blue), alpha(alpha) {}

		/**
		 * @brief      Destructor.
		 */
		~Color() =default;

		/**
		 * @brief      Clamps the values within range of `0` to `1`.
		 *
		 * @return     The clamped values.
		 */
		[[nodiscard]]
		constexpr Color saturated() const noexcept
		{
			return {
				std::clamp(red,   0.f, 1.f),
				std::clamp(green, 0.f, 1.f),
				std::clamp(blue,  0.f, 1.f),
				std::clamp(alpha, 0.f, 1.f),
			};
		}

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  _red    New `red` value.
		 * @param[in]  _green  New `green` value.
		 * @param[in]  _blue   New `blue` value.
		 * @param[in]  _alpha  New `alpha` value.
		 *
		 * @return     `*this`.
		 */
		Color& set(Float32 _red, Float32 _green, Float32 _blue, Float32 _alpha = 1.f) noexcept
		{
			red   = _red;
			green = _green;
			blue  = _blue;
			alpha = _alpha;

			return *this;
		}

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  color   New color value.
		 * @param[in]  _alpha  New `alpha` value.
		 *
		 * @return     `*this`.
		 */
		Color& set(const Color& color, Float32 _alpha) noexcept
		{
			red   = color.red;
			green = color.green;
			blue  = color.blue;
			alpha = _alpha;

			return *this;
		}

		/**
		 * @brief      Sets the color values.
		 *
		 * @param[in]  color   New color value.
		 *
		 * @return     `*this`.
		 */
		Color& set(const Color& color) noexcept
		{
			red   = color.red;
			green = color.green;
			blue  = color.blue;
			alpha = color.alpha;

			return *this;
		}

		/**
		 * @brief      Clamps the values within range of `0` to `1`.
		 *
		 * @return     `*this`.
		 */
		constexpr Color& saturate() noexcept
		{
			red   = std::clamp(red,   0.f, 1.f);
			green = std::clamp(green, 0.f, 1.f);
			blue  = std::clamp(blue,  0.f, 1.f);
			alpha = std::clamp(alpha, 0.f, 1.f);

			return *this;
		}

		/**
		 * @brief      Unary operator `+`.
		 *
		 * @return     `+(*this)`.
		 */
		[[nodiscard]]
		constexpr Color operator+() const noexcept
		{
			return { +red, +green, +blue, +alpha };
		}

		/**
		 * @brief      Unary operator `-`.
		 *
		 * @return     `-(*this)`.
		 */
		[[nodiscard]]
		constexpr Color operator-() const noexcept
		{
			return { -red, -green, -blue, -alpha };
		}

		/**
		 * @brief      Unary operator `~`.
		 *
		 * @return     `~(*this)`.
		 */
		[[nodiscard]]
		constexpr Color operator~() const noexcept
		{
			return { 1.f-red, 1.f-green, 1.f-blue, 1.f-alpha };
		}

		/**
		 * @brief      Binary operator `=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this = a`.
		 */
		constexpr Color& operator=(const Color& a) noexcept =default;

		/**
		 * @brief      Binary operator `+=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this += a`.
		 */
		constexpr Color& operator+=(const Color& a) noexcept
		{
			red   += a.red;
			green += a.green;
			blue  += a.blue;
			alpha += a.alpha;

			return *this;
		}

		/**
		 * @brief      Binary operator `-=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this -= a`.
		 */
		constexpr Color& operator-=(const Color& a) noexcept
		{
			red   -= a.red;
			green -= a.green;
			blue  -= a.blue;
			alpha -= a.alpha;

			return *this;
		}

		/**
		 * @brief      Binary operator `*=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this *= a`.
		 */
		constexpr Color& operator*=(Float32 a) noexcept
		{
			red   *= a;
			green *= a;
			blue  *= a;
			alpha *= a;

			return *this;
		}

		/**
		 * @brief      Binary operator `*=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this *= a`.
		 */
		constexpr Color& operator*=(const Color& a) noexcept
		{
			red   *= a.red;
			green *= a.green;
			blue  *= a.blue;
			alpha *= a.alpha;

			return *this;
		}

		/**
		 * @brief      Binary operator `/=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this /= a`.
		 */
		constexpr Color& operator/=(Float32 a) noexcept
		{
			red   /= a;
			green /= a;
			blue  /= a;
			alpha /= a;

			return *this;
		}
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
	constexpr Color operator+(const Color& a, const Color& b) noexcept
	{
		return {
			a.red   + b.red,
			a.green + b.green,
			a.blue  + b.blue,
			a.alpha + b.alpha,
		};
	}

	/**
	 * @brief      Binary operator `-`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a - b`.
	 */
	[[nodiscard]]
	constexpr Color operator-(const Color& a, const Color& b) noexcept
	{
		return {
			a.red   - b.red,
			a.green - b.green,
			a.blue  - b.blue,
			a.alpha - b.alpha,
		};
	}

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a * b`.
	 */
	[[nodiscard]]
	constexpr Color operator*(const Color& a, Float32 b) noexcept
	{
		return {
			a.red   * b,
			a.green * b,
			a.blue  * b,
			a.alpha * b,
		};
	}

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a * b`.
	 */
	[[nodiscard]]
	constexpr Color operator*(const Color& a, const Color& b) noexcept
	{
		return {
			a.red   * b.red,
			a.green * b.green,
			a.blue  * b.blue,
			a.alpha * b.alpha,
		};
	}

	/**
	 * @brief      Binary operator `/`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a / b`.
	 */
	[[nodiscard]]
	constexpr Color operator/(const Color& a, Float32 b) noexcept
	{
		return {
			a.red   / b,
			a.green / b,
			a.blue  / b,
			a.alpha / b,
		};
	}
}

#endif  // #ifndef INCLUDE_NENE_COLOR_HPP
