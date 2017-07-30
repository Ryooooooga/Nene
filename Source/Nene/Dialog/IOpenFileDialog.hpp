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

#ifndef INCLUDE_NENE_DIALOG_IOPENFILEDIALOG_HPP
#define INCLUDE_NENE_DIALOG_IOPENFILEDIALOG_HPP

#include "IFileDialog.hpp"

namespace Nene
{
	/**
	 * @brief      Open file dialog interface.
	 */
	class IOpenFileDialog
		: public IFileDialog
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		IOpenFileDialog() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IOpenFileDialog() =default;

		/**
		 * @brief      Determines if the multiselection is allowed.
		 *
		 * @return     `true` if multiselection allowed, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool multiselect() const =0;

		/**
		 * @brief      Determines if the dialog checks file existence.
		 *
		 * @return     `true` if check file, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool checkFileExists() const =0;

		/**
		 * @see        `Nene::IFileDialog::title()`.
		 */
		virtual IOpenFileDialog& title(const std::optional<std::string_view>& _title) override =0;

		/**
		 * @see        `Nene::IFileDialog::addFilter()`.
		 */
		virtual IOpenFileDialog& addFilter(std::string_view description, const path_type& filter) override =0;

		/**
		 * @see        `Nene::IFileDialog::filterIndex()`.
		 */
		virtual IOpenFileDialog& filterIndex(std::size_t index) override =0;

		/**
		 * @see        `Nene::IFileDialog::directory()`.
		 */
		virtual IOpenFileDialog& directory(const path_type& _directory) override =0;

		/**
		 * @see        `Nene::IFileDialog::filename()`.
		 */
		virtual IOpenFileDialog& filename(const path_type& _filename) override =0;

		/**
		 * @brief      Allows or disallows multiselection.
		 *
		 * @param[in]  enabled  The multiselection enabled flag.
		 *
		 * @return     `*this`.
		 */
		virtual IOpenFileDialog& multiselect(bool enabled) =0;

		/**
		 * @brief      Sets file existence checking flag.
		 *
		 * @param[in]  enabled  The file check enabled flag.
		 *
		 * @return     `*this`.
		 */
		virtual IOpenFileDialog& checkFileExists(bool enabled) =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_DIALOG_IOPENFILEDIALOG_HPP
