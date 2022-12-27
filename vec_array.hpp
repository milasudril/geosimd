#ifndef GEOSIMD_VEC_ARRAY_HPP
#define GEOSIMD_VEC_ARRAY_HPP

#include "./abstract_spaces.hpp"
#include "./basic_vector.hpp"

#include <algorithm>
#include <vector>
#include <cassert>

namespace geosimd
{
	template<vector_space V>
	class vec_array:private std::vector<basic_vector<V>>
	{
	public:
		using value_type = basic_vector<V>;
		using scalar_type = typename basic_vector<V>::scalar_type;
		using container_type = std::vector<basic_vector<V>>;

		using container_type::container_type;
		using container_type::begin;
		using container_type::end;
		using container_type::size;
		using container_type::operator[];
		using container_type::push_back;

		bool operator==(vec_array const&) const = default;
		bool operator!=(vec_array const&) const = default;

		vec_array& operator+=(vec_array const& other)
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

		vec_array& operator-=(vec_array const& other)
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

		vec_array& operator*=(scalar_type c)
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

		vec_array& operator/=(scalar_type c)
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

	template<vector_space V>
	auto operator+(vec_array<V> a, vec_array<V> const& b)
	{
		return a += b;
	}

	template<vector_space V>
	auto operator-(vec_array<V> a, vec_array<V> const& b)
	{
		return a -= b;
	}

	template<vector_space V>
	auto operator*(typename V::scalar_type b, vec_array<V> a)
	{
		return a *= b;
	}

	template<vector_space V>
	constexpr auto operator*(vec_array<V> a, typename V::scalar_type b)
	{
		return a *= b;
	}

	template<vector_space V>
	constexpr auto operator/(vec_array<V> a, typename V::scalar_type b)
	{
		return a /= b;
	}

	template<vector_space V>
	std::string to_string(vec_array<V> const& obj)
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
