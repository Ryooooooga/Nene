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
		std::string       title_;
		std::string       message_;
		MessageDialogType type_;
		MessageDialogIcon icon_;

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
			, type_(MessageDialogType::ok)
			, icon_(MessageDialogIcon::normal) {}

		/**
		 * @brief      Destructor.
		 */
		~MessageDialog() =default;

		/**
		 * @see        `Nene::IMessageDialog::title()`.
		 */
		[[nodiscard]]
		const std::string& title() const noexcept override
		{
			return title_;
		}

		/**
		 * @see        `Nene::IMessageDialog::message()`.
		 */
		[[nodiscard]]
		const std::string& message() const noexcept override
		{
			return message_;
		}

		/**
		 * @see        `Nene::IMessageDialog::type()`.
		 */
		[[nodiscard]]
		MessageDialogType type() const noexcept override
		{
			return type_;
		}

		/**
		 * @see        `Nene::IMessageDialog::icon()`.
		 */
		[[nodiscard]]
		MessageDialogIcon icon() const noexcept override
		{
			return icon_;
		}

		/**
		 * @see        `Nene::IMessageDialog::title()`.
		 */
		IMessageDialog& title(std::string_view title) override
		{
			title_ = static_cast<std::string>(title);

			return *this;
		}

		/**
		 * @see        `Nene::IMessageDialog::message()`.
		 */
		IMessageDialog& message(std::string_view message) override
		{
			message_ = static_cast<std::string>(message);

			return *this;
		}

		/**
		 * @see        `Nene::IMessageDialog::type()`.
		 */
		IMessageDialog& type(MessageDialogType type) override
		{
			type_ = type;

			return *this;
		}

		/**
		 * @see        `Nene::IMessageDialog::icon()`.
		 */
		IMessageDialog& icon(MessageDialogIcon icon) override
		{
			icon_ = icon;

			return *this;
		}

		/**
		 * @see        `Nene::IMessageDialog::show()`.
		 */
		MessageDialogButton show(const std::shared_ptr<const IWindow>& window = nullptr) const override;

		/**
		 * @see        `Nene::IMessageDialog::showAsync()`.
		 */
		std::future<MessageDialogButton> showAsync(const std::shared_ptr<const IWindow>& window = nullptr) const override;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_DIALOG_WINDOWS_MESSAGEDIALOG_HPP
