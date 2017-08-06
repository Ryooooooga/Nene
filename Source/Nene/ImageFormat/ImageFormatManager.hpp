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

#ifndef INCLUDE_NENE_IMAGEFORMAT_IMAGEFORMATMANAGER_HPP
#define INCLUDE_NENE_IMAGEFORMAT_IMAGEFORMATMANAGER_HPP

#include <memory>
#include <optional>
#include <experimental/filesystem>
#include "../ArrayView.hpp"
#include "../Image.hpp"
#include "../Uncopyable.hpp"

namespace Nene
{
	// Forward declarations.
	class IImageFormat;
	class IReader;

	/**
	 * @brief      Image format manager.
	 */
	class ImageFormatManager
		: private Uncopyable
	{
		std::vector<std::unique_ptr<IImageFormat>> formats_;

	public:
		using path_type = std::experimental::filesystem::path;

		/**
		 * @brief      Constructor.
		 */
		ImageFormatManager() =default;

		/**
		 * @brief      Destructor.
		 */
		~ImageFormatManager() =default;

		/**
		 * @brief      Adds the image format.
		 *
		 * @param      imageFormat  The image format to add.
		 *
		 * @return     `*this`.
		 */
		ImageFormatManager& add(std::unique_ptr<IImageFormat>&& imageFormat);

		/**
		 * @brief      Finds the image format from format name.
		 *
		 * @param[in]  formatName  Image format name to acquire.
		 *
		 * @return     Reference to the image format.
		 */
		[[nodiscard]]
		std::optional<std::reference_wrapper<IImageFormat>> findFormat(std::string_view formatName) const noexcept;

		/**
		 * @brief      Finds the image format from the file path.
		 *
		 * @param[in]  path  The image file path.
		 *
		 * @return     Reference to the image format.
		 */
		[[nodiscard]]
		std::optional<std::reference_wrapper<IImageFormat>> findFormatFromPath(const path_type& path) const noexcept;

		/**
		 * @brief      Finds the image format from the image file header.
		 *
		 * @param[in]  header  The header of the image file.
		 *
		 * @return     Reference to the image format.
		 */
		[[nodiscard]]
		std::optional<std::reference_wrapper<IImageFormat>> findFormatFromHeader(const std::array<Byte, 16>& header) const noexcept;

		/**
		 * @brief      Constructs a image from a reader.
		 *
		 * @param      reader  The image data reader.
		 *
		 * @return     The image from `reader`.
		 */
		[[nodiscard]]
		Image decode(IReader& reader);

		/**
		 * @brief      Returns the list of image format codecs.
		 *
		 * @return     The list of image format codecs.
		 */
		[[nodiscard]]
		ArrayView<std::unique_ptr<IImageFormat>> imageFormats() const noexcept;
	};
}

#endif  // #ifndef INCLUDE_NENE_IMAGEFORMAT_IMAGEFORMATMANAGER_HPP
