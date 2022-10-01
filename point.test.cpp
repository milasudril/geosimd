//@	{"target":{"name":"point.test"}}

#include "./point.hpp"

#include "testfwk/testfwk.hpp"

#include <array>

namespace testcases
{
	struct writable_address_space
	{
		using vector_type = intptr_t;
		using scalar_type = intptr_t;
		using point_type = std::byte*;
	};

	static_assert(geosimd::vector_space<writable_address_space>);
	static_assert(geosimd::affine_space<writable_address_space>);
	static_assert(geosimd::metric_space<writable_address_space>);

	constexpr std::array<std::byte, 4> testarray{};
	static_assert(geosimd::distance(std::data(testarray), std::data(testarray) + std::size(testarray))
	== std::ssize(testarray));
}


