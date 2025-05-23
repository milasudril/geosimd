//@	{"target":{"name":"box_size_test"}}

#include "./box_size.hpp"
#include "./euclidian_space.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(box_size_fit_xy_keep_z_wide_target)
{
	geosimd::box_size<geosimd::euclidian_space<float, 3>> const target_box{2.0f, 1.0f, 0.0f};
	geosimd::box_size<geosimd::euclidian_space<float, 3>> const source_box{1.5f, 1.0f, 0.0f};

	auto const result = source_box.fit_xy_keep_z(target_box);

	printf("%.8g %.8g\n", result[0], result[1]);
}

TESTCASE(box_size_fit_xy_keep_z_tall_target)
{
	geosimd::box_size<geosimd::euclidian_space<float, 3>> const target_box{1.0f, 2.0f, 0.0f};
	geosimd::box_size<geosimd::euclidian_space<float, 3>> const source_box{1.5f, 1.0f, 0.0f};

	auto const result = source_box.fit_xy_keep_z(target_box);

	printf("%.8g %.8g\n", result[0], result[1]);
}

TESTCASE(box_size_fit_xy_keep_z_small_target)
{
	geosimd::box_size<geosimd::euclidian_space<float, 3>> const target_box{1.0f, 0.5f, 0.0f};
	geosimd::box_size<geosimd::euclidian_space<float, 3>> const source_box{1.5f, 1.0f, 0.0f};

	auto const result = source_box.fit_xy_keep_z(target_box);

	printf("%.8g %.8g\n", result[0], result[1]);
}