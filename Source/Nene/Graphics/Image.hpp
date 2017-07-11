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

#ifndef INCLUDE_NENE_GRAPHICS_IMAGE_HPP
#define INCLUDE_NENE_GRAPHICS_IMAGE_HPP

#include <algorithm>
#include "../ArrayView.hpp"
#include "../Color.hpp"
#include "../Size2D.hpp"

namespace Nene
{
	/**
	 * @brief      Image data.
	 */
	class Image
	{
		std::vector<Color4> data_;
		Size2Di             size_;

	public:
		/**
		 * @brief      Default constructor.
		 */
		explicit Image()
			: data_()
			, size_(Size2Di::zero()) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  size  Image size.
		 */
		explicit Image(const Size2Di& size)
			: data_()
			, size_(size)
		{
			assert(size.width  >= 0);
			assert(size.height >= 0);

			data_.assign(size.width * size.height, Color4 { 0, 0, 0, 0 });
		}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  data  Color data.
		 * @param[in]  size  Image size.
		 */
		explicit Image(ArrayView<Color4> data, const Size2Di& size)
			: data_()
			, size_(size)
		{
			assert(size.width  >= 0);
			assert(size.height >= 0);
			assert(data.size() == size.width * size.height);

			data_ = data.to_vector();
		}

		/**
		 * @brief      Copy constructor.
		 */
		Image(const Image&) =delete;

		/**
		 * @brief      Move constructor.
		 */
		Image(Image&&) =default;

		/**
		 * @brief      Binary operator `=`.
		 */
		Image& operator=(const Image& a) =delete;

		/**
		 * @brief      Binary operator `=`.
		 */
		Image& operator=(Image&& a) =default;

		/**
		 * @brief      Destructor.
		 */
		~Image() =default;

		/**
		 * @brief      Returns the image color data.
		 *
		 * @return     The array of the pixel colors.
		 */
		[[nodiscard]]
		ArrayView<Color4> data() const noexcept
		{
			return data_;
		}

		/**
		 * @brief      Returns the pointer to the image color data.
		 *
		 * @return     The pointer to the array of the pixel colors.
		 */
		[[nodiscard]]
		Color4* dataPointer() noexcept
		{
			return data_.data();
		}

		[[nodiscard]]
		const Color4* dataPointer() const noexcept
		{
			return data_.data();
		}

		/**
		 * @brief      Returns the pointer to the image byte data.
		 *
		 * @return     The pointer to the array of the image bytes.
		 */
		[[nodiscard]]
		Byte* dataPointerAsByte() noexcept
		{
			return reinterpret_cast<Byte*>(data_.data());
		}

		[[nodiscard]]
		const Byte* dataPointerAsByte() const noexcept
		{
			return reinterpret_cast<const Byte*>(data_.data());
		}

		/**
		 * @brief      Returns the image size.
		 *
		 * @return     The image size.
		 */
		[[nodiscard]]
		const Size2Di& size() const noexcept
		{
			return size_;
		}

		/**
		 * @brief      Returns number of pixels the image contains.
		 *
		 * @return     Number of pixels the image contains.
		 */
		[[nodiscard]]
		std::size_t numPixels() const noexcept
		{
			return size_.width * size_.height;
		}

		/**
		 * @brief      Returns bytes size of the image data.
		 *
		 * @return     Bytes size of the image data.
		 */
		[[nodiscard]]
		std::size_t sizeBytes() const noexcept
		{
			return numPixels() * sizeof(Color4);
		}

		/**
		 * @brief      Resizes the image.
		 *
		 * @param[in]  size  New image size.
		 */
		void resize(const Size2Di& size)
		{
			resize(size.width, size.height);
		}

		/**
		 * @brief      Resizes the image.
		 *
		 * @param[in]  width   New image width.
		 * @param[in]  height  New image height.
		 */
		void resize(Int32 width, Int32 height)
		{
			assert(0 <= width  );
			assert(0 <= height );

			size_.set(width, height);
			data_.resize(width * height);
		}

		/**
		 * @brief      Resizes the image and fills pixels.
		 *
		 * @param[in]  size       New image size.
		 * @param[in]  fillColor  The fill color.
		 */
		void resize(const Size2Di& size, const Color4& fillColor)
		{
			resize(size.width, size.height, fillColor);
		}

		/**
		 * @brief      Resizes the image and fills pixels.
		 *
		 * @param[in]  width      New image width.
		 * @param[in]  height     New image height.
		 * @param[in]  fillColor  The fill color.
		 */
		void resize(Int32 width, Int32 height, const Color4& fillColor)
		{
			assert(0 <= width  );
			assert(0 <= height );

			size_.set(width, height);
			data_.assign(width * height, fillColor);
		}

		/**
		 * @brief      Creates the new image data from the image.
		 *
		 * @return     Copy of the image data.
		 */
		[[nodiscard]]
		Image clone() const noexcept
		{
			return Image { data_, size_ };
		}
	};
}

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_IMAGE_HPP
