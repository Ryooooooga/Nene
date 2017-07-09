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

#ifndef INCLUDE_NENE_ENGINE_IENGINE_HPP
#define INCLUDE_NENE_ENGINE_IENGINE_HPP

#include <memory>
#include <string>
#include "../Size2D.hpp"

namespace Nene
{
	// Forward declarations.
	class IGraphics;
	class IWindow;
	class Logger;

	/**
	 * @brief      Engine interface.
	 */
	class IEngine
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		IEngine() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IEngine() =default;

		/**
		 * @brief      Returns the logger.
		 *
		 * @return     The logger instance.
		 */
		[[nodiscard]]
		virtual const std::shared_ptr<Logger>& logger() const noexcept =0;

		/**
		 * @brief      Returns the graphics.
		 *
		 * @return     The graphics instance.
		 */
		[[nodiscard]]
		virtual const std::shared_ptr<IGraphics>& graphics() const noexcept =0;

		/**
		 * @brief      Creates a new window instance.
		 *
		 * @param[in]  title  The title of the window.
		 * @param[in]  size   The client area size of the window.
		 *
		 * @return     The new window instance.
		 */
		[[nodiscard]]
		virtual std::shared_ptr<IWindow> window(const std::string& title, const Size2Di& size) =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_ENGINE_IENGINE_HPP
