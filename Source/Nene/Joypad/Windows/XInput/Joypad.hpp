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

#ifndef INCLUDE_NENE_JOYPAD_WINDOWS_XINPUT_JOYPAD_HPP
#define INCLUDE_NENE_JOYPAD_WINDOWS_XINPUT_JOYPAD_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include "../../../Uncopyable.hpp"
#include "../../IJoypad.hpp"

namespace Nene::Windows::XInput
{
	/**
	 * @brief      XInput joypad device implementation.
	 */
	class Joypad final
		: public  IJoypad
		, private Uncopyable
	{
		class Button;
		class Axis;

		std::vector<std::unique_ptr<Button>> buttons_;
		std::vector<std::unique_ptr<Axis>>   axes_;

		std::string name_;
		UInt32      index_;
		bool        connected_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  index  The joypad index.
		 */
		explicit Joypad(UInt32 index);

		/**
		 * @brief      Destructor.
		 */
		~Joypad();

		/**
		 * @see        `Nene::IJoypad::update()`.
		 */
		void update() override;

		/**
		 * @see        `Nene::IJoypad::name()`.
		 */
		[[nodiscard]]
		std::string name() const override
		{
			return name_;
		}

		/**
		 * @see        `Nene::IJoypad::isConnected()`.
		 */
		[[nodiscard]]
		bool isConnected() const override
		{
			return connected_;
		}
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_JOYPAD_WINDOWS_XINPUT_JOYPAD_HPP
