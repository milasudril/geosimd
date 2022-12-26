#ifndef GEOSIMD_VEC_CONTAINER_HPP
#define GEOSIMD_VEC_CONTAINER_HPP

#include <algorithm>
#include <cassert>

namespace geosimd
{
	template<class Container>
	class vec_container:private Container
	{
	public:
		using Container::Container;
		using Container::operator=;
		using Container::begin;
		using Container::end;
		using Container::size;

		using value_type = typename Container::value_type;
		
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
		
		constexpr bool operator==(vec_container const& other) const
		{
			return std::ranges::equal(*this, other); 
		}
		
		constexpr bool operator!=(vec_container const& other) const
		{
			return !(*this == other);
		}
		
		constexpr vec_container& operator+=(vec_container const& other)
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
		
		constexpr vec_container& operator-=(vec_container const& other)
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
	
	template<class T>
	auto operator+(vec_container<T> a, vec_container<T> const& b)
	{
		return a += b;
	}
	
	template<class T>
	auto operator-(vec_container<T> a, vec_container<T> const& b)
	{
		return a -= b;
	}
	
	template<class T>
	auto operator*(typename vec_container<T>::value_type::scalar_type b, vec_container<T> a)
	{
		return a *= b;
	}
	
	template<class T>
	auto operator*(vec_container<T> a, typename vec_container<T>::value_type::scalar_type b)
	{
		return a *= b;
	}
	
	template<class T>
	auto operator/(vec_container<T> a, typename vec_container<T>::value_type::scalar_type b)
	{
		return a /= b;
	}
	
	template<class T>
	std::string to_string(vec_container<T> const& obj)
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
