#ifndef ARITHMETIC_MIXIN_HPP
#define ARITHMETIC_MIXIN_HPP

#include "./inline.hpp"

#include <cstddef>
#include <iterator>
#include <type_traits>

namespace geosimd
{
	template<class Derived, class ScalarType, bool EnableHadamardProduct = false>
	struct arithmetic_mixin
	{
		using scalar_type = ScalarType;


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

		GEOSIMD_FULL_INLINE constexpr Derived& operator*=(scalar_type other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.m_value *= other;
			return derived;
		}

		GEOSIMD_FULL_INLINE constexpr Derived& operator/=(scalar_type other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.m_value /= other;
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

		GEOSIMD_FLATTEN constexpr bool operator==(Derived other) const
		{
			auto const diff = static_cast<Derived const&>(*this) - other;
			for(size_t k = 0; k != std::size(diff); ++k)
			{
				if(diff[k] != scalar_type{})
				{ return false; }
			}
			return true;
		}

		GEOSIMD_INLINE_OPT constexpr bool operator!=(Derived other) const
		{
			return !(*this == other);
		}

		template<class T = Derived>
		requires EnableHadamardProduct
		GEOSIMD_FULL_INLINE constexpr Derived& operator*=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.m_value *= other.m_value;
			return derived;
		}

		template<class T = Derived>
		requires EnableHadamardProduct
		GEOSIMD_FULL_INLINE constexpr Derived& operator/=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.m_value /= other.m_value;
			return derived;
		}
	};

	template<class Op1, class Op2>
	GEOSIMD_FULL_INLINE constexpr auto operator*(Op1 a, Op2 b)
	{ return a *= b; }

	template<class Op1, class Op2>
	GEOSIMD_FULL_INLINE constexpr auto operator/(Op1 a, Op2 b)
	{ return a /= b; }

	template<class Op1, class Op2>
	GEOSIMD_FULL_INLINE constexpr auto operator+(Op1 a, Op2 b)
	{ return a += b; }

	template<class Op1, class Op2>
	GEOSIMD_FULL_INLINE constexpr auto operator-(Op1 a, Op2 b)
	{ return a -= b; }

	template<class Derived, class ScalarType = typename Derived::scalar_type>
	inline constexpr auto uses_arithmetic_mixin_v =
		std::is_base_of_v<arithmetic_mixin<Derived, ScalarType, false>, Derived> ||
		std::is_base_of_v<arithmetic_mixin<Derived, ScalarType, true>, Derived>;
}

#endif