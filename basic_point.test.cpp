//@	{"target":{"name":"basic_point.test"}}

#include "./basic_point.hpp"

#include "./vec_t.hpp"

#include "testfwk/testfwk.hpp"

namespace geosimd_test
{
	struct my_vector_space_3d:public geosimd::metric_normed_space<geosimd::vec4i32_t, geosimd::hilbert_space<geosimd::vec4i32_t>>
	{
		using enable_homogenous_coordinates_t = void;
	};

	static_assert(geosimd::affine_space<my_vector_space_3d>);
	static_assert(geosimd::point<geosimd::basic_point<my_vector_space_3d>>);
	static_assert(geosimd::is_hilbert_space_v<my_vector_space_3d>);
	static_assert(geosimd::has_homogenous_coordinates<my_vector_space_3d>);

	struct my_vector_space_1d
	{
		using vector_type = intptr_t;
		using scalar_type = intptr_t;
		using point_type = std::byte*;
	};

	static_assert(geosimd::affine_space<my_vector_space_1d>);
	static_assert(geosimd::point<geosimd::basic_point<my_vector_space_1d>>);
}

TESTCASE(geosimd_basic_point_3d_construct)
{
	geosimd::basic_point<geosimd_test::my_vector_space_3d> const a{};
	EXPECT_EQ(a[0], 0);
	EXPECT_EQ(a[1], 0);
	EXPECT_EQ(a[2], 0);
	EXPECT_EQ(a[3], 1);

	geosimd::basic_point<geosimd_test::my_vector_space_3d> const b{3, 2, 7};
	EXPECT_EQ(b[0], 3);
	EXPECT_EQ(b[1], 2);
	EXPECT_EQ(b[2], 7);
	EXPECT_EQ(b[3], 1);

	geosimd::basic_point<geosimd_test::my_vector_space_3d> const c{1, -1, 1};
	EXPECT_EQ(c[0], 1);
	EXPECT_EQ(c[1], -1);
	EXPECT_EQ(c[2], 1);
	EXPECT_EQ(c[3], 1);

	auto const delta = b - c;
	EXPECT_EQ(delta[0], 2);
	EXPECT_EQ(delta[1], 3);
	EXPECT_EQ(delta[2], 6);
	EXPECT_EQ(delta[3], 0);

	EXPECT_EQ(distance(b, c), 7);

	EXPECT_EQ(std::size(b), 3);

#if 0
/*
	EXPECT_EQ(norm(b), 7);
	geosimd::basic_vector<geosimd_test::my_vector_space_3d> a{2, 3, 6};
	EXPECT_EQ(b[0], 2);
	EXPECT_EQ(b[1], 3);
	EXPECT_EQ(b[2], 6);
	EXPECT_EQ(b[3], 0);*/



	EXPECT_EQ(norm_squared(b), 49);
#endif
}
