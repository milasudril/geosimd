#ifndef GEOSIMD_VECTORSPACE_HPP
#define GEOSIMD_VECTORSPACE_HPP

#include <cstddef>
#include <concepts>
#include <cstdint>
#include <complex>

#include <string>

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
	constexpr auto distance(T const* a, T const* b)
	{
		return a < b ? (b - a) : (a - b);
	}

	template<class T>
	concept metric_space = affine_space<T>
		&& requires(T)
	{
		{ distance(std::declval<typename T::point_type>(), std::declval<typename T::point_type>()) }
			-> std::same_as<typename T::scalar_type>;
	};


#if 0


	template<class T>
	concept vector_space = requires(T)
	{
		typename T::vector_type;
		typename T::scalar_type;

		{ std::declval<typename T::vector_type>() - std::declval<typename T::vector_type>() }
			-> std::same_as<typename T::vector_type>;

		{ std::declval<typename T::vector_type>() + std::declval<typename T::vector_type>() }
			-> std::same_as<typename T::vector_type>;

		{ std::declval<typename T::vector_type&>() -= std::declval<typename T::vector_type>() }
			-> std::same_as<typename T::vector_type&>;

		{ std::declval<typename T::vector_type&>() += std::declval<typename T::vector_type>() }
			-> std::same_as<typename T::vector_type&>;

		{ std::declval<typename T::vector_type&>() *= std::declval<typename T::scalar_type>() }
			-> std::same_as<typename T::vector_type&>;

		{ std::declval<typename T::vector_type&>() /= std::declval<typename T::scalar_type>() }
			-> std::same_as<typename T::vector_type&>;

		{ std::declval<typename T::scalar_type>() * std::declval<typename T::vector_type>() }
			-> std::same_as<typename T::vector_type>;

		{ std::declval<typename T::vector_type>() * std::declval<typename T::scalar_type>() }
			-> std::same_as<typename T::vector_type>;

		{ std::declval<typename T::vector_type>() / std::declval<typename T::scalar_type>() }
			-> std::same_as<typename T::vector_type>;

		{ typename T::vector_type{zero{}} } -> std::same_as<typename T::vector_type>;

		{ T::dimension_count() } -> std::same_as<size_t>;

		typename std::integral_constant<size_t, T::dimension_count()>;
	};
#endif
}
#endif