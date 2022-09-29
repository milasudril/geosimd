#ifndef GEOSIMD_HILBERTSPACE_HPP
#define GEOSIMD_HILBERTSPACE_HPP

#include <concepts>

namespace geosimd
{
	template<class T>
	concept hilbert_space = requires(T)
	{
		typename T::norm_is_sqrt_of_inner_product;

		{inner_product(std::declval<typename T::vector_type>(), std::declval<typename T::vector_type>())}
			-> std::same_as<typename T::scalar_type>;
	};
}

#endif