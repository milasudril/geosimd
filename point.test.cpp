//@	{"target":{"name":"point.test"}}

#include "./point.hpp"

#include "testfwk/testfwk.hpp"

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
}