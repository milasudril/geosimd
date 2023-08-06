#ifndef GEOSIMD_SCALING_HPP
#define GEOSIMD_SCALING_HPP

#include "./abstract_spaces.hpp"
#include "./container_props.hpp"
#include "./factories.hpp"

#include <cmath>

namespace geosimd
{
	template<vector_space V>
	requires (std::is_floating_point_v<typename V::scalar_type>)
	class scaling
	{
	public:
		using scalar_type = typename V::scalar_type;
		using storage_type = typename V::vector_type;

		GEOSIMD_INLINE_OPT constexpr scaling():
			m_value{ones(empty<storage_type>{})}{}

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
			&& (!has_homogenous_coordinates<V> && !std::is_same_v<scalar_type, storage_type>)
		GEOSIMD_INLINE_OPT constexpr explicit scaling(scalar_type x, Args ... xn):
			m_value{x, xn...}
		{ codecov::function_called(__FILE__, __LINE__); }

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
			&& (has_homogenous_coordinates<V>)
		GEOSIMD_INLINE_OPT constexpr explicit scaling(scalar_type x, Args ... xn):
			m_value{x, xn..., one<scalar_type>()}
		{ }

		GEOSIMD_INLINE_OPT constexpr auto const& get() const
		{ return m_value; }

		template<class = void>
		requires(!supports_static_constexpr_size<storage_type> && supports_size<storage_type>)
		GEOSIMD_INLINE_OPT constexpr size_t size() const
		{ return std::size(m_value) - static_cast<size_t>(has_homogenous_coordinates<V>); }

		template<class = void>
		requires(supports_static_constexpr_size<storage_type>)
		GEOSIMD_INLINE_OPT static constexpr size_t size()
		{ return storage_type::size() - static_cast<size_t>(has_homogenous_coordinates<V>); }

		template<class = void>
		requires(!supports_size<storage_type>)
		GEOSIMD_INLINE_OPT static constexpr size_t size()
		{ return 1; }

		GEOSIMD_INLINE_OPT scalar_type operator[](size_t index) const
		{ return m_value[index]; }

		constexpr bool operator==(scaling const&) const = default;

		constexpr bool operator!=(scaling const&) const = default;

		GEOSIMD_INLINE_OPT constexpr scaling& invert()
		{
			*this = scaling{}/(*this);
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr scaling& push(scaling other)
		{ return *this *= other; }

		GEOSIMD_INLINE_OPT constexpr scaling& pop(scaling other)
		{ return *this /= other; }

		GEOSIMD_INLINE_OPT constexpr scaling& operator/=(scaling other)
		{
			m_value/=other.get();
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr scaling& operator*=(scaling other)
		{
			m_value*=other.get();
			return *this;
		}


		GEOSIMD_INLINE_OPT constexpr scaling& operator/=(scalar_type other)
		{
			*this/=scaling{other, other, other};
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr scaling& operator*=(scalar_type other)
		{
			*this*=scaling{other, other, other};
			return *this;
		}

	private:
		storage_type m_value;
	};

	template<vector_space V>
	inline auto to_string(scaling<V> s)
	{ return to_string(s.get()); }

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr auto inverted(scaling<V> s)
	{
		auto tmp = s;
		return tmp.invert();
	}

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr auto one(empty<scaling<V>>)
	{ return scaling<V>{}; }

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr scaling<V> operator/(scaling<V> a, scaling<V> b)
	{
		a/=b;
		return a;
	}

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr scaling<V> operator*(scaling<V> a, scaling<V> b)
	{
		a*=b;
		return a;
	}

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr scaling<V> operator/(scaling<V> a, typename V::scalar_type b)
	{
		a/=b;
		return a;
	}

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr scaling<V> operator*(scaling<V> a, typename V::scalar_type b)
	{
		a*=b;
		return a;
	}

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr scaling<V> operator*(typename V::scalar_type a, scaling<V> b)
	{ return b*a; }


	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr auto norm(scaling<V> s)
	{
		using scalar_type = typename V::scalar_type;
		auto ret = one(empty<scalar_type>{});
		auto const val = s.get();
		for(size_t k = 0; k != std::size(s); ++k)
		{ ret*=val[k]; }

		return std::pow(ret, one(empty<scalar_type>{})/std::size(s));
	}
}

#endif