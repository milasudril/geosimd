//@	{"target":{"name":"angle.test.cpp"}}

#include "./angle.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geosimd_angle_from_turns)
{
	constexpr geosimd::angle a{geosimd::turns{-0.25f}};
	constexpr geosimd::angle b{geosimd::turns{0.0f  }};
	constexpr geosimd::angle c{geosimd::turns{0.25f }};
	constexpr geosimd::angle d{geosimd::turns{0.5f  }};
	constexpr geosimd::angle f{geosimd::turns{-0.5f }};
	constexpr geosimd::angle g{geosimd::turns{2.0f  }};
	constexpr geosimd::angle h{geosimd::turns{-2.0f }};

	EXPECT_EQ(a.get(), 0xc0000000);
	EXPECT_EQ(b.get(), 0x00000000);
	EXPECT_EQ(c.get(), 0x40000000);
	EXPECT_EQ(d.get(), 0x80000000);
	EXPECT_EQ(f.get(), 0x80000000);
	EXPECT_EQ(g.get(), 0x00000000);
	EXPECT_EQ(h.get(), 0x00000000);

	EXPECT_EQ(to_turns(a), geosimd::turns{0.75f} );
	EXPECT_EQ(to_turns(b), geosimd::turns{0.0f }  );
	EXPECT_EQ(to_turns(c), geosimd::turns{0.25f} );
	EXPECT_EQ(to_turns(d), geosimd::turns{0.5f });
}
