//@	{"target":{"name":"rocloc.test"}}

#include "./rotloc.hpp"
#include "./basic_point.hpp"

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

TESTCASE(geosimd_rotloc_inverse)
{
	geosimd::basic_vector<my_vector_space> const offset{1.0f, 2.0f, 3.0f};
	geosimd::translation const transl{offset};
	geosimd::rotloc const transform{
		transl,
 		geosimd::rotation<my_vector_space>{geosimd::rotation_angle{geosimd::turns{0.25f}},
			geosimd::dimension_tag<2>{}
		}
	};
	EXPECT_EQ(inverted(transform).get()*transform.get(), one(geosimd::empty<geosimd::mat_4x4<float>>{}));
	EXPECT_EQ(inverted(inverted(transform)), transform);
}

TESTCASE(geosimd_rotloc_extract_parts)
{
	geosimd::basic_vector<my_vector_space> const offset{1.0f, 2.0f, 3.0f};
	geosimd::translation const T{offset};
	geosimd::rotation const R{
		geosimd::rotation<my_vector_space>{geosimd::rotation_angle{geosimd::turns{0.25f}},
		geosimd::dimension_tag<2>{}
	}};

	geosimd::rotloc const A{T, R};
	EXPECT_EQ(A.translation_part(), T.offset());
	EXPECT_EQ(A.rotation_part(), R.get());
}

TESTCASE(geosimd_rotloc_apply)
{
	geosimd::basic_vector<my_vector_space> const offset{1.0f, 2.0f, 3.0f};
	geosimd::translation const T{offset};
	geosimd::rotation const R{
		geosimd::rotation<my_vector_space>{geosimd::rotation_angle{geosimd::turns{0.25f}},
		geosimd::dimension_tag<2>{}
	}};

	geosimd::rotloc const A{T, R};

	geosimd::basic_point<my_vector_space> loc{1.0f, 2.0f, 3.0f};

	EXPECT_EQ(A.get() * loc.get(), (geosimd::vec_t<float, 4>{-1.0f, 3.0f, 6.0f, 1.0f}));
}