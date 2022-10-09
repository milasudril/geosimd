#ifndef GEOSIMD_CONTAINER_PROPS_HPP
#define GEOSIMD_CONTAINER_PROPS_HPP

#include <iterator>
#include <type_traits>

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
		{ std::bool_constant<(std::size(std::declval<Container>()), true)>() } -> std::same_as<std::true_type>;
	};

	template<class Container>
	concept supports_static_constexpr_size = requires(Container a)
	{
		{ std::bool_constant<(Container::size(), true)>() } -> std::same_as<std::true_type>;
	};
}

#endif