//@	{"target":{"name":"point.test"}}

#include "./point.hpp"

#include "testfwk/testfwk.hpp"

namespace
{
	struct my_affine_space
	{
		using vector_type = int;
		using scalar_type = int;

		static constexpr size_t dimension_count()
		{ return 1; }

		static constexpr vector_type origin()
		{ return 0; }
	};
}

static_assert(std::is_same_v<geosimd::location<my_affine_space>::vector_type, int>);
static_assert(std::is_same_v<geosimd::location<my_affine_space>::scalar_type, int>);
static_assert(geosimd::location<my_affine_space>::dimension_count == 1);
static_assert(geosimd::origin<my_affine_space>().vector() ==
	geosimd::location<my_affine_space>{0}.vector());

TESTCASE(geosimd_location_add_vector)
{
	geosimd::location<my_affine_space> loc{1};
	loc += 2;

	EXPECT_EQ(loc.vector(), 3);

	loc = loc + 5;

	EXPECT_EQ(loc.vector(), 8);
}

TESTCASE(geosimd_location_subtract_vector)
{
	geosimd::location<my_affine_space> loc{3};
	loc -= 1;
	EXPECT_EQ(loc.vector(), 2);

	loc = loc - 10;

	EXPECT_EQ(loc.vector(), -8);
}

TESTCASE(geosimd_location_subtract)
{
	geosimd::location<my_affine_space> loc_a{5};
	geosimd::location<my_affine_space> loc_b{3};

	EXPECT_EQ(loc_a - loc_b, 2);
}

TESTCASE(geosimd_location_distance)
{
	geosimd::location<my_affine_space> loc_a{5};
	geosimd::location<my_affine_space> loc_b{-3};

	EXPECT_EQ(distance(loc_a, loc_b), 8);
}

