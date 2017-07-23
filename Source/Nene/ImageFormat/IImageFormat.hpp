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

#ifndef INCLUDE_IMAGEFORMAT_IIMAGEFORMAT_HPP
#define INCLUDE_IMAGEFORMAT_IIMAGEFORMAT_HPP

#include <experimental/filesystem>
#include "../Image.hpp"

namespace Nene
{
	// Forward declarations.
	class IReader;
	class IWriter;

	/**
	 * @brief      Image format interface.
	 */
	class IImageFormat
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		IImageFormat() noexcept =default;

		/**
		 * @brief      Destructor.
		 */
		virtual ~IImageFormat() =default;

		/**
		 * @brief      Returns the name of the image format.
		 *
		 * @return     The name of the image format.
		 */
		[[nodiscard]]
		virtual const std::string& name() const noexcept =0;

		/**
		 * @brief      Returns the list of possible extensions of the image format.
		 *
		 * @return     The list of possible extensions of the image format.
		 */
		[[nodiscard]]
		virtual ArrayView<std::experimental::filesystem::path> possibleExtensions() const noexcept =0;

		/**
		 * @brief      Determines if the given data is an image header.
		 *
		 * @param[in]  header  The header byte data.
		 *
		 * @return     `true` if `header` seems the image header supported,
		 *             `false` otherwise.
		 */
		[[nodiscard]]
		virtual bool isImageHeader(const std::array<Byte, 16>& header) const noexcept =0;

		/**
		 * @brief      Constructs a image from a reader.
		 *
		 * @param      reader  The image data reader.
		 *
		 * @return     The image from `reader`.
		 */
		[[nodiscard]]
		virtual Image decode(IReader& reader) =0;

		/**
		 * @brief      Writes a image to a writer.
		 *
		 * @param[in]  image   The image data to write.
		 * @param      writer  The image data writer.
		 */
		virtual void encode(const Image& image, IWriter& writer) =0;

		/**
		 * @brief      Writes a image to a writer.
		 *
		 * @param[in]  image    The image data to write.
		 * @param      writer   The image data writer.
		 * @param[in]  quality  The image quality.
		 */
		virtual void encode(const Image& image, IWriter& writer, Int32 quality) =0;
	};
}

#endif  // #ifndef INCLUDE_IMAGEFORMAT_IIMAGEFORMAT_HPP
