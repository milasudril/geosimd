#ifndef GEOSIMD_HILBERT_SPACE_HPP
#define GEOSIMD_HILBERT_SPACE_HPP

#include "./abstract_spaces.hpp"
#include "./inline.hpp"

namespace geosimd
{
	template<class VectorType, class ScalarType = typename VectorType::scalar_type>
	requires supports_inner_product<VectorType, ScalarType>
	struct hilbert_space_mixin
	{
		using vector_type = VectorType;
		using scalar_type = ScalarType;

		GEOSIMD_INLINE_OPT static constexpr auto norm(vector_type v)
		{
			codecov::function_called(__FILE__, __LINE__);
			return std::sqrt(norm_squared(v));
		}

		GEOSIMD_INLINE_OPT static constexpr auto norm_squared(vector_type v)
		{
			codecov::function_called(__FILE__, __LINE__);
			return inner_product(v);
		}
	};

	template<class V>
	concept hilbert_space = std::is_base_of_v<hilbert_space_mixin<typename V::vector_type, typename V::scalar_type>, V>;
}

#endif