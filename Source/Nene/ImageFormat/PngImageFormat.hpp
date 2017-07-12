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

#ifndef INCLUDE_NENE_IMAGEFORMAT_PNGIMAGEFORMAT_HPP
#define INCLUDE_NENE_IMAGEFORMAT_PNGIMAGEFORMAT_HPP

#include "../Uncopyable.hpp"
#include "IImageFormat.hpp"

namespace Nene
{
	/**
	 * @brief      PNG image format.
	 */
	class PngImageFormat final
		: public  IImageFormat
		, private Uncopyable
	{
		std::string name_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  name  Image format name.
		 */
		explicit PngImageFormat(std::string_view name);

		/**
		 * @brief      Destructor.
		 */
		~PngImageFormat() =default;

		/**
		 * @see        `Nene::IImageFormat::name()`.
		 */
		[[nodiscard]]
		const std::string& name() const noexcept override;

		/**
		 * @see        `Nene::IImageFormat::isImageHeader()`.
		 */
		[[nodiscard]]
		bool isImageHeader(const std::array<Byte, 16>& header) const noexcept override;

		/**
		 * @see        `Nene::IImageFormat::decode()`.
		 */
		[[nodiscard]]
		Image decode(IReader& reader) override;

		/**
		 * @see        `Nene::IImageFormat::encode()`.
		 */
		[[nodiscard]]
		void encode(const Image& image, IWriter& reader) override;
	};
}

#endif  // #ifndef INCLUDE_NENE_IMAGEFORMAT_PNGIMAGEFORMAT_HPP
