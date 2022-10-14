#ifndef GEOSIMD_VECTORPS_MIXIN_HPP
#define GEOSIMD_VECTORPS_MIXIN_HPP

#include "./inline.hpp"
#include "./container_props.hpp"

#include <cstddef>
#include <iterator>
#include <type_traits>

namespace geosimd
{
	template<class Derived>
	struct vectorops_mixin
	{
		GEOSIMD_FULL_INLINE constexpr Derived& operator+=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.m_value += other.m_value;
			return derived;
		}

		GEOSIMD_FULL_INLINE constexpr Derived& operator-=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.m_value -= other.m_value;
			return derived;
		}

		GEOSIMD_FULL_INLINE constexpr Derived operator-() const
		{
			auto& derived = static_cast<Derived const&>(*this);
			return Derived{-derived.m_value};
		}

		GEOSIMD_FULL_INLINE constexpr Derived operator+() const
		{
			auto& derived = static_cast<Derived const&>(*this);
			return derived;
		}

		template<class T = Derived>
		GEOSIMD_FULL_INLINE constexpr Derived& operator*=(typename T::scalar_type other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.m_value *= other;
			return derived;
		}

		template<class T = Derived>
		GEOSIMD_FULL_INLINE friend constexpr auto operator*(typename T::scalar_type a, Derived b)
		{ return b *= a; }

		template<class T = Derived>
		GEOSIMD_FULL_INLINE friend constexpr auto operator*(Derived b, typename T::scalar_type a)
		{ return b *= a; }

		template<class T = Derived>
		GEOSIMD_FULL_INLINE constexpr Derived& operator/=(typename T::scalar_type other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.m_value /= other;
			return derived;
		}

		GEOSIMD_FLATTEN constexpr bool operator==(Derived other) const
		{
			if constexpr(subscriptable<Derived>)
			{
				using scalar_type = typename Derived::scalar_type;
				auto const diff = static_cast<Derived const&>(*this) - other;
				for(size_t k = 0; k != std::size(diff); ++k)
				{
					if(diff[k] != scalar_type{})
					{ return false; }
				}
				return true;
			}
			else
			{return static_cast<Derived const&>(*this).m_value == other.m_value;}
		}

		GEOSIMD_INLINE_OPT constexpr bool operator!=(Derived other) const
		{
			return !(*this == other);
		}

		template<class T = Derived>
		requires requires(T) { typename Derived::enable_hadamard_product_t; }
		GEOSIMD_FULL_INLINE constexpr Derived& operator*=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.m_value *= other.m_value;
			return derived;
		}

		template<class T = Derived>
		requires requires(T) { typename T::enable_hadamard_product_t; }
		GEOSIMD_FULL_INLINE constexpr Derived& operator/=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.m_value /= other.m_value;
			return derived;
		}

		GEOSIMD_FULL_INLINE friend constexpr auto operator*(Derived a, Derived b)
		{ return a *= b; }

		GEOSIMD_FULL_INLINE friend constexpr auto operator/(Derived a, Derived b)
		{ return a /= b; }

		template<class T = Derived>
		GEOSIMD_FULL_INLINE friend constexpr auto operator/(Derived a, typename T::scalar_type b)
		{ return a /= b; }

		GEOSIMD_FULL_INLINE friend constexpr auto operator+(Derived a, Derived b)
		{ return a += b; }

		GEOSIMD_FULL_INLINE friend constexpr auto operator-(Derived a, Derived b)
		{ return a -= b; }
	};


	template<class Derived>
	inline constexpr auto uses_vectorops_mixin_v = std::is_base_of_v<vectorops_mixin<Derived>, Derived>;
}

#endif