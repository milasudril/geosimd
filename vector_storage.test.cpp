//@	{"target":{"name":"vector_storage.test"}}

#include "./vector_storage.hpp"

#include "testfwk/testfwk.hpp"

static_assert(!std::totally_ordered<geosimd::vector_storage<int, 4>>);
static_assert(!std::equality_comparable<geosimd::vector_storage<int, 4>>);
static_assert(!std::equality_comparable<geosimd::vector_storage<std::complex<int>, 4>>);