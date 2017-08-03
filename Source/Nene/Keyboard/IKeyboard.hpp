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

#ifndef INCLUDE_NENE_KEYBOARD_IKEYBOARD_HPP
#define INCLUDE_NENE_KEYBOARD_IKEYBOARD_HPP

#include "KeyCode.hpp"

namespace Nene
{
	/**
	 * @brief      Keyboard interface.
	 */
	class IKeyboard
	{
	public:
		/**
		 * @brief      Key interface.
		 */
		class IKey
		{
		public:
			/**
			 * @brief      Constructor.
			 */
			IKey() noexcept =default;

			/**
			 * @brief      Destructor.
			 */
			virtual ~IKey() =default;

			/**
			 * @brief      Returns the key name.
			 *
			 * @return     The name of the key.
			 */
			[[nodiscard]]
			virtual std::string name() const =0;

			/**
			 * @brief      Determines if the key is pressed.
			 *
			 * @return     `true` if pressed, `false` otherwise.
			 */
			[[nodiscard]]
			virtual bool isPressed() const =0;

			/**
			 * @brief      Determines if the key is clicked.
			 *
			 * @return     `true` if clicked, `false` otherwise.
			 */
			[[nodiscard]]
			virtual bool isClicked() const =0;

			/**
			 * @brief      Determines if the key is released.
			 *
			 * @return     `true` if released, `false` otherwise.
			 */
			[[nodiscard]]
			virtual bool isReleased() const =0;
		};

		/**
		 * @brief      Constructor.
		 */
		IKeyboard() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IKeyboard() =default;

		/**
		 * @brief      Returns reference to the key object.
		 *
		 * @param[in]  code  Key code to get.
		 *
		 * @return     Reference to the key.
		 */
		[[nodiscard]]
		virtual IKey& key(KeyCode code) =0;

		[[nodiscard]]
		virtual const IKey& key(KeyCode code) const =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_KEYBOARD_IKEYBOARD_HPP
