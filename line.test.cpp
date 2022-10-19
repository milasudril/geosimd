//@	{"target":{"name":"line.test"}}

#include "./line.hpp"
#include "./euclidian_space.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geodimd_line)
{
	using loc = geosimd::location<float, 3>;

	constexpr geosimd::line line{loc{1.0f, 2.0f, 3.0f}, loc{2.0f, 4.0f, 6.0f}};
	EXPECT_EQ(line.p1, (loc{1.0f, 2.0f, 3.0f}));
	EXPECT_EQ(line.p2, (loc{2.0f, 4.0f, 6.0f}));
}