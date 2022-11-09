//@	{"target":{"name":"complex_scalar.test"}}

#include "./abstract_spaces.hpp"
#include "./vector_storage.hpp"

#include "testfwk/testfwk.hpp"

static_assert(!geosimd::scalar<geosimd::vector_storage<std::complex<int>, 4>>);