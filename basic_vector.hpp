#ifndef GEOSIMD_BASICVECTOR_HPP
#define GEOSIMD_BASICVECTOR_HPP

#include "./abstract_spaces.hpp"
#include "./vectorops_mixin.hpp"
#include "./hilbert_space.hpp"

#include <utility>

namespace geosimd
{
	template<vector_space V>
	class basic_vector:public vectorops_mixin<basic_vector<V>>
	{
	public:
		using scalar_type = typename V::scalar_type;
		using storage_type = typename V::vector_type;
		using vector_type = basic_vector<V>;

		friend class vectorops_mixin<vector_type>;

		GEOSIMD_INLINE_OPT constexpr basic_vector():m_value{make_origin()}{}

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
			&& (!has_homogenous_coordinates<V>)
		GEOSIMD_INLINE_OPT constexpr explicit basic_vector(scalar_type x, Args ... xn):
			m_value{x, xn...}
		{}

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
			&& (has_homogenous_coordinates<V>)
		GEOSIMD_INLINE_OPT constexpr explicit basic_vector(scalar_type x, Args ... xn):
			m_value{x, xn..., zero(empty<scalar_type>{})}
		{}

		GEOSIMD_INLINE_OPT constexpr scalar_type operator[](size_t n) const
		{
			if constexpr(subscriptable<storage_type>)
			{ return m_value[n]; }
			else
			{ return m_value; }
		}

		GEOSIMD_INLINE_OPT constexpr size_t size() const
		{
			if constexpr(supports_size<storage_type>)
			{ return std::size(m_value) - static_cast<size_t>(has_homogenous_coordinates<V>); }
			else
			{ return 1; }
		}

		GEOSIMD_INLINE_OPT constexpr auto get() const
		{ return m_value; }

	private:
		storage_type m_value;

		template<size_t ... Is>
		GEOSIMD_INLINE_OPT static constexpr auto make_origin(std::index_sequence<Is...>)
		{
			return storage_type
			{
				(static_cast<void>(Is), zero(empty<scalar_type>{}))...,
				zero(empty<scalar_type>{})
			};
		}

		GEOSIMD_INLINE_OPT static constexpr auto make_origin()
		{
			if constexpr(supports_static_constexpr_size<storage_type>)
			{
				return make_origin(std::make_index_sequence<storage_type::size() - 1>());
			}
			else
			{ return zero(empty<storage_type>{}); }
		}
	};

	template<normed_space V>
	GEOSIMD_INLINE_OPT constexpr auto norm(basic_vector<V> a)
	{
		if constexpr(overrides_norm<V>)
		{ return V::norm(a.get()); }
		else
		{ return norm(a.get()); }
	}

	template<hilbert_space V>
	GEOSIMD_INLINE_OPT constexpr auto norm_squared(basic_vector<V> a)
	{
		return V::norm_squared(a.get());
	}
}

#endif