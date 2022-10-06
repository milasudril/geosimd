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
		using scalar_type = typename V::scalar_type;
		using storage_type = typename V::vector_type;
		using vector_type = basic_vector<V>;

		friend class vectorops_mixin<vector_type, typename V::scalar_type>;

		GEOSIMD_INLINE_OPT constexpr basic_vector():m_value{}{}

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
		GEOSIMD_INLINE_OPT constexpr explicit basic_vector(scalar_type x, Args ... xn):
			m_value{x, xn..., scalar_type{}}
		{}

		GEOSIMD_INLINE_OPT constexpr scalar_type operator[](size_t n) const
		{ return m_value[n]; }

	private:
		storage_type m_value;
	};
}

#endif