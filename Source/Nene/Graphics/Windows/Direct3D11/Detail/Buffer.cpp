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

#include "../../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include "../../../../Exceptions/Windows/DirectXException.hpp"
#include "Buffer.hpp"

namespace Nene::Windows::Direct3D11::Detail
{
	Microsoft::WRL::ComPtr<ID3D11Buffer> createBuffer(const Microsoft::WRL::ComPtr<ID3D11Device>& device, D3D11_BIND_FLAG bindFlag, UINT byteStride, UINT capacity)
	{
		assert(device);
		assert(byteStride);
		assert(capacity);

		D3D11_BUFFER_DESC desc = {};
		desc.ByteWidth           = byteStride * capacity;
		desc.Usage               = D3D11_USAGE_DYNAMIC;
		desc.BindFlags           = bindFlag;
		desc.CPUAccessFlags      = D3D11_CPU_ACCESS_WRITE;
		desc.MiscFlags           = 0;
		desc.StructureByteStride = byteStride;

		Microsoft::WRL::ComPtr<ID3D11Buffer> buffer;

		throwIfFailed(
			device->CreateBuffer(&desc, nullptr, buffer.GetAddressOf()),
			u8"Failed to create Direct3D11 buffer.");

		return buffer;
	}
}

#endif
