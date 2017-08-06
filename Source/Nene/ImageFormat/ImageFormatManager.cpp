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

#include "../Reader/IReader.hpp"
#include "ImageFormatManager.hpp"
#include "ImageFormatException.hpp"
#include "IImageFormat.hpp"

namespace Nene
{
	ImageFormatManager& ImageFormatManager::add(std::unique_ptr<IImageFormat>&& imageFormat)
	{
		assert(imageFormat);

		formats_.emplace_back(std::move(imageFormat));

		return *this;
	}

	std::optional<std::reference_wrapper<IImageFormat>> ImageFormatManager::findFormat(std::string_view formatName) const noexcept
	{
		const auto it = std::find_if(std::begin(formats_), std::end(formats_), [&](const auto& format)
		{
			return format->name() == formatName;
		});

		if (it == std::end(formats_))
		{
			return std::nullopt;
		}

		return **it;
	}

	std::optional<std::reference_wrapper<IImageFormat>> ImageFormatManager::findFormatFromPath(const path_type& path) const noexcept
	{
		const auto ext = path.extension();

		const auto it = std::find_if(std::begin(formats_), std::end(formats_), [&](const auto& format)
		{
			const auto exts = format->possibleExtensions();

			// Return true if `exts` contains `ext`.
			return std::find(std::begin(exts), std::end(exts), ext) != std::end(exts);
		});

		if (it == std::end(formats_))
		{
			return std::nullopt;
		}

		return **it;
	}

	std::optional<std::reference_wrapper<IImageFormat>> ImageFormatManager::findFormatFromHeader(const std::array<Byte, 16>& header) const noexcept
	{
		const auto it = std::find_if(std::begin(formats_), std::end(formats_), [&](const auto& format)
		{
			return format->isImageHeader(header);
		});

		if (it == std::end(formats_))
		{
			return std::nullopt;
		}

		return **it;
	}

	Image ImageFormatManager::decode(IReader& reader)
	{
		// Peek header.
		std::array<Byte, 16> header;
		reader.peek(header.data(), header.size());

		if (const auto format = findFormatFromHeader(header))
		{
			return format->get().decode(reader);
		}

		throw ImageFormatException { u8"Unknown image format." };
	}

	ArrayView<std::unique_ptr<IImageFormat>> ImageFormatManager::imageFormats() const noexcept
	{
		return formats_;
	}
}
