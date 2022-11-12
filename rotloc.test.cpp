//@	{"target":{"name":"rocloc.test"}}

#include "./rotloc.hpp"

#include "testfwk/testfwk.hpp"

namespace
{
	struct my_vector_space
	{
		using vector_type = geosimd::vec_t<float, 4>;
		using point_type = geosimd::vec_t<float, 4>;
		using scalar_type = float;
		using enable_homogenous_coordinates_t = void;
		using enable_rotations_t = void;
	};
}
TESTCASE(geosimd_rotloc_inverser)
{
	geosimd::basic_vector<my_vector_space> const offset{1.0f, 2.0f, 3.0f};
	geosimd::translation const transl{offset};
	geosimd::rotloc const transform{
		transl,
 		geosimd::rotation<my_vector_space>{geosimd::rotation_angle{geosimd::turns{0.25f}},
			geosimd::dimension_tag<2>{}
		}
	};

	printf("    T: %s\n", to_string(transform).c_str());
	printf("T inv: %s", to_string(inverted(transform)).c_str());

	EXPECT_EQ(inverted(transform).get()*transform.get(), one(geosimd::empty<geosimd::mat_4x4<float>>{}));
}