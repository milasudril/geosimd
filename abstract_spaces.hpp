#ifndef GEOSIMD_ABSTRACTSPACES_HPP
#define GEOSIMD_ABSTRACTSPACES_HPP

#include "./factories.hpp"
#include "./default_norm.hpp"

#include <complex>
#include <type_traits>

namespace geosimd
{
	template<class T>
	concept complex = requires(T a)
	{
		{a.real()} -> std::same_as<typename T::value_type>;
		{a.imag()}-> std::same_as<typename T::value_type>;
	};

	template<size_t N>
	struct dimension_tag:std::integral_constant<size_t, N>{};

	template<class T>
	concept scalar = (std::is_arithmetic_v<T> && std::is_signed_v<T>)
		|| (complex<T> && (std::is_arithmetic_v<typename T::value_type> &&
		// TODO: Does std::is_signed_v imply std::is_arithmetic_v?
		std::is_signed_v<typename T::value_type>));

	template<class T, class ScalarType = typename T::scalar_type>
	concept vector = std::equality_comparable<T> && scalar<ScalarType> && requires(T a, T b, ScalarType c)
	{
		{a + b} -> std::same_as<T>;
		{a - b} -> std::same_as<T>;
		{c * a} -> std::same_as<T>;
		{a * c} -> std::same_as<T>;
		{a / c} -> std::same_as<T>;
		{-a} -> std::same_as<T>;
		{zero(std::declval<empty<T>>())} -> std::same_as<T>;
	};

	template<class T>
	concept vector_space = vector<typename T::vector_type, typename T::scalar_type>;

	template<class T, class VectorType = typename T::vector_type, class ScalarType = typename T::scalar_type>
	concept point = std::equality_comparable<T>
		&& vector<VectorType, ScalarType>
		&& requires(T p1, T p2, VectorType v)
	{
		{p1 + v} -> std::same_as<T>;
		{p1 - v} -> std::same_as<T>;
		{p1 - p2} -> std::same_as<VectorType>;
	};

	template<class T>
	concept affine_space = vector_space<T>
		&& point<typename T::point_type, typename T::vector_type, typename T::scalar_type>;

	template<class T>
	concept overrides_distance = affine_space<T>
		&& requires(T)
	{
		{ T::distance(std::declval<typename T::point_type>(), std::declval<typename T::point_type>()) }
			-> std::totally_ordered;
	};

	template<class T>
	concept metric_space = affine_space<T> && (supports_distance<typename T::point_type> || overrides_distance<T>);

	template<class T>
	concept overrides_norm = vector_space<T>
		&& requires(T)
	{
		{ T::norm(std::declval<typename T::vector_type>()) } -> std::totally_ordered;
	};

	template<class T>
	concept normed_space = vector_space<T>
		&& (supports_norm<typename T::vector_type> || overrides_norm<T>);

	template<class T, class ScalarType>
	concept supports_inner_product = vector<T, ScalarType> && requires(T a, T b)
	{
		{inner_product(a, b)} -> std::same_as<ScalarType>;

		{inner_product(a)} -> std::totally_ordered;
	};

	template<class T>
	concept inner_product_space = vector_space<T>
		&& supports_inner_product<typename T::vector_type, typename T::scalar_type>;

	template<class V>
	concept has_homogenous_coordinates = requires(V){ typename V::enable_homogenous_coordinates_t; };

	template<class V>
	concept has_rotations = requires(V){ typename V::enable_rotations_t; };
}
#endif
