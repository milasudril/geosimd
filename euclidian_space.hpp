#ifndef GEOSIMD_EUCLIDIAN_SPACE_HPP
#define GEOSIMD_EUCLIDIAN_SPACE_HPP

#include "./vec_t.hpp"
#include "./metric_normed_space.hpp"
#include "./hilbert_space.hpp"
#include "./basic_point.hpp"
#include "./basic_vector.hpp"
#include "./unit_vector.hpp"

namespace geosimd
{
	template<class T, size_t N>
	struct euclidian_space :
		metric_normed_space_mixin<vec_t<T, N + 1>, hilbert_space_mixin<vec_t<T, N + 1>>>
	{
		using enable_homogenous_coordinates_t = void;
	};

	template<class T, size_t N>
	using location = basic_point<euclidian_space<T, N>>;

	template<class T, size_t N>
	using displacement = basic_vector<euclidian_space<T, N>>;

	template<class T, size_t N>
	using direction = unit_vector<euclidian_space<T, N>>;

	template<class T, size_t N>
	constexpr auto x(location<T, N> loc)
	{
		return loc[0];
	}

	template<class T, size_t N>
	constexpr auto y(location<T, N> loc)
	{
		return loc[1];
	}

	template<class T, size_t N>
	constexpr auto z(location<T, N> loc)
	{
		return loc[2];
	}

	template<class T, size_t N>
	constexpr auto x(displacement<T, N> dr)
	{
		return dr[0];
	}

	template<class T, size_t N>
	constexpr auto y(displacement<T, N> dr)
	{
		return dr[1];
	}

	template<class T, size_t N>
	constexpr auto z(displacement<T, N> dr)
	{
		return dr[2];
	}

	template<class T, size_t N>
	constexpr auto dot(displacement<T, N> a, displacement<T, N> b)
	{
		return inner_product(a, b);
	}
}

#endif