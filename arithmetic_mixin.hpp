#ifndef ARITHMETIC_MIXIN_HPP
#define ARITHMETIC_MIXIN_HPP

#include "./inline.hpp"

#include <cstddef>
#include <iterator>

namespace geosimd
{
	template<class Derived, class ScalarType>
	struct arithmetic_mixin
	{
		using scalar_type = ScalarType;

		GEOSIMD_FULL_INLINE constexpr Derived& operator*=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.get() *= other.get();
			return derived;
		}

		GEOSIMD_FULL_INLINE constexpr Derived& operator/=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.get() /= other.get();
			return derived;
		}

		GEOSIMD_FULL_INLINE constexpr Derived& operator+=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.get() += other.get();
			return derived;
		}

		GEOSIMD_FULL_INLINE constexpr Derived& operator-=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.get() -= other.get();
			return derived;
		}

		GEOSIMD_FULL_INLINE constexpr Derived& operator*=(scalar_type other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.get() *= other;
			return derived;
		}

		GEOSIMD_FULL_INLINE constexpr Derived& operator/=(scalar_type other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.get() /= other;
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

		GEOSIMD_INLINE constexpr bool operator!=(Derived other) const
		{
			return !(*this == other);
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
}

#endif