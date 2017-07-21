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

#ifndef INCLUDE_NENE_UNIQUERESOURCE_HPP
#define INCLUDE_NENE_UNIQUERESOURCE_HPP

#include "Uncopyable.hpp"

namespace Nene
{
	/**
	 * @brief      Unique resource.
	 *
	 * @tparam     Resource  The resource type.
	 * @tparam     Deleter   The deleter type.
	 */
	template <typename Resource, typename Deleter>
	class UniqueResource final
		: private Uncopyable
	{
		Resource resource_;
		Deleter  deleter_;
		bool     shouldRun_;

	public:
		/**
		 * @brief      Const
		 *
		 * @param      resource   The resource.
		 * @param      deleter    The resource deleter.
		 * @param[in]  shouldRun  Exucute `deleter` if `shouldRun == true`.
		 */
		explicit UniqueResource(Resource&& resource, Deleter&& deleter, bool shouldRun = true) noexcept
			: resource_(std::move(resource)), deleter_(std::move(deleter)), shouldRun_(shouldRun) {}

		/**
		 * @brief      Move constructor.
		 *
		 * @param      resource  The resource.
		 */
		UniqueResource(UniqueResource&& resource) noexcept
			: resource_(std::move(resource.resource_)), deleter_(std::move(resource.deleter_)), shouldRun_(resource.shouldRun) {}

		/**
		 * @brief      Destructor.
		 */
		~UniqueResource() noexcept(noexcept(reset()))
		{
			reset();
		}

		/**
		 * @brief      Move operator `=`.
		 *
		 * @param      resource  The resource.
		 *
		 * @return     `*this`.
		 */
		UniqueResource& operator=(UniqueResource&& resource) noexcept(noexcept(reset()))
		{
			reset();

			resource_  = std::move(resource.resource_);
			deleter_   = std::move(resource.deleter_);
			shouldRun_ = resource.shouldRun_;
			resource.release();

			return *this;
		}

		/**
		 * @brief      Resets the resource.
		 */
		void reset() noexcept(noexcept(deleter_(resource_)))
		{
			if (shouldRun_)
			{
				shouldRun_ = false;
				deleter_(resource_);
			}
		}

		/**
		 * @brief      Releases the resource.
		 *
		 * @return     `this->get()`.
		 */
		const Resource& release() noexcept
		{
			shouldRun_ = false;

			return resource_;
		}

		/**
		 * @brief      Returns the resource.
		 *
		 * @return     The resource contains.
		 */
		[[nodiscard]]
		const Resource& get() noexcept
		{
			return resource_;
		}

		/**
		 * @brief      Returns the deleter function.
		 *
		 * @return     The deleter function.
		 */
		[[nodiscard]]
		const Deleter& deleter() const noexcept
		{
			return deleter_;
		}

		/**
		 * @brief      Operator `->`.
		 *
		 * @return     `this->get()`.
		 */
		Resource operator->() const noexcept
		{
			return resource_;
		}

		/**
		 * @brief      Unary operator `*`.
		 *
		 * @return     The dereferenced resource.
		 */
		[[nodiscard]]
		decltype(auto) operator*() const
		{
			return *resource_;
		}
	};

	/**
	 * @brief      Unique resource factory.
	 *
	 * @param      resource  The resource.
	 * @param      deleter   The resource deleter.
	 *
	 * @tparam     Resource  The resource type.
	 * @tparam     Deleter   The resource deleter type.
	 *
	 * @return     Unique resource.
	 */
	template <typename Resource, typename Deleter>
	[[nodiscard]]
	auto uniqueResource(Resource&& resource, Deleter&& deleter) noexcept
	{
		return UniqueResource<Resource, std::remove_reference_t<Deleter>>
		{
			std::move(resource),
			std::forward<std::remove_reference_t<Deleter>>(deleter),
			true,
		};
	}
}

#endif  // #ifndef INCLUDE_NENE_UNIQUERESOURCE_HPP
