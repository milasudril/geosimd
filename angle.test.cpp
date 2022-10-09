//@	{"target":{"name":"angle.test.cpp"}}

#include "./angle.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geosimd_angle_from_turns)
{
	geosimd::angle const a{-0.25f, geosimd::turns{}};
	geosimd::angle const b{0.0f, geosimd::turns{}};
	geosimd::angle const c{0.25f, geosimd::turns{}};
	geosimd::angle const d{0.5f, geosimd::turns{}};
	geosimd::angle const f{-0.5f, geosimd::turns{}};
	geosimd::angle const g{2.0f, geosimd::turns{}};
	geosimd::angle const h{-2.0f, geosimd::turns{}};

	EXPECT_EQ(a.get(), 0xc0000000);
	EXPECT_EQ(b.get(), 0x00000000);
	EXPECT_EQ(c.get(), 0x40000000);
	EXPECT_EQ(d.get(), 0x80000000);
	EXPECT_EQ(f.get(), 0x80000000);
	EXPECT_EQ(g.get(), 0x00000000);
	EXPECT_EQ(h.get(), 0x00000000);

	EXPECT_EQ(a.in_turns(), 0.75f);
	EXPECT_EQ(b.in_turns(), 0.0f);
	EXPECT_EQ(c.in_turns(), 0.25f);
	EXPECT_EQ(d.in_turns(), 0.5f);
}
