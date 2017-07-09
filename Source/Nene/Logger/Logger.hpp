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

#ifndef INCLUDE_NENE_LOGGER_LOGGER_HPP
#define INCLUDE_NENE_LOGGER_LOGGER_HPP

#include <atomic>
#include <mutex>
#include "LogEntry.hpp"

namespace Nene
{
	/**
	 * @brief      Logger.
	 */
	class Logger
		: private Uncopyable
	{
	public:
		using clock_type      = LogEntry::clock_type;
		using time_point_type = LogEntry::time_point_type;

	protected:
		std::atomic<LogLevel>        level_;
		const time_point_type        startTime_;
		mutable std::recursive_mutex mutex_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  defaultLevel  Default log level.
		 */
		explicit Logger(LogLevel defaultLevel = LogLevel::all) noexcept
			: startTime_(clock_type::now()), level_(defaultLevel) {}

		/**
		 * @brief      Destructor.
		 */
		virtual ~Logger() =default;

		/**
		 * @brief      Returns the current log level.
		 *
		 * @return     The current log level.
		 */
		[[nodiscard]]
		LogLevel level() const noexcept
		{
			return level_;
		}

		/**
		 * @brief      Sets the output log level.
		 *
		 * @param[in]  level  New log level.
		 *
		 * @return     `*this`.
		 */
		Logger& level(LogLevel level) noexcept
		{
			level_ = level;

			return *this;
		}

		/**
		 * @brief      Returns the start time point.
		 *
		 * @return     The start time point.
		 */
		[[nodiscard]]
		time_point_type startTime() const noexcept
		{
			return startTime_;
		}

		/**
		 * @brief      Outputs the trace log.
		 *
		 * @param[in]  format  Log format string.
		 * @param[in]  args    Format parameters.
		 *
		 * @tparam     Args    Arguments parameter pack.
		 *
		 * @return     `*this`.
		 */
		template <typename... Args>
		Logger& trace(const std::string& format, Args&&... args);

		/**
		 * @brief      Outputs the debug log.
		 *
		 * @param[in]  format  Log format string.
		 * @param[in]  args    Format parameters.
		 *
		 * @tparam     Args    Arguments parameter pack.
		 *
		 * @return     `*this`.
		 */
		template <typename... Args>
		Logger& debug(const std::string& format, Args&&... args);

		/**
		 * @brief      Outputs the info log.
		 *
		 * @param[in]  format  Log format string.
		 * @param[in]  args    Format parameters.
		 *
		 * @tparam     Args    Arguments parameter pack.
		 *
		 * @return     `*this`.
		 */
		template <typename... Args>
		Logger& info(const std::string& format, Args&&... args);

		/**
		 * @brief      Outputs the warning log.
		 *
		 * @param[in]  format  Log format string.
		 * @param[in]  args    Format parameters.
		 *
		 * @tparam     Args    Arguments parameter pack.
		 *
		 * @return     `*this`.
		 */
		template <typename... Args>
		Logger& warning(const std::string& format, Args&&... args);

		/**
		 * @brief      Outputs the error log.
		 *
		 * @param[in]  format  Log format string.
		 * @param[in]  args    Format parameters.
		 *
		 * @tparam     Args    Arguments parameter pack.
		 *
		 * @return     `*this`.
		 */
		template <typename... Args>
		Logger& error(const std::string& format, Args&&... args);

		/**
		 * @brief      Outputs the fatal log.
		 *
		 * @param[in]  format  Log format string.
		 * @param[in]  args    Format parameters.
		 *
		 * @tparam     Args    Arguments parameter pack.
		 *
		 * @return     `*this`.
		 */
		template <typename... Args>
		Logger& fatal(const std::string& format, Args&&... args);

		/**
		 * @brief      Forwards log entry.
		 *
		 * @param[in]  entry  Log entry.
		 */
		void _forwardLogEntry(const LogEntry& entry);

	protected:
		/**
		 * @brief      Writes a given entry information to the log.
		 *
		 * @param[in]  entry  Log entry.
		 */
		virtual void writeLogEntry(const LogEntry& entry) =0;
	};
}

#include "Logger.inl.hpp"

#endif  // #ifndef INCLUDE_NENE_LOGGER_LOGGER_HPP
