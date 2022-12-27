//@	{"target":{"name":"point_array.test"}}

#include "./point_array.hpp"

#include "testfwk/testfwk.hpp"
#include <array>
#include <list>

namespace
{
	struct my_vector_space
	{
		using scalar_type = int;
		using vector_type = geosimd::vec_t<int, 4>;
		using point_type = geosimd::vec_t<int, 4>;
	};

	using my_point = geosimd::basic_point<my_vector_space>;
	using my_vector = geosimd::basic_vector<my_vector_space>;
}

TESTCASE(geosimd_point_array_add_sub)
{
	geosimd::point_array<my_vector_space> a(3);
	a[0] = my_point{1, 2, 3, 4};
	a[1] = my_point{5, 6, 7, 8};
	a[2] = my_point{9, 10, 11, 12};

	geosimd::vec_array<my_vector_space> b(3);
	b[0] = my_vector{12, 11, 10, 9};
	b[1] = my_vector{8, 7, 6, 5};
	b[2] = my_vector{4, 3, 2, 1};

	auto const old_a = a;

	a += b;

	geosimd::point_array<my_vector_space> expected_sum(3);
	expected_sum[2] = my_point{13, 13, 13, 13};
	expected_sum[1] = my_point{13, 13, 13, 13};
	expected_sum[0] = my_point{13, 13, 13, 13};

	EXPECT_EQ(a, expected_sum);

	a-=b;

	EXPECT_EQ(a, old_a);

	auto const c = a + b;
	EXPECT_EQ(a, old_a);
	EXPECT_EQ(c, expected_sum);

	auto const d = c - b;
	EXPECT_EQ(d, old_a);
}
