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

#ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_SHADERCOMPILER_HPP
#define INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_SHADERCOMPILER_HPP

#include "../../../Platform.hpp"
#if defined(NENE_OS_WINDOWS)

#include <string>
#include "../../../ArrayView.hpp"

namespace Nene::Windows::Direct3D11::Shader
{
	/**
	 * @brief      Compiles shader.
	 *
	 * @param[in]  name        The shader file name.
	 * @param[in]  entryPoint  The shader entry point.
	 * @param[in]  target      The shader compile target.
	 * @param[in]  source      The shader source.
	 *
	 * @return     The compiled shader binary.
	 */
	std::vector<Byte> compile(const std::string& name, const std::string& entryPoint, const std::string& target, ByteArrayView source);
}

#endif

#endif  // #ifndef INCLUDE_NENE_GRAPHICS_WINDOWS_DIRECT3D11_SHADERCOMPILER_HPP
