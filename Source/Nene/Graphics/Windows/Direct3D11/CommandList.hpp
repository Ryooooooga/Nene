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

#ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_COMMANDBUFFER_HPP
#define INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_COMMANDBUFFER_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include <memory>
#include <variant>
#include <vector>
#include <d3d11.h>
#include <wrl/client.h>
#include "../../../ArrayView.hpp"
#include "../../../Color.hpp"
#include "../../../Uncopyable.hpp"

namespace Nene::Windows::Direct3D11
{
	struct CommandClearRenderTarget
	{
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTarget;
		Color4f clearColor;
	};

	struct CommandNop
	{
	};

	using Command = std::variant
	<
		CommandClearRenderTarget,
		CommandNop
	>;

	/**
	 * @brief      Rendering command list.
	 */
	class CommandList final
		: private Uncopyable
	{
		std::vector<Command> commands_;

	public:
		/**
		 * @brief      Constructor.
		 */
		explicit CommandList()
			: commands_ { CommandNop {} }
		{
			commands_.reserve(2048);
		}

		/**
		 * @brief      Destructor.
		 */
		~CommandList() =default;

		/**
		 * @brief      Clears command list.
		 */
		void clear()
		{
			commands_.resize(1);
		}

		/**
		 * @brief      Returns the rendering command list.
		 *
		 * @return     The rendering command list.
		 */
		[[nodiscard]]
		ArrayView<Command> commands() const noexcept
		{
			return ArrayView<Command> {commands_}.substr(1);
		}

		/**
		 * @brief      Gets the last command if exists, or push new command.
		 *
		 * @tparam     CommandType  Command type.
		 *
		 * @return     Reference to the command.
		 */
		template <typename CommandType>
		[[nodiscard]]
		CommandType& lastCommandOrPush()
		{
			if (auto p = std::get_if<CommandType>(&commands_.back()))
			{
				return *p;
			}

			// Add command.
			commands_.emplace_back(CommandType {});

			return std::get<CommandType>(commands_.back());
		}
	};
}

#endif

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_COMMANDBUFFER_HPP