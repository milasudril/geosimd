#ifndef GEOSIMD_FACTORIES_HPP
#define GEOSIMD_FACTORIES_HPP

#include <type_traits>
#include <utility>

namespace geosimd
{
	template<class T>
	using empty = std::type_identity<T>;

	template<class T>
	constexpr T zero(empty<T>)
	{ return T{}; }

	template<class T>
	constexpr T one(empty<T>)
	{ return static_cast<T>(1); }

	template<class T, class ... Args>
	constexpr T create(empty<T>, Args&& ... args)
	{ return T{std::forward<Args>(args)...}; }

	template<class T>
	constexpr T zero()
	{ return zero(empty<T>{}); }

	template<class T>
	constexpr T one()
	{ return one(empty<T>{}); }

	template<class T, class ... Args>
	constexpr T create(Args&& ... args)
	{ return create<T>(empty<T>{}, std::forward<Args>(args)...); }
}

#endif