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

#ifndef INCLUDE_NENE_DIALOG_WINDOWS_MESSAGEDIALOG_HPP
#define INCLUDE_NENE_DIALOG_WINDOWS_MESSAGEDIALOG_HPP

#include "../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include <string_view>
#include "../../Uncopyable.hpp"
#include "../IMessageDialog.hpp"

namespace Nene::Windows
{
	/**
	 * @brief      Windows message dialog implementation.
	 */
	class MessageDialog final
		: public  IMessageDialog
		, private Uncopyable
	{
		std::string title_;
		std::string message_;
		Type        type_;
		Icon        icon_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  title    The dialog caption.
		 * @param[in]  message  The dialog message.
		 */
		explicit MessageDialog(std::string_view title, std::string_view message)
			: title_(title)
			, message_(message)
			, type_(Type::ok)
			, icon_(Icon::normal) {}

		/**
		 * @brief      Destructor.
		 */
		~MessageDialog() =default;

		/**
		 * @see        `Nene::IMessageDialog::title()`.
		 */
		[[nodiscard]]
		std::string title() const override
		{
			return title_;
		}

		/**
		 * @see        `Nene::IMessageDialog::message()`.
		 */
		[[nodiscard]]
		std::string message() const override
		{
			return message_;
		}

		/**
		 * @see        `Nene::IMessageDialog::type()`.
		 */
		[[nodiscard]]
		Type type() const noexcept override
		{
			return type_;
		}

		/**
		 * @see        `Nene::IMessageDialog::icon()`.
		 */
		[[nodiscard]]
		Icon icon() const noexcept override
		{
			return icon_;
		}

		/**
		 * @see        `Nene::IMessageDialog::title()`.
		 */
		IMessageDialog& title(std::string_view _title) override
		{
			title_ = static_cast<std::string>(_title);

			return *this;
		}

		/**
		 * @see        `Nene::IMessageDialog::message()`.
		 */
		IMessageDialog& message(std::string_view _message) override
		{
			message_ = static_cast<std::string>(_message);

			return *this;
		}

		/**
		 * @see        `Nene::IMessageDialog::type()`.
		 */
		IMessageDialog& type(Type _type) override
		{
			type_ = _type;

			return *this;
		}

		/**
		 * @see        `Nene::IMessageDialog::icon()`.
		 */
		IMessageDialog& icon(Icon _icon) override
		{
			icon_ = _icon;

			return *this;
		}

		/**
		 * @see        `Nene::IMessageDialog::show()`.
		 */
		Button show(const std::shared_ptr<const IWindow>& owner = nullptr) const override;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_DIALOG_WINDOWS_MESSAGEDIALOG_HPP
