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
}
