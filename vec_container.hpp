#ifndef GEOSIMD_VEC_CONTAINER_HPP
#define GEOSIMD_VEC_CONTAINER_HPP

#include "./abstract_spaces.hpp"

#include <algorithm>
#include <vector>
#include <cassert>

namespace geosimd
{
	template<vector V, class Container = std::vector<V>>
	requires requires(){typename V::scalar_type;}
	class vec_container:private Container
	{
	public:
		using Container::Container;
		using Container::operator=;
		using Container::begin;
		using Container::end;
		using Container::size;

		using value_type = typename Container::value_type;
		using container_type = Container;

		template<class Dummy = void>
		requires requires(Container x) {
			{x.push_back(value_type{})};
		}
		decltype(auto) push_back(value_type const& val)
		{
			return Container::push_back(val);
		}

		template<class Dummy = void>
		requires(std::ranges::random_access_range<Container>)
		value_type& operator[](size_t n)
		{
			return *(begin() + n);
		}

		template<class Dummy = void>
		requires(std::ranges::random_access_range<Container>)
		value_type operator[](size_t n) const
		{
			return *(begin() + n);
		}

		template<std::ranges::input_range Other>
		requires(std::is_same_v<std::ranges::range_value_t<Other>, value_type>)
		constexpr bool operator==(Other const& other) const
		{
			return std::ranges::equal(*this, other);
		}

		template<std::ranges::input_range Other>
		requires(std::is_same_v<std::ranges::range_value_t<Other>, value_type>)
		constexpr bool operator!=(vec_container const& other) const
		{
			return !(*this == other);
		}

		template<std::ranges::sized_range Other>
		requires(std::is_same_v<std::ranges::range_value_t<Other>, value_type>)
		constexpr vec_container& operator+=(Other const& other)
		{
			assert(size() == other.size());

			auto i_this = begin();
			auto i_other = other.begin();
			auto const this_end = end();

			while(i_this != this_end)
			{
				*i_this += *i_other;

				++i_this;
				++i_other;
			}

			return *this;
		}

		template<std::ranges::sized_range Other>
		requires(std::is_same_v<std::ranges::range_value_t<Other>, value_type>)
		constexpr vec_container& operator-=(Other const& other)
		{
			assert(size() == other.size());

			auto i_this = begin();
			auto i_other = other.begin();
			auto const this_end = end();

			while(i_this != this_end)
			{
				*i_this -= *i_other;

				++i_this;
				++i_other;
			}

			return *this;
		}

		constexpr vec_container& operator*=(value_type::scalar_type c)
		{
			auto i_this = begin();
			auto const this_end = end();
			while(i_this != this_end)
			{
				*i_this *= c;
				++i_this;
			}
			return *this;
		}

		constexpr vec_container& operator/=(value_type::scalar_type c)
		{
			auto i_this = begin();
			auto const this_end = end();
			while(i_this != this_end)
			{
				*i_this /= c;
				++i_this;
			}
			return *this;
		}
	};

	template<vector V, class Container, std::ranges::input_range Other>
	requires(std::is_same_v<std::ranges::range_value_t<Other>, V>)
	constexpr auto operator+(vec_container<V, Container> a, Other const& b)
	{
		return a += b;
	}

	template<vector V, class Container, std::ranges::input_range Other>
	requires(std::is_same_v<std::ranges::range_value_t<Other>, V>)
	constexpr auto operator-(vec_container<V, Container> a, Other const& b)
	{
		return a -= b;
	}

	template<vector V, class Container>
	constexpr auto operator*(typename V::scalar_type b, vec_container<V, Container> a)
	{
		return a *= b;
	}

	template<vector V, class Container>
	constexpr auto operator*(vec_container<V, Container> a, typename V::scalar_type b)
	{
		return a *= b;
	}

	template<vector V, class Container>
	constexpr auto operator/(vec_container<V, Container> a, typename V::scalar_type b)
	{
		return a /= b;
	}

	template<vector V, class Container>
	std::string to_string(vec_container<V, Container> const& obj)
	{
		std::string ret{};
		std::ranges::for_each(obj, [&ret](auto const& item){
			ret.append(to_string(item));
			ret.push_back('\n');
		});
		return ret;
	}
}
#endif
