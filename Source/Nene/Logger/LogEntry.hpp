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

#ifndef INCLUDE_NENE_LOGGER_LOGENTRY_HPP
#define INCLUDE_NENE_LOGGER_LOGENTRY_HPP

#include <chrono>
#include <thread>
#include "../Uncopyable.hpp"

#include "LogLevel.hpp"

namespace Nene
{
	// Forward declaration.
	class Logger;

	/**
	 * @brief      Log entry information;
	 */
	class LogEntry
		: private Uncopyable
	{
	public:
		using clock_type      = std::chrono::steady_clock;
		using time_point_type = clock_type::time_point;

	private:
		const Logger&   logger_;
		std::thread::id threadId_;
		time_point_type timestamp_;
		LogLevel        level_;
		std::string     message_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param      logger   Reference to the logger.
		 * @param[in]  level    Output log level.
		 * @param[in]  message  Log message.
		 */
		explicit LogEntry(const Logger& logger, LogLevel level, const std::string& message) noexcept
			: logger_    (logger)
			, threadId_  (std::this_thread::get_id())
			, timestamp_ (clock_type::now())
			, level_     (level)
			, message_   (message) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param      logger   Reference to the logger.
		 * @param[in]  level    Output log level.
		 * @param[in]  message  Log message.
		 */
		explicit LogEntry(const Logger& logger, LogLevel level, std::string&& message) noexcept
			: logger_    (logger)
			, threadId_  (std::this_thread::get_id())
			, timestamp_ (clock_type::now())
			, level_     (level)
			, message_   (std::move(message)) {}

		/**
		 * @brief      Destructor.
		 */
		~LogEntry() =default;

		/**
		 * @brief      Returns reference to the logger.
		 *
		 * @return     Reference to the logger.
		 */
		[[nodiscard]]
		const Logger& logger() const noexcept
		{
			return logger_;
		}

		/**
		 * @brief      Returns thread id.
		 *
		 * @return     Thread id.
		 */
		[[nodiscard]]
		std::thread::id threadId() const noexcept
		{
			return threadId_;
		}

		/**
		 * @brief      Returns the logging timestamp.
		 *
		 * @return     The logging timestamp.
		 */
		[[nodiscard]]
		time_point_type timestamp() const noexcept
		{
			return timestamp_;
		}

		/**
		 * @brief      Returns the log level.
		 *
		 * @return     The log level.
		 */
		[[nodiscard]]
		LogLevel level() const noexcept
		{
			return level_;
		}

		/**
		 * @brief      Returns the log message.
		 *
		 * @return     The log message.
		 */
		[[nodiscard]]
		const std::string& message() const noexcept
		{
			return message_;
		}
	};
}

#endif  // #ifndef INCLUDE_NENE_LOGGER_LOGENTRY_HPP
