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

#include "../../../Encoding.hpp"
#include "../../../Exceptions/Windows/DirectXException.hpp"
#include "Joypad.hpp"

namespace Nene::Windows::DirectInput
{
	namespace
	{
		constexpr UInt32 maxNumButtons = 24;
		constexpr Int32  axisMagnitude = 1024;
	}

	// Joypad button base.
	class Joypad::ButtonBase
		: public IJoypad::IButton
		, private Uncopyable
	{
	protected:
		std::string name_;
		UInt8       history_;

	public:
		explicit ButtonBase(std::string&& name)
			: name_(std::move(name))
			, history_(0) {}

		~ButtonBase() =default;

		// Update state.
		virtual void update(const DIJOYSTATE2& state) =0;

		[[nodiscard]]
		std::string name() const override final
		{
			return name_;
		}

		[[nodiscard]]
		bool isPressed() const override final
		{
			return (history_ & 0b01) == 0b01;
		}

		[[nodiscard]]
		bool isClicked() const override final
		{
			return (history_ & 0b11) == 0b01;
		}

		[[nodiscard]]
		bool isReleased() const override final
		{
			return (history_ & 0b11) == 0b10;
		}
	};

	// Button object implementation.
	class Joypad::Button final
		: public ButtonBase
	{
		UInt32 index_;

	public:
		explicit Button(UInt32 index)
			: ButtonBase(fmt::format(u8"Button-{}", index))
			, index_(index)
		{
			assert(index < 128);
		}

		~Button() =default;

		void update(const DIJOYSTATE2& state)
		{
			history_ <<= 1;
			history_  |= state.rgbButtons[index_] ? 1 : 0;
		}
	};

	// POV button object implementation.
	class Joypad::POV final
		: public ButtonBase
	{
		std::string name_;
		UInt32      angle_;

	public:
		explicit POV(std::string&& name, UInt32 angle) noexcept
			: ButtonBase(std::move(name))
			, angle_(angle) {}

		~POV() =default;

		void update(const DIJOYSTATE2& state)
		{
			history_ <<= 1;
			history_  |= (state.rgdwPOV[0] == angle_) ? 1 : 0;
		}
	};

	// Axis object implementation.
	class Joypad::Axis final
		: public  IJoypad::IAxis
		, private Uncopyable
	{
		std::string         name_;
		LONG DIJOYSTATE2::* data_;
		Float32             state_;
		Float32             prev_;

	public:
		explicit Axis(std::string&& name, LONG DIJOYSTATE2::*data) noexcept
			: name_(std::move(name))
			, data_(data)
			, state_(0.f)
			, prev_(0.f)
		{
			assert(data);
		}

		~Axis() =default;

		void update(const DIJOYSTATE2& state)
		{
			prev_  = state_;
			state_ = static_cast<Float32>(state.*data_) / axisMagnitude;
		}

		[[nodiscard]]
		std::string name() const override
		{
			return name_;
		}

		[[nodiscard]]
		Float32 state() const override
		{
			return state_;
		}
	};

	Joypad::Joypad(const Microsoft::WRL::ComPtr<IDirectInputDevice8W>& device)
		: device_(device)
		, buttons_()
		, axes_()
		, name_()
		, connected_(true)
	{
		assert(device);

		// Get device info.
		DIDEVICEINSTANCEW info;
		info.dwSize = sizeof(info);

		throwIfFailed(
			device_->GetDeviceInfo(&info),
			u8"Failed to get DirectInput device information.");

		name_ = Encoding::toUtf8(info.tszInstanceName);

		// Set data format.
		throwIfFailed(
			device_->SetDataFormat(&c_dfDIJoystick2),
			u8"Failed to set DirectInput joypad data format.");

		// Set cooperative level.
		throwIfFailed(
			device_->SetCooperativeLevel(nullptr, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE),
			u8"Failed to set DirectInput joypad cooperative level.");

		// Get device capabilities.
		DIDEVCAPS capability;
		capability.dwSize = sizeof(capability);

		throwIfFailed(
			device_->GetCapabilities(&capability),
			u8"Failed to get DirectInput joypad capabilities.");

		// Set axes properties.
		const auto onEnumAxes = [](LPCDIDEVICEOBJECTINSTANCEW instance, LPVOID context)
		{
			const auto self = static_cast<Joypad*>(context);

			DIPROPRANGE propRange = {};
			propRange.diph.dwSize       = sizeof(DIPROPRANGE);
			propRange.diph.dwHeaderSize = sizeof(DIPROPHEADER);
			propRange.diph.dwHow        = DIPH_BYID;
			propRange.diph.dwObj        = instance->dwType;
			propRange.lMin              = -axisMagnitude;
			propRange.lMax              = +axisMagnitude;

			throwIfFailed(
				self->device_->SetProperty(DIPROP_RANGE, &propRange.diph),
				u8"Failed to set DirectInput joypad object property.");

			return DIENUM_CONTINUE;
		};

		throwIfFailed(
			device_->EnumObjects(onEnumAxes, this, DIDFT_AXIS),
			u8"Failed to enumerate DirectInput joypad axes.");

		// Register button objects.
		for (UInt32 i = 0; i < maxNumButtons; i++)
		{
			buttons_.emplace_back(std::make_unique<Button>(i));
		}

		// Register POV objects.
		buttons_.emplace_back(std::make_unique<POV>(u8"POV-left",  27000));
		buttons_.emplace_back(std::make_unique<POV>(u8"POV-down",  18000));
		buttons_.emplace_back(std::make_unique<POV>(u8"POV-right",  9000));
		buttons_.emplace_back(std::make_unique<POV>(u8"POV-up",        0));

		// Register axis objects.
		axes_.emplace_back(std::make_unique<Axis>(u8"X-axis",     &DIJOYSTATE2::lX));
		axes_.emplace_back(std::make_unique<Axis>(u8"Y-axis",     &DIJOYSTATE2::lY));
		axes_.emplace_back(std::make_unique<Axis>(u8"Z-axis",     &DIJOYSTATE2::lZ));
		axes_.emplace_back(std::make_unique<Axis>(u8"X-rotation", &DIJOYSTATE2::lRx));
		axes_.emplace_back(std::make_unique<Axis>(u8"Y-rotation", &DIJOYSTATE2::lRy));
		axes_.emplace_back(std::make_unique<Axis>(u8"Z-rotation", &DIJOYSTATE2::lRz));
	}

	Joypad::~Joypad() =default;

	void Joypad::update()
	{
		if (FAILED(device_->Poll()))
		{
			device_->Acquire();
		}

		// Get joypad state.
		DIJOYSTATE2 state;

		if (FAILED(device_->GetDeviceState(sizeof(state), &state)))
		{
			// Input lost.
			connected_ = false;

			return;
		}

		connected_ = true;

		// Update buttons.
		for (const auto& button : buttons_)
		{
			button->update(state);
		}

		// Update axes.
		for (const auto& axis : axes_)
		{
			axis->update(state);
		}
	}

	[[nodiscard]]
	std::string Joypad::name() const
	{
		return name_;
	}

	[[nodiscard]]
	bool Joypad::isConnected() const
	{
		return connected_;
	}

	[[nodiscard]]
	UInt32 Joypad::numButtons() const
	{
		return static_cast<UInt32>(buttons_.size());
	}

	[[nodiscard]]
	UInt32 Joypad::numAxes() const
	{
		return static_cast<UInt32>(axes_.size());
	}

	[[nodiscard]]
	IJoypad::IButton& Joypad::button(UInt32 index)
	{
		assert(index < numButtons());

		return *buttons_[index];
	}

	[[nodiscard]]
	const IJoypad::IButton& Joypad::button(UInt32 index) const
	{
		assert(index < numButtons());

		return *buttons_[index];
	}

	[[nodiscard]]
	IJoypad::IAxis& Joypad::axis(UInt32 index)
	{
		assert(index < numAxes());

		return *axes_[index];
	}

	[[nodiscard]]
	const IJoypad::IAxis& Joypad::axis(UInt32 index) const
	{
		assert(index < numAxes());

		return *axes_[index];
	}
}

#endif
