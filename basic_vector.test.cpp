//@	{"target":{"name":"basic_vector.test"}}

#include "./basic_vector.hpp"

#include "./vec_t.hpp"

#include "testfwk/testfwk.hpp"

namespace geosimd_test
{
	struct my_vector_space_3d
	{
		using vector_type = geosimd::vec4i32_t;
		using scalar_type = int;
		using enable_homogenous_coordinates_t = void;

		static constexpr auto norm(vector_type a)
		{ return static_cast<int>(std::sqrt(inner_product(a))); }
	};

	static_assert(geosimd::vector_space<my_vector_space_3d>);
	static_assert(geosimd::vector<geosimd::basic_vector<my_vector_space_3d>, int>);

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

	constexpr geosimd::basic_vector<geosimd_test::my_vector_space_3d> b{1, 2, 3};
	EXPECT_EQ(b[0], 1);
	EXPECT_EQ(b[1], 2);
	EXPECT_EQ(b[2], 3);
	EXPECT_EQ(b[3], 0);

	EXPECT_EQ(std::size(b), 3);

	EXPECT_EQ(norm(b), 3);
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
