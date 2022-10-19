//@	{"target":{"name":"line.test"}}

#include "./line.hpp"
#include "./euclidian_space.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geodimd_line)
{
	using loc = geosimd::location<float, 3>;

	geosimd::line line{loc{1.0f, 2.0f, 3.0f}, loc{2.0f, 2.0f, 3.0f}};
	(void)line;
}