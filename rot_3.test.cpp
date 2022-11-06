//@	{"target":{"name":"rot_3.test"}}

#include "./rot_3.hpp"
#include "./abstract_spaces.hpp"

#include "testfwk/testfwk.hpp"

static_assert(!geosimd::vector<geosimd::rot_3<float>, float>);