//@	{"target":{"name":"translation.test"}}

#include "./translation.hpp"
#include "./abstract_spaces.hpp"

#include "testfwk/testfwk.hpp"

namespace
{
	struct my_affine_space
	{
		using vector_type = geosimd::vec_t<int, 4>;
		using scalar_type = int;
		using point_type = vector_type;
		using enable_homogenous_coordinates_t = void;
	};
}

static_assert(!geosimd::vector<geosimd::translation<my_affine_space>>);

TESTCASE(geosimd_translation_default_value)
{
	geosimd::translation<my_affine_space> transl;
	EXPECT_EQ(transl.get(), one(geosimd::empty<geosimd::mat_4x4<int>>{}));
}