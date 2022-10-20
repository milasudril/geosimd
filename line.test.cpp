//@	{"target":{"name":"line.test"}}

#include "./line.hpp"
#include "./euclidian_space.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geodimd_line_verify_points)
{
	using loc = geosimd::location<float, 3>;

	constexpr geosimd::line line{loc{1.0f, 2.0f, 3.0f}, loc{2.0f, 4.0f, 6.0f}};
	EXPECT_EQ(line.p1, (loc{1.0f, 2.0f, 3.0f}));
	EXPECT_EQ(line.p2, (loc{2.0f, 4.0f, 6.0f}));
}

TESTCASE(geodimd_line_line_intersection)
{
	using loc = geosimd::location<float, 3>;

	constexpr geosimd::line line_a{loc{0.0f, 1.0f, 0.0f}, loc{1.0f, 0.0f, 0.0f}};
	constexpr geosimd::line line_b{loc{0.0f, 0.0f, 0.0f}, loc{2.0f, 1.0f, 0.0f}};

	constexpr auto intersect_ab = intersection(line_a, line_b);
	EXPECT_EQ(intersect_ab.a, 2.0f/3.0f);
	EXPECT_EQ(intersect_ab.b, 1.0f/3.0f);

	constexpr auto intersect_ba = intersection(line_b, line_a);
	EXPECT_EQ(intersect_ba.b, 2.0f/3.0f);
	EXPECT_EQ(intersect_ba.a, 1.0f/3.0f);
}