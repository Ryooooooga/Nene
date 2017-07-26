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

#ifndef INCLUDE_NENE_EVENT_EVENT_OBSERVABLE_HPP
#define INCLUDE_NENE_EVENT_EVENT_OBSERVABLE_HPP

#include <algorithm>
#include <vector>

namespace Nene
{
	// Forward declarations.
	template <typename... Args>
	class IEventObserver;

	/**
	 * @brief      Event subject.
	 *
	 * @tparam     Args  Event parameter types.
	 */
	template <typename... Args>
	class EventObservable final
	{
		std::vector<std::weak_ptr<IEventObserver<Args...>>> observers_;

	public:
		using observer_type = IEventObserver<Args...>;

		/**
		 * @brief      Constructor.
		 */
		EventObservable() =default;

		/**
		 * @brief      Destructor.
		 */
		~EventObservable() =default;

		/**
		 * @brief      Adds an observer.
		 *
		 * @param[in]  observer  The weak pointer of the observer.
		 */
		void addObserver(const std::shared_ptr<observer_type>& observer)
		{
			if (observer)
			{
				observers_.emplace_back(observer);
			}

			removeObserver(nullptr);
		}

		/**
		 * @brief      Removes an observer.
		 *
		 * @param[in]  observer  The observer to remove.
		 */
		void removeObserver(const std::shared_ptr<observer_type>& observer)
		{
			const auto checker = [&](const auto& x)
			{
				if (const auto p = x.lock())
				{
					return p == observer;
				}

				return true;
			};

			const auto newEnd = std::remove_if(std::begin(observers_), std::end(observers_), checker);
			observers_.erase(newEnd, std::end(observers_));
		}

		/**
		 * @brief      Notifys the event to listeners.
		 *
		 * @param[in]  args  Event parameters.
		 */
		void notify(Args... args)
		{
			for (const auto& observer : observers_)
			{
				if (const auto p = observer.lock())
				{
					p->updateEvent(args...);
				}
			}

			removeObserver(nullptr);
		}
	};
}

#endif  // #ifndef INCLUDE_NENE_EVENT_EVENT_OBSERVABLE_HPP
