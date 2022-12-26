#ifndef GEOSIMD_POINT_CONTAINER_HPP
#define GEOSIMD_POINT_CONTAINER_HPP

#include <algorithm>
#include <cassert>

namespace geosimd
{
	template<class Container>
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

	template<class T, std::ranges::input_range Other>
	requires(std::is_same_v<std::ranges::range_value_t<Other>, typename point_container<T>::value_type::vector_type>)
	constexpr auto operator+(point_container<T> a, Other const& b)
	{
		return a += b;
	}
	
	template<class T, std::ranges::input_range Other>
	requires(std::is_same_v<std::ranges::range_value_t<Other>, typename point_container<T>::value_type::vector_type>)
	constexpr auto operator-(point_container<T> a, Other const& b)
	{
		return a -= b;
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
