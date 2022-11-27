#ifndef GEOSIMD_CONTAINER_PROPS_HPP
#define GEOSIMD_CONTAINER_PROPS_HPP

#include "./inline.hpp"

#include <iterator>
#include <type_traits>
#include <utility>

namespace geosimd
{
	template<class Container>
	concept subscriptable = requires(Container a)
	{
		{ a[std::declval<size_t>()] };
	};

	template<class Container>
	concept supports_size = requires(Container a)
	{
		{ std::size(a) } -> std::same_as<size_t>;
	};

	template<class Container>
	concept supports_constexpr_size = supports_size<Container>
		&& requires(Container a)
	{
		{ std::bool_constant<(std::size(Container{}), true)> {} } -> std::same_as<std::true_type>;
	};

	template<class Container>
	concept supports_static_constexpr_size = requires(Container a)
	{
		{ std::bool_constant<(Container::size(), true)>() } -> std::same_as<std::true_type>;
	};

	template<size_t N, subscriptable Container>
	requires supports_static_constexpr_size<Container>
	GEOSIMD_INLINE_OPT constexpr decltype(auto) get(Container&& a)
	{
		static_assert(N < Container::size());
		return std::forward<Container>(a)[N];
	}
}

namespace std
{
	template<geosimd::subscriptable Container>
	requires geosimd::supports_static_constexpr_size<Container>
	struct tuple_size<Container>:integral_constant<size_t, Container::size()>
	{
	};

	template<size_t N, geosimd::subscriptable Container>
	requires geosimd::supports_static_constexpr_size<Container>
	struct tuple_element<N, Container>
	{
		using type = std::add_const_t<typename Container::value_type>;
	};
}

#endif