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

#ifndef INCLUDE_NENE_GEOMETRY_LINE2D_HPP
#define INCLUDE_NENE_GEOMETRY_LINE2D_HPP

#include "../Vector2D.hpp"

namespace Nene
{
	/**
	 * @brief      Line geometry.
	 *
	 * @tparam     T     Element type.
	 */
	template <typename T>
	class Line2D
	{
	public:
		using value_type  = T;
		using vector_type = Vector2D<T>;

		vector_type p1, p2;

		/**
		 * @brief      Constructor.
		 */
		constexpr Line2D() noexcept =default;

		/**
		 * @brief      Copy constructor.
		 */
		constexpr Line2D(const Line2D&) noexcept =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  x1
		 * @param[in]  y1
		 * @param[in]  x2
		 * @param[in]  y2
		 */
		constexpr Line2D(T x1, T y1, T x2, T y2) noexcept
			: p1(x1, y1), p2(x2, y2) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  p1
		 * @param[in]  p2
		 */
		constexpr Line2D(const vector_type& p1, const vector_type& p2) noexcept
			: p1(p1), p2(p2) {}

		/**
		 * @brief      Destructor.
		 */
		~Line2D() =default;

		/**
		 * @brief      Computes squared length of the line.
		 *
		 * @return     Squared length of the line.
		 */
		[[nodiscard]]
		constexpr T lengthSq() const noexcept
		{
			return p1.distanceSq(p2);
		}

		/**
		 * @brief      Computes length of the line.
		 *
		 * @return     Length of the line.
		 */
		[[nodiscard]]
		T length() const noexcept
		{
			return p1.distance(p2);
		}

		/**
		 * @brief      Returns the center location of the line.
		 *
		 * @return     The center location of the line.
		 */
		[[nodiscard]]
		constexpr vector_type center() const noexcept
		{
			return (p1 + p2) / 2;
		}

		/**
		 * @brief      Copy operator `=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this = a`.
		 */
		constexpr Line2D& operator=(const Line2D& a) noexcept =default;
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
	constexpr bool operator==(const Line2D<T>& a, const Line2D<T>& b) noexcept
	{
		return a.p1 == b.p1 && a.p2 == b.p2;
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
	constexpr bool operator!=(const Line2D<T>& a, const Line2D<T>& b) noexcept
	{
		return !(a == b);
	}

	using Line2Di = Line2D<Int32>;
	using Line2Df = Line2D<Float32>;
	using Line2Dd = Line2D<Float64>;
}

#endif  // #ifndef INCLUDE_NENE_GEOMETRY_LINE2D_HPP
