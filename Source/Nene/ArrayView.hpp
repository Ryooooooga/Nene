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

#ifndef INCLUDE_NENE_ARRAYVIEW_HPP
#define INCLUDE_NENE_ARRAYVIEW_HPP

#include <cassert>
#include <array>
#include <vector>
#include "Types.hpp"

namespace Nene
{
	/**
	 * @brief      Array reference.
	 *
	 * @tparam     T     Element type.
	 *
	 * @see        http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3334.html
	 */
	template <typename T>
	class ArrayView
	{
		const T*    ptr_;
		std::size_t size_;

	public:
		using value_type             = T;
		using pointer                = const T*;
		using const_pointer          = pointer;
		using reference              = const T&;
		using const_reference        = const T&;
		using iterator               = const_pointer;
		using const_iterator         = iterator;
		using reverse_iterator       = std::reverse_iterator<iterator>;
		using const_reverse_iterator = std::reverse_iterator<const_iterator>;
		using size_type              = std::size_t;
		using difference_type        = std::ptrdiff_t;

		/**
		 * @brief      Default constructor.
		 */
		constexpr ArrayView() noexcept
			: ptr_(nullptr), size_(0) {}

		/**
		 * @brief      Copy constructor.
		 */
		constexpr ArrayView(const ArrayView&) noexcept =default;

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  pointer  Pointer to an array.
		 * @param[in]  length   Length of an array.
		 */
		constexpr ArrayView(const T* pointer, std::size_t length) noexcept
			: ptr_(pointer), size_(pointer ? length : 0) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  a     Reference to an array.
		 *
		 * @tparam     N     Length of an array.
		 */
		template <std::size_t N>
		constexpr ArrayView(const T (&a)[N]) noexcept
			: ptr_(a), size_(N) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  a     Reference to an array.
		 *
		 * @tparam     N     Length of an array.
		 */
		template <std::size_t N>
		constexpr ArrayView(const std::array<T, N>& a) noexcept
			: ptr_(a.data()), size_(N) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  v          Reference to a vector.
		 *
		 * @tparam     Allocator  Allocator type.
		 */
		template <typename Allocator>
		ArrayView(const std::vector<T, Allocator>& v) noexcept
			: ptr_(v.data()), size_(v.size()) {}

		/**
		 * @brief      Constructor.
		 *
		 * @param[in]  list  Initializer list.
		 */
		constexpr explicit ArrayView(const std::initializer_list<T>& list) noexcept
			: ptr_(list.data()), size_(list.size()) {}

		/**
		 * @brief      Returns an iterator to the beginning.
		 *
		 * @return     An iterator to the first element of the array.
		 */
		[[nodiscard]]
		constexpr const_iterator begin() const noexcept
		{
			return ptr_;
		}

		[[nodiscard]]
		constexpr const_iterator cbegin() const noexcept
		{
			return begin();
		}

		/**
		 * @brief      Returns an iterator to the end.
		 *
		 * @return     An iterator to the element following the last element of
		 *             the array.
		 */
		[[nodiscard]]
		constexpr const_iterator end() const noexcept
		{
			return ptr_ + size_;
		}

		[[nodiscard]]
		constexpr const_iterator cend() const noexcept
		{
			return ptr_ + size_;
		}

		/**
		 * @brief      Returns a reverse iterator to the beginning.
		 *
		 * @return     An iterator to the first element of the reversed array.
		 */
		[[nodiscard]]
		const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator { ptr_ + size_ };
		}

		[[nodiscard]]
		const_reverse_iterator crbegin() const noexcept
		{
			return rbegin();
		}

		/**
		 * @brief      Returns an reverse iterator to the end.
		 *
		 * @return     An iterator to the element following the last element of
		 *             the reversed array.
		 */
		[[nodiscard]]
		const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator { ptr_ };
		}

		[[nodiscard]]
		const_reverse_iterator crend() const noexcept
		{
			return rend();
		}

		/**
		 * @brief      Returns the pointer to the first element of the array.
		 *
		 * @return     The pointer to the first element of the array.
		 */
		[[nodiscard]]
		constexpr const T* data() const noexcept
		{
			return ptr_;
		}

		/**
		 * @brief      Returns length of the array.
		 *
		 * @return     The number of elements.
		 */
		[[nodiscard]]
		constexpr std::size_t size() const noexcept
		{
			return size_;
		}

		/**
		 * @brief      Returns the maximum possible number of elements.
		 *
		 * @return     `std::size_t {-1}`.
		 */
		[[nodiscard]]
		constexpr std::size_t max_size() const noexcept
		{
			return std::size_t {-1};
		}

		/**
		 * @brief      Checks whether the array is empty.
		 *
		 * @return     `true` if the array is empty, `false` otherwise.
		 */
		[[nodiscard]]
		constexpr bool empty() const noexcept
		{
			return size_ == 0;
		}

		/**
		 * @brief      Access the first element.
		 *
		 * @return     The first element of the array.
		 */
		[[nodiscard]]
		constexpr const T& front() const noexcept
		{
			return (*this)[0];
		}

		/**
		 * @brief      Access the last element.
		 *
		 * @return     The last element of the array.
		 */
		[[nodiscard]]
		constexpr const T& last() const noexcept
		{
			return (*this)[size_ - 1];
		}

		/**
		 * @brief      Access specified element with boudns checking.
		 *
		 * @param[in]  position  Position of the element to return.
		 *
		 * @return     Reference to the element at specified location
		 *             `position`.
		 */
		[[nodiscard]]
		constexpr const T& at(std::size_t position) const
		{
			if (position >= size_)
			{
				throw std::out_of_range { u8"out of range: Nene::ArrayView<T>::at()" };
			}

			return (*this)[position];
		}

		/**
		 * @brief      Returns a subarray.
		 *
		 * @param[in]  position  The start position of the subarray.
		 * @param[in]  length    The length of the subarray.
		 *
		 * @return     A slice of the array.
		 */
		[[nodiscard]]
		constexpr ArrayView substr(std::size_t position, std::size_t length = SIZE_MAX) const
		{
			if (position >= size_)
			{
				throw std::out_of_range { u8"out of range: Nene::ArrayView<T>::at()" };
			}

			return { ptr_ + position, (size_ - position < length) ? size_ - position : length };
		}

		/**
		 * @brief      Converts the array to the vector.
		 *
		 * @return     Copy of the array.
		 */
		template <typename Allocator = std::allocator<T>>
		[[nodiscard]]
		std::vector<T, Allocator> to_vector() const
		{
			return std::vector<T, Allocator>(ptr_, ptr_ + size_);
		}

		/**
		 * @brief      Clears the array.
		 */
		constexpr void clear() noexcept
		{
			ptr_  = nullptr;
			size_ = 0;
		}

		/**
		 * @brief      Removes the prefix element of the array.
		 *
		 * @param[in]  n     Number of elements to remove.
		 */
		constexpr void remove_prefix(std::size_t n) noexcept
		{
			if (n < size_)
			{
				ptr_  += n;
				size_ -= n;
			}
			else
			{
				clear();
			}
		}

		/**
		 * @brief      Removes a suffix element of the array.
		 *
		 * @param[in]  n     Number of elements to remove.
		 */
		constexpr void remove_suffix(std::size_t n) noexcept
		{
			if (n < size_)
			{
				size_ -= n;
			}
			else
			{
				clear();
			}
		}

		/**
		 * @brief      Removes the first element of the array.
		 */
		constexpr void pop_front() noexcept
		{
			remove_prefix(1);
		}

		/**
		 * @brief      Removes the last element of the array.
		 */
		constexpr void pop_back() noexcept
		{
			remove_suffix(1);
		}

		/**
		 * @brief      Operator `[]`.
		 *
		 * @param[in]  position  Position of the element to return.
		 *
		 * @return     Reference to the element at specified location
		 *             `position`.
		 */
		[[nodiscard]]
		constexpr const T& operator[](std::size_t position) const noexcept
		{
			assert(position < size_);
			return ptr_[position];
		}

		/**
		 * @brief      Binary operator `=`.
		 *
		 * @param[in]  a     Right hand side operand.
		 *
		 * @return     `*this = a`.
		 */
		constexpr ArrayView& operator=(const ArrayView& a) =default;
	};

	using ByteArrayView = ArrayView<Byte>;
}

#endif  // #ifndef INCLUDE_NENE_ARRAYVIEW_HPP
