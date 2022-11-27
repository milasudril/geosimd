//@	{"target":{"name":"metric_normed_space.test"}}

#include "./metric_normed_space.hpp"

#include "testfwk/testfwk.hpp"

namespace
{
	size_t norm_called = 0;
	size_t norm_squared_called = 0;

	struct my_vector_space
	{
		using vector_type = int;
		using point_type = int;
		using scalar_type = int;

		static constexpr auto norm(vector_type v)
		{
			if(!std::is_constant_evaluated())
			{ ++norm_called; }
			return geosimd::norm(v);
		}

		static constexpr auto norm_squared(vector_type v)
		{
			if(!std::is_constant_evaluated())
			{ ++norm_squared_called; }
			return v*v;
		}
	};

	using my_metric_normed_space_mixin = geosimd::metric_normed_space_mixin<int, my_vector_space>;
}

TESTCASE(geosimd_metric_normed_space_distance)
{
	if(!std::is_constant_evaluated())
	{
		norm_called = 0;
		norm_squared_called = 0;
	}

	auto d1 = my_metric_normed_space_mixin::distance(1, 5);
	auto d2 = my_metric_normed_space_mixin::distance(5, 1);
	static_assert(std::is_same_v<decltype(d1), int>);
	static_assert(std::is_same_v<decltype(d2), int>);
	EXPECT_EQ(d1, 4);
	EXPECT_EQ(d2, 4);

	if(!std::is_constant_evaluated())
	{
		EXPECT_EQ(norm_called, 2);
		EXPECT_EQ(norm_squared_called, 0);
		norm_called = 0;
	}
}

TESTCASE(geosimd_metric_normed_space_distance_squared)
{
	if(!std::is_constant_evaluated())
	{
		norm_called = 0;
	}

	auto d1 = my_metric_normed_space_mixin::distance_squared(1, 5);
	auto d2 = my_metric_normed_space_mixin::distance_squared(5, 1);
	static_assert(std::is_same_v<decltype(d1), int>);
	static_assert(std::is_same_v<decltype(d2), int>);
	EXPECT_EQ(d1, 16);
	EXPECT_EQ(d2, 16);

	if(!std::is_constant_evaluated())
	{
		EXPECT_EQ(norm_called, 0);
		EXPECT_EQ(norm_squared_called, 2);
		norm_squared_called = 0;
	}
}


namespace
{
	struct my_metric_normed_space:geosimd::metric_normed_space_mixin<int, my_vector_space>
	{
	};

	static_assert(geosimd::metric_normed_space<my_metric_normed_space>);
}