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
	EXPECT_EQ(transl.get(), geosimd::one<geosimd::mat_4x4<int>>());
}

TESTCASE(geosimd_translation_create)
{
	geosimd::translation<my_affine_space> transl{geosimd::basic_vector<my_affine_space>{1, 2, 3}};
	EXPECT_EQ(transl.get(), (geosimd::mat_4x4{
		geosimd::vec_t<int, 4>{1, 0, 0, 0},
		geosimd::vec_t<int, 4>{0, 1, 0, 0},
		geosimd::vec_t<int, 4>{0, 0, 1, 0},
		geosimd::vec_t<int, 4>{1, 2, 3, 1}
	}));

	EXPECT_EQ(transl.get()*inverted(transl).get(), geosimd::one<geosimd::mat_4x4<int>>());
}

TESTCASE(geosimd_translation_push_pop)
{
	geosimd::translation<my_affine_space> transl;
	EXPECT_EQ(transl.get(), geosimd::one<geosimd::mat_4x4<int>>());

	transl.push(geosimd::basic_vector<my_affine_space>{1, 2, 3});
	EXPECT_EQ(transl.get(), (geosimd::mat_4x4{
		geosimd::vec_t<int, 4>{1, 0, 0, 0},
		geosimd::vec_t<int, 4>{0, 1, 0, 0},
		geosimd::vec_t<int, 4>{0, 0, 1, 0},
		geosimd::vec_t<int, 4>{1, 2, 3, 1}
	}));

	transl.push(geosimd::basic_vector<my_affine_space>{2, 3, 4});
	EXPECT_EQ(transl.get(), (geosimd::mat_4x4{
		geosimd::vec_t<int, 4>{1, 0, 0, 0},
		geosimd::vec_t<int, 4>{0, 1, 0, 0},
		geosimd::vec_t<int, 4>{0, 0, 1, 0},
		geosimd::vec_t<int, 4>{3, 5, 7, 1}
	}));

	transl.pop(geosimd::basic_vector<my_affine_space>{1, 2, 3});
	EXPECT_EQ(transl.get(), (geosimd::mat_4x4{
		geosimd::vec_t<int, 4>{1, 0, 0, 0},
		geosimd::vec_t<int, 4>{0, 1, 0, 0},
		geosimd::vec_t<int, 4>{0, 0, 1, 0},
		geosimd::vec_t<int, 4>{2, 3, 4, 1}
	}));

	transl.pop(geosimd::basic_vector<my_affine_space>{2, 3, 4});
	EXPECT_EQ(transl.get(), (geosimd::mat_4x4{
		geosimd::vec_t<int, 4>{1, 0, 0, 0},
		geosimd::vec_t<int, 4>{0, 1, 0, 0},
		geosimd::vec_t<int, 4>{0, 0, 1, 0},
		geosimd::vec_t<int, 4>{0, 0, 0, 1}
	}));
}

