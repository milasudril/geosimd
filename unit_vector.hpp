#ifndef GEOSIMD_UNITVECTOR_HPP
#define GEOSIMD_UNITVECTOR_HPP

#include "./abstract_spaces.hpp"
#include "./vectorops_mixin.hpp"
#include "./basic_vector.hpp"

namespace geosimd
{
	template<normed_space V>
	class unit_vector:public vectorops_mixin<unit_vector<V>>
	{
		using vectorops_magic = typename vectorops_mixin<unit_vector<V>>::magic;
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

		void get(vectorops_magic) = delete;

		GEOSIMD_INLINE_OPT friend constexpr auto operator*(scalar_type c, unit_vector v)
		{
			return c*v.m_value;
		}

		GEOSIMD_INLINE_OPT friend constexpr auto operator*(unit_vector v, scalar_type c)
		{
			return v.m_value*c;
		}

		GEOSIMD_INLINE_OPT friend constexpr auto operator/(unit_vector v, scalar_type c)
		{
			return v.m_value/c;
		}

	private:
		vector_type m_value;
	};

	template<normed_space V>
	inline auto to_string(unit_vector<V> val)
	{
		using std::to_string;
		return to_string(val.get());
	}

	template<inner_product_space V>
	GEOSIMD_INLINE_OPT constexpr auto inner_product(basic_vector<V> a, unit_vector<V> b)
	{
		return inner_product(a, b.get());
	}

	template<inner_product_space V>
	GEOSIMD_INLINE_OPT constexpr auto inner_product(unit_vector<V> a, unit_vector<V> b)
	{
		return inner_product(a.get(), b.get());
	}
}

#endif