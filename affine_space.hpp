#ifndef GEOSIMD_AFFINESPACE_HPP
#define GEOSIMD_AFFINESPACE_HPP

#include "./vector_space.hpp"

#include <cstddef>
#include <concepts>

namespace geosimd
{
	template<class T>
	concept affine_space = requires(T)
	{
		typename T::vector_type;
		typename T::scalar_type;

		{ std::declval<typename T::vector_type>() - std::declval<typename T::vector_type>() } -> std::same_as<typename T::vector_type>;

		{ std::declval<typename T::vector_type>() + std::declval<typename T::vector_type>() } -> std::same_as<typename T::vector_type>;

		{ std::declval<typename T::vector_type&>() -= std::declval<typename T::vector_type>() } -> std::same_as<typename T::vector_type&>;

		{ std::declval<typename T::vector_type&>() += std::declval<typename T::vector_type>() } -> std::same_as<typename T::vector_type&>;

		{ T::dimension_count() } -> std::same_as<size_t>;
		typename std::integral_constant<size_t, T::dimension_count()>;
	};
}

#endif