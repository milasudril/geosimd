#ifndef GEOSIMD_VEC_ARRAY_HPP
#define GEOSIMD_VEC_ARRAY_HPP

#include "./abstract_spaces.hpp"
#include "./basic_vector.hpp"
#include "./unit_vector.hpp"

#include <algorithm>
#include <vector>
#include <cassert>
#include <valarray>

namespace geosimd
{
	template<vector_space V>
	class vec_array:private std::vector<basic_vector<V>>
	{
	public:
		using value_type = basic_vector<V>;
		using scalar_type = typename value_type::scalar_type;
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

		vec_array& operator*=(std::valarray<scalar_type> const& other)
		{
			assert(size() == other.size());
			for(size_t k = 0; k != size(); ++k)
			{
				(*this)[k] *= other[k];
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

	template<vector_space V, class Generator, class ... Args>
	requires(generator<Generator, basic_vector<V>, Args...>)
	auto generate_vectors(size_t n, Generator&& gen, Args... args)
	{
		vec_array<V> ret(n);
		for(size_t k = 0; k != n; ++k)
		{
			ret[k] = gen(args...);
		}
		return ret;
	}


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
	auto operator*(vec_array<V> a, typename V::scalar_type b)
	{
		return a *= b;
	}

	template<vector_space V>
	auto operator*(std::valarray<typename V::scalar_type> const& b, vec_array<V> a)
	{
		return a *= b;
	}

	template<vector_space V>
	auto operator*(vec_array<V> a, std::valarray<typename V::scalar_type> const& b)
	{
		return a *= b;
	}

	template<vector_space V>
	auto operator/(vec_array<V> a, typename V::scalar_type b)
	{
		return a /= b;
	}

	template<normed_space V>
	auto norm(vec_array<V> const& vals)
	{
		std::valarray<typename V::scalar_type> ret(std::size(vals));
		for(size_t k = 0; k != std::size(vals); ++k)
		{
			ret[k] = norm(vals[k]);
		}
		return ret;
	}

	template<hilbert_space V>
	auto norm_squared(vec_array<V> const& vals)
	{
		std::valarray<typename V::scalar_type> ret(std::size(vals));
		for(size_t k = 0; k != std::size(vals); ++k)
		{
			ret[k] = norm_squared(vals[k]);
		}
		return ret;
	}

	template<inner_product_space V>
	auto inner_product(vec_array<V> const& a, vec_array<V> const& b)
	{
		assert(std::size(a) == std::size(b));

		std::valarray<typename V::scalar_type> ret(std::size(a));
		for(size_t k = 0; k != std::size(a); ++k)
		{
			ret[k] = inner_product(a[k], b[k]);
		}

		return ret;
	}

	template<inner_product_space V>
	auto inner_product(vec_array<V> const& a)
	{
		return inner_product(a, a);
	}

	template<hilbert_space V>
	auto angular_difference(vec_array<V> const& a, vec_array<V> const& b)
	{
		assert(std::size(a) == std::size(b));

		std::valarray<turn_angle> ret(std::size(a));
		for(size_t k = 0; k != std::size(a); ++k)
		{
			ret[k] = angular_difference(unit_vector{a[k]}, unit_vector{b[k]});
		}

		return ret;
	}


	template<hilbert_space V>
	auto angular_difference_broadcast(vec_array<V> const& a, unit_vector<V> b)
	{
		std::valarray<turn_angle> ret(std::size(a));
		for(size_t k = 0; k != std::size(a); ++k)
		{
			ret[k] = angular_difference(unit_vector{a[k]}, b);
		}

		return ret;
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
