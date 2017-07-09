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

#ifndef INCLUDE_NENE_ROTATION_HPP
#define INCLUDE_NENE_ROTATION_HPP

#include <cmath>
#include <cstdint>

namespace Nene
{
	/**
	 * @brief      Rotation.
	 *
	 * @tparam     T     Element type.
	 */
	template <typename T>
	class Rotation
	{
		T cos_, sin_;

		constexpr explicit Rotation(T cos, T sin) noexcept
			: cos_(cos), sin_(sin) {}

	public:
		using value_type    = T;
		using rotation_type = Rotation<T>;

		/**
		 * @brief      Returns 0 deg rotation.
		 *
		 * @return     0 deg rotation.
		 */
		[[nodiscard]]
		constexpr static Rotation forward() noexcept
		{
			return Rotation { 1, 0 };
		}

		/**
		 * @brief      Returns 90 deg rotation.
		 *
		 * @return     90 deg rotation.
		 */
		[[nodiscard]]
		constexpr static Rotation right() noexcept
		{
			return Rotation { 0, 1 };
		}

		/**
		 * @brief      Returns 180 deg rotation.
		 *
		 * @return     180 deg rotation.
		 */
		[[nodiscard]]
		constexpr static Rotation backward() noexcept
		{
			return Rotation { -1, 0 };
		}

		/**
		 * @brief      Returns 270 deg rotation.
		 *
		 * @return     270 deg rotation.
		 */
		[[nodiscard]]
		constexpr static Rotation left() noexcept
		{
			return Rotation { 0, -1 };
		}

		/**
		 * @brief      Default constructor.
		 */
		constexpr Rotation() noexcept
			: Rotation(1, 0) {}

		/**
		 * @brief      Copy constructor.
		 */
		constexpr Rotation(const Rotation&) noexcept =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  angle  Rotation angle [rad].
		 */
		constexpr Rotation(T angle) noexcept
			: Rotation(std::cos(angle), std::sin(angle)) {}

		/**
		 * @brief      Destructor.
		 */
		~Rotation() =default;

		/**
		 * @brief      Returns cosine.
		 *
		 * @return     Cosine.
		 */
		[[nodiscard]]
		constexpr T cos() const noexcept
		{
			return cos_;
		}

		/**
		 * @brief      Returns sine.
		 *
		 * @return     Sine.
		 */
		[[nodiscard]]
		constexpr T sin() const noexcept
		{
			return sin_;
		}

		/**
		 * @brief      Returns tangent.
		 *
		 * @return     Tangent.
		 */
		[[nodiscard]]
		constexpr T tan() const noexcept
		{
			return sin_ / cos_;
		}

		/**
		 * @brief      Calculates the rotation angle.
		 *
		 * @return     The rotation angle.
		 */
		[[nodiscard]]
		T angle() const noexcept
		{
			return std::atan2(sin, cos);
		}

		/**
		 * @brief      Calculated the turned rotation.
		 *
		 * @param[in]  rotation  Rotation.
		 *
		 * @return     Turned rotation.
		 */
		[[nodiscard]]
		Rotation rotated(T rotation) const noexcept
		{
			return rotated(Rotation { rotation });
		}

		/**
		 * @brief      Calculated the turned rotation.
		 *
		 * @param[in]  rotation  Rotation.
		 *
		 * @return     Turned rotation.
		 */
		[[nodiscard]]
		constexpr Rotation rotated(const Rotation& rotation) const noexcept
		{
			return { cos_ * rotation.cos_ - sin_ * rotation.sin_, cos_ * rotation.sin_ + sin_ * rotation.cos_ };
		}

		/**
		 * @brief      Sets the rotation value.
		 *
		 * @param[in]  rotation  New rotation.
		 *
		 * @return     `*this`.
		 */
		constexpr Rotation& set(T rotation) noexcept
		{
			return set(Rotation { rotation });
		}

		/**
		 * @brief      Sets the rotation value.
		 *
		 * @param[in]  rotation  New rotation.
		 *
		 * @return     `*this`.
		 */
		constexpr Rotation& set(const Rotation& rotation) noexcept
		{
			cos_ = rotation.cos_;
			sin_ = rotation.sin_;

			return *this;
		}

		/**
		 * @brief      Unary operator `+`.
		 *
		 * @return     `+(*this)`.
		 */
		[[nodiscard]]
		constexpr Rotation operator+() const noexcept
		{
			return { cos_, +sin_ };
		}

		/**
		 * @brief      Unary operator `-`.
		 *
		 * @return     `-(*this)`.
		 */
		[[nodiscard]]
		constexpr Rotation operator-() const noexcept
		{
			return { cos_, -sin_ };
		}

		/**
		 * @brief      Binary operator `=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this = a`.
		 */
		constexpr Rotation& operator=(const Rotation& a) =default;

		/**
		 * @brief      Binary operator `+=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this += a`.
		 */
		constexpr Rotation& operator+=(const Rotation& a)
		{
			return *this = *this + a;
		}

		/**
		 * @brief      Binary operator `-=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this -= a`.
		 */
		constexpr Rotation& operator-=(const Rotation& a)
		{
			return *this = *this - a;
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
	template <typename T>
	[[nodiscard]]
	constexpr Rotation<T> operator+(const Rotation<T>& a, const Rotation<T>& b) noexcept
	{
		return a.rotated(b);
	}

	/**
	 * @brief      Binary operator `-`.
	 *
	 * @param[in]  a     Left hand side operand.
	 * @param[in]  b     Right hand side operand.
	 *
	 * @return     `a - b`.
	 */
	template <typename T>
	[[nodiscard]]
	constexpr Rotation<T> operator-(const Rotation<T>& a, const Rotation<T>& b) noexcept
	{
		return a.rotated(-b);
	}

	using Rotationi = Rotation<std::int32_t>;
	using Rotationf = Rotation<float>;
	using Rotationd = Rotation<double>;
}

#endif  // #ifndef INCLUDE_NENE_ROTATION_HPP
