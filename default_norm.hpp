#ifndef GEOSIMD_DEFAULTNORM_HPP
#define GEOSIMD_DEFAULTNORM_HPP

#include <cstdlib>
#include <cmath>
#include <concepts>

namespace geosimd
{
	template<class T>
	concept supports_abs = requires(T a)
	{
		{ abs(a) } -> std::totally_ordered;
	} || requires(T a)
	{
		{ std::abs(a) } -> std::totally_ordered;
	};

	template<supports_abs T>
	constexpr auto distance(T a, T b)
	{
		using std::abs;
		return abs(a - b);
	}

	template<std::totally_ordered T>
	requires (!supports_abs<T>)
	constexpr auto distance(T a, T b)
	{
		return a < b ? (b - a) : (a - b);
	}

	template<class T>
	concept supports_distance = requires(T a, T b)
	{
		{ distance(a, b) } -> std::totally_ordered;
	};

	template<supports_abs T>
	constexpr auto norm(T val)
	{
		using std::abs;
		return abs(val);
	}

	template<class T>
	concept supports_norm = requires(T a)
	{
		{ norm(a) } -> std::totally_ordered;
	};
}
#endif