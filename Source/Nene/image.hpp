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

#ifndef INCLUDE_NENE_IMAGE_HPP
#define INCLUDE_NENE_IMAGE_HPP

#include <functional>
#include "ArrayView.hpp"
#include "Color.hpp"
#include "Size2D.hpp"
#include "Vector2D.hpp"

namespace Nene
{
	/**
	 * @brief      Image object.
	 */
	class Image
	{
		std::vector<Color4> data_;
		Size2Di             size_;

	public:
		/**
		 * @brief      Copy constructor.
		 */
		Image(const Image&) =delete;

		/**
		 * @brief      Move constructor.
		 */
		Image(Image&&) =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  width   The image width.
		 * @param[in]  height  The image height.
		 * @param[in]  color   The fill color.
		 */
		explicit Image(Int32 width, Int32 height, const Color4& color = 0x00000000)
			: data_()
			, size_(width, height)
		{
			assert(width  > 0);
			assert(height > 0);

			data_.assign(width * height, color);
		}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  size   The image size.
		 * @param[in]  color  The fill color.
		 */
		explicit Image(const Size2Di& size, const Color4& color = 0x00000000)
			: Image(size.width, size.height, color) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  width   The image width.
		 * @param[in]  height  The image height.
		 * @param[in]  data    The pixel data.
		 */
		explicit Image(Int32 width, Int32 height, ArrayView<Color4> data)
			: data_(data.to_vector())
			, size_(width, height)
		{
			assert(width  > 0);
			assert(height > 0);
			assert(data.size() == width * height);
		}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  size  The image size.
		 * @param[in]  data  The pixel data.
		 */
		explicit Image(const Size2Di& size, ArrayView<Color4> data)
			: Image(size.width, size.height, data) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  width      The image width.
		 * @param[in]  height     The image height.
		 * @param[in]  generator  The pixel generator function.
		 */
		explicit Image(Int32 width, Int32 height, const std::function<Color4(const Vector2Di&)>& generator)
			: data_()
			, size_(width, height)
		{
			assert(width  > 0);
			assert(height > 0);

			data_.resize(width * height);

			for (int y = 0; y < height; y++)
			{
				for (int x = 0; x < width; x++)
				{
					data_[x + y*width] = generator({ x, y });
				}
			}
		}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  size       The image size.
		 * @param[in]  generator  The pixel generator function.
		 */
		explicit Image(const Size2Di& size, const std::function<Color4(const Vector2Di&)>& generator)
			: Image(size.width, size.height, generator) {}

		/**
		 * @brief      Destructor.
		 */
		~Image() =default;

		/**
		 * @brief      Copy operator `=`.
		 */
		Image& operator=(const Image&) =delete;

		/**
		 * @brief      Move operator `=`.
		 */
		Image& operator=(Image&&) =default;

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
		Byte* dataBytes() noexcept
		{
			return reinterpret_cast<Byte*>(data_.data());
		}

		[[nodiscard]]
		const Byte* dataBytes() const noexcept
		{
			return reinterpret_cast<const Byte*>(data_.data());
		}

		/**
		 * @brief      Returns the image width.
		 *
		 * @return     The image width.
		 */
		[[nodiscard]]
		Int32 width() const noexcept
		{
			return size_.width;
		}

		/**
		 * @brief      Returns the image height.
		 *
		 * @return     The image height.
		 */
		[[nodiscard]]
		Int32 height() const noexcept
		{
			return size_.height;
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
		 * @brief      Creates the new image data from the image.
		 *
		 * @return     Copy of the image data.
		 */
		[[nodiscard]]
		Image clone() const noexcept
		{
			return Image { size_, data_ };
		}
	};
}

#endif  // #ifndef INCLUDE_NENE_IMAGE_HPP
