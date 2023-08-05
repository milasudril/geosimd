//@	{"target":{"name":"scaling.test"}}

#include "./scaling.hpp"

#include "./euclidian_space.hpp"

#include "testfwk/testfwk.hpp"

namespace
{
	using my_vector_space = geosimd::euclidian_space<float, 3>;
}

TESTCASE(geosimd_scaling_test_default_construct)
{
	geosimd::scaling<my_vector_space> scale;
	EXPECT_EQ(scale.get()[0], 1.0f);
	EXPECT_EQ(scale.get()[1], 1.0f);
	EXPECT_EQ(scale.get()[2], 1.0f);
	EXPECT_EQ(scale.get()[3], 1.0f);
	EXPECT_EQ(std::size(scale), 3);
	EXPECT_EQ(norm(scale), 1.0f);
}

TESTCASE(geosimd_scaling_test_construct_with_factors)
{
	geosimd::scaling<my_vector_space> scale{1.0f, 2.0f, 3.0f};
	EXPECT_EQ(scale.get()[0], 1.0f);
	EXPECT_EQ(scale.get()[1], 2.0f);
	EXPECT_EQ(scale.get()[2], 3.0f);
	EXPECT_EQ(scale.get()[3], 1.0f);
	EXPECT_EQ(std::size(scale), 3);
	auto const expected_norm = std::pow(6.0f, 1.0f/3.0f);
	EXPECT_EQ(norm(scale), expected_norm);
}

TESTCASE(geosimd_scaling_test_normalize)
{
	geosimd::scaling<my_vector_space> scale{1.0f, 2.0f, 3.0f};
	EXPECT_LT(std::abs(norm(scale/norm(scale)) - 1.0f), 1.0e-6f);
}

TESTCASE(geosimd_scaling_test_div_by_scalar)
{
	geosimd::scaling<my_vector_space> scale{1.0f, 2.0f, 3.0f};
	auto const new_scale = scale/2.0f;
	EXPECT_EQ(new_scale, (geosimd::scaling<my_vector_space>{0.5f, 1.0f, 1.5f}));
	EXPECT_LT(std::abs(norm(new_scale) - 0.5*norm(scale)), 1.0e-6f);
}

TESTCASE(geosimd_scaling_test_mul_by_scalar)
{
	geosimd::scaling<my_vector_space> scale{1.0f, 2.0f, 3.0f};
	auto const new_scale = 2.0f*scale;
	EXPECT_EQ(new_scale, (geosimd::scaling<my_vector_space>{2.0f, 4.0f, 6.0f}));
	EXPECT_EQ(norm(new_scale), 2.0f*norm(scale));
}

TESTCASE(geosimd_scaling_test_mul_by_scaling)
{
	geosimd::scaling<my_vector_space> scale_a{1.0f, 2.0f, 3.0f};
	geosimd::scaling<my_vector_space> scale_b{2.0f, 3.0f, 4.0f};
	auto const res = scale_a * scale_b;
	EXPECT_EQ(res, (geosimd::scaling<my_vector_space>{2.0f, 6.0f, 12.0f}));
}

TESTCASE(geosimd_scaling_test_div_by_scaling)
{
	geosimd::scaling<my_vector_space> scale_a{1.0f, 2.0f, 3.0f};
	geosimd::scaling<my_vector_space> scale_b{2.0f, 3.0f, 4.0f};
	auto const res = scale_a / scale_b;
	EXPECT_EQ(res, (geosimd::scaling<my_vector_space>{0.5f, 2.0f/3.0f, 0.75f}));
}

TESTCASE(geosimd_scaling_test_invert)
{
	geosimd::scaling<my_vector_space> scale{1.0f, 2.0f, 3.0f};
	auto const inv = inverted(scale);
	EXPECT_EQ(inv*scale, geosimd::scaling<my_vector_space>{});
}

TESTCASE(geosimd_scaling_test_unity)
{
	geosimd::scaling<my_vector_space> scale{};
	auto const unity = one(geosimd::empty<geosimd::scaling<my_vector_space>>{});
	EXPECT_EQ(scale, unity);
}