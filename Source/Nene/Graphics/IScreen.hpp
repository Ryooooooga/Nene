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

#ifndef INCLUDE_GRAPHICS_ISCREEN_HPP
#define INCLUDE_GRAPHICS_ISCREEN_HPP

namespace Nene
{
	// Forward declarations.
	class IDynamicTexture;
	class IWindow;

	/**
	 * @brief      Screen interface.
	 */
	class IScreen
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		IScreen() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IScreen() =default;

		/**
		 * @brief      Returns the render target window.
		 *
		 * @return     The render target window.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IWindow> window() const =0;

		/**
		 * @brief      Returns the render target texture.
		 *
		 * @return     The render target texture.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IDynamicTexture> renderTarget() const =0;
	};
}

#endif  // #ifndef INCLUDE_GRAPHICS_ISCREEN_HPP
