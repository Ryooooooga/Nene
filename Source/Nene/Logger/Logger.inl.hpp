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

#ifndef INCLUDE_NENE_LOGGER_LOGGER_INL_HPP
#define INCLUDE_NENE_LOGGER_LOGGER_INL_HPP

#include <fmt/ostream.h>

namespace Nene
{
	template <typename... Args>
	inline Logger& Logger::trace(const std::string& format, Args&&... args)
	{
		_forwardLogEntry(LogEntry { *this, LogLevel::trace, fmt::format(format, std::forward<Args>(args)...) });

		return *this;
	}

	template <typename... Args>
	inline Logger& Logger::debug(const std::string& format, Args&&... args)
	{
		_forwardLogEntry(LogEntry { *this, LogLevel::trace, fmt::format(format, std::forward<Args>(args)...) });

		return *this;
	}

	template <typename... Args>
	inline Logger& Logger::info(const std::string& format, Args&&... args)
	{
		_forwardLogEntry(LogEntry { *this, LogLevel::trace, fmt::format(format, std::forward<Args>(args)...) });

		return *this;
	}

	template <typename... Args>
	inline Logger& Logger::warning(const std::string& format, Args&&... args)
	{
		_forwardLogEntry(LogEntry { *this, LogLevel::trace, fmt::format(format, std::forward<Args>(args)...) });

		return *this;
	}

	template <typename... Args>
	inline Logger& Logger::error(const std::string& format, Args&&... args)
	{
		_forwardLogEntry(LogEntry { *this, LogLevel::trace, fmt::format(format, std::forward<Args>(args)...) });

		return *this;
	}

	template <typename... Args>
	inline Logger& Logger::fatal(const std::string& format, Args&&... args)
	{
		_forwardLogEntry(LogEntry { *this, LogLevel::trace, fmt::format(format, std::forward<Args>(args)...) });

		return *this;
	}

	inline void Logger::_forwardLogEntry(const LogEntry& entry)
	{
		if (entry.level() >= level_)
		{
			[[maybe_unused]] std::lock_guard<decltype(mutex_)> _ {mutex_};
			writeLogEntry(entry);
		}
	}
}

#endif  // #ifndef INCLUDE_NENE_LOGGER_LOGGER_INL_HPP
