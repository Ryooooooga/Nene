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

#ifndef INCLUDE_NENE_LOGGER_MULTILOGGER_HPP
#define INCLUDE_NENE_LOGGER_MULTILOGGER_HPP

#include <algorithm>
#include <vector>
#include "Logger.hpp"

namespace Eico
{
	/**
	 * @brief      Multi logger.
	 */
	class MultiLogger final
		: public Logger
	{
		std::vector<std::shared_ptr<Logger>> loggers_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  defaultLevel  Default log level.
		 */
		explicit MultiLogger(LogLevel defaultLevel = LogLevel::all)
			: Logger(defaultLevel), loggers_() {}

		/**
		 * @brief      Destructor.
		 */
		virtual ~MultiLogger() =default;

		/**
		 * @brief      Adds logger.
		 *
		 * @param[in]  logger  Logger.
		 *
		 * @return     `*this`.
		 */
		MultiLogger& add(const std::shared_ptr<Logger>& logger) noexcept
		{
			loggers_.emplace_back(logger);

			return *this;
		}

		/**
		 * @brief      Removes logger.
		 *
		 * @param[in]  logger  Logger.
		 *
		 * @return     `*this`.
		 */
		MultiLogger& remove(const std::shared_ptr<Logger>& logger) noexcept
		{
			// Erace-remove idiom.
			loggers_.erase(std::remove(std::begin(loggers_), std::end(loggers_), logger), std::end(loggers_));

			return *this;
		}

	protected:
		void writeLogEntry(const LogEntry& entry) override final
		{
			for (const auto& logger : loggers_)
			{
				logger->_forwardLogEntry(entry);
			}
		}
	};
}

#endif  // #ifndef INCLUDE_NENE_LOGGER_MULTILOGGER_HPP
