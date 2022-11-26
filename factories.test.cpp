//@	{"target":{"name":"factories.test"}}

#include "./factories.hpp"

#include "testfwk/testfwk.hpp"

int (* one_ptr)();

TESTCASE(factories_one)
{
	auto one = geosimd::one<int>();
	static_assert(std::is_same_v<decltype(one), int>);
	EXPECT_EQ(one, 1);

	if(!std::is_constant_evaluated())
	{
		// Do an indirect call through a global pointer to collect code coverage
		one_ptr = geosimd::one<int>;
		EXPECT_EQ(one_ptr(), 1);
	}
}

int (* zero_ptr)();

TESTCASE(factories_zero)
{
	auto zero = geosimd::zero<int>();
	static_assert(std::is_same_v<decltype(zero), int>);
	EXPECT_EQ(zero, 0);

	if(!std::is_constant_evaluated())
	{
		// Do an indirect call through a global pointer to collect code coverage
		zero_ptr = geosimd::zero<int>;
		EXPECT_EQ(zero_ptr(), 0);
	}
}

TESTCASE(factories_create)
{
	auto val = geosimd::create<std::tuple<int, double>>(1, 2.0);
	static_assert(std::is_same_v<decltype(val), std::tuple<int, double>>);

	auto [first, second] = val;

	EXPECT_EQ(first, 1);
	EXPECT_EQ(second, 2.0);
}
