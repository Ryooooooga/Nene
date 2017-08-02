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

#ifndef INCLUDE_NENE_JOYPAD_WINDOWS_DIRECTINPUT_JOYPAD_HPP
#define INCLUDE_NENE_JOYPAD_WINDOWS_DIRECTINPUT_JOYPAD_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800

#include <vector>
#include <dinput.h>
#include <wrl/client.h>
#include "../../../Uncopyable.hpp"
#include "../../IJoypad.hpp"

namespace Nene::Windows::DirectInput
{
	/**
	 * @brief      DirectInput joypad device implementation.
	 */
	class Joypad final
		: public  IJoypad
		, private Uncopyable
	{
		class ButtonBase;
		class Button;
		class POV;
		class Axis;

		Microsoft::WRL::ComPtr<IDirectInputDevice8W> device_;

		std::vector<std::unique_ptr<ButtonBase>> buttons_;
		std::vector<std::unique_ptr<Axis>>       axes_;

		std::string name_;
		bool connected_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  device  DirectInput device.
		 */
		explicit Joypad(const Microsoft::WRL::ComPtr<IDirectInputDevice8W>& device);

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
		std::string name() const override;

		/**
		 * @see        `Nene::IJoypad::isConnected()`.
		 */
		[[nodiscard]]
		bool isConnected() const override;

		/**
		 * @see        `Nene::IJoypad::numButtons()`.
		 */
		[[nodiscard]]
		UInt32 numButtons() const override;

		/**
		 * @see        `Nene::IJoypad::numAxes()`.
		 */
		[[nodiscard]]
		UInt32 numAxes() const override;

		/**
		 * @see        `Nene::IJoypad::button()`.
		 */
		[[nodiscard]]
		IButton& button(UInt32 index) override;

		[[nodiscard]]
		const IButton& button(UInt32 index) const override;

		/**
		 * @see        `Nene::IJoypad::axis()`.
		 */
		[[nodiscard]]
		IAxis& axis(UInt32 index) override;

		[[nodiscard]]
		const IAxis& axis(UInt32 index) const override;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_JOYPAD_WINDOWS_DIRECTINPUT_JOYPAD_HPP
