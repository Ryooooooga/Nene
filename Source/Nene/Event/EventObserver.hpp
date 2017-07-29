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

#ifndef INCLUDE_NENE_EVENT_EVENTOBSERVER_HPP
#define INCLUDE_NENE_EVENT_EVENTOBSERVER_HPP

#include <functional>
#include <memory>
#include "../Uncopyable.hpp"
#include "IEventObserver.hpp"

namespace Nene
{
	/**
	 * @brief      Callback function event observer implementation.
	 *
	 * @tparam     Args  Event parameter types.
	 */
	template <typename... Args>
	class EventObserver
		: public  IEventObserver<Args...>
		, private Uncopyable
	{
		std::function<void(Args...)> callback_;

	public:
		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  callback  The event callback function.
		 */
		explicit EventObserver(const std::function<void(Args...)>& callback)
			: callback_(callback) {}

		/**
		 * @brief      Destructor.
		 */
		~EventObserver() =default;

		/**
		 * @see        `Nene::IEventObserver::updateEvent()`.
		 */
		void updateEvent(Args... args) override
		{
			callback_(args...);
		}
	};

	/**
	 * @brief      Creates the event observer instance.
	 *
	 * @param[in]  callback  The callback function.
	 *
	 * @tparam     Args      Event parameter types.
	 *
	 * @return     The event observer instance.
	 */
	template <typename... Args>
	[[nodiscard]]
	std::shared_ptr<EventObserver<Args...> > observer(const std::function<void(Args...)>& callback)
	{
		return std::make_shared<EventObserver<Args...>>(callback);
	}
}

#endif  // #ifndef INCLUDE_NENE_EVENT_EVENTOBSERVER_HPP
