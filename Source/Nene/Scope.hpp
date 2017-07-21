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

#ifndef INCLUDE_NENE_SCOPE_HPP
#define INCLUDE_NENE_SCOPE_HPP

#include <exception>
#include "Uncopyable.hpp"

namespace Nene
{
	namespace Detail
	{
		template <typename Callback>
		class Scope final
			: private Uncopyable
		{
			Callback callback_;
			bool callOnSuccess_;
			bool callOnFailure_;

		public:
			explicit Scope(Callback&& callback, bool callOnSuccess, bool callOnFailure) noexcept
				: callback_(std::move(callback)), callOnSuccess_(callOnSuccess), callOnFailure_(callOnFailure) {}

			Scope(Scope&& scope) noexcept
				: callback_(std::move(scope.callback_)), callOnSuccess_(scope.callOnSuccess_), callOnFailure_(scope.callOnFailure_) {}

			~Scope() noexcept(noexcept(callback_()))
			{
				if (callOnSuccess_ && !std::uncaught_exception())
				{
					callback_();
				}
				else if (callOnFailure_ && std::uncaught_exception())
				{
					callback_();
				}
			}
		};
	}

	template <typename Callback>
	[[nodiscard]]
	Detail::Scope<Callback> scopeExit(Callback&& callback) noexcept
	{
		return Detail::Scope<Callback> { std::move(callback), true, true };
	}

	template <typename Callback>
	[[nodiscard]]
	Detail::Scope<Callback> scopeSuccess(Callback&& callback) noexcept
	{
		return Detail::Scope<Callback> { std::move(callback), true, false };
	}

	template <typename Callback>
	[[nodiscard]]
	Detail::Scope<Callback> scopeFailure(Callback&& callback) noexcept
	{
		return Detail::Scope<Callback> { std::move(callback), false, true };
	}
}

#endif  // #ifndef INCLUDE_NENE_SCOPE_HPP
