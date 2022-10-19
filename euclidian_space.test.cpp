//@	{"target":{"name":"euclidian_space.test"}}

#include "./euclidian_space.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geosimd_euclidian_space_subset)
{
	using my_vector_space = geosimd::euclidian_space<float, 3>;
	static_assert(geosimd::hilbert_space<my_vector_space>);
	static_assert(geosimd::metric_normed_space<my_vector_space>);
	static_assert(!geosimd::vector<geosimd::direction<float, 3>>);
}

TESTCASE(geosimd_euclidian_space_point_props)
{
	using loc = geosimd::location<float, 3>;
	static_assert(geosimd::point<loc>);
	using vec = geosimd::displacement<float, 3>;
	static_assert(geosimd::vector<vec>);
	static_assert(loc::size() == 3);

	constexpr loc a{1.0f, 4.0f, 5.0f};
	constexpr loc b{-1.0f, 1.0f, -1.0f};
	constexpr auto c = a - b;
	static_assert(c == vec{2.0f, 3.0f, 6.0f});

	constexpr auto distance_ab = distance(a, b);
	constexpr auto distance_ba = distance(b, a);
	static_assert(distance_ab == distance_ba);
	static_assert(distance_ab == 7.0f);
	static_assert(distance_ab == norm(c));

	static_assert(x(a) == 1.0f);
	static_assert(y(a) == 4.0f);
	static_assert(z(a) == 5.0f);

	constexpr auto bpc = b + c;
	static_assert(bpc == a);

	constexpr auto bmc = b - c;
	static_assert(bmc == loc{-3.0f, -2.0f, -7.0f});

	constexpr auto mid = midpoint(a, b);
	static_assert(mid == loc{0.0f, 2.5f, 2.0f});
	static_assert(mid[3] == 1.0f);

	static_assert(lerp(loc{1.0f, 2.0f, 4.0f}, loc{2.0f, 4.0f, 8.0f}, 0.25f) == loc{1.25f, 2.5f, 5.0f});
}

TESTCASE(geosimd_euclidian_space_to_string)
{
	using loc = geosimd::location<float, 3>;
	using vec = geosimd::displacement<float, 3>;
	auto const str_vec = to_string(vec{2.0f, 3.0f, 6.0f});
	auto const str_point = to_string(loc{1.0f, 4.0f, 5.0f});
	EXPECT_EQ(str_vec, "(2.000000, 3.000000, 6.000000)");
	EXPECT_EQ(str_point, "(1.000000, 4.000000, 5.000000)");
}

TESTCASE(geosimd_euclidian_space_direction)
{
	using vec = geosimd::displacement<float, 3>;
	geosimd::direction dir{vec{1.0f, 0.0f, 0.0f}};
	auto const x = 2.0f*dir;
	static_assert(std::is_same_v<decltype(x), vec const>);
	EXPECT_EQ(x, (vec{2.0f, 0.0f, 0.0f}));
}