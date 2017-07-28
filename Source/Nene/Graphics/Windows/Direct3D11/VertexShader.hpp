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

#ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIERECT3D11_VERTEXSHADER_HPP
#define INCLUDE_NENE_GRAPHICS_WINDOWS_DIERECT3D11_VERTEXSHADER_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include <d3d11.h>
#include <wrl/client.h>
#include "../../../ArrayView.hpp"
#include "../../../Uncopyable.hpp"
#include "../../IVertexShader.hpp"

namespace Nene::Windows::Direct3D11
{
	/**
	 * @brief      Vertex shader implementation.
	 */
	class VertexShader final
		: public IVertexShader
	{
		Microsoft::WRL::ComPtr<ID3D11VertexShader> shader_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  device          Direct3D11 device.
		 * @param[in]  compiledBinary  The compiled shader binary.
		 */
		explicit VertexShader(const Microsoft::WRL::ComPtr<ID3D11Device>& device, ByteArrayView compiledBinary);

		/**
		 * @brief      Destructor.
		 */
		~VertexShader() =default;

		/**
		 * @brief      Returns Direct3D11 vertex shader object.
		 *
		 * @return     Direct3D11 vertex shader object.
		 */
		[[nodiscard]]
		Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader() const noexcept
		{
			return shader_;
		}
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIERECT3D11_VERTEXSHADER_HPP
