#ifndef GEOSIMD_BASICPOINT_HPP
#define GEOSIMD_BASICPOINT_HPP

#include "./vector_spaces.hpp"
#include "./vectorops_mixin.hpp"
#include "./basic_vector.hpp"

namespace geosimd
{
	template<affine_space V>
	class basic_point
	{
	public:
		using vector_type = typename V::vector_type;
		using scalar_type = typename V::scalar_type;
		using storage_type = typename V::point_type;

		template<class T = void>
		requires(!has_homogenous_coordinates<V>)
		GEOSIMD_INLINE_OPT constexpr basic_point():m_value{}{}

		template<class T = void>
		requires(has_homogenous_coordinates<V> && has_size<storage_type>)
		GEOSIMD_INLINE_OPT constexpr basic_point():m_value{}
		{
			m_value[std::size(m_value) - 1] = one(empty<scalar_type>{});
		}

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
			&& (!has_homogenous_coordinates<V>)
		GEOSIMD_INLINE_OPT constexpr explicit basic_point(scalar_type x, Args ... xn):
			m_value{x, xn...}
		{}

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
			&& (has_homogenous_coordinates<V>)
		GEOSIMD_INLINE_OPT constexpr explicit basic_point(scalar_type x, Args ... xn):
			m_value{x, xn..., one(empty<scalar_type>{})}
		{}

		GEOSIMD_INLINE_OPT constexpr scalar_type operator[](size_t n) const
		{
			if constexpr(has_subscript_operator<storage_type>)
			{ return m_value[n]; }
			else
			{ return m_value; }
		}

		GEOSIMD_INLINE_OPT constexpr size_t size() const
		{
			if constexpr(has_size<storage_type>)
			{ return std::size(m_value) - static_cast<size_t>(has_homogenous_coordinates<V>); }
			else
			{ return 1; }
		}

		GEOSIMD_INLINE_OPT constexpr auto get() const
		{ return m_value; }

	private:
		storage_type m_value;
	};
#if 0
	template<normed_space V>
	auto norm(basic_point<V> a)
	{
		if constexpr(overrides_norm<V>)
		{ return V::norm(a.get()); }
		else
		{ return norm(a.get()); }
	}

	template<vector_space V>
	requires is_hilbert_space_v<V>
	auto norm_squared(basic_point<V> a)
	{
		return V::norm_squared(a.get());
	}
#endif
}

#endif