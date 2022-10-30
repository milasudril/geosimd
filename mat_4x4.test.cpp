//@	{"target":{"name":"mat_4x4.test"}}

#include "./mat_4x4.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geosimd_mat44_zero)
{
	using mat44 = geosimd::mat_4x4<int>;
	auto const A = zero(geosimd::empty<mat44>{});
	EXPECT_EQ(A.col(0), zero(geosimd::empty<mat44::column_type>{}));
	EXPECT_EQ(A.col(1), zero(geosimd::empty<mat44::column_type>{}));
	EXPECT_EQ(A.col(2), zero(geosimd::empty<mat44::column_type>{}));
	EXPECT_EQ(A.col(3), zero(geosimd::empty<mat44::column_type>{}));

	std::array<mat44::column_type, 4> cols{};
	for(int k = 0; k != 4; ++k)
	{
		cols[k] = 4*geosimd::vec_t<int, 4>{0, 1, 2, 3} + geosimd::vec_t<int, 4>{k, k, k, k};
	}

	mat44 const B{cols};
	fprintf(stderr, "%s\n", to_string(B).c_str());
}

TESTCASE(geosimd_mat44_one)
{
	using mat44 = geosimd::mat_4x4<int>;
	auto const A = one(geosimd::empty<mat44>{});
	using vec = mat44::column_type;
	EXPECT_EQ(A.col(0), (vec{1, 0, 0, 0}));
	EXPECT_EQ(A.col(1), (vec{0, 1, 0, 0}));
	EXPECT_EQ(A.col(2), (vec{0, 0, 1, 0}));
	EXPECT_EQ(A.col(3), (vec{0, 0, 0, 1}));
}