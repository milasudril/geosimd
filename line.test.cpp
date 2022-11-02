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
	constexpr geosimd::ray ray_a{loc{2.0f, 1.0f, 0.0f}, loc{3.0f, 2.0f, 0.0f}};

	constexpr auto res_a = get_closest_points(line, ray_a);
	EXPECT_EQ(res_a.a, (loc{2.0f, 0.0f, 0.0f}));
	EXPECT_EQ(res_a.b, ray_a.origin);

	constexpr geosimd::ray ray_b{loc{-1.0f, -1.0f, 0.0f}, loc{1.0f, 1.0f, 0.0f}};
	constexpr auto res_b = get_closest_points(line, ray_b);
	EXPECT_EQ(res_b.a, (loc{0.0f, 0.0f, 0.0f}));
	EXPECT_EQ(res_b.b, (loc{0.0f, 0.0f, 0.0f}));
}

TESTCASE(geosimd_ray_ray_intersection)
{
	using loc = geosimd::location<float, 3>;

	{
		constexpr geosimd::ray ray_a{loc{-1.0f, -1.0f, 0.0f}, loc{1.0f, 1.0f, 0.0f}};
		constexpr geosimd::ray ray_b{loc{1.0f, -1.0f, 0.0f}, loc{-1.0f, 1.0f, 0.0f}};

		auto const res_ab = get_closest_points(ray_a, ray_b);
		EXPECT_EQ(res_ab.a, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab.b, (loc{0.0f, 0.0f, 0.0f}));

		auto const res_ba = get_closest_points(ray_b, ray_a);
		EXPECT_EQ(res_ba.a, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba.b, (loc{0.0f, 0.0f, 0.0f}));
	}

	{
		constexpr geosimd::ray ray_a{loc{-2.0f, 0.0f, 0.0f}, loc{0.0f, 0.0f, 0.0f}};
		constexpr geosimd::ray ray_b{loc{0.0f, -1.0f, 0.0f}, loc{-1.0f, -2.0f, 0.0f}};

		auto const res_ab = get_closest_points(ray_a, ray_b);
		EXPECT_EQ(res_ab.a, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab.b, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ba = get_closest_points(ray_b, ray_a);
		EXPECT_EQ(res_ba.a, (loc{0.0f, -1.0f, 0.0f}))
		EXPECT_EQ(res_ba.b, (loc{0.0f, 0.0f, 0.0f}));
	}

	{
		constexpr geosimd::ray ray_a{loc{0.0f, 0.0f, 0.0f}, loc{1.0f, 0.0f, 0.0f}};
		constexpr geosimd::ray ray_b{loc{1.0f, 2.0f, 0.0f}, loc{2.0f, 3.0f, 0.0f}};

		auto const res_ab = get_closest_points(ray_a, ray_b);
		EXPECT_EQ(res_ab.a, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab.b, (loc{1.0f, 2.0f, 0.0f}));

		auto const res_ba = get_closest_points(ray_b, ray_a);
		EXPECT_EQ(res_ba.a, (loc{1.0f, 2.0f, 0.0f}));
		EXPECT_EQ(res_ba.b, (loc{1.0f, 0.0f, 0.0f}));
	}

	{
		constexpr geosimd::ray ray_a{loc{0.0f, 1.0f, 0.0f}, loc{2.0f, 2.0f, 0.0f}};
		constexpr geosimd::ray ray_b{loc{0.0f, -1.0f, 0.0f}, loc{2.0f, -2.0f, 0.0f}};

		auto const res_ab = get_closest_points(ray_a, ray_b);
		EXPECT_EQ(res_ab.a, (loc{0.0f, 1.0f, 0.0f}));
		EXPECT_EQ(res_ab.b, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ba = get_closest_points(ray_b, ray_a);
		EXPECT_EQ(res_ba.a, (loc{0.0f, -1.0f, 0.0f}));
		EXPECT_EQ(res_ba.b, (loc{0.0f, 1.0f, 0.0f}));
	}
}

TESTCASE(geosimd_line_segemt_flip)
{
	using loc = geosimd::location<float, 3>;

	constexpr geosimd::line_segment seg{loc{-1.0f, -1.0f, 0.0f}, loc{1.0f, 1.0f, 0.0f}};
	EXPECT_EQ(seg.p1, (loc{-1.0f, -1.0f, 0.0f}));
	EXPECT_EQ(seg.p2, (loc{1.0f, 1.0f, 0.0f}));

	auto const seg_flipped = flip(seg);
	EXPECT_EQ(seg_flipped.p1, (loc{1.0f, 1.0f, 0.0f}));
	EXPECT_EQ(seg_flipped.p2, (loc{-1.0f, -1.0f, 0.0f}));
}

TESTCASE(geosimd_line_segment_line_segment_intersection)
{
	using loc = geosimd::location<float, 3>;

	{
		constexpr geosimd::line_segment line_segment_a{loc{-1.0f, -1.0f, 0.0f}, loc{1.0f, 1.0f, 0.0f}};
		constexpr geosimd::line_segment line_segment_b{loc{1.0f, -1.0f, 0.0f}, loc{-1.0f, 1.0f, 0.0f}};

		auto const res_ab_00 = get_closest_points(line_segment_a, line_segment_b);
		EXPECT_EQ(res_ab_00.a, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_00.b, (loc{0.0f, 0.0f, 0.0f}));

		auto const res_ab_01 = get_closest_points(line_segment_a, flip(line_segment_b));
		EXPECT_EQ(res_ab_01.a, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_01.b, (loc{0.0f, 0.0f, 0.0f}));

		auto const res_ab_10 = get_closest_points(flip(line_segment_a), line_segment_b);
		EXPECT_EQ(res_ab_10.a, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_10.b, (loc{0.0f, 0.0f, 0.0f}));

		auto const res_ab_11 = get_closest_points(flip(line_segment_a), flip(line_segment_b));
		EXPECT_EQ(res_ab_11.a, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_11.b, (loc{0.0f, 0.0f, 0.0f}));

		auto const res_ba_00 = get_closest_points(line_segment_b, line_segment_a);
		EXPECT_EQ(res_ba_00.b, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_00.a, (loc{0.0f, 0.0f, 0.0f}));

		auto const res_ba_01 = get_closest_points(line_segment_b, flip(line_segment_a));
		EXPECT_EQ(res_ba_01.b, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_01.a, (loc{0.0f, 0.0f, 0.0f}));

		auto const res_ba_10 = get_closest_points(flip(line_segment_b), line_segment_a);
		EXPECT_EQ(res_ba_10.b, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_10.a, (loc{0.0f, 0.0f, 0.0f}));

		auto const res_ba_11 = get_closest_points(flip(line_segment_b), flip(line_segment_a));
		EXPECT_EQ(res_ba_11.b, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_11.a, (loc{0.0f, 0.0f, 0.0f}));
	}

	{
		constexpr geosimd::line_segment line_segment_a{loc{-2.0f, 0.0f, 0.0f}, loc{2.0f, 0.0f, 0.0f}};
		constexpr geosimd::line_segment line_segment_b{loc{0.0f, -1.0f, 0.0f}, loc{-4.0f, -5.0f, 0.0f}};

		auto const res_ab_00 = get_closest_points(line_segment_a, line_segment_b);
		EXPECT_EQ(res_ab_00.a, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_00.b, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ab_01 = get_closest_points(line_segment_a, flip(line_segment_b));
		EXPECT_EQ(res_ab_01.a, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_01.b, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ab_10 = get_closest_points(flip(line_segment_a), line_segment_b);
		EXPECT_EQ(res_ab_10.a, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_10.b, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ab_11 = get_closest_points(flip(line_segment_a), flip(line_segment_b));
		EXPECT_EQ(res_ab_11.a, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_11.b, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ba_00 = get_closest_points(line_segment_b, line_segment_a);
		EXPECT_EQ(res_ba_00.b, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_00.a, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ba_01 = get_closest_points(line_segment_b, flip(line_segment_a));
		EXPECT_EQ(res_ba_01.b, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_01.a, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ba_10 = get_closest_points(flip(line_segment_b), line_segment_a);
		EXPECT_EQ(res_ba_10.b, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_10.a, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ba_11 = get_closest_points(flip(line_segment_b), flip(line_segment_a));
		EXPECT_EQ(res_ba_11.b, (loc{0.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_11.a, (loc{0.0f, -1.0f, 0.0f}));
	}

	{
		constexpr geosimd::line_segment line_segment_a{loc{0.0f, 0.0f, 0.0f}, loc{8.0f, 0.0f, 0.0f}};
		constexpr geosimd::line_segment line_segment_b{loc{1.0f, 2.0f, 0.0f}, loc{7.0f, 8.0f, 0.0f}};

		auto const res_ab_00 = get_closest_points(line_segment_a, line_segment_b);
		EXPECT_EQ(res_ab_00.a, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_00.b, (loc{1.0f, 2.0f, 0.0f}));

		auto const res_ab_01 = get_closest_points(line_segment_a, flip(line_segment_b));
		EXPECT_EQ(res_ab_01.a, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_01.b, (loc{1.0f, 2.0f, 0.0f}));

		auto const res_ab_10 = get_closest_points(flip(line_segment_a), line_segment_b);
		EXPECT_EQ(res_ab_10.a, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_10.b, (loc{1.0f, 2.0f, 0.0f}));

		auto const res_ab_11 = get_closest_points(flip(line_segment_a), flip(line_segment_b));
		EXPECT_EQ(res_ab_11.a, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_11.b, (loc{1.0f, 2.0f, 0.0f}));

		auto const res_ba_00 = get_closest_points(line_segment_b, line_segment_a);
		EXPECT_EQ(res_ba_00.b, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_00.a, (loc{1.0f, 2.0f, 0.0f}));

		auto const res_ba_01 = get_closest_points(line_segment_b, flip(line_segment_a));
		EXPECT_EQ(res_ba_01.b, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_01.a, (loc{1.0f, 2.0f, 0.0f}));

		auto const res_ba_10 = get_closest_points(flip(line_segment_b), line_segment_a);
		EXPECT_EQ(res_ba_10.b, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_10.a, (loc{1.0f, 2.0f, 0.0f}));

		auto const res_ba_11 = get_closest_points(flip(line_segment_b), flip(line_segment_a));
		EXPECT_EQ(res_ba_11.b, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_11.a, (loc{1.0f, 2.0f, 0.0f}));
	}

	{
		constexpr geosimd::line_segment line_segment_a{loc{0.0f, 1.0f, 0.0f}, loc{8.0f, 8.0f, 0.0f}};
		constexpr geosimd::line_segment line_segment_b{loc{0.0f, -1.0f, 0.0f}, loc{8.0f, -8.0f, 0.0f}};

		auto const res_ab_00 = get_closest_points(line_segment_a, line_segment_b);
		EXPECT_EQ(res_ab_00.a, (loc{0.0f, 1.0f, 0.0f}));
		EXPECT_EQ(res_ab_00.b, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ab_01 = get_closest_points(line_segment_a, flip(line_segment_b));
		EXPECT_EQ(res_ab_01.a, (loc{0.0f, 1.0f, 0.0f}));
		EXPECT_EQ(res_ab_01.b, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ab_10 = get_closest_points(flip(line_segment_a), line_segment_b);
		EXPECT_EQ(res_ab_10.a, (loc{0.0f, 1.0f, 0.0f}));
		EXPECT_EQ(res_ab_10.b, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ab_11 = get_closest_points(flip(line_segment_a), flip(line_segment_b));
		EXPECT_EQ(res_ab_11.a, (loc{0.0f, 1.0f, 0.0f}));
		EXPECT_EQ(res_ab_11.b, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ba_00 = get_closest_points(line_segment_b, line_segment_a);
		EXPECT_EQ(res_ba_00.b, (loc{0.0f, 1.0f, 0.0f}));
		EXPECT_EQ(res_ba_00.a, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ba_01 = get_closest_points(line_segment_b, flip(line_segment_a));
		EXPECT_EQ(res_ba_01.b, (loc{0.0f, 1.0f, 0.0f}));
		EXPECT_EQ(res_ba_01.a, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ba_10 = get_closest_points(flip(line_segment_b), line_segment_a);
		EXPECT_EQ(res_ba_10.b, (loc{0.0f, 1.0f, 0.0f}));
		EXPECT_EQ(res_ba_10.a, (loc{0.0f, -1.0f, 0.0f}));

		auto const res_ba_11 = get_closest_points(flip(line_segment_b), flip(line_segment_a));
		EXPECT_EQ(res_ba_11.b, (loc{0.0f, 1.0f, 0.0f}));
		EXPECT_EQ(res_ba_11.a, (loc{0.0f, -1.0f, 0.0f}));
	}

	{
		constexpr geosimd::line_segment line_segment_a{loc{-1.0f, 0.0f, 0.0f}, loc{1.0f, 0.0f, 0.0f}};
		constexpr geosimd::line_segment line_segment_b{loc{2.0f, 2.0f, 0.0f},
			loc{3.0f, 3.0f, 0.0f}};

		auto const res_ab_00 = get_closest_points(line_segment_a, line_segment_b);
		EXPECT_EQ(res_ab_00.a, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_00.b, (loc{2.0f, 2.0f, 0.0f}));

		auto const res_ab_01 = get_closest_points(line_segment_a, flip(line_segment_b));
		EXPECT_EQ(res_ab_01.a, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_01.b, (loc{2.0f, 2.0f, 0.0f}));

		auto const res_ab_10 = get_closest_points(flip(line_segment_a), line_segment_b);
		EXPECT_EQ(res_ab_10.a, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_10.b, (loc{2.0f, 2.0f, 0.0f}));

		auto const res_ab_11 = get_closest_points(flip(line_segment_a), flip(line_segment_b));
		EXPECT_EQ(res_ab_11.a, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ab_11.b, (loc{2.0f, 2.0f, 0.0f}));

		auto const res_ba_00 = get_closest_points(line_segment_b, line_segment_a);
		EXPECT_EQ(res_ba_00.b, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_00.a, (loc{2.0f, 2.0f, 0.0f}));

		auto const res_ba_01 = get_closest_points(line_segment_b, flip(line_segment_a));
		EXPECT_EQ(res_ba_01.b, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_01.a, (loc{2.0f, 2.0f, 0.0f}));

		auto const res_ba_10 = get_closest_points(flip(line_segment_b), line_segment_a);
		EXPECT_EQ(res_ba_10.b, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_10.a, (loc{2.0f, 2.0f, 0.0f}));

		auto const res_ba_11 = get_closest_points(flip(line_segment_b), flip(line_segment_a));
		EXPECT_EQ(res_ba_11.b, (loc{1.0f, 0.0f, 0.0f}));
		EXPECT_EQ(res_ba_11.a, (loc{2.0f, 2.0f, 0.0f}));
	}

	{
		constexpr geosimd::line_segment line_segment_a{loc{1.0f, 0.0f, 0.0f}, loc{3.0f, 0.0f, 0.0f}};
		constexpr geosimd::line_segment line_segment_b{loc{4.0f, 4.0f, 0.0f}, loc{8.0f, 8.0f, 0.0f}};

		auto const res_ab_00 = get_closest_points(line_segment_a, line_segment_b);
		EXPECT_EQ(res_ab_00.a, (loc{3.0f, 0.0f ,0.0f}));
		EXPECT_EQ(res_ab_00.b, (loc{4.0f, 4.0f ,0.0f}));

		auto const res_ab_01 = get_closest_points(line_segment_a, flip(line_segment_b));
		EXPECT_EQ(res_ab_01.a, (loc{3.0f, 0.0f ,0.0f}));
		EXPECT_EQ(res_ab_01.b, (loc{4.0f, 4.0f ,0.0f}));

		auto const res_ab_10 = get_closest_points(flip(line_segment_a), line_segment_b);
		EXPECT_EQ(res_ab_10.a, (loc{3.0f, 0.0f ,0.0f}));
		EXPECT_EQ(res_ab_10.b, (loc{4.0f, 4.0f ,0.0f}));

		auto const res_ab_11 = get_closest_points(flip(line_segment_a), flip(line_segment_b));
		EXPECT_EQ(res_ab_11.a, (loc{3.0f, 0.0f ,0.0f}));
		EXPECT_EQ(res_ab_11.b, (loc{4.0f, 4.0f ,0.0f}));

		auto const res_ba_00 = get_closest_points(line_segment_b, line_segment_a);
		EXPECT_EQ(res_ba_00.b, (loc{3.0f, 0.0f ,0.0f}));
		EXPECT_EQ(res_ba_00.a, (loc{4.0f, 4.0f ,0.0f}));

		auto const res_ba_01 = get_closest_points(line_segment_b, flip(line_segment_a));
		EXPECT_EQ(res_ba_01.b, (loc{3.0f, 0.0f ,0.0f}));
		EXPECT_EQ(res_ba_01.a, (loc{4.0f, 4.0f ,0.0f}));

		auto const res_ba_10 = get_closest_points(flip(line_segment_b), line_segment_a);
		EXPECT_EQ(res_ba_10.b, (loc{3.0f, 0.0f ,0.0f}));
		EXPECT_EQ(res_ba_10.a, (loc{4.0f, 4.0f ,0.0f}));

		auto const res_ba_11 = get_closest_points(flip(line_segment_b), flip(line_segment_a));
		EXPECT_EQ(res_ba_11.b, (loc{3.0f, 0.0f ,0.0f}));
		EXPECT_EQ(res_ba_11.a, (loc{4.0f, 4.0f ,0.0f}));
	}
}