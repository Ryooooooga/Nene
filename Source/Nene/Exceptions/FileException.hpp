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

#ifndef INCLUDE_NENE_EXCEPTIONS_FILEEXCEPTION_HPP
#define INCLUDE_NENE_EXCEPTIONS_FILEEXCEPTION_HPP

#include "EngineException.hpp"

namespace Nene
{
	/**
	 * @brief      Exception for signaling file errors.
	 */
	class FileException
		: public EngineException
	{
	public:
		/**
		 * @brief      Constructor.
		 */
		using EngineException::EngineException;

		/**
		 * @brief      Destructor.
		 */
		virtual ~FileException() =default;
	};
}

#endif  // #ifndef INCLUDE_NENE_EXCEPTIONS_FILEEXCEPTION_HPP
