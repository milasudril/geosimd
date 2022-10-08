#ifndef GEOSIMD_VECTORSPACES_HPP
#define GEOSIMD_VECTORSPACES_HPP

#include <cstddef>
#include <concepts>
#include <cstdint>
#include <complex>
#include <cmath>
#include <cstdlib>

namespace geosimd
{
	template<class T>
	using empty = std::type_identity<T>;

	template<class T>
	constexpr T zero(empty<T>)
	{ return T{}; }

	template<class T, class U>
	constexpr auto is_complex_v = std::is_same_v<T, std::complex<U>>;

	template<class T>
	concept scalar = (std::is_arithmetic_v<T> && std::is_signed_v<T>)
		|| is_complex_v<T, char>
		|| is_complex_v<T, short>
		|| is_complex_v<T, int>
		|| is_complex_v<T, long>
		|| is_complex_v<T, long long>
		|| is_complex_v<T, float>
		|| is_complex_v<T, double>;

	template<class T, class ScalarType>
	concept vector = std::equality_comparable<T> && scalar<ScalarType> && requires(T a, T b, ScalarType c)
	{
		{a + b} -> std::same_as<T>;
		{a - b} -> std::same_as<T>;
		{a += b} -> std::same_as<T&>;
		{a -= b} -> std::same_as<T&>;
		{c * a} -> std::same_as<T>;
		{a * c} -> std::same_as<T>;
		{a / c} -> std::same_as<T>;
		{a *= c} -> std::same_as<T&>;
		{a /= c} -> std::same_as<T&>;
		{-a} -> std::same_as<T>;
		{zero(std::declval<empty<T>>())} -> std::same_as<T>;
	};

	template<class T>
	concept vector_space = vector<typename T::vector_type, typename T::scalar_type>;

	template<class T, class VectorType, class ScalarType>
	concept point = std::equality_comparable<T>
		&& vector<VectorType, ScalarType>
		&& requires(T p1, T p2, VectorType v)
	{
		{p1 + v} -> std::same_as<T>;
		{p1 - v} -> std::same_as<T>;
		{p1 += v} -> std::same_as<T&>;
		{p1 -= v} -> std::same_as<T&>;
		{p1 - p2} -> std::same_as<VectorType>;
	};

	template<class T>
	concept affine_space = vector_space<T>
		&& point<typename T::point_type, typename T::vector_type, typename T::scalar_type>;

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
	concept metric_space = affine_space<T>
		&& requires(T)
	{
		{ distance(std::declval<typename T::point_type>(), std::declval<typename T::point_type>()) }
			-> std::totally_ordered;
	};

	template<supports_abs T>
	constexpr auto norm(T val)
	{
		using std::abs;
		return abs(val);
	}

	template<class T>
	concept normed_space = vector_space<T>
		&& requires(T)
	{
		{ norm(std::declval<typename T::vector_type>()) } -> std::totally_ordered;
	};

	template<class T, class ScalarType>
	concept usable_in_hilbert_space = vector<T, ScalarType>
		&& requires(T a)
	{
		{ inner_product(a) } -> std::totally_ordered;
	};

	template<class T>
	concept hilbert_space = normed_space<T>
		&& requires(T)
	{
		typename T::norm_is_sqrt_of_inner_product;

		{ inner_product(std::declval<typename T::vector_type>(), std::declval<typename T::vector_type>()) }
			-> std::totally_ordered;
	};

	template<hilbert_space H>
	constexpr auto norm_squared(typename H::vector_type a)
	{
		return inner_product(a, a);
	}

	template<hilbert_space H>
	constexpr auto norm(typename H::vector_type a)
	{
		return std::sqrt(norm_squared(a));
	}

	template<class T>
	concept affine_hilbert_space = metric_space<T> && hilbert_space<T>;

	template<affine_hilbert_space H>
	constexpr auto distance_squared(typename H::point_type a, typename H::point_type b)
	{
		return norm_squared(a - b);
	}

	template<affine_hilbert_space H>
	constexpr auto distnace(typename H::point_type a, typename H::point_type b)
	{
		return std::sqrt(distance_squared(a, b));
	}
}
#endif