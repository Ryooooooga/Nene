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

#ifndef INCLUDE_NENE_DIALOG_IFILEDIALOG_HPP
#define INCLUDE_NENE_DIALOG_IFILEDIALOG_HPP

#include <memory>
#include <optional>
#include <experimental/filesystem>
#include "../ArrayView.hpp"

namespace Nene
{
	// Forward declarations.
	class IWindow;

	/**
	 * @brief      File dialog interface.
	 */
	class IFileDialog
	{
	public:
		using path_type = std::experimental::filesystem::path;

		/**
		 * @brief      File dialog filter information.
		 */
		struct Filter
		{
			std::string description;
			path_type   filter;
		};

		/**
		 * @brief      Constructor.
		 */
		IFileDialog() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IFileDialog() =default;

		/**
		 * @brief      Returns the dialog caption.
		 *
		 * @return     The caption of the dialog.
		 */
		[[nodiscard]]
		virtual std::optional<std::string> title() const =0;

		/**
		 * @brief      Returns the filters.
		 *
		 * @return     The file filters.
		 */
		[[nodiscard]]
		virtual ArrayView<Filter> filters() const =0;

		/**
		 * @brief      Returns the index of the initial filter.
		 *
		 * @return     The index of the initial filter.
		 */
		[[nodiscard]]
		virtual std::size_t filterIndex() const =0;

		/**
		 * @brief      Returns the directory where the dialog opens.
		 *
		 * @return     The directory of the dialog.
		 */
		[[nodiscard]]
		virtual path_type directory() const =0;

		/**
		 * @brief      Returns the file name.
		 *
		 * @return     The file name of the dialog.
		 */
		[[nodiscard]]
		virtual path_type filename() const =0;

		/**
		 * @brief      Sets the dialog caption.
		 *
		 * @param[in]  _title  The caption to set, `std::nullopt` if use system default title.
		 *
		 * @return     `*this`.
		 */
		virtual IFileDialog& title(const std::optional<std::string_view>& _title) =0;

		/**
		 * @brief      Adds a file filter.
		 *
		 * @param[in]  description  The description of the filter.
		 * @param[in]  filter       The file filter.
		 *
		 * @return     `*this`.
		 */
		virtual IFileDialog& addFilter(std::string_view description, const path_type& filter) =0;

		/**
		 * @brief      Sets the initial filter index.
		 *
		 * @param[in]  index  The filter index to set.
		 *
		 * @return     `*this`.
		 */
		virtual IFileDialog& filterIndex(std::size_t index) =0;

		/**
		 * @brief      Sets the initial dialog directory.
		 *
		 * @param[in]  _directory  The initial directory to set.
		 *
		 * @return     `*this`.
		 */
		virtual IFileDialog& directory(const path_type& _directory) =0;

		/**
		 * @brief      Sets the initial file name.
		 *
		 * @param[in]  _filename  The initial file name to set.
		 *
		 * @return     `*this`.
		 */
		virtual IFileDialog& filename(const path_type& _filename) =0;

		/**
		 * @brief      Displays the file dialog.
		 *
		 * @param[in]  owner  The dialog owner window.
		 *
		 * @return     List of selected file path.
		 */
		[[nodiscard]]
		virtual std::vector<path_type> show(const std::shared_ptr<IWindow>& owner = nullptr) =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_DIALOG_IFILEDIALOG_HPP
