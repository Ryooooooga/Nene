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

#ifndef INCLUDE_NENE_VECTOR2D_HPP
#define INCLUDE_NENE_VECTOR2D_HPP

#include "Rotation.hpp"

namespace Nene
{
	// Forward declarations.
	template <typename T>
	class Matrix3x2;

	/**
	 * @brief      2D vector.
	 *
	 * @tparam     T     Element type.
	 */
	template <typename T>
	class Vector2D
	{
	public:
		T x, y;

		using value_type  = T;
		using vector_type = Vector2D<T>;

		/**
		 * @brief      Returns zero vector.
		 *
		 * @return     Zero vector.
		 */
		[[nodiscard]]
		constexpr static Vector2D zero() noexcept
		{
			return { 0, 0 };
		}

		/**
		 * @brief      Returns x-axis unit vector.
		 *
		 * @return     X-axis unit vector.
		 */
		[[nodiscard]]
		constexpr static Vector2D unitX() noexcept
		{
			return { 1, 0 };
		}

		/**
		 * @brief      Returns y-axis unit vector.
		 *
		 * @return     Y-axis unit vector.
		 */
		[[nodiscard]]
		constexpr static Vector2D unitY() noexcept
		{
			return { 0, 1 };
		}

		/**
		 * @brief      Returns left direction vector.
		 *
		 * @param[in]  length  Length of the vector.
		 *
		 * @return     Left direction vector.
		 */
		[[nodiscard]]
		constexpr static Vector2D left(T length = 1) noexcept
		{
			return { -length, 0 };
		}

		/**
		 * @brief      Returns right direction vector.
		 *
		 * @param[in]  length  Length of the vector.
		 *
		 * @return     Right direction vector.
		 */
		[[nodiscard]]
		constexpr static Vector2D right(T length = 1) noexcept
		{
			return { length, 0 };
		}

		/**
		 * @brief      Returns up direction vector.
		 *
		 * @param[in]  length  Length of the vector.
		 *
		 * @return     Up direction vector.
		 */
		[[nodiscard]]
		constexpr static Vector2D up(T length = 1) noexcept
		{
			return { 0, -length };
		}

		/**
		 * @brief      Returns down direction vector.
		 *
		 * @param[in]  length  Length of the vector.
		 *
		 * @return     Down direction vector.
		 */
		[[nodiscard]]
		constexpr static Vector2D down(T length = 1) noexcept
		{
			return { 0, length };
		}

		/**
		 * @brief      Default constructor.
		 */
		constexpr Vector2D() noexcept =default;

		/**
		 * @brief      Copy constructor.
		 */
		constexpr Vector2D(const Vector2D&) noexcept =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  x     Initial `x` value.
		 * @param[in]  y     Initial `y` value.
		 */
		constexpr Vector2D(T x, T y) noexcept
			: x(x), y(y) {}

		/**
		 * @brief      Converting constructor.
		 *
		 * @param[in]  v     Vector to convert.
		 */
		template <typename U>
		constexpr Vector2D(const Vector2D<U>& v) noexcept
			: x(v.x), y(v.y) {}

		/**
		 * @brief      Destructor.
		 */
		~Vector2D() =default;

		/**
		 * @brief      Returns `(x, x)`.
		 *
		 * @return     `(x, x)`.
		 */
		[[nodiscard]]
		constexpr Vector2D xx() const noexcept
		{
			return { x, x };
		}

		/**
		 * @brief      Returns `(x, y)`.
		 *
		 * @return     `(x, y)`.
		 */
		[[nodiscard]]
		constexpr Vector2D xy() const noexcept
		{
			return { x, y };
		}

		/**
		 * @brief      Returns `(y, x)`.
		 *
		 * @return     `(y, x)`.
		 */
		[[nodiscard]]
		constexpr Vector2D yx() const noexcept
		{
			return { y, x };
		}

		/**
		 * @brief      Returns `(y, y)`.
		 *
		 * @return     `(y, y)`.
		 */
		[[nodiscard]]
		constexpr Vector2D yy() const noexcept
		{
			return { y, y };
		}

		/**
		 * @brief      Returns the forward vector.
		 *
		 * @return     The forward vector.
		 */
		[[nodiscard]]
		constexpr Vector2D forward() const noexcept
		{
			return { x, y };
		}

		/**
		 * @brief      Returns the backward vector.
		 *
		 * @return     The backward vector.
		 */
		[[nodiscard]]
		constexpr Vector2D backward() const noexcept
		{
			return { -x, -y };
		}

		/**
		 * @brief      Returns the left vector.
		 *
		 * @return     The left vector.
		 */
		[[nodiscard]]
		constexpr Vector2D left() const noexcept
		{
			return { -y, x };
		}

		/**
		 * @brief      Returns the right vector.
		 *
		 * @return     The right vector.
		 */
		[[nodiscard]]
		constexpr Vector2D right() const noexcept
		{
			return { y, -x };
		}

		/**
		 * @brief      Determines if the vector is zero.
		 *
		 * @return     `true` if the vector is zero, `false` otherwise.
		 */
		[[nodiscard]]
		constexpr bool isZero() const noexcept
		{
			return x == 0 && y == 0;
		}

		/**
		 * @brief      Determines if the vector has NaN.
		 *
		 * @return     `true` if the vector has NaN, `false` otherwise.
		 */
		[[nodiscard]]
		bool hasNaN() const noexcept
		{
			return std::isnan(x) || std::isnan(y);
		}

		/**
		 * @brief      Determines if the vector has infinity.
		 *
		 * @return     `true` if the vector has Infinity, `false` otherwise.
		 */
		[[nodiscard]]
		bool hasInfinity() const noexcept
		{
			return std::isinf(x) || std::isinf(y);
		}

		/**
		 * @brief      Calculates squared length of the vector.
		 *
		 * @return     Squared length of the vector.
		 */
		[[nodiscard]]
		constexpr T lengthSq() const noexcept
		{
			return dot(*this);
		}

		/**
		 * @brief      Calculates length of the vector.
		 *
		 * @return     Length of the vector.
		 */
		[[nodiscard]]
		T length() const noexcept
		{
			return std::hypot(x, y);
		}

		/**
		 * @brief      Calculates cosine.
		 *
		 * @return     Cosine.
		 */
		[[nodiscard]]
		T cos() const noexcept
		{
			return isZero() ? 1 : x / length();
		}

		/**
		 * @brief      Calculates sine.
		 *
		 * @return     Sine.
		 */
		[[nodiscard]]
		T sin() const noexcept
		{
			return isZero() ? 0 : y / length();
		}

		/**
		 * @brief      Calculates tangent.
		 *
		 * @return     Tangent.
		 */
		[[nodiscard]]
		T tan() const noexcept
		{
			return y / x;
		}

		/**
		 * @brief      Calculates the amplitude of the vector.
		 *
		 * @return     The amplitude of the vector.
		 */
		[[nodiscard]]
		T angle() const noexcept
		{
			return std::atan2(y, x);
		}

		/**
		 * @brief      Calculates the mirrored vector.
		 *             Mirrors if `doMirror == true`, does nothing otherwise.
		 *
		 * @param[in]  doMirror  Mirroring flag.
		 *
		 * @return     the mirrored vector if `doMirror == true`,
		 *             `*this` otherwise.
		 */
		[[nodiscard]]
		constexpr Vector2D mirrored(bool doMirror = true) const noexcept
		{
			return { doMirror ? -x : x, y };
		}

		/**
		 * @brief      Calculates the flipped vector.
		 *             Flips if `doMirror == true`, does nothing otherwise.
		 *
		 * @param[in]  doFlip  Flipping flag.
		 *
		 * @return     the flipped vector if `doMirror == true`,
		 *             `*this` otherwise.
		 */
		[[nodiscard]]
		constexpr Vector2D flipped(bool doFlip = true) const noexcept
		{
			return { x, doFlip ? -y : y };
		}

		/**
		 * @brief      Calculates the normalized vector.
		 *
		 * @return     The normalized vector.
		 */
		[[nodiscard]]
		Vector2D normalized() const noexcept
		{
			return *this / length();
		}

		/**
		 * @brief      Calculates the vector having the same direction of this
		 *             vector and the given length.
		 *
		 * @param[in]  _length  New length.
		 *
		 * @return     The vector having the same direction of `this` and the
		 *             given length.
		 */
		[[nodiscard]]
		Vector2D ofLength(T _length) noexcept
		{
			return isZero() ? zero() : (*this * _length / length());
		}

		/**
		 * @brief      Calculates the dot product.
		 *
		 * @param[in]  v     Right hand side operand.
		 *
		 * @return     Dot product.
		 */
		[[nodiscard]]
		constexpr T dot(const Vector2D& v) const noexcept
		{
			return x*v.x + y*v.y;
		}

		/**
		 * @brief      Calculates the cross product.
		 *
		 * @param[in]  v     Right hand side operand.
		 *
		 * @return     Cross product.
		 */
		[[nodiscard]]
		constexpr T cross(const Vector2D& v) const noexcept
		{
			return x*v.y - y*v.x;
		}

		/**
		 * @brief      Calculates the squared distance from the given vector.
		 *
		 * @param[in]  v     Other vector.
		 *
		 * @return     Squared distance from `v`.
		 */
		[[nodiscard]]
		constexpr T distanceSq(const Vector2D& v) const noexcept
		{
			return (*this - v).lengthSq();
		}

		/**
		 * @brief      Calculates the distance from the given vector.
		 *
		 * @param[in]  v     Other vector.
		 *
		 * @return     Distance from `v`.
		 */
		[[nodiscard]]
		constexpr T distance(const Vector2D& v) const noexcept
		{
			return std::hypot(x - v.x, y - v.y);
		}

		/**
		 * @brief      Calculates the moved vector.
		 *
		 * @param[in]  dx    X-axis movement.
		 * @param[in]  dy    Y-axis movement.
		 *
		 * @return     The moved vector by `(dx, dy)`.
		 */
		[[nodiscard]]
		constexpr Vector2D movedBy(T dx, T dy) const noexcept
		{
			return { x + dx, y + dy };
		}

		/**
		 * @brief      Calculates the moved vector.
		 *
		 * @param[in]  v     Movement vector.
		 *
		 * @return     The moved vector by `v`.
		 */
		[[nodiscard]]
		constexpr Vector2D movedBy(const Vector2D& v) const noexcept
		{
			return movedBy(v.x, v.y);
		}

		/**
		 * @brief      Calculates the scaled vector.
		 *
		 * @param[in]  s     Scaling.
		 *
		 * @return     Scaled vector.
		 */
		[[nodiscard]]
		constexpr Vector2D scaled(T s) const noexcept
		{
			return scaled(s, s);
		}

		/**
		 * @brief      Calculates the scaled vector.
		 *
		 * @param[in]  sx    X-axis scaling.
		 * @param[in]  sy    Y-axis scaling.
		 *
		 * @return     Scaled vector.
		 */
		[[nodiscard]]
		constexpr Vector2D scaled(T sx, T sy) const noexcept
		{
			return { x * sx, y * sy };
		}

		/**
		 * @brief      Calculates the scaled vector.
		 *
		 * @param[in]  s     Scaling.
		 *
		 * @return     Scaled vector.
		 */
		[[nodiscard]]
		constexpr Vector2D scaled(const Vector2D<T>& s) const noexcept
		{
			return scaled(s.x, s.y);
		}

		/**
		 * @brief      Calculates the rotated vector.
		 *
		 * @param[in]  rotation  Rotation angle [rad].
		 *
		 * @return     The rotated vector.
		 */
		[[nodiscard]]
		Vector2D rotated(T rotation) const noexcept
		{
			return rotated(Rotation<T> {rotation});
		}

		/**
		 * @brief      Calculates the rotated vector.
		 *
		 * @param[in]  rotation  Rotation.
		 *
		 * @return     The rotated vector.
		 */
		[[nodiscard]]
		constexpr Vector2D rotated(const Rotation<T>& rotation) const noexcept
		{
			return { x*rotation.cos() - y*rotation.sin(), x*rotation.sin() + y*rotation.cos() };
		}

		/**
		 * @brief      Sets the vector value.
		 *
		 * @param[in]  _x    New x value.
		 * @param[in]  _y    New y value.
		 *
		 * @return     `*this`.
		 */
		constexpr Vector2D& set(T _x, T _y) noexcept
		{
			x = _x;
			y = _y;

			return *this;
		}

		/**
		 * @brief      Sets the vector value.
		 *
		 * @param[in]  v     New vector value.
		 *
		 * @return     `*this`.
		 */
		constexpr Vector2D& set(const Vector2D& v) noexcept
		{
			x = v.x;
			y = v.y;

			return *this;
		}

		/**
		 * @brief      Mirrors the vector if `doMirror == true`.
		 *
		 * @param[in]  doMirror  Mirroring flag.
		 *
		 * @return     `*this`.
		 */
		Vector2D& mirror(bool doMirror = true) noexcept
		{
			if (doMirror) x = -x;
			return *this;
		}

		/**
		 * @brief      Flips the vector if `doFlip == true`.
		 *
		 * @param[in]  doFlip  Mirroring flag.
		 *
		 * @return     `*this`.
		 */
		Vector2D& flip(bool doFlip= true) noexcept
		{
			if (doFlip) y = -y;
			return *this;
		}

		/**
		 * @brief      Normalizes the vector.
		 *
		 * @return     `*this`.
		 */
		Vector2D& normalize() noexcept
		{
			return *this /= length();
		}

		/**
		 * @brief      Sets the vector length.
		 *
		 * @param[in]  _length  New length.
		 *
		 * @return     `*this`.
		 */
		Vector2D& setLength(T _length) noexcept
		{
			return isZero() ? *this : (*this *= _length / length());
		}

		/**
		 * @brief      Moves the vector.
		 *
		 * @param[in]  dx    X-axis movement.
		 * @param[in]  dy    Y-axis movement.
		 *
		 * @return     `*this`.
		 */
		constexpr Vector2D& moveBy(T dx, T dy) noexcept
		{
			x += dx;
			y += dy;

			return *this;
		}

		/**
		 * @brief      Moves the vector.
		 *
		 * @param[in]  v     movement.
		 *
		 * @return     `*this`.
		 */
		constexpr Vector2D& moveBy(const Vector2D& v) noexcept
		{
			return moveBy(v.x, v.y);
		}

		/**
		 * @brief      Scales the vector.
		 *
		 * @param[in]  s     Scaling.
		 *
		 * @return     `*this`.
		 */
		constexpr Vector2D& scale(T s) noexcept
		{
			return scale(s, s);
		}

		/**
		 * @brief      Scales the vector.
		 *
		 * @param[in]  sx    X-axis scaling.
		 * @param[in]  sy    Y-axis scaling.
		 *
		 * @return     `*this`.
		 */
		constexpr Vector2D& scale(T sx, T sy) noexcept
		{
			x *= sx;
			y *= sy;

			return *this;
		}

		/**
		 * @brief      Scales the vector.
		 *
		 * @param[in]  s     scaling.
		 *
		 * @return     `*this`.
		 */
		constexpr Vector2D& scale(const Vector2D& s) noexcept
		{
			return scale(s.x, s.y);
		}

		/**
		 * @brief      Rotates the vector.
		 *
		 * @param[in]  rotation  Rotation angle [rad].
		 *
		 * @return     `*this`.
		 */
		Vector2D& rotate(T rotation) noexcept
		{
			return *this = rotated(rotation);
		}

		/**
		 * @brief      Rotates the vector.
		 *
		 * @param[in]  rotation  Rotation angle [rad].
		 *
		 * @return     `*this`.
		 */
		constexpr Vector2D& rotate(const Rotation<T>& rotation) noexcept
		{
			return *this = rotated(rotation);
		}

		/**
		 * @brief      Unary operator `+`.
		 *
		 * @return     `+(*this)`.
		 */
		[[nodiscard]]
		constexpr Vector2D operator+() const noexcept
		{
			return { +x, +y };
		}

		/**
		 * @brief      Unary operator `-`.
		 *
		 * @return     `-(*this)`.
		 */
		[[nodiscard]]
		constexpr Vector2D operator-() const noexcept
		{
			return { -x, -y };
		}

		/**
		 * @brief      Binary operator `=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this = a`.
		 */
		constexpr Vector2D& operator=(const Vector2D& a) noexcept =default;

		/**
		 * @brief      Binary operator `+=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this += a`.
		 */
		constexpr Vector2D& operator+=(const Vector2D& a) noexcept
		{
			x += a.x;
			y += a.y;

			return *this;
		}

		/**
		 * @brief      Binary operator `-=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this -= a`.
		 */
		constexpr Vector2D& operator-=(const Vector2D& a) noexcept
		{
			x -= a.x;
			y -= a.y;

			return *this;
		}

		/**
		 * @brief      Binary operator `*=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this *= a`.
		 */
		constexpr Vector2D& operator*=(T a) noexcept
		{
			x *= a;
			y *= a;

			return *this;
		}

		/**
		 * @brief      Binary operator `*=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this *= a`.
		 */
		constexpr Vector2D& operator*=(const Vector2D& a) noexcept
		{
			x *= a.x;
			y *= a.y;

			return *this;
		}

		/**
		 * @brief      Binary operator `*=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this *= a`.
		 */
		constexpr Vector2D& operator*=(const Matrix3x2<T>& a) noexcept;

		/**
		 * @brief      Binary operator `/=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this /= a`.
		 */
		constexpr Vector2D& operator/=(T a) noexcept
		{
			x /= a;
			y /= a;

			return *this;
		}

		/**
		 * @brief      Binary operator `/=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this /= a`.
		 */
		constexpr Vector2D& operator/=(const Vector2D& a) noexcept
		{
			x /= a.x;
			y /= a.y;

			return *this;
		}
	};

	/**
	 * @brief      Binary operator `+`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @tparam     T     Left hand side element type.
	 * @tparam     U     Right hand side element type.
	 *
	 * @return     `a + b`.
	 */
	template <typename T, typename U>
	[[nodiscard]]
	constexpr auto operator+(const Vector2D<T>& a, const Vector2D<U>& b) noexcept
		-> Vector2D<decltype(a.x + b.x)>
	{
		return { a.x + b.x, a.y + b.y };
	}

	/**
	 * @brief      Binary operator `-`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @tparam     T     Left hand side element type.
	 * @tparam     U     Right hand side element type.
	 *
	 * @return     `a - b`.
	 */
	template <typename T, typename U>
	[[nodiscard]]
	constexpr auto operator-(const Vector2D<T>& a, const Vector2D<U>& b) noexcept
		-> Vector2D<decltype(a.x - b.x)>
	{
		return { a.x - b.x, a.y - b.y };
	}

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @tparam     T     Left hand side element type.
	 * @tparam     U     Right hand side type.
	 *
	 * @return     `a * b`.
	 */
	template <typename T, typename U>
	[[nodiscard]]
	constexpr auto operator*(const Vector2D<T>& a, U b) noexcept
		-> Vector2D<decltype(a.x * b)>
	{
		return { a.x * b, a.y * b };
	}

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @tparam     T     Left hand side type.
	 * @tparam     U     Right hand side element type.
	 *
	 * @return     `a * b`.
	 */
	template <typename T, typename U>
	[[nodiscard]]
	constexpr auto operator*(T a, const Vector2D<U>& b) noexcept
		-> Vector2D<decltype(a * b.x)>
	{
		return { a * b.x, a * b.y };
	}

	/**
	 * @brief      Binary operator `*`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @tparam     T     Left hand side element type.
	 * @tparam     U     Right hand side element type.
	 *
	 * @return     `a * b`.
	 */
	template <typename T, typename U>
	[[nodiscard]]
	constexpr auto operator*(const Vector2D<T>& a, const Vector2D<U>& b) noexcept
		-> Vector2D<decltype(a.x * b.x)>
	{
		return { a.x * b.x, a.y * b.y };
	}

	/**
	 * @brief      Binary operator `/`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @tparam     T     Left hand side element type.
	 * @tparam     U     Right hand side type.
	 *
	 * @return     `a / b`.
	 */
	template <typename T, typename U>
	[[nodiscard]]
	constexpr auto operator/(const Vector2D<T>& a, U b) noexcept
		-> Vector2D<decltype(a.x / b)>
	{
		return { a.x / b, a.y / b };
	}

	/**
	 * @brief      Binary operator `/`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @tparam     T     Left hand side element type.
	 * @tparam     U     Right hand side element type.
	 *
	 * @return     `a / b`.
	 */
	template <typename T, typename U>
	[[nodiscard]]
	constexpr auto operator/(const Vector2D<T>& a, const Vector2D<U>& b) noexcept
		-> Vector2D<decltype(a.x / b.x)>
	{
		return { a.x / b.x, a.y / b.y };
	}

	/**
	 * @brief      Binary operator `==`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @tparam     T     Element type.
	 *
	 * @return     `a == b`.
	 */
	template <typename T>
	[[nodiscard]]
	constexpr bool operator==(const Vector2D<T>& a, const Vector2D<T>& b) noexcept
	{
		return a.x == b.x && a.y == b.y;
	}

	/**
	 * @brief      Binary operator `!=`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @tparam     T     Element type.
	 *
	 * @return     `a != b`.
	 */
	template <typename T>
	[[nodiscard]]
	constexpr bool operator!=(const Vector2D<T>& a, const Vector2D<T>& b) noexcept
	{
		return !(a == b);
	}

	using Vector2Di = Vector2D<Int32>;
	using Vector2Df = Vector2D<Float32>;
	using Vector2Dd = Vector2D<Float64>;
}

#endif  // #ifndef INCLUDE_NENE_VECTOR2D_HPP
