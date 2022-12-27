#ifndef GEOSIMD_POINT_ARRAY_HPP
#define GEOSIMD_POINT_ARRAY_HPP

#include "./abstract_spaces.hpp"
#include "./basic_point.hpp"
#include "./vec_array.hpp"

#include <algorithm>
#include <vector>
#include <cassert>

namespace geosimd
{
	template<vector_space V>
	class point_array:private std::vector<basic_point<V>>
	{
	public:
		using value_type = basic_point<V>;
		using vector_type = typename value_type::vector_type;
		using scalar_type = typename value_type::scalar_type;
		using container_type = std::vector<basic_point<V>>;

		using container_type::container_type;
		using container_type::begin;
		using container_type::end;
		using container_type::size;
		using container_type::operator[];
		using container_type::push_back;

		bool operator==(point_array const&) const = default;
		bool operator!=(point_array const&) const = default;

		point_array& operator+=(vec_array<V> const& other)
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

		point_array& operator-=(vec_array<V> const& other)
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

	template<vector_space V>
	auto operator+(point_array<V> a, vec_array<V> const& b)
	{
		return a += b;
	}

	template<vector_space V>
	auto operator-(point_array<V> a, vec_array<V> const& b)
	{
		return a -= b;
	}

	template<vector_space V>
	std::string to_string(point_array<V> const& obj)
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
