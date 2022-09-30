#ifndef GEOSIMD_VECTORSPACE_HPP
#define GEOSIMD_VECTORSPACE_HPP

#include <cstddef>
#include <concepts>
#include <cstdint>

namespace geosimd
{
	template<class T>
	using empty = std::type_identity<T>;

	template<class T>
	T zero(empty<T>)
	{ return T{}; }

	template<class T, class ScalarType>
	concept vector = std::equality_comparable<T> && requires(T a, T b, ScalarType c)
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

	template<class T, class VectorType>
	concept point = std::equality_comparable<T>
		&& !std::is_same_v<T, VectorType>
		&& requires(T p1,T p2, VectorType v)
	{
		{p1 + v} -> std::same_as<T>;
		{p1 - v} -> std::same_as<T>;
		{p1 += v} -> std::same_as<T&>;
		{p1 -= v} -> std::same_as<T&>;
		{p1 - p2} -> std::same_as<VectorType>;
	};

	static_assert(point<int*, intptr_t>);

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