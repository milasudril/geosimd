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
	using vector_1d = geosimd::basic_vector<my_1d_vector_space>;
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

#ifdef FAIL_geosimd_basic_point_1d_index
TESTCASE(FAIL_geosimd_basic_point_1d_index)
{
	point_1d x;
	(void)x[0];
}
#endif

TESTCASE(geosimd_basic_point_1d_add_vector)
{
	point_1d x{2};
	x += vector_1d{3};
	EXPECT_EQ(x, point_1d{5});
}

TESTCASE(geosimd_basic_point_1d_subtract_vector)
{
	point_1d x{2};
	x -= vector_1d{3};
	EXPECT_EQ(x, point_1d{-1});
}

TESTCASE(geosimd_basic_point_1d_add_vector_no_assign)
{
	point_1d const x1{2};
	auto x2 = x1 + vector_1d{3};
	static_assert(std::is_same_v<decltype(x2), point_1d>);
	EXPECT_EQ(x1, point_1d{2});
	EXPECT_EQ(x2, point_1d{5});
}

TESTCASE(geosimd_basic_point_1d_subtract_vector_no_assign)
{
	point_1d const x1{2};
	auto x2 = x1 - vector_1d{3};
	static_assert(std::is_same_v<decltype(x2), point_1d>);
	EXPECT_EQ(x1, point_1d{2});
	EXPECT_EQ(x2, point_1d{-1});
}

TESTCASE(geosimd_basic_point_1d_difference)
{
	point_1d const x1{2};
	point_1d const x2{5};
	auto diff = x1 - x2;
	static_assert(std::is_same_v<decltype(diff), vector_1d>);
	EXPECT_EQ(diff, vector_1d{-3});
}

TESTCASE(geosimd_basic_point_1d_distance)
{
	point_1d const x1{2};
	point_1d const x2{5};
	auto d1 = distance(x1, x2);
	auto d2 = distance(x2, x1);
	static_assert(std::is_same_v<decltype(d1), typename my_1d_vector_space::scalar_type>);
	EXPECT_EQ(d1, d2);
	EXPECT_EQ(d1, 3);
}

TESTCASE(geosimd_basic_point_1d_radius_vector)
{
	point_1d const x{5};
	auto r = radius_vector(x);
	static_assert(std::is_same_v<decltype(r), vector_1d>);
	EXPECT_EQ(r, vector_1d{5});
}

TESTCASE(geosimd_basic_point_1d_midpoint)
{
	point_1d const x1{5};
	point_1d const x2{9};
	auto mid = midpoint(x1, x2);
	static_assert(std::is_same_v<decltype(mid), point_1d>);
	EXPECT_EQ(mid, point_1d{7});
}

#ifdef FAIL_geosimd_basic_point_1d_lerp
TESTCASE(geosimd_basic_point_1d_lerp)
{
	point_1d const x1{5};
	point_1d const x2{9};
	(void)lerp(x1, x2, 1);
}
#endif

TESTCASE(geosimd_basic_point_1d_to_string)
{
	point_1d const x1{5};
	auto const str = to_string(x1);
	EXPECT_EQ(str, "5");
}

TESTCASE(geosimd_basic_point_1d_point_pair_distance)
{
	geosimd::point_pair const p{point_1d{5}, point_1d{9}};
	auto d = p.distance();
	static_assert(std::is_same_v<decltype(d), typename my_1d_vector_space::scalar_type>);
	EXPECT_EQ(d, 4);
}


namespace
{
	struct my_1d_vector_space_float
	{
		using scalar_type = float;
		using vector_type = float;
		using point_type = float;
	};

	using point_1d_float = geosimd::basic_point<my_1d_vector_space_float>;
	using vector_1d_float = geosimd::basic_vector<my_1d_vector_space_float>;
}

TESTCASE(geosimd_basic_point_1d_float_lerp)
{
	point_1d_float const x1{5.0f};
	point_1d_float const x2{9.0f};
	auto val = lerp(x1, x2, 0.75f);
	static_assert(std::is_same_v<decltype(val), point_1d_float>);
	EXPECT_EQ(val, point_1d_float{8.0f});
}