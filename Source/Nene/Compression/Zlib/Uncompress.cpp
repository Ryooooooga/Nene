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

#include <zlib/zlib.h>
#include "../../Scope.hpp"
#include "Uncompress.hpp"
#include "ZlibException.hpp"

namespace Nene::Compression::Zlib
{
	std::vector<Byte> uncompress(ByteArrayView data, std::size_t uncompressedSize)
	{
		std::vector<Byte> uncompressed(uncompressedSize);

		::z_stream zs = {};
		zs.next_in   = const_cast<Byte*>(data.data()); // Never rewrited.
		zs.avail_in  = static_cast<uInt>(data.size());
		zs.next_out  = uncompressed.data();
		zs.avail_out = static_cast<uInt>(uncompressed.size());

		if (inflateInit2(&zs, -MAX_WBITS))
		{
			throw ZlibException { u8"Failed to initialize zlib inflate stream." };
		}

		scopeExit([&]()
		{
			::inflateEnd(&zs);
		});

		int result = ::inflate(&zs, Z_FINISH);

		if (result != Z_STREAM_END)
		{
			throw ZlibException { u8"Failed to inflate data." };
		}

		return uncompressed;
	}
}
