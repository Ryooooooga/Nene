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

#ifndef INCLUDE_NENE_MOUSE_IMOUSE_HPP
#define INCLUDE_NENE_MOUSE_IMOUSE_HPP

#include "../Vector2D.hpp"

namespace Nene
{
	/**
	 * @brief      Mouse input.
	 */
	class IMouse
	{
	public:
		/**
		 * @brief      Mouse button interface.
		 */
		class IButton
		{
		public:
			/**
			 * @brief      Constructor.
			 */
			IButton() noexcept =default;

			/**
			 * @brief      Destructor.
			 */
			~IButton() =default;

			/**
			 * @brief      Returns the button name.
			 *
			 * @return     The button name.
			 */
			[[nodiscard]]
			virtual std::string name() const =0;

			/**
			 * @brief      Determines if the button is pressed.
			 *
			 * @return     `true` if pressed, `false` otherwise.
			 */
			[[nodiscard]]
			virtual bool isPressed() const =0;

			/**
			 * @brief      Determines if the button is clicked.
			 *
			 * @return     `true` if clicked, `false` otherwise.
			 */
			[[nodiscard]]
			virtual bool isClicked() const =0;

			/**
			 * @brief      Determines if the button is released.
			 *
			 * @return     `true` if released, `false` otherwise.
			 */
			[[nodiscard]]
			virtual bool isReleased() const =0;
		};

		/**
		 * @brief      Constructor.
		 */
		IMouse() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		~IMouse() =default;

		/**
		 * @brief      Updates mouse data.
		 */
		virtual void update() =0;

		/**
		 * @brief      Returns the mouse position.
		 *
		 * @return     The position of the mouse.
		 */
		[[nodiscard]]
		virtual Vector2Di position() const =0;

		/**
		 * @brief      Returns the mouse movement.
		 *
		 * @return     The mouse movement.
		 */
		[[nodiscard]]
		virtual Vector2Di delta() const =0;

		/**
		 * @brief      Returns the mouse wheel state.
		 *
		 * @return     The mouse wheel.
		 */
		[[nodiscard]]
		virtual Int32 wheel() const =0;

		/**
		 * @brief      Returns number of buttons.
		 *
		 * @return     Number of buttons.
		 */
		[[nodiscard]]
		virtual UInt32 numButtons() const =0;

		/**
		 * @brief      Returns reference to the button.
		 *
		 * @param[in]  index  The index of the button to get.
		 *
		 * @return     Reference to the button.
		 */
		[[nodiscard]]
		virtual IButton& button(UInt32 index) =0;

		[[nodiscard]]
		virtual const IButton& button(UInt32 index) const =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_MOUSE_IMOUSE_HPP
