#ifndef GEOSIMD_FACTORIES_HPP
#define GEOSIMD_FACTORIES_HPP

#include "./inline.hpp"

#include <type_traits>
#include <utility>

namespace geosimd
{
	template<class T>
	using empty = std::type_identity<T>;

	template<class T>
	constexpr T zero(empty<T>)
	{
		codecov::function_called(__FILE__, __LINE__);
		return T{};
	}

	template<class T>
	constexpr T one(empty<T>)
	{
		codecov::function_called(__FILE__, __LINE__);
		return static_cast<T>(1);
	}

	template<class T, class ... Args>
	constexpr T create(empty<T>, Args&& ... args)
	{
		codecov::function_called(__FILE__, __LINE__);
		return T{std::forward<Args>(args)...};
	}

	template<class T>
	constexpr T zero()
	{
		codecov::function_called(__FILE__, __LINE__);
		return zero(empty<T>{});
	}

	template<class T>
	constexpr T one()
	{
		codecov::function_called(__FILE__, __LINE__);
		return one(empty<T>{});
	}

	template<class T, class ... Args>
	constexpr T create(Args&& ... args)
	{
		codecov::function_called(__FILE__, __LINE__);
		return create<T>(empty<T>{}, std::forward<Args>(args)...);
	}

	template<class Generator, class Value, class ... Args>
	concept generator = requires(Generator x, Args... args)
	{
		{x(args...)} -> std::same_as<Value>;
	};
}

#endif
