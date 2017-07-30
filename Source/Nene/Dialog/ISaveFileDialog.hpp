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

#ifndef INCLUDE_NENE_DIALOG_ISAVEFILEDIALOG_HPP
#define INCLUDE_NENE_DIALOG_ISAVEFILEDIALOG_HPP

#include "IFileDialog.hpp"

namespace Nene
{
	/**
	 * @brief      Save file dialog interface.
	 */
	class ISaveFileDialog
		: public IFileDialog
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		ISaveFileDialog() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~ISaveFileDialog() =default;

		/**
		 * @brief      Determines if the overwrite checking enabled.
		 *
		 * @return     `true` if overwrite checking is enabled, `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool warnFileOverwrite() const =0;

		/**
		 * @see        `Nene::IFileDialog::title()`.
		 */
		virtual ISaveFileDialog& title(const std::optional<std::string_view>& _title) override =0;

		/**
		 * @see        `Nene::IFileDialog::addFilter()`.
		 */
		virtual ISaveFileDialog& addFilter(std::string_view description, const path_type& filter) override =0;

		/**
		 * @see        `Nene::IFileDialog::filterIndex()`.
		 */
		virtual ISaveFileDialog& filterIndex(std::size_t index) override =0;

		/**
		 * @see        `Nene::IFileDialog::directory()`.
		 */
		virtual ISaveFileDialog& directory(const path_type& _directory) override =0;

		/**
		 * @see        `Nene::IFileDialog::filename()`.
		 */
		virtual ISaveFileDialog& filename(const path_type& _filename) override =0;

		/**
		 * @brief      Sets the overwrite checking flag.
		 *
		 * @param[in]  enabled  The overwrite checking flag.
		 *
		 * @return     `*this`.
		 */
		virtual ISaveFileDialog& warnFileOverwrite(bool enabled) =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_DIALOG_ISAVEFILEDIALOG_HPP
