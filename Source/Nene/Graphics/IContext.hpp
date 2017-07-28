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

#ifndef INCLUDE_NENE_GRAPHICS_ICONTEXT_HPP
#define INCLUDE_NENE_GRAPHICS_ICONTEXT_HPP

#include <memory>
#include "../Color.hpp"

namespace Nene
{
	// Forward declarations.
	class IDynamicTexture;
	class IIndexBuffer;
	class IPixelShader;
	class IScreen;
	class ITexture;
	class IVertexBuffer;
	class IVertexShader;

	/**
	 * @brief      Graphics context interface.
	 */
	class IContext
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		IContext() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IContext() =default;

		/**
		 * @brief      Excutes all rendering commands.
		 *
		 * @return     `*this`.
		 */
		virtual IContext& flush() =0;

		/**
		 * @brief      Presents the screen.
		 *
		 * @param[in]  screen  The screen instance.
		 *
		 * @return     `*this`.
		 */
		virtual IContext& present(const std::shared_ptr<IScreen>& screen) =0;

		/**
		 * @brief      Clears the dynamic texture.
		 *
		 * @param[in]  texture     The dynamic texture to clear.
		 * @param[in]  clearColor  The clear color.
		 *
		 * @return     `*this`.
		 */
		virtual IContext& clear(const std::shared_ptr<IDynamicTexture>& texture, const Color4f& clearColor) =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_ICONTEXT_HPP
