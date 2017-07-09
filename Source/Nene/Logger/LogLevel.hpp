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

#ifndef INCLUDE_NENE_LOGGER_LOGLEVEL_HPP
#define INCLUDE_NENE_LOGGER_LOGLEVEL_HPP

#include <cstdint>

namespace Nene
{
	/**
	 * @brief      Log level.
	 */
	enum class LogLevel: std::int32_t
	{
		all,
		trace,
		debug,
		info,
		warning,
		error,
		fatal,
		off,
	};

	/**
	 * @brief      Converts log level into string.
	 *
	 * @param[in]  level  Log level to convert.
	 *
	 * @return     String representation of log level.
	 */
	[[nodiscard]]
	constexpr const char* toString(LogLevel level) noexcept
	{
		switch (level)
		{
			case LogLevel::all    : return u8"ALL";
			case LogLevel::trace  : return u8"TRACE";
			case LogLevel::debug  : return u8"DEBUG";
			case LogLevel::info   : return u8"INFO";
			case LogLevel::warning: return u8"WARN";
			case LogLevel::error  : return u8"ERROR";
			case LogLevel::fatal  : return u8"FATAL";
			case LogLevel::off    : return u8"OFF";
			default               : return u8"UNKNOWN";
		}
	}

	/**
	 * @brief      Binary operator `<<`.
	 *
	 * @param      stream  Left hand side operand.
	 * @param[in]  level   Right hand side operand.
	 *
	 * @return     `stream << level`.
	 */
	inline std::ostream& operator<<(std::ostream& stream, LogLevel level)
	{
		return stream << toString(level);
	}
}

#endif  // #ifndef INCLUDE_NENE_LOGGER_LOGLEVEL_HPP
