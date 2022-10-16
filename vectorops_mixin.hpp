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
	class vectorops_mixin
	{
	protected:
		struct magic{};
	public:
		GEOSIMD_FULL_INLINE friend constexpr auto& operator+=(Derived& a, Derived b)
		{
			a.get(magic{}) += b.get();
			return a;
		}

		GEOSIMD_FULL_INLINE friend constexpr auto& operator-=(Derived& a, Derived b)
		{
			a.get(magic{}) -= b.get();
			return a;
		}

		GEOSIMD_FULL_INLINE constexpr Derived operator-() const
		{
			auto& derived = static_cast<Derived const&>(*this);
			return Derived{-derived.get()};
		}

		GEOSIMD_FULL_INLINE constexpr Derived operator+() const
		{ return static_cast<Derived const&>(*this); }

		template<class T = Derived>
		GEOSIMD_FULL_INLINE friend constexpr auto& operator*=(Derived& a, typename T::scalar_type b)
		{
			a.get(magic{}) *= b;
			return a;
		}

		template<class T = Derived>
		GEOSIMD_FULL_INLINE friend constexpr auto operator*(typename T::scalar_type a, Derived b)
		{ return b *= a; }

		template<class T = Derived>
		GEOSIMD_FULL_INLINE friend constexpr auto operator*(Derived b, typename T::scalar_type a)
		{ return b *= a; }

		template<class T = Derived>
		GEOSIMD_FULL_INLINE friend constexpr Derived& operator/=(Derived& a, typename T::scalar_type b)
		{
			a.get(magic{}) /= b;
			return a;
		}

		GEOSIMD_FLATTEN friend constexpr bool operator==(Derived a, Derived b)
		{
			if constexpr(subscriptable<Derived>)
			{
				using scalar_type = typename Derived::scalar_type;
				auto const diff = a - b;
				for(size_t k = 0; k != std::size(diff); ++k)
				{
					if(diff[k] != scalar_type{})
					{ return false; }
				}
				return true;
			}
			else
			{return a.get() == b.get();}
		}

		GEOSIMD_INLINE_OPT friend constexpr bool operator!=(Derived a, Derived b)
		{
			return !(a == b);
		}

		template<class T = Derived>
		requires requires(T) { typename Derived::enable_hadamard_product_t; }
		GEOSIMD_FULL_INLINE friend constexpr Derived& operator*=(Derived& a, Derived b)
		{
			a.get(magic{}) *= b.get();
			return a;
		}

		template<class T = Derived>
		requires requires(T) { typename T::enable_hadamard_product_t; }
		GEOSIMD_FULL_INLINE friend constexpr Derived& operator/=(Derived& a, Derived b)
		{
			a.get(magic{}) /= b.get();
			return a;
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