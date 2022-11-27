//@	{"target":{"name":"default_norm.test"}}

#include "./default_norm.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geosimd_distance_int)
{
	auto d1 = geosimd::distance(-2, 5);
	auto d2 = geosimd::distance(5, -2);
	static_assert(std::is_same_v<decltype(d1), int>);
	static_assert(std::is_same_v<decltype(d2), int>);
	EXPECT_EQ(d1, 7);
	EXPECT_EQ(d2, 7);
}

TESTCASE(geosimd_distance_int_ptr)
{
	std::array<int, 5> buffer{};
	auto d1 = geosimd::distance(std::begin(buffer), std::end(buffer));
	auto d2 = geosimd::distance(std::end(buffer), std::begin(buffer));
	static_assert(std::is_same_v<decltype(d1), ptrdiff_t>);
	static_assert(std::is_same_v<decltype(d2), ptrdiff_t>);
	EXPECT_EQ(d1, std::ssize(buffer));
	EXPECT_EQ(d2, std::ssize(buffer));
}

TESTCASE(geosimd_norm)
{
	auto val = geosimd::norm(-4);
	static_assert(std::is_same_v<decltype(val), int>);
	EXPECT_EQ(val, 4);
}