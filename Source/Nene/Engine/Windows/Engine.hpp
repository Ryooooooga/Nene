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

#ifndef INCLUDE_NENE_ENGINE_WINDOWS_ENGINE_HPP
#define INCLUDE_NENE_ENGINE_WINDOWS_ENGINE_HPP

#include "../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include "../../Uncopyable.hpp"
#include "../IEngine.hpp"

namespace Nene::Windows
{
	/**
	 * @brief      Windows engine implementation.
	 */
	class Engine final
		: public  IEngine
		, private Uncopyable
	{
		std::shared_ptr<Logger>    logger_;
		std::shared_ptr<IGraphics> graphics_;

	public:
		/**
		 * @brief      Constructor.
		 */
		explicit Engine();

		/**
		 * @brief      Destructor.
		 */
		~Engine() =default;

		/**
		 * @see        `Nene::IEngine::logger()`.
		 */
		[[nodiscard]]
		const std::shared_ptr<Logger>& logger() const noexcept override;

		/**
		 * @see        `Nene::IEngine::graphics()`.
		 */
		[[nodiscard]]
		const std::shared_ptr<IGraphics>& graphics() const noexcept override;

		/**
		 * @see        `Nene::IEngine::window()`.
		 */
		[[nodiscard]]
		std::shared_ptr<IWindow> window(const std::string& title, const Size2Di& size) override;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_ENGINE_WINDOWS_ENGINE_HPP
