//@	{"target":{"name":"mat_4x4.test"}}

#include "./mat_4x4.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geosimd_mat44_zero)
{
	using mat44 = geosimd::mat_4x4<int>;
	auto const val = zero(geosimd::empty<mat44>{});
	EXPECT_EQ(val.col(0), zero(geosimd::empty<mat44::column_type>{}));
	EXPECT_EQ(val.col(1), zero(geosimd::empty<mat44::column_type>{}));
	EXPECT_EQ(val.col(2), zero(geosimd::empty<mat44::column_type>{}));
	EXPECT_EQ(val.col(3), zero(geosimd::empty<mat44::column_type>{}));
}

TESTCASE(geosimd_mat44_one)
{
	using mat44 = geosimd::mat_4x4<int>;
	auto const val = one(geosimd::empty<mat44>{});
	using vec = mat44::column_type;
	EXPECT_EQ(val.col(0), (vec{1, 0, 0, 0}));
	EXPECT_EQ(val.col(1), (vec{0, 1, 0, 0}));
	EXPECT_EQ(val.col(2), (vec{0, 0, 1, 0}));
	EXPECT_EQ(val.col(3), (vec{0, 0, 0, 1}));
}