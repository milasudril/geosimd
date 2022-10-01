//@	{"target":{"name":"vector_limits.test"}}

#include "./vector_limits.hpp"

#include "testfwk/testfwk.hpp"

namespace testcases
{
	// This should be true on any x86-64 system

	static_assert(geosimd::vector_limits::can_vectorize<float>(4));
	static_assert(geosimd::vector_limits::can_vectorize<double>(2));
	static_assert(!geosimd::vector_limits::can_vectorize<float>(2));
}