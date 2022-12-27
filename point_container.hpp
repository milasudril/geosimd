#ifndef GEOSIMD_POINT_CONTAINER_HPP
#define GEOSIMD_POINT_CONTAINER_HPP

#include "./vec_container.hpp"
#include "./abstract_spaces.hpp"

#include <algorithm>
#include <cassert>

namespace geosimd
{
	template<point P, class Container = std::vector<P>>
	requires requires(){typename P::scalar_type; typename P::vector_type;}
	class point_container:private Container
	{
	public:
		using Container::Container;
		using Container::operator=;
		using Container::begin;
		using Container::end;
		using Container::size;

		using value_type = typename Container::value_type;
		
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
		constexpr bool operator!=(point_container const& other) const
		{
			return !(*this == other);
		}
		
		template<std::ranges::sized_range Other>
		requires(std::is_same_v<std::ranges::range_value_t<Other>, typename value_type::vector_type>)
		constexpr point_container& operator+=(Other const& other)
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
		requires(std::is_same_v<std::ranges::range_value_t<Other>, typename value_type::vector_type>)
		constexpr point_container& operator-=(Other const& other)
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
	};

	template<point P, class Container, std::ranges::input_range Other>
	requires(std::is_same_v<std::ranges::range_value_t<Other>, typename P::vector_type>)
	constexpr auto operator+(point_container<P, Container> a, Other const& b)
	{
		return a += b;
	}
	
	template<point P, class Container, std::ranges::input_range Other>
	requires(std::is_same_v<std::ranges::range_value_t<Other>, typename P::vector_type>)
	constexpr auto operator-(point_container<P, Container> a, Other const& b)
	{
		return a -= b;
	}
	
	template<class T>
	auto distance(point_container<T> const& a, point_container<T> const& b)
	{
		assert(std::size(a) == std::size(b));
		std::valarray<typename T::value_type::scalar_type> ret(std::size(a));
		auto i_a = std::begin(a);
		auto i_b = std::begin(b);
		auto const a_end = std::end(a);
		size_t k = 0;
		while(i_a != a_end)
		{
			ret[k] = distance(*i_a, *i_b);
			
			++i_a;
			++i_b;
			++k;
		}		
		return ret;
	}

	template<class T>
	std::string to_string(point_container<T> const& obj)
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
