//@	{"target":{"name":"rotation.test"}}

#include "./rotation.hpp"
#include "./abstract_spaces.hpp"

#include "testfwk/testfwk.hpp"

namespace
{
	struct my_vector_space
	{
		using vector_type = geosimd::vec_t<float, 4>;
		using scalar_type = float;
		using enable_homogenous_coordinates_t = void;
		using enable_rotations_t = void;
	};
}

static_assert(!geosimd::vector<geosimd::rotation<my_vector_space>>);

TESTCASE(geosimd_rot3_default_value)
{
	geosimd::rotation<my_vector_space> rot;
	EXPECT_EQ(rot.get(), one(geosimd::empty<geosimd::mat_4x4<float>>{}));
}

TESTCASE(geosimd_rot3_init_quater_0)
{
	geosimd::rotation<my_vector_space> rot{geosimd::rotation_angle{geosimd::turns{0.25}}, geosimd::dimension_tag<0>{}};

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
	geosimd::rotation<my_vector_space> rot{geosimd::rotation_angle{geosimd::turns{0.25}}, geosimd::dimension_tag<1>{}};

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
	geosimd::rotation<my_vector_space> rot{geosimd::rotation_angle{geosimd::turns{0.25}}, geosimd::dimension_tag<2>{}};

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

TESTCASE(geosimd_rot3_push_quater)
{
	auto const res = geosimd::rotation<my_vector_space>{}.push(geosimd::turns{0.25}, geosimd::dimension_tag<2>{}).get()
		* geosimd::vec_t<float, 4>{1.0f, 0.0f, 0.0f, 0.0f};
	EXPECT_EQ(res, (geosimd::vec_t<float, 4>{0.0f, 1.0f, 0.0f, 0.0f}))
}

TESTCASE(geosimd_rot3_pop_quater)
{
	auto const res = geosimd::rotation<my_vector_space>{}.pop(geosimd::turns{0.25}, geosimd::dimension_tag<2>{}).get()
		* geosimd::vec_t<float, 4>{1.0f, 0.0f, 0.0f, 0.0f};
	EXPECT_EQ(res, (geosimd::vec_t<float, 4>{0.0f, -1.0f, 0.0f, 0.0f}))
}

TESTCASE(geosimd_rot3_push_and_pop)
{
	geosimd::rotation<my_vector_space> test;

	auto const init = test;
	test.push(geosimd::turns{0.25}, geosimd::dimension_tag<0>{});
	auto const after_first = test;
	test.push(geosimd::turns{0.25}, geosimd::dimension_tag<1>{});
	auto const after_second = test;
	test.push(geosimd::turns{0.25}, geosimd::dimension_tag<2>{});

	EXPECT_EQ(inverted(test).get()*test.get(), geosimd::rotation<my_vector_space>{}.get());
	EXPECT_EQ(test.get() * inverted(test).get(), geosimd::rotation<my_vector_space>{}.get());
	EXPECT_EQ(inverted(geosimd::rotation<my_vector_space>{}.push(geosimd::turns{0.25}, geosimd::dimension_tag<0>{})),
		geosimd::rotation<my_vector_space>{}.pop(geosimd::turns{0.25}, geosimd::dimension_tag<0>{}));
	EXPECT_EQ(geosimd::rotation<my_vector_space>{}.pop(geosimd::turns{0.25}, geosimd::dimension_tag<0>{}),
		geosimd::rotation<my_vector_space>{}.push(geosimd::turns{-0.25}, geosimd::dimension_tag<0>{}));

	test.pop(geosimd::turns{0.25}, geosimd::dimension_tag<2>{});
	EXPECT_EQ(test, after_second);

	test.pop(geosimd::turns{0.25}, geosimd::dimension_tag<1>{});
	EXPECT_EQ(test, after_first);

	test.pop(geosimd::turns{0.25}, geosimd::dimension_tag<0>{});
	EXPECT_EQ(test, init);
}