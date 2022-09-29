#ifndef GEOSIMD_NORMEDSPACE_HPP
#define GEOSIMD_NORMEDSPACE_HPP

#include <concepts>
#include <cstdlib>
#include <cmath>

namespace geosimd
{
	template<std::integral Int>
	auto norm(Int x)
	{
		return std::abs(x);
	}

	template<std::floating_point Float>
	auto norm(Float x)
	{
		return std::abs(x);
	}

	template<class T>
	concept normed_space = requires(T)
	{
		typename T::vector_type;
		typename T::scalar_type;

		{ norm(std::declval<typename T::vector_type>()) } -> std::same_as<typename T::scalar_type>;
	};
}

#endif