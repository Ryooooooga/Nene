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

#ifndef INCLUDE_NENE_VERTEX2D_HPP
#define INCLUDE_NENE_VERTEX2D_HPP

#include "Color.hpp"
#include "Vector2D.hpp"

namespace Nene
{
	/**
	 * @brief      2D vertex.
	 */
	class Vertex2D
	{
	public:
		Vector2Df position;
		Color     color;
		Vector2Df uv;

		/**
		 * @brief      Default constructor.
		 */
		constexpr Vertex2D() noexcept =default;

		/**
		 * @brief      Copy constructor.
		 */
		constexpr Vertex2D(const Vertex2D&) noexcept =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  position  The vertex location.
		 * @param[in]  color     The vertex color.
		 * @param[in]  uv        The vertex texture UV position.
		 */
		constexpr Vertex2D(const Vector2Df& position, const Color& color, const Vector2Df& uv = Vector2Df::zero()) noexcept
			: position(position), color(color), uv(uv) {}

		/**
		 * @brief      Destructor.
		 */
		~Vertex2D() =default;
	};
}

#endif  // #ifndef INCLUDE_NENE_VERTEX2D_HPP
