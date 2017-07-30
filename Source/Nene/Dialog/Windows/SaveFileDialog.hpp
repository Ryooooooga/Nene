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

#ifndef INCLUDE_NENE_DIALOG_WINDOWS_SAVEFILEDIALOG_HPP
#define INCLUDE_NENE_DIALOG_WINDOWS_SAVEFILEDIALOG_HPP

#include "../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include "../../Uncopyable.hpp"
#include "../ISaveFileDialog.hpp"

namespace Nene::Windows
{
	/**
	 * @brief      Windows save file dialog implementation.
	 */
	class SaveFileDialog final
		: public  ISaveFileDialog
		, private Uncopyable
	{
		path_type                  directory_;
		path_type                  filename_;
		std::optional<std::string> title_;
		std::vector<Filter>        filters_;
		std::size_t                filterIndex_;
		bool                       warnOverwrite_;

	public:
		/**
		 * @brief      Constructor.
		 */
		explicit SaveFileDialog()
			: directory_(std::experimental::filesystem::current_path())
			, filename_()
			, title_()
			, filters_()
			, filterIndex_(0)
			, warnOverwrite_(true) {}

		/**
		 * @brief      Destructor.
		 */
		~SaveFileDialog() =default;

		/**
		 * @see        `Nene::IFileDialog::title()`.
		 */
		[[nodiscard]]
		std::optional<std::string> title() const override
		{
			return title_;
		}

		/**
		 * @see        `Nene::IFileDialog::filters()`.
		 */
		[[nodiscard]]
		ArrayView<Filter> filters() const override
		{
			return filters_;
		}

		/**
		 * @see        `Nene::IFileDialog::filterIndex()`.
		 */
		[[nodiscard]]
		std::size_t filterIndex() const override
		{
			return filterIndex_;
		}

		/**
		 * @see        `Nene::IFileDialog::directory()`.
		 */
		[[nodiscard]]
		path_type directory() const override
		{
			return directory_;
		}

		/**
		 * @see        `Nene::IFileDialog::filename()`.
		 */
		[[nodiscard]]
		path_type filename() const override
		{
			return filename_;
		}

		/**
		 * @see        `Nene::IFileDialog::warnFileOverwrite()`.
		 */
		[[nodiscard]]
		bool warnFileOverwrite() const override
		{
			return warnOverwrite_;
		}

		/**
		 * @see        `Nene::IFileDialog::title()`.
		 * @see        `Nene::ISaveFileDialog::directory()`.
		 */
		SaveFileDialog& title(const std::optional<std::string_view>& _title) override
		{
			title_ = _title;

			return *this;
		}

		/**
		 * @see        `Nene::IFileDialog::directory()`.
		 * @see        `Nene::ISaveFileDialog::directory()`.
		 */
		SaveFileDialog& addFilter(std::string_view description, const path_type& filter)
		{
			filters_.emplace_back(Filter { static_cast<std::string>(description), filter });

			return *this;
		}

		/**
		 * @see        `Nene::IFileDialog::filterIndex()`.
		 * @see        `Nene::ISaveFileDialog::filterIndex()`.
		 */
		SaveFileDialog& filterIndex(std::size_t index) override
		{
			filterIndex_ = index < filters_.size() ? index : 0;

			return *this;
		}

		/**
		 * @see        `Nene::IFileDialog::directory()`.
		 * @see        `Nene::ISaveFileDialog::directory()`.
		 */
		SaveFileDialog& directory(const path_type& _directory) override
		{
			directory_ = std::experimental::filesystem::absolute(_directory);

			return *this;
		}

		/**
		 * @see        `Nene::IFileDialog::filename()`.
		 * @see        `Nene::ISaveFileDialog::filename()`.
		 */
		SaveFileDialog& filename(const path_type& _filename) override
		{
			filename_ = _filename.filename();

			return *this;
		}

		/**
		 * @see        `Nene::ISaveFileDialog::filename()`.
		 */
		SaveFileDialog& warnFileOverwrite(bool enabled) override
		{
			warnOverwrite_ = enabled;

			return *this;
		}

		/**
		 * @see        `Nene::ISaveFileDialog::show()`.
		 */
		[[nodiscard]]
		std::vector<path_type> show(const std::shared_ptr<IWindow>& owner = nullptr) override;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_DIALOG_WINDOWS_SAVEFILEDIALOG_HPP
