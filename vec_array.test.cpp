//@	{"target":{"name":"vec_array.test"}}

#include "./vec_array.hpp"
#include "./basic_vector.hpp"

#include "testfwk/testfwk.hpp"
#include <array>
#include <list>

namespace
{
	struct my_vector_space
	{
		using scalar_type = int;
		using vector_type = geosimd::vec_t<int, 4>;
	};

	using my_vector = geosimd::basic_vector<my_vector_space>;
}

TESTCASE(geosimd_vec_array_add_sub)
{
	geosimd::vec_array<my_vector_space> a(3);
	a[0] = my_vector{1, 2, 3, 4};
	a[1] = my_vector{5, 6, 7, 8};
	a[2] = my_vector{9, 10, 11, 12};

	geosimd::vec_array<my_vector_space> b(3);
	b[0] = my_vector{12, 11, 10, 9};
	b[1] = my_vector{8, 7, 6, 5};
	b[2] = my_vector{4, 3, 2, 1};

	auto const old_a = a;

	a += b;

	geosimd::vec_array<my_vector_space> expected_sum(3);
	expected_sum[2] = my_vector{13, 13, 13, 13};
	expected_sum[1] = my_vector{13, 13, 13, 13};
	expected_sum[0] = my_vector{13, 13, 13, 13};

	EXPECT_EQ(a, expected_sum);

	a-=b;

	EXPECT_EQ(a, old_a);

	auto const c = a + b;
	EXPECT_EQ(a, old_a);
	EXPECT_EQ(c, expected_sum);

	auto const d = c - b;
	EXPECT_EQ(d, old_a);
}

TESTCASE(geosimd_vec_array_mul_div)
{
	geosimd::vec_array<my_vector_space> a(3);
	a[0] = my_vector{1, 2, 3, 4};
	a[1] = my_vector{5, 6, 7, 8};
	a[2] = my_vector{9, 10, 11, 12};

	auto const old_a = a;

	a *= 3;

	geosimd::vec_array<my_vector_space> expected_prod(3);
	expected_prod[0] = 3*old_a[0];
	expected_prod[1] = 3*old_a[1];
	expected_prod[2] = 3*old_a[2];

	EXPECT_EQ(a, expected_prod);

	a/=3;

	EXPECT_EQ(a, old_a);

	auto const c = a*3;
	EXPECT_EQ(c, expected_prod);
	EXPECT_EQ(a,old_a);
	EXPECT_EQ(3*a, a*3);
	EXPECT_EQ(c/3, old_a);
}

TESTCASE(geosimd_vec_array_norm)
{
	struct vector_space_int
	{
		using vector_type = int;
		using scalar_type = int;
	};

	static_assert(geosimd::normed_space<vector_space_int>);

	geosimd::vec_array<vector_space_int> a{geosimd::basic_vector<vector_space_int>{1},
		geosimd::basic_vector<vector_space_int>{-2},
		geosimd::basic_vector<vector_space_int>{3}};

	auto const n = norm(a);
	REQUIRE_EQ(std::size(n), std::size(a));
	for(size_t k = 0; k != std::size(n); ++k)
	{
		EXPECT_EQ(n[k], norm(a[k]));
	}
}
