#ifndef GEOSIMD_ADLFACTORIES_HPP
#define GEOSIMD_ADLFACTORIES_HPP

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
}

#endif