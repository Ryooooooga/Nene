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

#ifndef INCLUDE_NENE_LOGGER_FORMATLOGGER_HPP
#define INCLUDE_NENE_LOGGER_FORMATLOGGER_HPP

#include <functional>
#include "Logger.hpp"

namespace Nene
{
	/**
	 * @brief      Format logger.
	 */
	class FormatLogger
		: public Logger
	{
	public:
		using formatter_type = std::function<std::string(const LogEntry&)>;

	private:
		formatter_type formatter_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  defaultLevel  Default log level.
		 * @param[in]  formatter     Log message formatter.
		 */
		explicit FormatLogger(LogLevel defaultLevel = LogLevel::all, const formatter_type& formatter = defaultFormatter) noexcept
			: Logger(defaultLevel), formatter_(formatter) {}

		/**
		 * @brief      Destructor.
		 */
		virtual ~FormatLogger() =default;

		/**
		 * @brief      Returns the current log formatter.
		 *
		 * @return     The current log formatter.
		 */
		[[nodiscard]]
		formatter_type formatter() const noexcept
		{
			[[maybe_unused]] std::lock_guard<decltype(mutex_)> _ {mutex_};
			return formatter_;
		}

		/**
		 * @brief      Sets the log formatter.
		 *
		 * @param[in]  formatter  New log formatter.
		 *
		 * @return     `*this`.
		 */
		FormatLogger& formatter(const formatter_type& formatter) noexcept
		{
			[[maybe_unused]] std::lock_guard<decltype(mutex_)> _ {mutex_};
			formatter_ = formatter;

			return *this;
		}

		/**
		 * @brief      Default log formatter.
		 *
		 * @param[in]  entry  Log entry.
		 *
		 * @return     Log message.
		 */
		[[nodiscard]]
		static std::string defaultFormatter(const LogEntry& entry)
		{
			const auto time     = entry.timestamp() - entry.logger().startTime();
			const auto time_us  = std::chrono::duration_cast<std::chrono::microseconds>(time).count();

			return fmt::format(u8"Thread: {}, Time: {}, Level: {}, Message: {}",
				entry.threadId(), time_us, entry.level(), entry.message());
		}

	protected:
		void writeLogEntry(const LogEntry& entry) override final
		{
			writeLogMessage(formatter_(entry));
		}

		/**
		 * @brief      Outputs log string.
		 *
		 * @param[in]  message  Log message.
		 */
		virtual void writeLogMessage(const std::string& message) =0;
	};
}

#endif  // #ifndef INCLUDE_NENE_LOGGER_FORMATLOGGER_HPP
