//@	{"target":{"name":"vector_limits.test"}}

#include "./vector_limits.hpp"

#include "testfwk/testfwk.hpp"

#include <complex>

namespace geosimd_test
{
	// This should be true on any x86-64 system

	static_assert(geosimd::vector_limits::can_vectorize<float>(4));
	static_assert(geosimd::vector_limits::can_vectorize<double>(2));
	static_assert(!geosimd::vector_limits::can_vectorize<float>(2));


	// std::complex cannot be vectorized directly

	static_assert(!geosimd::vector_limits::can_vectorize<std::complex<float>>(4));

}