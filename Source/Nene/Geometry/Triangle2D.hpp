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

#ifndef INCLUDE_NENE_GEOMETRY_TRIANGLE2D_HPP
#define INCLUDE_NENE_GEOMETRY_TRIANGLE2D_HPP

#include <cmath>
#include "../Vector2D.hpp"

namespace Nene
{
	/**
	 * @brief      Triangle geometry.
	 *
	 * @tparam     T     Element type.
	 */
	template <typename T>
	class Triangle2D
	{
	public:
		using value_type  = T;
		using vector_type = Vector2D<T>;

		vector_type p1, p2, p3;

		/**
		 * @brief      Constructor.
		 */
		constexpr Triangle2D() noexcept =default;

		/**
		 * @brief      Copy constructor.
		 */
		constexpr Triangle2D(const Triangle2D&) noexcept =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  x1
		 * @param[in]  y1
		 * @param[in]  x2
		 * @param[in]  y2
		 * @param[in]  x3
		 * @param[in]  y3
		 */
		constexpr Triangle2D(T x1, T y1, T x2, T y2, T x3, T y3) noexcept
			: p1(x1, y1), p2(x2, y2), p3(x3, y3) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  p1
		 * @param[in]  p2
		 * @param[in]  p3
		 */
		constexpr Triangle2D(const vector_type& p1, const vector_type& p2, const vector_type& p3) noexcept
			: p1(p1), p2(p2), p3(p3) {}

		/**
		 * @brief      Destructor.
		 */
		~Triangle2D() =default;

		/**
		 * @brief      Computes area of the triangle.
		 *
		 * @return     Area of the triangle.
		 */
		[[nodiscard]]
		constexpr T area() const noexcept
		{
			return std::abs((p2 - p1).cross(p3 - p1)) / 2;
		}

		/**
		 * @brief      Returns the center location of the triangle.
		 *
		 * @return     The center location of the triangle.
		 */
		[[nodiscard]]
		constexpr vector_type center() const noexcept
		{
			return (p1 + p2 + p3) / 3;
		}

		/**
		 * @brief      Copy operator `=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this = a`.
		 */
		constexpr Triangle2D& operator=(const Triangle2D& a) noexcept =default;
	};

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
	constexpr bool operator==(const Triangle2D<T>& a, const Triangle2D<T>& b) noexcept
	{
		return a.p1 == b.p1 && a.p2 == b.p2 && a.p3 == b.p3;
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
	constexpr bool operator!=(const Triangle2D<T>& a, const Triangle2D<T>& b) noexcept
	{
		return !(a == b);
	}

	using Triangle2Di = Triangle2D<Int32>;
	using Triangle2Df = Triangle2D<Float32>;
	using Triangle2Dd = Triangle2D<Float64>;
}

#endif  // #ifndef INCLUDE_NENE_GEOMETRY_TRIANGLE2D_HPP
