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

#ifndef INCLUDE_NENE_MOUSE_WINDOWS_DIRECTINPUT_MOUSE_HPP
#define INCLUDE_NENE_MOUSE_WINDOWS_DIRECTINPUT_MOUSE_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800

#include <memory>
#include <vector>
#include <dinput.h>
#include <wrl/client.h>
#include "../../../Uncopyable.hpp"
#include "../../IMouse.hpp"

namespace Nene::Windows::DirectInput
{
	/**
	 * @brief      DirectInput mouse device implementation.
	 */
	class Mouse
		: public  IMouse
		, private Uncopyable
	{
		class Button;

		Microsoft::WRL::ComPtr<IDirectInputDevice8W> device_;

		std::vector<std::unique_ptr<Button>> buttons_;

		Vector2Di position_;
		Vector2Di delta_;
		Int32     wheel_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  input  DirectInput factory object.
		 */
		explicit Mouse(const Microsoft::WRL::ComPtr<IDirectInput8W>& input);

		/**
		 * @brief      Destructor.
		 */
		~Mouse();

		/**
		 * @see        `Nene::IMouse::update()`.
		 */
		void update() override;

		/**
		 * @see        `Nene::IMouse::position()`.
		 */
		[[nodiscard]]
		Vector2Di position() const override;

		/**
		 * @see        `Nene::IMouse::delta()`.
		 */
		[[nodiscard]]
		Vector2Di delta() const override;

		/**
		 * @see        `Nene::IMouse::wheel()`.
		 */
		[[nodiscard]]
		Int32 wheel() const override;

		/**
		 * @see        `Nene::IMouse::numButtons()`.
		 */
		[[nodiscard]]
		UInt32 numButtons() const override;

		/**
		 * @see        `Nene::IMouse::button()`.
		 */
		[[nodiscard]]
		IButton& button(UInt32 index) override;

		[[nodiscard]]
		const IButton& button(UInt32 index) const override;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_MOUSE_WINDOWS_DIRECTINPUT_MOUSE_HPP
