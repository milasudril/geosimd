#ifndef GEOSIMD_HILBERTSPACE_HPP
#define GEOSIMD_HILBERTSPACE_HPP

#include "./abstract_spaces.hpp"

namespace geosimd
{
	template<class VectorType, class ScalarType = typename VectorType::scalar_type>
	requires supports_inner_product<VectorType, ScalarType>
	struct hilbert_space_mixin
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
	concept hilbert_space = std::is_base_of_v<hilbert_space_mixin<typename V::vector_type, typename V::scalar_type>, V>;
}

#endif