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

#ifndef INCLUDE_NENE_GEOMETRY_CIRCLE_HPP
#define INCLUDE_NENE_GEOMETRY_CIRCLE_HPP

#include "../Vector2D.hpp"
#include "../Math/Constants.hpp"

namespace Nene
{
	/**
	 * @brief      Circle geometry.
	 *
	 * @tparam     T     Element type.
	 */
	template <typename T>
	class Circle
	{
	public:
		using value_type  = T;
		using vector_type = Vector2D<T>;

		vector_type center;
		value_type  radius;

		/**
		 * @brief      Default constructor.
		 */
		constexpr Circle() noexcept =default;

		/**
		 * @brief      Copy constructor.
		 */
		constexpr Circle(const Circle&) noexcept =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  x
		 * @param[in]  y
		 * @param[in]  radius
		 */
		constexpr Circle(T x, T y, T radius) noexcept
			: center(x, y), radius(radius) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  center
		 * @param[in]  radius
		 */
		constexpr Circle(const vector_type& center, T radius) noexcept
			: center(center), radius(radius) {}

		/**
		 * @brief      Destructor.
		 */
		~Circle() =default;

		/**
		 * @brief      Computes area of the circle.
		 *
		 * @return     Area of the circle.
		 */
		[[nodiscard]]
		constexpr T area() const noexcept
		{
			return radius * radius * Math::pi<T>;
		}

		/**
		 * @brief      Copy operator `=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this = a`.
		 */
		constexpr Circle& operator=(const Circle& a) noexcept =default;
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
	constexpr bool operator==(const Circle<T>& a, const Circle<T>& b) noexcept
	{
		return a.position == b.position && a.radius == b.radius;
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
	constexpr bool operator!=(const Circle<T>& a, const Circle<T>& b) noexcept
	{
		return !(a == b);
	}

	using Circlei = Circle<Int32>;
	using Circlef = Circle<Float32>;
	using Circled = Circle<Float64>;
}

#endif  // #ifndef INCLUDE_NENE_GEOMETRY_CIRCLE_HPP
