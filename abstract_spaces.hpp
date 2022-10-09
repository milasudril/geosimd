#ifndef GEOSIMD_ABSTRACTSPACES_HPP
#define GEOSIMD_ABSTRACTSPACES_HPP

#include "./adl_factories.hpp"

#include <cstddef>
#include <concepts>
#include <cstdint>
#include <complex>
#include <cmath>
#include <cstdlib>

namespace geosimd
{
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

	template<class T, class ScalarType = typename T::scalar_type>
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

	template<class T, class VectorType = typename T::vector_type, class ScalarType = typename T::scalar_type>
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
	concept supports_distance = requires(T a, T b)
	{
		{ distance(a, b) } -> std::totally_ordered;
	};

	template<class T>
	concept overrides_distance = affine_space<T>
		&& requires(T)
	{
		{ T::distance(std::declval<typename T::point_type>(), std::declval<typename T::point_type>()) }
			-> std::totally_ordered;
	};

	template<class T>
	concept metric_space = affine_space<T> && (supports_distance<typename T::point_type> || overrides_distance<T>);

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

	template<class VectorType, class ScalarType = typename VectorType::scalar_type>
	requires supports_inner_product<VectorType, ScalarType>
	struct hilbert_space
	{
		using vector_type = VectorType;
		using scalar_type = ScalarType;

		static constexpr auto norm(vector_type v)
		{
			return std::sqrt(norm_squared(v));
		}

		static constexpr auto norm_squared(vector_type v)
		{
			return inner_product(v);
		}
	};

	template<class V>
	concept implements_hilbert_space = std::is_base_of_v<hilbert_space<typename V::vector_type, typename V::scalar_type>, V>;

	template<vector_space V>
	constexpr inline auto is_hilbert_space_v = implements_hilbert_space<V>;

	template<class PointType, normed_space V>
	struct metric_normed_space: public V
	{
		using point_type = PointType;
		using vector_space = V;
		using vector_type = vector_space::vector_type;
		using scalar_type = vector_space::scalar_type;

		static constexpr auto distance(point_type a, point_type b)
		{ return vector_space::norm(a - b); }

		static constexpr auto distance_squared(point_type a, point_type b)
		{ return vector_space::norm_squared(a - b); }
	};

	template<class V>
	concept has_homogenous_coordinates = requires(V){ typename V::enable_homogenous_coordinates_t; };

	template<class VectorType>
	concept has_subscript_operator = requires(VectorType a)
	{
		{ a[std::declval<size_t>()] };
	};

	template<class VectorType>
	concept has_size = requires(VectorType a)
	{
		{ std::size(a) } -> std::same_as<size_t>;
	};

}
#endif