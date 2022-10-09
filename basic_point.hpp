#ifndef GEOSIMD_BASICPOINT_HPP
#define GEOSIMD_BASICPOINT_HPP

#include "./vectorops_mixin.hpp"
#include "./basic_vector.hpp"

#include <utility>

namespace geosimd
{
	template<affine_space V>
	class basic_point
	{
	public:
		using vector_type = typename V::vector_type;
		using scalar_type = typename V::scalar_type;
		using storage_type = typename V::point_type;

		GEOSIMD_INLINE_OPT constexpr basic_point(): m_value{make_origin()}
		{}

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
			&& (!has_homogenous_coordinates<V>)
		GEOSIMD_INLINE_OPT constexpr explicit basic_point(scalar_type x, Args ... xn):
			m_value{x, xn...}
		{}

		template<class T = void>
		requires(!has_homogenous_coordinates<V>)
		GEOSIMD_INLINE_OPT constexpr explicit basic_point(storage_type val):
			m_value{val}
		{}

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
			&& (has_homogenous_coordinates<V>)
		GEOSIMD_INLINE_OPT constexpr explicit basic_point(scalar_type x, Args ... xn):
			m_value{x, xn..., one(empty<scalar_type>{})}
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

		constexpr bool operator==(basic_point const&) const = default;
		constexpr bool operator!=(basic_point const&) const = default;

		GEOSIMD_INLINE_OPT constexpr basic_point& operator+=(vector_type other)
		{
			m_value += other;
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr basic_point& operator-=(vector_type other)
		{
			m_value -= other;
			return *this;
		}

	private:
		storage_type m_value;

		template<size_t ... Is>
		GEOSIMD_INLINE_OPT static constexpr auto make_origin(std::index_sequence<Is...>)
		{
			if constexpr(has_homogenous_coordinates<V>)
			{
				return storage_type
				{
					(static_cast<void>(Is), zero(empty<scalar_type>{}))...,
					one(empty<scalar_type>{})
				};
			}
			else
			{
				return storage_type
				{
					(static_cast<void>(Is), zero(empty<scalar_type>{}))...,
					zero(empty<scalar_type>{})
				};
			}
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

	template<affine_space V>
	GEOSIMD_INLINE_OPT constexpr auto operator+(basic_point<V> a, typename basic_point<V>::vector_type b)
	{ return a += b; }

	template<affine_space V>
	GEOSIMD_INLINE_OPT constexpr auto operator-(basic_point<V> a, typename basic_point<V>::vector_type b)
	{ return a -= b; }

	template<affine_space V>
	GEOSIMD_INLINE_OPT constexpr auto operator-(basic_point<V> a, basic_point<V> b)
	{ return typename basic_point<V>::vector_type{a.get() - b.get()}; }

	template<metric_space V>
	GEOSIMD_INLINE_OPT constexpr auto distance(basic_point<V> a, basic_point<V> b)
	{
		if constexpr(overrides_distance<V>)
		{ return V::distance(a.get(), b.get()); }
		else
		{ return distance(a.get(), b.get()); }
	}

	template<metric_space V>
	GEOSIMD_INLINE_OPT constexpr auto distance_squared(basic_point<V> a, basic_point<V> b)
	{
		return V::distance_squared(a.get(), b.get());
	}

	template<affine_space V>
	GEOSIMD_INLINE_OPT constexpr auto origin()
	{
		return basic_point<V>{};
	}
}

#endif