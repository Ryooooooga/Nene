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

#ifndef INCLUDE_NENE_GRAPHICS_IPIXELSHADER_HPP
#define INCLUDE_NENE_GRAPHICS_IPIXELSHADER_HPP

#include "../ArrayView.hpp"

namespace Nene
{
	/**
	 * @brief      Pixel shader interface.
	 */
	class IPixelShader
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		IPixelShader() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IPixelShader() =default;

		/**
		 * @brief      Returns the compiled pixel shader binary.
		 *
		 * @return     The compilex pixel shader binary.
		 */
		[[nodiscard]]
		virtual ByteArrayView compiledBinary() const noexcept =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_IPIXELSHADER_HPP