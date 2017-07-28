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

#ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_SCREEN_HPP
#define INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_SCREEN_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN

#include <memory>
#include <d3d11.h>
#include <wrl/client.h>
#include "../../../Uncopyable.hpp"
#include "../../IScreen.hpp"

#include "../../../Size2D.hpp" // TODO: include dependencies.

namespace Nene::Windows
{
	// Forward declarations.
	class Window;
}

namespace Nene::Windows::Direct3D11
{
	// Forward declarations.
	class DynamicTexture;

	/**
	 * @brief      Direct3D11 screen implementation.
	 */
	class Screen final
		: public  IScreen
		, private Uncopyable
	{
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain_;

		std::shared_ptr<Window>         window_;
		std::shared_ptr<DynamicTexture> renderTarget_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  device  Direct3D11 device.
		 * @param[in]  window  The render target window.
		 * @param[in]  size    The screen size.
		 */
		explicit Screen(const Microsoft::WRL::ComPtr<ID3D11Device>& device, const std::shared_ptr<Window>& window, const Size2Di& size);

		/**
		 * @brief      Destructor.
		 */
		~Screen() =default;

		/**
		 * @see        `Nene::IScreen::window()`.
		 */
		[[nodiscard]]
		std::shared_ptr<IWindow> window() const override;

		/**
		 * @see        `Nene::IScreen::renderTarget()`.
		 */
		[[nodiscard]]
		std::shared_ptr<IDynamicTexture> renderTarget() const override;

		/**
		 * @brief      Returns DXGI swap chain.
		 *
		 * @return     DXGI swap chain.
		 */
		[[nodiscard]]
		Microsoft::WRL::ComPtr<IDXGISwapChain> swapChain() const noexcept
		{
			return swapChain_;
		}
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_SCREEN_HPP
