//@	{"target":{"name":"angle.test"}}

#include "./angle.hpp"
#include "./abstract_spaces.hpp"

#include "testfwk/testfwk.hpp"

static_assert(geosimd::vector<geosimd::turn_angle>);
static_assert(std::totally_ordered<geosimd::turn_angle>);
static_assert(geosimd::point<geosimd::rotation_angle>);
static_assert(geosimd::uses_vectorops_mixin_v<geosimd::turn_angle>);

TESTCASE(geosimd_rad_from_value)
{
	geosimd::rad const x{0.5};
	EXPECT_EQ(x.value, 0.5);
}

TESTCASE(geosimd_rad_from_turns)
{
	geosimd::rad const x{geosimd::turns{0.5}};
	EXPECT_EQ(x.value, std::numbers::pi_v<double>);
	EXPECT_EQ(static_cast<geosimd::turns>(x), geosimd::turns{0.5});
}

TESTCASE(geosimd_turn_angle_full_turn)
{
	EXPECT_EQ(geosimd::turn_angle::full_turn, 0x1'0000'0000L);
}

TESTCASE(geosimd_turn_angle_from_value)
{
	geosimd::turn_angle x{0x80000000};
	EXPECT_EQ(x.get(), 0x80000000);
}

TESTCASE(geosimd_trun_angle_from_turns)
{
	geosimd::turn_angle x{geosimd::turns{0.5}};
	EXPECT_EQ(x.get(), 0x80000000);
}

TESTCASE(geosimd_trun_angle_from_rad)
{
	geosimd::turn_angle x{geosimd::rad{std::numbers::pi_v<double>}};
	EXPECT_EQ(x.get(), 0x80000000);
}

TESTCASE(geosimd_trun_angle_scale_mult)
{
	geosimd::turn_angle x{0x40000000};
	x *= 2.0;

	EXPECT_EQ(x.get(), 0x80000000);
}

TESTCASE(geosimd_trun_angle_scale_div)
{
	geosimd::turn_angle x{0x40000000};
	x /= 2.0;

	EXPECT_EQ(x.get(), 0x20000000);
}

TESTCASE(geosimd_turn_angle_add)
{
	geosimd::turn_angle a{0x40000000};
	a += geosimd::turn_angle{0x20000000};
	EXPECT_EQ(a.get(), 0x60000000);
}

TESTCASE(geosimd_turn_angle_zero)
{
	EXPECT_EQ(geosimd::zero<geosimd::turn_angle>().get(), 0);
}

TESTCASE(geosimd_rotation_angle_from_rad)
{
	geosimd::rotation_angle const x{geosimd::rad{std::numbers::pi_v<double>}};
	EXPECT_EQ(x.get(), 0x80000000);
	EXPECT_EQ(to_rad(x), geosimd::rad{std::numbers::pi_v<double>});
}

TESTCASE(geosimd_rotation_angle_from_turns)
{
	geosimd::rotation_angle const a{geosimd::turns{-0.25f}};
	geosimd::rotation_angle const b{geosimd::turns{0.0f  }};
	geosimd::rotation_angle const c{geosimd::turns{0.25f }};
	geosimd::rotation_angle const d{geosimd::turns{0.5f  }};
	geosimd::rotation_angle const f{geosimd::turns{-0.5f }};
	geosimd::rotation_angle const g{geosimd::turns{2.0f  }};
	geosimd::rotation_angle const h{geosimd::turns{-2.0f }};

	EXPECT_EQ(a.get(), 0xc0000000);
	EXPECT_EQ(b.get(), 0x00000000);
	EXPECT_EQ(c.get(), 0x40000000);
	EXPECT_EQ(d.get(), 0x80000000);
	EXPECT_EQ(f.get(), 0x80000000);
	EXPECT_EQ(g.get(), 0x00000000);
	EXPECT_EQ(h.get(), 0x00000000);

	EXPECT_EQ(to_turns(a), geosimd::turns{0.75} );
	EXPECT_EQ(to_turns(b), geosimd::turns{0.0 } );
	EXPECT_EQ(to_turns(c), geosimd::turns{0.25} );
	EXPECT_EQ(to_turns(d), geosimd::turns{0.5 });
}

TESTCASE(geosimd_rotation_angle_add_subtract)
{
	geosimd::rotation_angle const a{geosimd::turns{-0.25}};
	geosimd::rotation_angle const b{geosimd::turns{0.5}};
	geosimd::turn_angle const c{geosimd::turns{-0.25}};
	geosimd::turn_angle const d{geosimd::turns{0.5}};

	EXPECT_EQ((a + d).get(), 0x40000000);
	EXPECT_EQ((b - c).get(), 0xc0000000);

	EXPECT_EQ((b + geosimd::turns{0.25f}).get(), 0xc0000000);
	EXPECT_EQ((b - geosimd::turns{0.25f}).get(), 0x40000000);

	geosimd::rotation_angle const almost_full_turn{0xffffffff};
	auto no_rot = geosimd::zero<geosimd::rotation_angle>();
	EXPECT_EQ(almost_full_turn - no_rot, geosimd::turn_angle{0xffffffff});
	EXPECT_EQ(no_rot - almost_full_turn, geosimd::turn_angle{-0xffffffffll});
}

TESTCASE(geosimd_rotation_angle_sine_cosine)
{
	geosimd::rotation_angle const a{geosimd::turns{-0.25f}};
	geosimd::rotation_angle const b{geosimd::turns{0.0f  }};
	geosimd::rotation_angle const c{geosimd::turns{0.25f }};
	geosimd::rotation_angle const d{geosimd::turns{0.5f  }};

	EXPECT_EQ(sin(a), -1.0f);
	EXPECT_EQ(sin(b), 0.0f);
	EXPECT_EQ(sin(c), 1.0f);
	EXPECT_EQ(sin(d), 0.0f);

	EXPECT_EQ(cos(a), 0.0f);
	EXPECT_EQ(cos(b), 1.0f);
	EXPECT_EQ(cos(c), 0.0f);
	EXPECT_EQ(cos(d), -1.0f);

	std::array<std::pair<float, float>, 16> std_vals{
		std::pair{1.0f, 0.0f},
		std::pair{0.5f*std::numbers::sqrt3_v<float>, 0.5f},
		std::pair{0.5f*std::numbers::sqrt2_v<float>, 0.5f*std::numbers::sqrt2_v<float>},
		std::pair{0.5f, 0.5f*std::numbers::sqrt3_v<float>},
		std::pair{0.0f, 1.0f},
		std::pair{-0.5f, 0.5f*std::numbers::sqrt3_v<float>},
		std::pair{-0.5f*std::numbers::sqrt2_v<float>, 0.5f*std::numbers::sqrt2_v<float>},
		std::pair{-0.5f*std::numbers::sqrt3_v<float>, 0.5f},
		std::pair{-1.0f, 0.0f},
		std::pair{-0.5f*std::numbers::sqrt3_v<float>, -0.5f},
		std::pair{-0.5f*std::numbers::sqrt2_v<float>, -0.5f*std::numbers::sqrt2_v<float>},
		std::pair{-0.5f, -0.5f*std::numbers::sqrt3_v<float>},
		std::pair{0.0f, -1.0f},
		std::pair{0.5f, -0.5f*std::numbers::sqrt3_v<float>},
		std::pair{0.5f*std::numbers::sqrt2_v<float>, -0.5f*std::numbers::sqrt2_v<float>},
		std::pair{0.5f*std::numbers::sqrt3_v<float>, -0.5f},
	};

	size_t l = 0;
	for(int k = 24; k != 48; ++k)
	{
		if( (k % 2 == 0) || (k - 3)%6 == 0)
		{
			auto val = static_cast<double>(k)/24.0;
			auto const rotation_angle = geosimd::rotation_angle{geosimd::turns{val}};
			EXPECT_EQ(cos(rotation_angle), std_vals[l].first);
			EXPECT_EQ(sin(rotation_angle), std_vals[l].second);
			EXPECT_LE(cos(rotation_angle)*cos(rotation_angle) + sin(rotation_angle)*sin(rotation_angle), 1.0f);
			++l;
		}
	}
}

TESTCASE(geosimd_turn_angle_scale)
{
	geosimd::turn_angle const x{geosimd::turns{0.25}};
	auto const y = 4.0*x;
	EXPECT_EQ(y.get(), 0x1'0000'0000ll);
}
