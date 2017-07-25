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

#ifndef INCLUDE_NENE_PLATFORM_HPP
#define INCLUDE_NENE_PLATFORM_HPP

#if defined(_WIN32) || defined(_WIN64)
#  define NENE_OS_WINDOWS
#else
#  error Unsupported platform
#endif

#if defined(_MSC_VER)
#  define NENE_COMPILER_MSVC
#elif defined(__clang__)
#  define NENE_COMPILER_CLANG
#elif defined(__GNUC__)
#  define NENE_COMPILER_GCC
#else
#  define NENE_COMPILER_UNKNOWN
#endif

#if defined(_DEBUG) || defined(DEBUG) || !defined(NDEBUG)
#  define NENE_DEBUG
#else
#  define NENE_RELEASE
#endif

#if defined(NENE_COMPILER_MSVC)
#  define NENE_SUPPRESS_WARNING_MSVC(x) __pragma(warning(suppress: x))
#else
#  define NENE_SUPPRESS_WARNING_MSVC(x)
#endif

#endif  // #ifndef INCLUDE_NENE_PLATFORM_HPP
