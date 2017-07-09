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

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include "Monitor.hpp"
#include "../../../Encoding.hpp"
#include "../../../Exceptions/Windows/DirectXException.hpp"

namespace Nene::Windows::Direct3D11
{
	Monitor::Monitor(const Microsoft::WRL::ComPtr<IDXGIOutput>& output)
		: output_(output)
		, name_()
		, coordinate_()
	{
		assert(output);

		DXGI_OUTPUT_DESC desc;
		output->GetDesc(&desc);

		name_                   = Encoding::toUtf8(desc.DeviceName);
		coordinate_.position.x  = static_cast<Int32>(desc.DesktopCoordinates.left );
		coordinate_.position.y  = static_cast<Int32>(desc.DesktopCoordinates.top  );
		coordinate_.size.width  = static_cast<Int32>(desc.DesktopCoordinates.right  - desc.DesktopCoordinates.left );
		coordinate_.size.height = static_cast<Int32>(desc.DesktopCoordinates.bottom - desc.DesktopCoordinates.top  );
	}

	const std::string& Monitor::name() const noexcept
	{
		return name_;
	}

	const Rectanglei& Monitor::coordinate() const noexcept
	{
		return coordinate_;
	}

	const Vector2Di& Monitor::position() const noexcept
	{
		return coordinate_.position;
	}

	const Size2Di& Monitor::size() const noexcept
	{
		return coordinate_.size;
	}
}

#endif
