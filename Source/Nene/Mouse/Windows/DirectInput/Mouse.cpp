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
#include "Mouse.hpp"

namespace Nene::Windows::DirectInput
{
	class Mouse::Button final
		: public  IButton
		, private Uncopyable
	{
		std::string name_;
		UInt8 index_;
		UInt8 history_;

	public:
		explicit Button(std::string&& name, UInt8 index)
			: name_(std::move(name)), index_(index), history_(0)
		{
			assert(index < 8);
		}

		~Button() =default;

		void update(const DIMOUSESTATE2& state)
		{
			history_ <<= 1;
			history_  |= state.rgbButtons[index_] ? 1 : 0;
		}

		std::string name() const override
		{
			return name_;
		}

		bool isPressed() const override
		{
			return (history_ & 0b01) == 0b01;
		}

		bool isClicked() const override
		{
			return (history_ & 0b11) == 0b01;
		}

		bool isReleased() const override
		{
			return (history_ & 0b11) == 0b10;
		}
	};

	Mouse::Mouse(const Microsoft::WRL::ComPtr<IDirectInput8W>& input)
		: device_()
		, buttons_()
		, position_(0, 0)
		, delta_(0, 0)
		, wheel_(0)
	{
		assert(input);

		// Create device.
		throwIfFailed(
			input->CreateDevice(GUID_SysMouse, device_.GetAddressOf(), nullptr),
			u8"Failed to create DirectInput mouse device.");

		// Set data format.
		throwIfFailed(
			device_->SetDataFormat(&c_dfDIMouse2),
			u8"Failed to set DirectInput mouse data format.");

		// Set cooperative level.
		throwIfFailed(
			device_->SetCooperativeLevel(nullptr, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE),
			u8"Failed to set DirectInput mouse device cooperative level.");

		// Set device properties.
		DIPROPDWORD prop = {};
		prop.diph.dwSize       = sizeof(prop);
		prop.diph.dwHeaderSize = sizeof(prop.diph);
		prop.diph.dwObj        = 0;
		prop.diph.dwHow        = DIPH_DEVICE;
		prop.dwData            = DIPROPAXISMODE_REL;

		throwIfFailed(
			device_->SetProperty(DIPROP_AXISMODE, &prop.diph),
			u8"Failed to set DirectInput mouse device property.");

		device_->Acquire();

		buttons_.emplace_back(std::make_unique<Button>(u8"Left button",   UInt8 {0}));
		buttons_.emplace_back(std::make_unique<Button>(u8"Right button",  UInt8 {1}));
		buttons_.emplace_back(std::make_unique<Button>(u8"Middle button", UInt8 {2}));
		buttons_.emplace_back(std::make_unique<Button>(u8"Button-4",      UInt8 {3}));
		buttons_.emplace_back(std::make_unique<Button>(u8"Button-5",      UInt8 {4}));
	}

	Mouse::~Mouse() =default;

	void Mouse::update()
	{
		// Get position.
		POINT pos;
		::GetCursorPos(&pos);

		position_.x = static_cast<Int32>(pos.x);
		position_.y = static_cast<Int32>(pos.y);

		// Get state.
		DIMOUSESTATE2 state;
		device_->GetDeviceState(sizeof(state), &state);

		delta_.x = static_cast<Int32>(state.lX);
		delta_.y = static_cast<Int32>(state.lY);
		wheel_   = static_cast<Int32>(state.lZ);

		for (const auto& button : buttons_)
		{
			button->update(state);
		}
	}

	Vector2Di Mouse::position() const
	{
		return position_;
	}

	Vector2Di Mouse::delta() const
	{
		return delta_;
	}

	Int32 Mouse::wheel() const
	{
		return wheel_;
	}

	UInt32 Mouse::numButtons() const
	{
		return static_cast<UInt32>(buttons_.size());
	}

	IMouse::IButton& Mouse::button(UInt32 index)
	{
		assert(index < numButtons());

		return *buttons_[index];
	}

	const IMouse::IButton& Mouse::button(UInt32 index) const
	{
		assert(index < numButtons());

		return *buttons_[index];
	}
}

#endif
