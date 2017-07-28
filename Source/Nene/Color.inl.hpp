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

#ifndef INCLUDE_NENE_COLOR_INL_HPP
#define INCLUDE_NENE_COLOR_INL_HPP

#include <cassert>
#include <algorithm>

namespace Nene
{
	constexpr Color4 Color4::gray(UInt8 gray, UInt8 alpha) noexcept
	{
		return { gray, gray, gray, alpha };
	}

	constexpr Color4::Color4(UInt8 red, UInt8 green, UInt8 blue, UInt8 alpha) noexcept
		: red(red), green(green), blue(blue), alpha(alpha) {}

	constexpr Color4::Color4(UInt32 color) noexcept
		: red   ((color >> 16) & 0xff)
		, green ((color >>  8) & 0xff)
		, blue  ((color >>  0) & 0xff)
		, alpha ((color >> 24) & 0xff) {}

	constexpr Color4::Color4(UInt32 color, UInt8 alpha) noexcept
		: red   ((color >> 16) & 0xff)
		, green ((color >>  8) & 0xff)
		, blue  ((color >>  0) & 0xff)
		, alpha (alpha) {}

	constexpr Color4::Color4(const Color4f& color) noexcept
		: red   (static_cast<UInt8>(std::clamp(color.red   , 0.f, 1.f) * 255))
		, green (static_cast<UInt8>(std::clamp(color.green , 0.f, 1.f) * 255))
		, blue  (static_cast<UInt8>(std::clamp(color.blue  , 0.f, 1.f) * 255))
		, alpha (static_cast<UInt8>(std::clamp(color.alpha , 0.f, 1.f) * 255)) {}

	constexpr Color4::Color4(const Color4f& color, UInt8 alpha) noexcept
		: red   (static_cast<UInt8>(std::clamp(color.red   , 0.f, 1.f) * 255))
		, green (static_cast<UInt8>(std::clamp(color.green , 0.f, 1.f) * 255))
		, blue  (static_cast<UInt8>(std::clamp(color.blue  , 0.f, 1.f) * 255))
		, alpha (alpha) {}

	constexpr Color4& Color4::set(UInt8 _red, UInt8 _green, UInt8 _blue, UInt8 _alpha) noexcept
	{
		red   = red;
		green = green;
		blue  = blue;
		alpha = alpha;

		return *this;
	}

	constexpr Color4& Color4::set(const Color4& color) noexcept
	{
		red   = color.red;
		green = color.green;
		blue  = color.blue;
		alpha = color.alpha;

		return *this;
	}

	constexpr Color4& Color4::set(const Color4& color, UInt8 _alpha) noexcept
	{
		red   = color.red;
		green = color.green;
		blue  = color.blue;
		alpha = alpha;

		return *this;
	}

	constexpr Color4& Color4::set(const Color4f& color) noexcept
	{
		red   = static_cast<UInt8>(std::clamp(color.red   , 0.f, 1.f) * 255);
		green = static_cast<UInt8>(std::clamp(color.green , 0.f, 1.f) * 255);
		blue  = static_cast<UInt8>(std::clamp(color.blue  , 0.f, 1.f) * 255);
		alpha = static_cast<UInt8>(std::clamp(color.alpha , 0.f, 1.f) * 255);

		return *this;
	}

	constexpr Color4& Color4::set(const Color4f& color, UInt8 _alpha) noexcept
	{
		red   = static_cast<UInt8>(std::clamp(color.red   , 0.f, 1.f) * 255);
		green = static_cast<UInt8>(std::clamp(color.green , 0.f, 1.f) * 255);
		blue  = static_cast<UInt8>(std::clamp(color.blue  , 0.f, 1.f) * 255);
		alpha = alpha;

		return *this;
	}

	constexpr Color4 Color4::operator~() const noexcept
	{
		return
		{
			static_cast<UInt8>(~red),
			static_cast<UInt8>(~green),
			static_cast<UInt8>(~blue),
			static_cast<UInt8>(~alpha)
		};
	}

	constexpr Color4& Color4::operator+=(const Color4& a) noexcept
	{
		return *this = *this + a;
	}

	constexpr Color4& Color4::operator-=(const Color4& a) noexcept
	{
		return *this = *this - a;
	}

	constexpr Color4& Color4::operator*=(UInt8 a) noexcept
	{
		return *this = *this * a;
	}

	constexpr Color4& Color4::operator*=(const Color4& a) noexcept
	{
		return *this = *this * a;
	}

	constexpr Color4& Color4::operator/=(UInt8 a) noexcept
	{
		return *this = *this / a;
	}

	constexpr Color4 operator+(const Color4& a, const Color4& b) noexcept
	{
		return
		{
			static_cast<UInt8>((std::min)(a.red   + b.red   , 255)),
			static_cast<UInt8>((std::min)(a.green + b.green , 255)),
			static_cast<UInt8>((std::min)(a.blue  + b.blue  , 255)),
			static_cast<UInt8>((std::min)(a.alpha + b.alpha , 255)),
		};
	}

	constexpr Color4 operator-(const Color4& a, const Color4& b) noexcept
	{
		return
		{
			static_cast<UInt8>((std::max)(a.red   - b.red   , 0)),
			static_cast<UInt8>((std::max)(a.green - b.green , 0)),
			static_cast<UInt8>((std::max)(a.blue  - b.blue  , 0)),
			static_cast<UInt8>((std::max)(a.alpha - b.alpha , 0)),
		};
	}

	constexpr Color4 operator*(const Color4& a, UInt8 b) noexcept
	{
		return
		{
			static_cast<UInt8>((std::min)(a.red   * b, 255)),
			static_cast<UInt8>((std::min)(a.green * b, 255)),
			static_cast<UInt8>((std::min)(a.blue  * b, 255)),
			static_cast<UInt8>((std::min)(a.alpha * b, 255)),
		};
	}

	constexpr Color4 operator*(UInt8 a, const Color4& b) noexcept
	{
		return
		{
			static_cast<UInt8>((std::min)(a * b.red   , 255)),
			static_cast<UInt8>((std::min)(a * b.green , 255)),
			static_cast<UInt8>((std::min)(a * b.blue  , 255)),
			static_cast<UInt8>((std::min)(a * b.alpha , 255)),
		};
	}

	constexpr Color4 operator*(const Color4& a, const Color4& b) noexcept
	{
		return
		{
			static_cast<UInt8>((std::min)(a.red   * b.red   , 255)),
			static_cast<UInt8>((std::min)(a.green * b.green , 255)),
			static_cast<UInt8>((std::min)(a.blue  * b.blue  , 255)),
			static_cast<UInt8>((std::min)(a.alpha * b.alpha , 255)),
		};
	}

	constexpr Color4 operator/(const Color4& a, UInt8 b) noexcept
	{
		assert(b != 0);

		return
		{
			static_cast<UInt8>(a.red   / b),
			static_cast<UInt8>(a.green / b),
			static_cast<UInt8>(a.blue  / b),
			static_cast<UInt8>(a.alpha / b),
		};
	}

	constexpr Color4f Color4f::gray(Float32 gray, Float32 alpha) noexcept
	{
		return { gray, gray, gray, alpha };
	}

	constexpr Color4f::Color4f(Float32 red, Float32 green, Float32 blue, Float32 alpha) noexcept
		: red   (red   )
		, green (green )
		, blue  (blue  )
		, alpha (alpha ) {}

	constexpr Color4f::Color4f(UInt32 color) noexcept
		: red   (((color >> 16) & 0xff) / 255.f)
		, green (((color >>  8) & 0xff) / 255.f)
		, blue  (((color >>  0) & 0xff) / 255.f)
		, alpha (((color >> 24) & 0xff) / 255.f) {}

	constexpr Color4f::Color4f(UInt32 color, Float32 alpha) noexcept
		: red   (((color >> 16) & 0xff) / 255.f)
		, green (((color >>  8) & 0xff) / 255.f)
		, blue  (((color >>  0) & 0xff) / 255.f)
		, alpha (alpha) {}

	constexpr Color4f::Color4f(const Color4& color) noexcept
		: red   (color.red   / 255.f)
		, green (color.green / 255.f)
		, blue  (color.blue  / 255.f)
		, alpha (color.alpha / 255.f) {}

	constexpr Color4f::Color4f(const Color4& color, Float32 alpha) noexcept
		: red   (color.red   / 255.f)
		, green (color.green / 255.f)
		, blue  (color.blue  / 255.f)
		, alpha (alpha) {}

	constexpr Color4f::Color4f(const Color4f& color, Float32 alpha) noexcept
		: red   (color.red   )
		, green (color.green )
		, blue  (color.blue  )
		, alpha (alpha) {}

	constexpr Color4f Color4f::saturated() const noexcept
	{
		return
		{
			std::clamp(red   , 0.f, 1.f),
			std::clamp(green , 0.f, 1.f),
			std::clamp(blue  , 0.f, 1.f),
			std::clamp(alpha , 0.f, 1.f),
		};
	}

	constexpr Color4f& Color4f::set(Float32 _red, Float32 _green, Float32 _blue, Float32 _alpha) noexcept
	{
		red   = _red;
		green = _green;
		blue  = _blue;
		alpha = _alpha;

		return *this;
	}

	constexpr Color4f& Color4f::set(const Color4& color) noexcept
	{
		red   = color.red   / 255.f;
		green = color.green / 255.f;
		blue  = color.blue  / 255.f;
		alpha = color.alpha / 255.f;

		return *this;
	}

	constexpr Color4f& Color4f::set(const Color4& color, Float32 _alpha) noexcept
	{
		red   = color.red   / 255.f;
		green = color.green / 255.f;
		blue  = color.blue  / 255.f;
		alpha = _alpha;

		return *this;
	}

	constexpr Color4f& Color4f::set(const Color4f& color) noexcept
	{
		red   = color.red;
		green = color.green;
		blue  = color.blue;
		alpha = color.alpha;

		return *this;
	}

	constexpr Color4f& Color4f::set(const Color4f& color, Float32 _alpha) noexcept
	{
		red   = color.red;
		green = color.green;
		blue  = color.blue;
		alpha = alpha;

		return *this;
	}

	constexpr Color4f& Color4f::saturate() noexcept
	{
		red   = std::clamp(red   , 0.f, 1.f);
		green = std::clamp(green , 0.f, 1.f);
		blue  = std::clamp(blue  , 0.f, 1.f);
		alpha = std::clamp(alpha , 0.f, 1.f);

		return *this;
	}

	constexpr Color4f Color4f::operator+() const noexcept
	{
		return
		{
			+red,
			+green,
			+blue,
			+alpha,
		};
	}

	constexpr Color4f Color4f::operator-() const noexcept
	{
		return
		{
			-red,
			-green,
			-blue,
			-alpha,
		};
	}

	constexpr Color4f Color4f::operator~() const noexcept
	{
		return
		{
			1.f - red,
			1.f - green,
			1.f - blue,
			1.f - alpha,
		};
	}

	constexpr Color4f& Color4f::operator+=(const Color4f& a) noexcept
	{
		return *this = *this + a;
	}

	constexpr Color4f& Color4f::operator-=(const Color4f& a) noexcept
	{
		return *this = *this - a;
	}

	constexpr Color4f& Color4f::operator*=(Float32 a) noexcept
	{
		return *this = *this * a;
	}

	constexpr Color4f& Color4f::operator*=(const Color4f& a) noexcept
	{
		return *this = *this * a;
	}

	constexpr Color4f& Color4f::operator/=(Float32 a) noexcept
	{
		return *this = *this / a;
	}

	constexpr Color4f operator+(const Color4f& a, const Color4f& b) noexcept
	{
		return
		{
			a.red   + b.red,
			a.green + b.green,
			a.blue  + b.blue,
			a.alpha + b.alpha,
		};
	}

	constexpr Color4f operator-(const Color4f& a, const Color4f& b) noexcept
	{
		return
		{
			a.red   - b.red,
			a.green - b.green,
			a.blue  - b.blue,
			a.alpha - b.alpha,
		};
	}

	constexpr Color4f operator*(const Color4f& a, Float32 b) noexcept
	{
		return
		{
			a.red   * b,
			a.green * b,
			a.blue  * b,
			a.alpha * b,
		};
	}

	constexpr Color4f operator*(Float32 a, const Color4f& b) noexcept
	{
		return
		{
			a * b.red,
			a * b.green,
			a * b.blue,
			a * b.alpha,
		};
	}

	constexpr Color4f operator*(const Color4f& a, const Color4f& b) noexcept
	{
		return
		{
			a.red   * b.red,
			a.green * b.green,
			a.blue  * b.blue,
			a.alpha * b.alpha,
		};
	}

	constexpr Color4f operator/(const Color4f& a, Float32 b) noexcept
	{
		assert(b != 0.f);

		return
		{
			a.red   / b,
			a.green / b,
			a.blue  / b,
			a.alpha / b,
		};
	}
}

#endif  // #ifndef INCLUDE_NENE_COLOR_INL_HPP
