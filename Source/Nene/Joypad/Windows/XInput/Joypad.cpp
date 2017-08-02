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

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <Windows.h>
#include <Xinput.h>
#include <fmt/ostream.h>
#include "Joypad.hpp"

namespace Nene::Windows::XInput
{
	// Button object implementation.
	class Joypad::Button final
		: public  IButton
		, private Uncopyable
	{
		std::string name_;
		WORD        mask_;
		UInt8       history_;

	public:
		explicit Button(std::string&& name, WORD mask) noexcept
			: name_(std::move(name))
			, mask_(mask)
			, history_(0) {}

		~Button() =default;

		void update(const XINPUT_STATE& state)
		{
			history_ <<= 1;
			history_  |= (state.Gamepad.wButtons & mask_) ? 1 : 0;
		}

		[[nodiscard]]
		std::string name() const override
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

	// Axis object implementation.
	class Joypad::Axis final
		: public  IAxis
		, private Uncopyable
	{
	public:
		enum class Type
		{
			leftX,
			leftY,
			rightX,
			rightY,
			leftTrigger,
			rightTrigger,
		};

	private:
		std::string name_;
		Type        type_;
		Float32     state_;
		Float32     prev_;

	public:
		explicit Axis(std::string&& name, Type type) noexcept
			: name_(std::move(name))
			, type_(type)
			, state_(0.f)
			, prev_(0.f) {}

		~Axis() =default;

		void update(const XINPUT_STATE& state)
		{
			prev_ = state_;

			switch (type_)
			{
				case Type::leftX:
					state_ = static_cast<Float32>(state.Gamepad.sThumbLX) / 32768;
					break;

				case Type::leftY:
					state_ = static_cast<Float32>(state.Gamepad.sThumbLY) / 32768;
					break;

				case Type::rightX:
					state_ = static_cast<Float32>(state.Gamepad.sThumbRX) / 32768;
					break;

				case Type::rightY:
					state_ = static_cast<Float32>(state.Gamepad.sThumbRY) / 32768;
					break;

				case Type::leftTrigger:
					state_ = static_cast<Float32>(state.Gamepad.bLeftTrigger) / 255;
					break;

				case Type::rightTrigger:
					state_ = static_cast<Float32>(state.Gamepad.bRightTrigger) / 255;
					break;
			}
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

	Joypad::Joypad(UInt32 index)
		: buttons_()
		, axes_()
		, name_()
		, index_(index)
		, connected_()
	{
		assert(0 <= index && index < 4);

		XINPUT_STATE state;

		name_      = fmt::format(u8"XInput controller - {}", index);
		connected_ = ::XInputGetState(index_, &state) == ERROR_SUCCESS;

		// Register buttons.
		buttons_.emplace_back(std::make_unique<Button>(u8"A button",     WORD {XINPUT_GAMEPAD_A              }));
		buttons_.emplace_back(std::make_unique<Button>(u8"B button",     WORD {XINPUT_GAMEPAD_B              }));
		buttons_.emplace_back(std::make_unique<Button>(u8"X button",     WORD {XINPUT_GAMEPAD_X              }));
		buttons_.emplace_back(std::make_unique<Button>(u8"Y button",     WORD {XINPUT_GAMEPAD_Y              }));
		buttons_.emplace_back(std::make_unique<Button>(u8"Left bumper",  WORD {XINPUT_GAMEPAD_LEFT_SHOULDER  }));
		buttons_.emplace_back(std::make_unique<Button>(u8"Right bumper", WORD {XINPUT_GAMEPAD_RIGHT_SHOULDER }));
		buttons_.emplace_back(std::make_unique<Button>(u8"Left stick",   WORD {XINPUT_GAMEPAD_LEFT_THUMB     }));
		buttons_.emplace_back(std::make_unique<Button>(u8"Right stick",  WORD {XINPUT_GAMEPAD_RIGHT_THUMB    }));
		buttons_.emplace_back(std::make_unique<Button>(u8"Back button",  WORD {XINPUT_GAMEPAD_BACK           }));
		buttons_.emplace_back(std::make_unique<Button>(u8"Start button", WORD {XINPUT_GAMEPAD_START          }));
		buttons_.emplace_back(std::make_unique<Button>(u8"POV-left",     WORD {XINPUT_GAMEPAD_DPAD_LEFT      }));
		buttons_.emplace_back(std::make_unique<Button>(u8"POV-down",     WORD {XINPUT_GAMEPAD_DPAD_DOWN      }));
		buttons_.emplace_back(std::make_unique<Button>(u8"POV-right",    WORD {XINPUT_GAMEPAD_DPAD_RIGHT     }));
		buttons_.emplace_back(std::make_unique<Button>(u8"POV-up",       WORD {XINPUT_GAMEPAD_DPAD_UP        }));

		// Register axes.
		axes_.emplace_back(std::make_unique<Axis>(u8"Left-X",        Axis::Type::leftX        ));
		axes_.emplace_back(std::make_unique<Axis>(u8"Left-Y",        Axis::Type::leftY        ));
		axes_.emplace_back(std::make_unique<Axis>(u8"Right-X",       Axis::Type::rightX       ));
		axes_.emplace_back(std::make_unique<Axis>(u8"Right-Y",       Axis::Type::rightY       ));
		axes_.emplace_back(std::make_unique<Axis>(u8"Left trigger",  Axis::Type::leftTrigger  ));
		axes_.emplace_back(std::make_unique<Axis>(u8"Right trigger", Axis::Type::rightTrigger ));
	}

	Joypad::~Joypad() =default;

	void Joypad::update()
	{
		XINPUT_STATE state;
		
		if (::XInputGetState(index_, &state) != ERROR_SUCCESS)
		{
			// Lost input
			connected_ = false;

			return;
		}

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
