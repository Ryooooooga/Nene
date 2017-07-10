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

#ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_TEXTURE_HPP
#define INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_TEXTURE_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include <d3d11.h>
#include <wrl/client.h>
#include "../../../Uncopyable.hpp"
#include "../../ITexture.hpp"

namespace Nene::Windows::Direct3D11
{
	/**
	 * @brief      Direct3D11 texture implementation.
	 */
	class Texture final
		: public  ITexture
		, private Uncopyable
	{
		Microsoft::WRL::ComPtr<ID3D11Device>             device_;
		Microsoft::WRL::ComPtr<ID3D11Texture2D>          texture_;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> shaderResource_;

		Size2Di size_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  texture  Direct3D11 texture.
		 */
		explicit Texture(const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texture);

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  device   Direct3D11 device.
		 * @param[in]  size     The texture size.
		 * @param[in]  dynamic  The dynamic texture flag.
		 */
		explicit Texture(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const Size2Di& size, bool dynamic);

		/**
		 * @brief      Destructor.
		 */
		~Texture() =default;

		/**
		 * @see        `Nene::ITexture::size()`.
		 */
		[[nodiscard]]
		const Size2Di& size() const noexcept override;

		/**
		 * @brief      Returns Direct3D11 device.
		 *
		 * @return     Direct3D11 device.
		 */
		[[nodiscard]]
		const Microsoft::WRL::ComPtr<ID3D11Device>& device() const noexcept;

		/**
		 * @brief      Returns Direct3D11 texture2D.
		 *
		 * @return     Direct3D11 texture2D.
		 */
		[[nodiscard]]
		const Microsoft::WRL::ComPtr<ID3D11Texture2D>& texture2D() const noexcept;

		/**
		 * @brief      Returns Direct3D11 shader resource view.
		 *
		 * @return     Direct3D11 shader resource view.
		 */
		[[nodiscard]]
		const Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>& shaderResourceView() const noexcept;
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_TEXTURE_HPP
