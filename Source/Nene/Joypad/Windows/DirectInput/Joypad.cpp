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

		// Button object implementation.
		class Button final
			: public  IJoypad::IButton
			, private Uncopyable
		{
			std::string name_;
			UInt32      index_;

		public:
			explicit Button(UInt32 index)
				: name_(fmt::format(u8"Button-{}", index))
				, index_(index)
			{
				assert(index < 128);
			}

			~Button() =default;

			[[nodiscard]]
			std::string name() const override
			{
				return name_;
			}
		};

		// POV button object implementation.
		class POV final
			: public  IJoypad::IButton
			, private Uncopyable
		{
			std::string name_;
			UInt32      angle_;

		public:
			explicit POV(std::string&& name, UInt32 angle) noexcept
				: name_(std::move(name)), angle_(angle) {}

			~POV() =default;

			[[nodiscard]]
			std::string name() const override
			{
				return name_;
			}
		};

		// Axis object implementation.
		struct Axis final
			: public  IJoypad::IAxis
			, private Uncopyable
		{
			std::string name_;
			LONG DIJOYSTATE2::*data_;

		public:
			explicit Axis(std::string&& name, LONG DIJOYSTATE2::*data) noexcept
				: name_(std::move(name)), data_(data)
			{
				assert(data);
			}

			~Axis() =default;

			[[nodiscard]]
			std::string name() const override
			{
				return name_;
			}
		};
	}

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
			propRange.lMin              = -1024;
			propRange.lMax              = +1024;

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
		buttons_.emplace_back(std::make_unique<POV>(u8"POV-up",        0));
		buttons_.emplace_back(std::make_unique<POV>(u8"POV-down",  18000));
		buttons_.emplace_back(std::make_unique<POV>(u8"POV-right",  9000));

		// Register axis objects.
		axes_.emplace_back(std::make_unique<Axis>(u8"X-axis",     &DIJOYSTATE2::lX));
		axes_.emplace_back(std::make_unique<Axis>(u8"Y-axis",     &DIJOYSTATE2::lY));
		axes_.emplace_back(std::make_unique<Axis>(u8"Z-axis",     &DIJOYSTATE2::lZ));
		axes_.emplace_back(std::make_unique<Axis>(u8"X-rotation", &DIJOYSTATE2::lRx));
		axes_.emplace_back(std::make_unique<Axis>(u8"Y-rotation", &DIJOYSTATE2::lRy));
		axes_.emplace_back(std::make_unique<Axis>(u8"Z-rotation", &DIJOYSTATE2::lRz));
	}
}

#endif
