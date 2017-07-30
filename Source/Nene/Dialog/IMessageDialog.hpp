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

#ifndef INCLUDE_NENE_DIALOG_IMESSAGEDIALOG_HPP
#define INCLUDE_NENE_DIALOG_IMESSAGEDIALOG_HPP

#include <memory>
#include <string>

namespace Nene
{
	// Forward declarations.
	class IWindow;

	/**
	 * @brief      Message dialog interface.
	 */
	class IMessageDialog
	{
	public:
		/**
		 * @brief      Message dialog types.
		 */
		enum class Type
		{
			ok,
			okCancel,
			yesNo,
			yesNoCancel,
		};

		/**
		 * @brief      Message dialog icon.
		 */
		enum class Icon
		{
			normal,
			info,
			question,
			warning,
			error,
		};

		/**
		 * @brief      Message dialog buttons.
		 */
		enum class Button
		{
			none,
			ok,
			cancel,
			yes,
			no,
		};

		/**
		 * @brief      Constructor.
		 */
		IMessageDialog() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IMessageDialog() =default;

		/**
		 * @brief      Returns the dialog caption.
		 *
		 * @return     The caption of the dialog.
		 */
		[[nodiscard]]
		virtual std::string title() const =0;

		/**
		 * @brief      Returns the dialog message.
		 *
		 * @return     The message message of the dialog.
		 */
		[[nodiscard]]
		virtual std::string message() const =0;

		/**
		 * @brief      Returns the dialog type.
		 *
		 * @return     The dialog type.
		 */
		[[nodiscard]]
		virtual Type type() const =0;

		/**
		 * @brief      Returns the dialog icon.
		 *
		 * @return     The dialog icon.
		 */
		[[nodiscard]]
		virtual Icon icon() const =0;

		/**
		 * @brief      Sets the dialog caption.
		 *
		 * @param[in]  _title  The caption to set.
		 *
		 * @return     `*this`.
		 */
		virtual IMessageDialog& title(std::string_view _title) =0;

		/**
		 * @brief      Sets the dialog message.
		 *
		 * @param[in]  _message  The dialog message to set.
		 *
		 * @return     `*this`.
		 */
		virtual IMessageDialog& message(std::string_view _message) =0;

		/**
		 * @brief      Sets the dialog type.
		 *
		 * @param[in]  _type  The dialog type to set.
		 *
		 * @return     `*this`.
		 */
		virtual IMessageDialog& type(Type _type) =0;

		/**
		 * @brief      Sets the dialog icon.
		 *
		 * @param[in]  _icon  The dialog icon to set.
		 *
		 * @return     `*this`.
		 */
		virtual IMessageDialog& icon(Icon _icon) =0;

		/**
		 * @brief      Displays the message dialog.
		 *
		 * @param[in]  owner  The owner window.
		 *
		 * @return     The button selected.
		 */
		virtual Button show(const std::shared_ptr<const IWindow>& owner = nullptr) const =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_DIALOG_IMESSAGEDIALOG_HPP
