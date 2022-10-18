#ifndef GEOSIMD_UNITVECTOR_HPP
#define GEOSIMD_UNITVECTOR_HPP

#include "./abstract_spaces.hpp"

namespace geosimd
{
	template<normed_space V>
	class unit_vector
	{
	public:
		using vector_type = basic_vector<V>;
		using scalar_type = vector_type::scalar_type;

		GEOSIMD_INLINE_OPT constexpr explicit unit_vector(vector_type val):
			m_value{val/norm(val)}
		{}

		GEOSIMD_INLINE_OPT constexpr scalar_type operator[](size_t n) const
		{
			if constexpr(subscriptable<vector_type>)
			{ return m_value[n]; }
			else
			{ return m_value; }
		}

		GEOSIMD_INLINE_OPT constexpr size_t size() const
		{
			if constexpr(supports_size<vector_type>)
			{ return std::size(m_value) - static_cast<size_t>(has_homogenous_coordinates<V>); }
			else
			{ return 1; }
		}

		auto get() const
		{ return m_value; }

		GEOSIMD_INLINE_OPT friend constexpr auto operator*(scalar_type c, unit_vector v)
		{
			return c*v.m_value;
		}

		GEOSIMD_INLINE_OPT friend constexpr auto operator*(unit_vector v, scalar_type c)
		{
			return v.m_value*c;
		}

	private:
		vector_type m_value;
	};
}

#endif