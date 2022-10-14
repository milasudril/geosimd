//@	{"target":{"name":"angle.test.cpp"}}

#include "./angle.hpp"
#include "./abstract_spaces.hpp"

#include "testfwk/testfwk.hpp"

static_assert(geosimd::vector<geosimd::turn_angle>);
static_assert(geosimd::point<geosimd::rotation_angle>);

TESTCASE(geosimd_rotation_angle_from_turns)
{
	constexpr geosimd::rotation_angle a{geosimd::turns{-0.25f}};
	constexpr geosimd::rotation_angle b{geosimd::turns{0.0f  }};
	constexpr geosimd::rotation_angle c{geosimd::turns{0.25f }};
	constexpr geosimd::rotation_angle d{geosimd::turns{0.5f  }};
	constexpr geosimd::rotation_angle f{geosimd::turns{-0.5f }};
	constexpr geosimd::rotation_angle g{geosimd::turns{2.0f  }};
	constexpr geosimd::rotation_angle h{geosimd::turns{-2.0f }};

	EXPECT_EQ(a.get(), 0xc0000000);
	EXPECT_EQ(b.get(), 0x00000000);
	EXPECT_EQ(c.get(), 0x40000000);
	EXPECT_EQ(d.get(), 0x80000000);
	EXPECT_EQ(f.get(), 0x80000000);
	EXPECT_EQ(g.get(), 0x00000000);
	EXPECT_EQ(h.get(), 0x00000000);

	EXPECT_EQ(to_turns(a), geosimd::turns{0.75} );
	EXPECT_EQ(to_turns(b), geosimd::turns{0.0 }  );
	EXPECT_EQ(to_turns(c), geosimd::turns{0.25} );
	EXPECT_EQ(to_turns(d), geosimd::turns{0.5 });
}

TESTCASE(geosimd_rotation_angle_from_rad)
{
	constexpr geosimd::rotation_angle x{geosimd::rad{std::numbers::pi_v<double>}};
	EXPECT_EQ(x.get(), 0x80000000);
	EXPECT_EQ(to_rad(x), geosimd::rad{std::numbers::pi_v<double>});
}

TESTCASE(geosimd_rotation_angle_add_subtract)
{
	constexpr geosimd::rotation_angle a{geosimd::turns{-0.25}};
	constexpr geosimd::rotation_angle b{geosimd::turns{0.5}};
	constexpr geosimd::turn_angle c{geosimd::turns{-0.25}};
	constexpr geosimd::turn_angle d{geosimd::turns{0.5}};

	EXPECT_EQ((a + d).get(), 0x40000000);
	EXPECT_EQ((b - c).get(), 0xc0000000);

	EXPECT_EQ((b + geosimd::turns{0.25f}).get(), 0xc0000000);
	EXPECT_EQ((b - geosimd::turns{0.25f}).get(), 0x40000000);

	constexpr geosimd::rotation_angle almost_full_turn{0xffffffff};
	constexpr auto no_rot = zero(geosimd::empty<geosimd::rotation_angle>{});
	EXPECT_EQ(almost_full_turn - no_rot, geosimd::turn_angle{0xffffffff});
	EXPECT_EQ(no_rot - almost_full_turn, geosimd::turn_angle{-0xffffffffll});
}

TESTCASE(geosimd_rotation_angle_sine_cosine)
{
	constexpr geosimd::rotation_angle a{geosimd::turns{-0.25f}};
	constexpr geosimd::rotation_angle b{geosimd::turns{0.0f  }};
	constexpr geosimd::rotation_angle c{geosimd::turns{0.25f }};
	constexpr geosimd::rotation_angle d{geosimd::turns{0.5f  }};

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
	constexpr geosimd::turn_angle x{geosimd::turns{0.25}};
	constexpr auto y = 4.0*x;
	EXPECT_EQ(y.get(), 0x1'0000'0000ll);
}
