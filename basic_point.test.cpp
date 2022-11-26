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
}

TESTCASE(geosimd_basic_point_regular_coords_construct)
{
	using point = geosimd::basic_point<my_1d_vector_space>;
	static_assert(std::is_same_v<typename point::vector_type, geosimd::basic_vector<my_1d_vector_space>>);
	static_assert(std::is_same_v<typename point::scalar_type, int>);
	static_assert(std::is_same_v<typename point::value_type, int>);
	static_assert(std::is_same_v<typename point::storage_type, int>);

	point x{2};
	EXPECT_EQ(x.get(), 2);
}