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

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include "../../../Exceptions/Windows/DirectXException.hpp"
#include "Keyboard.hpp"

namespace Nene::Windows::DirectInput
{
	class Keyboard::Key final
		: public  IKey
		, private Uncopyable
	{
		std::string name_;
		UInt8       code_;
		UInt8       history_;

	public:
		explicit Key(std::string&& name, UInt8 code) noexcept
			: name_(std::move(name))
			, code_(code)
			, history_(0) {}

		~Key() =default;

		void update(const std::array<UInt8, 256>& state)
		{
			history_ <<= 1;
			history_  |= state[code_] ? 1 : 0;
		}

		[[nodiscard]]
		std::string name() const override
		{
			return name_;
		}

		[[nodiscard]]
		bool isPressed() const override
		{
			return (history_ & 0b01) == 0b01;
		}

		[[nodiscard]]
		bool isClicked() const override
		{
			return (history_ & 0b11) == 0b01;
		}

		[[nodiscard]]
		bool isReleased() const override
		{
			return (history_ & 0b11) == 0b10;
		}
	};

	Keyboard::Keyboard(const Microsoft::WRL::ComPtr<IDirectInput8W>& input)
		: device_()
		, keys_()
	{
		assert(input);

		// Create device.
		throwIfFailed(
			input->CreateDevice(GUID_SysKeyboard, device_.GetAddressOf(), nullptr),
			u8"Failed to create DirectInput keyboard device.");

		// Set data format.
		throwIfFailed(
			device_->SetDataFormat(&c_dfDIKeyboard),
			u8"Failed to set DirectInput keyboard data format.");

		// Set cooperative level.
		throwIfFailed(
			device_->SetCooperativeLevel(nullptr, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE),
			u8"Failed to set DirectInput keyboard device cooperative level.");

		device_->Acquire();

		// Create key objects.
#define NENE_KEY_CODE(name, text, code, diCode)\
		keys_[code] = std::make_unique<Key>(text, UInt8 {diCode});
#include "../../KeyCode.inc"

		for (auto& key : keys_)
		{
			if (!key)
			{
				key = std::make_unique<Key>(u8"Unknown", UInt8 {0x00});
			}
		}
	}

	Keyboard::~Keyboard() =default;

	void Keyboard::update()
	{
		std::array<UInt8, 256> state = {};
		device_->GetDeviceState(256, state.data());

		for (const auto& key : keys_)
		{
			key->update(state);
		}
	}

	IKeyboard::IKey& Keyboard::key(UInt8 code)
	{
		return *keys_[code];
	}

	const IKeyboard::IKey& Keyboard::key(UInt8 code) const
	{
		return *keys_[code];
	}

	IKeyboard::IKey& Keyboard::key(KeyCode code)
	{
		return key(static_cast<UInt8>(code));
	}

	const IKeyboard::IKey& Keyboard::key(KeyCode code) const
	{
		return key(static_cast<UInt8>(code));
	}
}

#endif
