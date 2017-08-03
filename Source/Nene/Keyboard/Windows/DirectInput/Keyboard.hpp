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

#ifndef INCLUDE_NENE_KEYBOARD_WINDOWS_DIRECTINPUT_KEYBOARD_HPP
#define INCLUDE_NENE_KEYBOARD_WINDOWS_DIRECTINPUT_KEYBOARD_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN
#define DIRECTINPUT_VERSION 0x0800

#include <array>
#include <memory>
#include <dinput.h>
#include <wrl/client.h>
#include "../../../Uncopyable.hpp"
#include "../../IKeyboard.hpp"

namespace Nene::Windows::DirectInput
{
	/**
	 * @brief      DirectInput keyboard device implementation.
	 */
	class Keyboard final
		: public  IKeyboard
		, private Uncopyable
	{
		class Key;

		Microsoft::WRL::ComPtr<IDirectInputDevice8W> device_;

		std::array<std::unique_ptr<Key>, 256> keys_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  input  DirectInput object.
		 */
		explicit Keyboard(const Microsoft::WRL::ComPtr<IDirectInput8W>& input);

		/**
		 * @brief      Destructor.
		 */
		~Keyboard();

		/**
		 * @see        `Nene::IKeyboard::update()`.
		 */
		void update() override;

		/**
		 * @see        `Nene::IKeyboard::key()`.
		 */
		[[nodiscard]]
		IKey& key(UInt8 code) override;

		[[nodiscard]]
		const IKey& key(UInt8 code) const override;

		[[nodiscard]]
		IKey& key(KeyCode code) override;

		[[nodiscard]]
		const IKey& key(KeyCode code) const override;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_KEYBOARD_WINDOWS_DIRECTINPUT_KEYBOARD_HPP
