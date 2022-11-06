//@	{"target":{"name":"rot_3.test"}}

#include "./rot_3.hpp"
#include "./abstract_spaces.hpp"

#include "testfwk/testfwk.hpp"

static_assert(!geosimd::vector<geosimd::rot_3>);

TESTCASE(geosimd_rot3_default_value)
{
	geosimd::rot_3 rot;
	EXPECT_EQ(rot.get(), one(geosimd::empty<geosimd::mat_4x4<float>>{}));
}

TESTCASE(geosimd_rot3_init_quater_0)
{
	geosimd::rot_3 rot{geosimd::rotation_angle{geosimd::turns{0.25}}, geosimd::dimension_tag<0>{}};

	geosimd::vec_t<float, 4> const x{1.0f, 0.0f, 0.0f, 0.0f};
	geosimd::vec_t<float, 4> const y{0.0f, 1.0f, 0.0f, 0.0f};
	geosimd::vec_t<float, 4> const z{0.0f, 0.0f, 1.0f, 0.0f};


	auto const x_prime = rot.get() * x;
	EXPECT_EQ(x_prime, x);

	auto const y_prime = rot.get() * y;
	EXPECT_EQ(y_prime, (geosimd::vec_t<float, 4>{0.0f, 0.0f, 1.0f, 0.0f}));

	auto const z_prime = rot.get() * z;
	EXPECT_EQ(z_prime, (geosimd::vec_t<float, 4>{0.0f, -1.0f, 0.0f, 0.0f}));
}

TESTCASE(geosimd_rot3_init_quater_1)
{
	geosimd::rot_3 rot{geosimd::rotation_angle{geosimd::turns{0.25}}, geosimd::dimension_tag<1>{}};

	geosimd::vec_t<float, 4> const x{1.0f, 0.0f, 0.0f, 0.0f};
	geosimd::vec_t<float, 4> const y{0.0f, 1.0f, 0.0f, 0.0f};
	geosimd::vec_t<float, 4> const z{0.0f, 0.0f, 1.0f, 0.0f};


	auto const x_prime = rot.get() * x;
	EXPECT_EQ(x_prime, (geosimd::vec_t<float, 4>{0.0f, 0.0f, -1.0f, 0.0f}));

	auto const y_prime = rot.get() * y;
	EXPECT_EQ(y_prime, y);

	auto const z_prime = rot.get() * z;
	EXPECT_EQ(z_prime, (geosimd::vec_t<float, 4>{1.0f, 0.0f, 0.0f, 0.0f}));
}

TESTCASE(geosimd_rot3_init_quater_2)
{
	geosimd::rot_3 rot{geosimd::rotation_angle{geosimd::turns{0.25}}, geosimd::dimension_tag<2>{}};

	geosimd::vec_t<float, 4> const x{1.0f, 0.0f, 0.0f, 0.0f};
	geosimd::vec_t<float, 4> const y{0.0f, 1.0f, 0.0f, 0.0f};
	geosimd::vec_t<float, 4> const z{0.0f, 0.0f, 1.0f, 0.0f};


	auto const x_prime = rot.get() * x;
	EXPECT_EQ(x_prime, (geosimd::vec_t<float, 4>{0.0f, 1.0f, 0.0f, 0.0f}));

	auto const y_prime = rot.get() * y;
	EXPECT_EQ(y_prime, (geosimd::vec_t<float, 4>{-1.0f, 0.0f, 0.0f, 0.0f}));

	auto const z_prime = rot.get() * z;
	EXPECT_EQ(z_prime, z);
}