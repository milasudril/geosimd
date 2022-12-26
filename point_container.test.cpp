//@	{"target":{"name":"point_container.test"}}

#include "./point_container.hpp"
#include "./basic_vector.hpp"
#include "./basic_point.hpp"

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
	
	using my_vector = geosimd::basic_vector<my_vector_space>;
	using my_point = geosimd::basic_point<my_vector_space>;
}

TESTCASE(geosimd_point_container_add_sub)
{
	geosimd::point_container<std::array<my_point, 3>> a;
	a[0] = my_point{1, 2, 3, 4};
	a[1] = my_point{5, 6, 7, 8};
	a[2] = my_point{9, 10, 11, 12};
	
	std::array<my_vector, 3> b;
	b[0] = my_vector{12, 11, 10, 9};
	b[1] = my_vector{8, 7, 6, 5};
	b[2] = my_vector{4, 3, 2, 1};
	
	auto const old_a = a;
	
	a += b;
	geosimd::point_container<std::array<my_point, 3>> expected_sum;
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


TESTCASE(geosimd_point_container_add_other_container)
{
	geosimd::point_container<std::array<my_point, 3>> a;
	a[0] = my_point{1, 2, 3, 4};
	a[1] = my_point{5, 6, 7, 8};
	a[2] = my_point{9, 10, 11, 12};
	
	std::list<my_vector> b;
	b.push_back(my_vector{12, 11, 10, 9});
	b.push_back(my_vector{8, 7, 6, 5});
	b.push_back(my_vector{4, 3, 2, 1});
	
	geosimd::point_container<std::array<my_point, 3>> expected_sum;
	expected_sum[2] = my_point{13, 13, 13, 13};
	expected_sum[1] = my_point{13, 13, 13, 13};
	expected_sum[0] = my_point{13, 13, 13, 13};
	
	EXPECT_EQ(a + b, expected_sum);
}
