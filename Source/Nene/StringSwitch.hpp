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

#ifndef INCLUDE_NENE_STRINGSWITCH_HPP
#define INCLUDE_NENE_STRINGSWITCH_HPP

#include <optional>
#include <string_view>

namespace Nene
{
	/**
	 * @brief      String switch.
	 *
	 * @tparam     T       Value type.
	 * @tparam     Char    Character type.
	 * @tparam     Traits  Character traits type.
	 */
	template <typename T, typename Char, typename Traits = std::char_traits<Char>>
	class BasicStringSwitch
	{
	public:
		using value_type       = T;
		using character_type   = Char;
		using traits_type      = Traits;
		using string_view_type = std::basic_string_view<Char, Traits>;

	private:
		string_view_type label_;
		const T*         data_;

	public:
		explicit BasicStringSwitch(string_view_type label) noexcept
			: label_(label), data_(nullptr) {}

		~BasicStringSwitch() =default;

		[[nodiscard]]
		BasicStringSwitch& Case(string_view_type label, const T& data) noexcept
		{
			if (!data_ && label == label_)
			{
				data_ = std::addressof(data);
			}

			return *this;
		}

		[[nodiscard]]
		const T& Default(const T& data) const noexcept
		{
			return data_ ? *data_ : data;
		}

		[[nodiscard]]
		std::optional<std::reference_wrapper<const T>> value() const noexcept
		{
			if (data_)
			{
				return *data_;
			}

			return std::nullopt;
		}
	};

	template <typename T, typename Traits = std::char_traits<char>>
	using StringSwitch = BasicStringSwitch<T, char, Traits>;

	template <typename T, typename Traits = std::char_traits<wchar_t>>
	using WStringSwitch = BasicStringSwitch<T, wchar_t, Traits>;

	template <typename T, typename Traits = std::char_traits<char>>
	using U8StringSwitch = BasicStringSwitch<T, char, Traits>;

	template <typename T, typename Traits = std::char_traits<char16_t>>
	using U16StringSwitch = BasicStringSwitch<T, char16_t, Traits>;

	template <typename T, typename Traits = std::char_traits<char32_t>>
	using U32StringSwitch = BasicStringSwitch<T, char32_t, Traits>;
}

#endif  // #ifndef INCLUDE_NENE_STRINGSWITCH_HPP
