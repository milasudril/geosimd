#ifndef GEOSIMD_BASICVECTOR_HPP
#define GEOSIMD_BASICVECTOR_HPP

#include "./vector_spaces.hpp"
#include "./vectorops_mixin.hpp"

namespace geosimd
{
	template<vector_space V>
	class basic_vector:public vectorops_mixin<basic_vector<V>, typename V::scalar_type>
	{
	public:
		friend class vectorops_mixin<basic_vector<V>, typename V::scalar_type>;

		using scalar_type = typename V::scalar_type;
		using vector_type = typename V::vector_type;

		GEOSIMD_INLINE_OPT constexpr scalar_type operator[](size_t n) const
		{ return m_value[n]; }

	private:
		vector_type m_value;
	};
}

#endif