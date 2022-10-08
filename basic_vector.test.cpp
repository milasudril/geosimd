//@	{"target":{"name":"basic_vector.test"}}

#include "./basic_vector.hpp"

#include "./vec_t.hpp"

#include "testfwk/testfwk.hpp"

namespace geosimd_test
{
	struct my_vector_space_3d:public geosimd::hilbert_space<geosimd::vec4i32_t, int>
	{
		using enable_homogenous_coordinates_t = void;
	};

	static_assert(geosimd::vector_space<my_vector_space_3d>);
	static_assert(geosimd::vector<geosimd::basic_vector<my_vector_space_3d>, int>);
	static_assert(geosimd::inner_product_space<my_vector_space_3d>);

	struct my_vector_space_1d
	{
		using vector_type = intptr_t;
		using scalar_type = intptr_t;
		using point_type = std::byte*;
	};
}

TESTCASE(geosimd_basic_vector_3d_construct)
{
	constexpr geosimd::basic_vector<geosimd_test::my_vector_space_3d> a{};
	EXPECT_EQ(a[0], 0);
	EXPECT_EQ(a[1], 0);
	EXPECT_EQ(a[2], 0);
	EXPECT_EQ(a[3], 0);

	constexpr geosimd::basic_vector<geosimd_test::my_vector_space_3d> b{2, 3, 6};
	EXPECT_EQ(b[0], 2);
	EXPECT_EQ(b[1], 3);
	EXPECT_EQ(b[2], 6);
	EXPECT_EQ(b[3], 0);

	EXPECT_EQ(std::size(b), 3);

	EXPECT_EQ(norm(b), 7);
}

TESTCASE(geosimd_basic_vector_1d_construct)
{
	constexpr geosimd::basic_vector<geosimd_test::my_vector_space_1d> a{};
	EXPECT_EQ(a[0], 0);

	constexpr geosimd::basic_vector<geosimd_test::my_vector_space_1d> b{1};
	EXPECT_EQ(b[0], 1);

	EXPECT_EQ(std::size(b), 1);

	EXPECT_EQ(norm(b), 1);
}
