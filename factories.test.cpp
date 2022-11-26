//@	{"target":{"name":"factories.test"}}

#include "./factories.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(factories_one)
{
	auto one = geosimd::one<int>();
	static_assert(std::is_same_v<decltype(one), int>);
	EXPECT_EQ(one, 1);
}

TESTCASE(factories_zero)
{
	auto one = geosimd::zero<int>();
	static_assert(std::is_same_v<decltype(one), int>);
	EXPECT_EQ(one, 0);
}

TESTCASE(factories_create)
{
	auto val = geosimd::create<std::tuple<int, double>>(1, 2.0);
	static_assert(std::is_same_v<decltype(val), std::tuple<int, double>>);

	auto [first, second] = val;

	EXPECT_EQ(first, 1);
	EXPECT_EQ(second, 2.0);
}
