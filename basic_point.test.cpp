//@	{"target":{"name":"basic_point.test"}}

#include "./basic_point.hpp"

#include "testfwk/testfwk.hpp"

namespace
{
	struct my_1d_vector_space
	{
		using scalar_type = int;
		using vector_type = int;
		using point_type = int;
	};

	using point_1d = geosimd::basic_point<my_1d_vector_space>;

}

TESTCASE(geosimd_basic_point_1d_default_construct)
{
	point_1d x;
	EXPECT_EQ(x.get(), 0);
}

TESTCASE(geosimd_basic_point_1d_origin)
{
	point_1d x;
	EXPECT_EQ(x, geosimd::origin<my_1d_vector_space>());
}

TESTCASE(geosimd_basic_point_1d_construct)
{
	static_assert(std::is_same_v<typename point_1d::vector_type, geosimd::basic_vector<my_1d_vector_space>>);
	static_assert(std::is_same_v<typename point_1d::scalar_type, int>);
	static_assert(std::is_same_v<typename point_1d::value_type, int>);
	static_assert(std::is_same_v<typename point_1d::storage_type, int>);

	point_1d x{2};
	EXPECT_EQ(x.get(), 2);
}

TESTCASE(geosimd_basic_point_1d_size)
{
	EXPECT_EQ(point_1d::size(), 1);
}