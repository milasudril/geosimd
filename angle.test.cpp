//@	{"target":{"name":"angle.test.cpp"}}

#include "./angle.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geosimd_angle_from_turns)
{
	constexpr geosimd::angle a{-0.25f, geosimd::turns{}};
	constexpr geosimd::angle b{0.0f, geosimd::turns{}};
	constexpr geosimd::angle c{0.25f, geosimd::turns{}};
	constexpr geosimd::angle d{0.5f, geosimd::turns{}};
	constexpr geosimd::angle f{-0.5f, geosimd::turns{}};
	constexpr geosimd::angle g{2.0f, geosimd::turns{}};

	static_assert(a.get() == 0xc0000000);
	static_assert(b.get() == 0x00000000);
	static_assert(c.get() == 0x40000000);
	static_assert(d.get() == 0x80000000);
	static_assert(f.get() == 0x80000000);

	EXPECT_EQ(a.in_turns(), 0.75f);
	EXPECT_EQ(b.in_turns(), 0.0f);
	EXPECT_EQ(c.in_turns(), 0.25f);
	EXPECT_EQ(d.in_turns(), 0.5f);
}
