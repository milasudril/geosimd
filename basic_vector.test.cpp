//@	{"target":{"name":"basic_vector.test"}}

#include "./basic_vector.hpp"

#include "./vec_t.hpp"

#include "testfwk/testfwk.hpp"

namespace geosimd_test
{
	struct my_vector_space
	{
		using vector_type = geosimd::vec4i32_t;
		using scalar_type = int;
	};

	static_assert(geosimd::vector_space<my_vector_space>);
	static_assert(geosimd::vector<geosimd::basic_vector<my_vector_space>, int>);
}

TESTCASE(geosimd_basic_vector_construct)
{
	constexpr geosimd::basic_vector<geosimd_test::my_vector_space> a{};
	EXPECT_EQ(a[0], 0);
	EXPECT_EQ(a[1], 0);
	EXPECT_EQ(a[2], 0);
	EXPECT_EQ(a[3], 0);

	constexpr geosimd::basic_vector<geosimd_test::my_vector_space> b{1, 2, 3};
	EXPECT_EQ(b[0], 1);
	EXPECT_EQ(b[1], 2);
	EXPECT_EQ(b[2], 3);
	EXPECT_EQ(b[3], 0);

}