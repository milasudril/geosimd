//@	{"target":{"name":"euclidian_space.test"}}

#include "./euclidian_space.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geosimd_euclidian_space_subset)
{
	using my_vector_space = geosimd::euclidian_space<float, 3>;
	static_assert(geosimd::hilbert_space<my_vector_space>);
	static_assert(geosimd::metric_normed_space<my_vector_space, geosimd::hilbert_space_mixin<geosimd::vec4f32_t>>);
}

TESTCASE(geosimd_euclidian_space_point_props)
{
	using loc = geosimd::location<float, 3>;
	using vec = geosimd::displacement<float, 3>;
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
