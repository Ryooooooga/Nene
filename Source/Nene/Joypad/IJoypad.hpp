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

#ifndef INCLUDE_NENE_JOYPAD_IJOYPAD_HPP
#define INCLUDE_NENE_JOYPAD_IJOYPAD_HPP

#include <memory>
#include "../Types.hpp"

namespace Nene
{
	/**
	 * @brief      Joypad interface.
	 */
	class IJoypad
	{
	public:
		/**
		 * @brief      Joypad button interface.
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
			virtual ~IButton() =default;

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
		 * @brief      Joypad axis interface.
		 */
		class IAxis
		{
		public:
			/**
			 * @brief      Constructor.
			 */
			IAxis() noexcept =default;

			/**
			 * @brief      Destructor.
			 */
			virtual ~IAxis() =default;

			/**
			 * @brief      Returns the axis name.
			 *
			 * @return     The axis name.
			 */
			[[nodiscard]]
			virtual std::string name() const =0;

			/**
			 * @brief      Returns the axis state.
			 *
			 * @return     The state of the axis.
			 */
			[[nodiscard]]
			virtual Float32 state() const =0;
		};

		/**
		 * @brief      Constructor.
		 */
		IJoypad() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IJoypad() =default;

		/**
		 * @brief      Updates joypad data.
		 */
		virtual void update() =0;

		/**
		 * @brief      Returns the joypad device name.
		 *
		 * @return     The name of the joypad device.
		 */
		[[nodiscard]]
		virtual std::string name() const =0;

		/**
		 * @brief      Determines if the joypad is connected.
		 *
		 * @return     `true` if the joypad is connected, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool isConnected() const =0;

		/**
		 * @brief      Returns number of buttons.
		 *
		 * @return     Number of buttons.
		 */
		[[nodiscard]]
		virtual UInt32 numButtons() const =0;

		/**
		 * @brief      Returns number of axes.
		 *
		 * @return     Number of axes.
		 */
		[[nodiscard]]
		virtual UInt32 numAxes() const =0;

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

		/**
		 * @brief      Returns reference to the axis.
		 *
		 * @param[in]  index  The index of the axis to get.
		 *
		 * @return     Reference to the axis.
		 */
		[[nodiscard]]
		virtual IAxis& axis(UInt32 index) =0;

		[[nodiscard]]
		virtual const IAxis& axis(UInt32 index) const =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_JOYPAD_IJOYPAD_HPP
