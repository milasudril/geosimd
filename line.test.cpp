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
	EXPECT_EQ(intersect_ab.a.get(), 2.0f/3.0f);
	EXPECT_EQ(intersect_ab.b.get(), 1.0f/3.0f);

	constexpr auto p1 = point_at(line_a, intersect_ab.a);
	EXPECT_LT(distance(p1, loc{2.0f/3.0f, 1.0f/3.0f, 0.0f}), 1e-7f);

	constexpr auto p2 = point_at(line_b, intersect_ab.b);
	EXPECT_LT(distance(p1, p2), 1e-7f);
	EXPECT_LT(std::abs(distance(p1, p2)
		- get_closest_points(line_a, line_b).get_distance()), 1e-7);

	constexpr auto intersect_ba = intersection(line_b, line_a);
	EXPECT_EQ(intersect_ba.b.get(), 2.0f/3.0f);
	EXPECT_EQ(intersect_ba.a.get(), 1.0f/3.0f);
}

TESTCASE(geosimd_line_ray_intersection)
{
	using loc = geosimd::location<float, 3>;

	constexpr geosimd::line line{loc{0.0f, 0.0f, 0.0f}, loc{1.0f, 0.0f, 0.0f}};
	constexpr geosimd::ray ray_a{loc{1.0f, 1.0f, 0.0f}, loc{1.0f, 2.0f, 0.0f}};

	constexpr auto res_a = get_closest_points(line, ray_a);
	EXPECT_EQ(res_a.a, (loc{1.0f, 0.0f, 0.0f}));
	EXPECT_EQ(res_a.b, ray_a.origin);

	constexpr geosimd::ray ray_b{loc{-1.0f, -1.0f, 0.0f}, loc{1.0f, 1.0f, 0.0f}};
	constexpr auto res_b = get_closest_points(line, ray_b);
	EXPECT_EQ(res_b.a, (loc{0.0f, 0.0f, 0.0f}));
	EXPECT_EQ(res_b.b, (loc{0.0f, 0.0f, 0.0f}));
}

TESTCASE(geosimd_ray_ray_intersection)
{
	using loc = geosimd::location<float, 3>;

	constexpr geosimd::ray ray_ref{loc{0.0f, 0.0f, 0.0f}, loc{1.0f, 0.0f, 0.0f}};

	constexpr geosimd::ray ray_a{loc{0.0f, 1.0f, 0.0f}, loc{1.0f, 2.0f, 0.0f}};
	constexpr auto res_a = get_closest_points(ray_ref, ray_a);
	EXPECT_EQ(res_a.a, ray_ref.origin);
	EXPECT_EQ(res_a.b, ray_a.origin);

	constexpr geosimd::ray ray_b{loc{1.0f, 1.0f, 0.0f}, loc{2.0f, 2.0f, 0.0f}};
	constexpr auto res_b = get_closest_points(ray_ref, ray_b);
	EXPECT_EQ(res_b.a, (loc{1.0f, 0.0f, 0.0f}));
	EXPECT_EQ(res_b.b, ray_b.origin);

	constexpr auto res_c = get_closest_points(ray_b, ray_ref);
	EXPECT_EQ(res_c.a, ray_b.origin);
	EXPECT_EQ(res_c.b, (loc{1.0f, 0.0f, 0.0f}));

	constexpr geosimd::ray ray_c{loc{0.0f, -1.0f, 0.0f}, loc{2.0f, 1.0f, 0.0f}};
	constexpr auto res_d = get_closest_points(ray_ref, ray_c);
	EXPECT_EQ(res_d.a, (loc{1.0f, 0.0f, 0.0f}));
	EXPECT_EQ(res_d.b, (loc{1.0f, 0.0f, 0.0f}));


}