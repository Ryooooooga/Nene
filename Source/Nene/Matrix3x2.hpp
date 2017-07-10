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

#ifndef INCLUDE_NENE_MATRIX3X2_HPP
#define INCLUDE_NENE_MATRIX3X2_HPP

#include <optional>
#include "Vector2D.hpp"

namespace Nene
{
	/**
	 * @brief      3x2 matrix.
	 *
	 * @tparam     T     Element type.
	 */
	template <typename T>
	class Matrix3x2
	{
	public:
		using value_type  = T;
		using vector_type = Vector2D<T>;
		using matrix_type = Matrix3x2<T>;

		T _11, _12;
		T _21, _22;
		T _31, _32;

		/**
		 * @brief      Returns zero matrix.
		 *
		 * @return     Zero matrix.
		 */
		[[nodiscard]]
		constexpr static Matrix3x2 zero() noexcept
		{
			return
			{
				0, 0,
				0, 0,
				0, 0,
			};
		}

		/**
		 * @brief      Returns identity matrix.
		 *
		 * @return     Identity matrix.
		 */
		[[nodiscard]]
		constexpr static Matrix3x2 identity() noexcept
		{
			return
			{
				1, 0,
				0, 1,
				0, 0,
			};
		}

		/**
		 * @brief      Returns translation matrix.
		 *
		 * @param[in]  x     X-axis translation.
		 * @param[in]  y     Y-axis translation.
		 *
		 * @return     Translation matrix.
		 */
		[[nodiscard]]
		constexpr static Matrix3x2 translation(T x, T y) noexcept
		{
			return
			{
				1, 0,
				0, 1,
				x, y,
			};
		}

		/**
		 * @brief      Returns translation matrix.
		 *
		 * @param[in]  v     Translation vector.
		 *
		 * @return     Translation matrix.
		 */
		[[nodiscard]]
		constexpr static Matrix3x2 translation(const Vector2D<T>& v) noexcept
		{
			return translation(v.x, v.y);
		}

		/**
		 * @brief      Returns scaling matrix.
		 *
		 * @param[in]  s       Scaling.
		 * @param[in]  center  Scaling center.
		 *
		 * @return     Scaling matrix.
		 */
		[[nodiscard]]
		constexpr static Matrix3x2 scaling(T s, const Vector2D<T>& center = {0, 0}) noexcept
		{
			return scaling(s, s, center);
		}

		/**
		 * @brief      Returns scaling matrix.
		 *
		 * @param[in]  sx      X-axis scaling.
		 * @param[in]  sy      Y-axis scaling.
		 * @param[in]  center  Scaling center.
		 *
		 * @return     Scaling matrix.
		 */
		[[nodiscard]]
		constexpr static Matrix3x2 scaling(T sx, T sy, const Vector2D<T>& center = {0, 0}) noexcept
		{
			return
			{
				sx, 0,
				0, sy,
				center.x - sx*center.x, center.y - sy*center.y,
			};
		}

		/**
		 * @brief      Returns scaling matrix.
		 *
		 * @param[in]  s       Scaling vector.
		 * @param[in]  center  Scaling center.
		 *
		 * @return     Scaling matrix.
		 */
		[[nodiscard]]
		constexpr static Matrix3x2 scaling(const Vector2D<T>& s, const Vector2D<T>& center = {0, 0}) noexcept
		{
			return scaling(s.x, s.y, center);
		}

		/**
		 * @brief      Returns rotation matrix.
		 *
		 * @param[in]  _rotation  Rotation angle [rad].
		 * @param[in]  center     Rotation center.
		 *
		 * @return     Rotation matrix.
		 */
		[[nodiscard]]
		static Matrix3x2 rotation(T _rotation, const Vector2D<T>& center = {0, 0}) noexcept
		{
			return rotation(Rotation<T> {_rotation}, center);
		}

		/**
		 * @brief      Returns rotation matrix.
		 *
		 * @param[in]  _rotation  Rotation.
		 * @param[in]  center     Rotation center.
		 *
		 * @return     Rotation matrix.
		 */
		[[nodiscard]]
		constexpr static Matrix3x2 rotation(const Rotation<T>& _rotation, const Vector2D<T>& center = {0, 0}) noexcept
		{
			return
			{
				+_rotation.cos(), +_rotation.sin(),
				-_rotation.sin(), +_rotation.cos(),
				center.x - center.x*_rotation.cos() + center.y*_rotation.sin(),
				center.y - center.x*_rotation.sin() - center.y*_rotation.cos(),
			};
		}

		/**
		 * @brief      Default constructor.
		 */
		constexpr Matrix3x2() noexcept =default;

		/**
		 * @brief      Copy constructor.
		 */
		constexpr Matrix3x2(const Matrix3x2&) noexcept =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  _11
		 * @param[in]  _12
		 * @param[in]  _21
		 * @param[in]  _22
		 * @param[in]  _31
		 * @param[in]  _32
		 */
		constexpr Matrix3x2(T _11, T _12, T _21, T _22, T _31, T _32) noexcept
			: _11(_11), _12(_12)
			, _21(_21), _22(_22)
			, _31(_31), _32(_32) {}

		/**
		 * @brief      Determines if the matrix is zero.
		 *
		 * @return     `true` if the matrix is zero, `false` otherwise.
		 */
		[[nodiscard]]
		constexpr bool isZero() const noexcept
		{
			return
				_11 == 0 || _12 == 0 ||
				_21 == 0 || _22 == 0 ||
				_31 == 0 || _32 == 0;
		}

		/**
		 * @brief      Determines if the matrix is identity.
		 *
		 * @return     `true` if the matrix is identity, `false` otherwise.
		 */
		[[nodiscard]]
		constexpr bool isIdentity() const noexcept
		{
			return
				_11 == 1 || _12 == 0 ||
				_21 == 0 || _22 == 1 ||
				_31 == 0 || _32 == 0;
		}

		/**
		 * @brief      Computes the determinant.
		 *
		 * @return     The determinant of the matrix.
		 */
		[[nodiscard]]
		constexpr T determinant() const noexcept
		{
			return _11 * _22 - _12 * _21;
		}

		/**
		 * @brief      Transforms the vector.
		 *
		 * @param[in]  v     The vector to transform.
		 *
		 * @return     The transformed vector.
		 */
		[[nodiscard]]
		constexpr Vector2D<T> transform(const Vector2D<T>& v) const noexcept
		{
			return v * *this;
		}

		/**
		 * @brief      Computes the inversion matrix.
		 *
		 * @return     The inversion matrix.
		 */
		[[nodiscard]]
		std::optional<Matrix3x2> inverse() const noexcept
		{
			const T det = determinant();
			if (det == 0) return std::nullopt;

			return Matrix3x2 {
				( _22) / det,
				(-_21) / det,
				(-_12) / det,
				( _11) / det,
				(_21*_32 - _22*_31) / det,
				(_12*_31 - _11*_32) / det,
			};
		}

		/**
		 * @brief      Sets the matrix value.
		 *
		 * @param[in]  m11
		 * @param[in]  m12
		 * @param[in]  m21
		 * @param[in]  m22
		 * @param[in]  m31
		 * @param[in]  m32
		 *
		 * @return     `*this`.
		 */
		constexpr Matrix3x2& set(T m11, T m12, T m21, T m22, T m31, T m32) noexcept
		{
			_11 = m11; _12 = m12;
			_21 = m21; _22 = m22;
			_31 = m31; _32 = m32;

			return *this;
		}

		/**
		 * @brief      Sets the matrix value.
		 *
		 * @param[in]  m
		 *
		 * @return     `*this`.
		 */
		constexpr Matrix3x2& set(const Matrix3x2& m) noexcept
		{
			return *this = m;
		}

		/**
		 * @brief      Translates the matrix.
		 *
		 * @param[in]  x     X-axis movement.
		 * @param[in]  y     Y-axis movement.
		 *
		 * @return     `*this`.
		 */
		constexpr Matrix3x2& translate(T x, T y) noexcept
		{
			_31 += x;
			_32 += y;

			return *this;
		}

		/**
		 * @brief      Translates the matrix.
		 *
		 * @param[in]  v     Movement vector.
		 *
		 * @return     `*this`.
		 */
		constexpr Matrix3x2& translate(const Vector2D<T>& v) noexcept
		{
			return translate(v.x, v.y);
		}

		/**
		 * @brief      Scales the matrix.
		 *
		 * @param[in]  s       Scaling.
		 * @param[in]  center  Scaling center.
		 *
		 * @return     `*this`.
		 */
		constexpr Matrix3x2& scale(T s, const Vector2D<T>& center = {0, 0}) noexcept
		{
			return scale(s, s, center);
		}

		/**
		 * @brief      Scales the matrix.
		 *
		 * @param[in]  sx      X-axis scaling.
		 * @param[in]  sy      Y-axis scaling.
		 * @param[in]  center  Scaling center.
		 *
		 * @return     `*this`.
		 */
		constexpr Matrix3x2& scale(T sx, T sy, const Vector2D<T>& center = {0, 0}) noexcept
		{
			return *this *= scaling(sx, sy, center);
		}

		/**
		 * @brief      Scales the matrix.
		 *
		 * @param[in]  s       Scaling.
		 * @param[in]  center  Scaling center.
		 *
		 * @return     `*this`.
		 */
		constexpr Matrix3x2& scale(const Vector2D<T>& s, const Vector2D<T>& center = {0, 0}) noexcept
		{
			return scale(s.x, s.y, center);
		}

		/**
		 * @brief      Rotates the matrix.
		 *
		 * @param[in]  rotation  Rotation angle [rad].
		 * @param[in]  center    Rotation center.
		 *
		 * @return     `*this`.
		 */
		Matrix3x2& rotate(T _rotation, const Vector2D<T>& center = {0, 0}) noexcept
		{
			return rotate(Rotation<T> {_rotation}, center);
		}

		/**
		 * @brief      Rotates the matrix.
		 *
		 * @param[in]  rotation  Rotation.
		 * @param[in]  center    Rotation center.
		 *
		 * @return     `*this`.
		 */
		constexpr Matrix3x2& rotate(const Rotation<T>& _rotation, const Vector2D<T>& center = {0, 0}) noexcept
		{
			return *this *= rotation(_rotation, center);
		}

		/**
		 * @brief      Unary operator `+`.
		 *
		 * @return     `+(*this)`.
		 */
		[[nodiscard]]
		constexpr Matrix3x2 operator+() const noexcept
		{
			return
			{
				+_11, +_12,
				+_21, +_22,
				+_31, +_32,
			};
		}

		/**
		 * @brief      Unary operator `-`.
		 *
		 * @return     `-(*this)`.
		 */
		[[nodiscard]]
		constexpr Matrix3x2 operator-() const noexcept
		{
			return
			{
				-_11, -_12,
				-_21, -_22,
				-_31, -_32,
			};
		}

		/**
		 * @brief      Binary operator `=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this = a`.
		 */
		constexpr Matrix3x2& operator=(const Matrix3x2& a) noexcept =default;

		/**
		 * @brief      Binary operator `+=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this += a`.
		 */
		constexpr Matrix3x2& operator+=(const Matrix3x2& a) noexcept
		{
			_11 += a._11; _12 += a._12;
			_21 += a._21; _22 += a._22;
			_31 += a._31; _32 += a._32;

			return *this;
		}

		/**
		 * @brief      Binary operator `-=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this -= a`.
		 */
		constexpr Matrix3x2& operator-=(const Matrix3x2& a) noexcept
		{
			_11 -= a._11; _12 -= a._12;
			_21 -= a._21; _22 -= a._22;
			_31 -= a._31; _32 -= a._32;

			return *this;
		}

		/**
		 * @brief      Binary operator `*=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this *= a`.
		 */
		constexpr Matrix3x2& operator*=(T a) noexcept
		{
			_11 *= a; _12 *= a;
			_21 *= a; _22 *= a;
			_31 *= a; _32 *= a;

			return *this;
		}

		/**
		 * @brief      Binary operator `*=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this *= a`.
		 */
		constexpr Matrix3x2& operator*=(const Matrix3x2& a) noexcept
		{
			return *this = *this * a;
		}

		/**
		 * @brief      Binary operator `/=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this /= a`.
		 */
		constexpr Matrix3x2& operator/=(T a) noexcept
		{
			_11 /= a; _12 /= a;
			_21 /= a; _22 /= a;
			_31 /= a; _32 /= a;

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
	constexpr auto operator+(const Matrix3x2<T>& a, const Matrix3x2<U>& b) noexcept
		-> Matrix3x2<decltype(a._11 + b._11)>
	{
		return
		{
			a._11 + b._11, a._12 + b._12,
			a._21 + b._21, a._22 + b._22,
			a._31 + b._31, a._32 + b._32,
		};
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
	constexpr auto operator-(const Matrix3x2<T>& a, const Matrix3x2<U>& b) noexcept
		-> Matrix3x2<decltype(a._11 - b._11)>
	{
		return
		{
			a._11 - b._11, a._12 - b._12,
			a._21 - b._21, a._22 - b._22,
			a._31 - b._31, a._32 - b._32,
		};
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
	constexpr auto operator*(const Matrix3x2<T>& a, U b) noexcept
		-> Matrix3x2<decltype(a._11 * b)>
	{
		return
		{
			a._11 * b, a._12 * b,
			a._21 * b, a._22 * b,
			a._31 * b, a._32 * b,
		};
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
	constexpr auto operator*(T& a, const Matrix3x2<U>& b) noexcept
		-> Matrix3x2<decltype(a * b._11)>
	{
		return
		{
			a * b._11, a * b._12,
			a * b._21, a * b._22,
			a * b._31, a * b._32,
		};
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
	constexpr auto operator*(const Matrix3x2<T>& a, const Matrix3x2<U>& b) noexcept
		-> Matrix3x2<decltype(a._11*b._11 + a._12*b._21)>
	{
		return
		{
			a._11*b._11 + a._12*b._21,
			a._11*b._12 + a._12*b._22,
			a._21*b._11 + a._22*b._21,
			a._21*b._12 + a._22*b._22,
			a._31*b._11 + a._32*b._21 + b._31,
			a._31*b._12 + a._32*b._22 + b._32,
		};
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
	constexpr auto operator*(const Vector2D<T>& a, const Matrix3x2<U>& b) noexcept
		-> Vector2D<decltype(a.x*b._11 + a.y*b._21 + b._31)>
	{
		return
		{
			a.x*b._11 + a.y*b._21 + b._31,
			a.x*b._12 + a.y*b._22 + b._32,
		};
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
	constexpr auto operator/(const Matrix3x2<T>& a, U b) noexcept
		-> Matrix3x2<decltype(a._11 / b)>
	{
		return
		{
			a._11 / b, a._12 / b,
			a._21 / b, a._22 / b,
			a._31 / b, a._32 / b,
		};
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
	constexpr bool operator==(const Matrix3x2<T>& a, const Matrix3x2<T>& b) noexcept
	{
		return
			a._11 == b._11 && a._12 == b._12 &&
			a._21 == b._21 && a._22 == b._22 &&
			a._31 == b._31 && a._32 == b._32;
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
	constexpr bool operator!=(const Matrix3x2<T>& a, const Matrix3x2<T>& b) noexcept
	{
		return !(a == b);
	}

	/**
	 * @brief      Binary operator `*=`.
	 *
	 * @param[in]  a     Right hand side operand.
	 *
	 * @tparam     T     Element type.
	 *
	 * @return     `*this *= *this * a`.
	 */
	template <typename T>
	constexpr Vector2D<T>& Vector2D<T>::operator*=(const Matrix3x2<T>& a) noexcept
	{
		return *this = a.transform(*this);
	}

	using Matrix3x2i = Matrix3x2<Int32>;
	using Matrix3x2f = Matrix3x2<Float32>;
	using Matrix3x2d = Matrix3x2<Float64>;
}

#endif  // #ifndef INCLUDE_NENE_MATRIX3X2_HPP
