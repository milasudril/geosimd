//@	{"target":{"name":"mat_4x4.test"}}

#include "./mat_4x4.hpp"
#include "./abstract_spaces.hpp"

#include "testfwk/testfwk.hpp"

static_assert(geosimd::vector<geosimd::mat_4x4<int>>);

namespace
{
	auto gen_matrix()
	{
		using mat44 = geosimd::mat_4x4<int>;

		std::array<mat44::column_type, 4> cols{};
		for(int k = 0; k != 4; ++k)
		{
			cols[k] = 4*geosimd::vec_t<int, 4>{0, 1, 2, 3} + geosimd::vec_t<int, 4>{k, k, k, k};
		}
		return mat44{cols};
	}
}

TESTCASE(geosimd_mat44_zero)
{
	using mat44 = geosimd::mat_4x4<int>;
	auto const A = zero(geosimd::empty<mat44>{});
	EXPECT_EQ(A.col(0), zero(geosimd::empty<mat44::column_type>{}));
	EXPECT_EQ(A.col(1), zero(geosimd::empty<mat44::column_type>{}));
	EXPECT_EQ(A.col(2), zero(geosimd::empty<mat44::column_type>{}));
	EXPECT_EQ(A.col(3), zero(geosimd::empty<mat44::column_type>{}));

	mat44 const B = gen_matrix();

	auto const C = A + B;
	EXPECT_EQ(C, B);

	auto const D = A*B;
	EXPECT_EQ(D, A);

	auto const E = B*A;
	EXPECT_EQ(E, A);

	auto const f = geosimd::vec_t<int, 4>{1, 2, 3, 4};
	auto const g = A*f;
	EXPECT_EQ(g, zero(geosimd::empty<geosimd::vec_t<int, 4>>{}));
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

	mat44 const B = gen_matrix();

	auto const C = A*B;
	EXPECT_EQ(C, B);

	auto const D = B*A;
	EXPECT_EQ(D, B);

	auto const e = geosimd::vec_t<int, 4>{1, 2, 3, 4};
	auto const f = A*e;
	EXPECT_EQ(f, e);
}

TESTCASE(geosimd_mat44_data)
{
	auto const A = gen_matrix();
	auto const elems = A.column_major_elements();
	REQUIRE_EQ(std::size(elems), 16);
	EXPECT_EQ(static_cast<void const*>(&A), static_cast<void const*>(std::data(elems)));
	for(int k = 0; k != 4; ++k)
	{
		for(int l = 0; l != 4; ++l)
		{
			EXPECT_EQ(elems[4*k + l], k + 4*l);
		}
	}
}

TESTCASE(geosimd_mat44_columns)
{
	auto const A = gen_matrix();
	auto const& cols = A.columns();
	EXPECT_EQ(std::size(cols), 4);
	for(int k = 0; k != static_cast<int>(std::size(cols)); ++k)
	{
		auto const expected = 4*geosimd::vec_t<int, 4>{0, 1, 2, 3} + geosimd::vec_t<int, 4>{k, k, k, k};
		EXPECT_EQ(cols[k], expected);
	}
}


TESTCASE(geosimd_mat44_col)
{
	auto const A = gen_matrix();
	for(int k = 0; k != 4; ++k)
	{
		auto const expected = 4*geosimd::vec_t<int, 4>{0, 1, 2, 3} + geosimd::vec_t<int, 4>{k, k, k, k};
		EXPECT_EQ(A.col(k), expected);
	}
}

TESTCASE(geosimd_mat44_assign_col)
{
	using mat44 = geosimd::mat_4x4<int>;
	auto A = zero(geosimd::empty<mat44>{});
	for(int k = 0; k != 4; ++k)
	{
		A.assign(k, geosimd::vec_t<int, 4>{k, k, k, k});
		for(int l = 0; l != (k + 1); ++l)
		{
			EXPECT_EQ(A.col(l), (geosimd::vec_t<int, 4>{l, l, l, l}));
		}
	}
}

TESTCASE(geosimd_mat44_add)
{
	using mat44 = geosimd::mat_4x4<int>;
	constexpr mat44 A{
		geosimd::vec_t<int, 4>{-3, 8, -1, 3},
		geosimd::vec_t<int, 4>{-7, 4, -2, -5},
		geosimd::vec_t<int, 4>{6, 7, 0, 5},
		geosimd::vec_t<int, 4>{-6, -8, 1, 2}
	};

	constexpr mat44 B{
		geosimd::vec_t<int, 4>{4, 1, -7, -2},
		geosimd::vec_t<int, 4>{-6, 7, 0, -5},
		geosimd::vec_t<int, 4>{5, 8, -1, -4},
		geosimd::vec_t<int, 4>{3, 6, 2, -8}
	};

	auto const C = A + B;
	auto const D = B + A;
	EXPECT_EQ(C, D);
	EXPECT_EQ(C, (mat44{
		geosimd::vec_t<int, 4>{1, 9, -8, 1},
		geosimd::vec_t<int, 4>{-13, 11, -2, -10},
		geosimd::vec_t<int, 4>{11, 15, -1, 1},
		geosimd::vec_t<int, 4>{-3, -2, 3, -6}
	}));
}

TESTCASE(geosimd_mat44_sub)
{
	using mat44 = geosimd::mat_4x4<int>;
	constexpr mat44 A{
		geosimd::vec_t<int, 4>{-3, 8, -1, 3},
		geosimd::vec_t<int, 4>{-7, 4, -2, -5},
		geosimd::vec_t<int, 4>{6, 7, 0, 5},
		geosimd::vec_t<int, 4>{-6, -8, 1, 2}
	};

	constexpr mat44 B{
		geosimd::vec_t<int, 4>{4, 1, -7, -2},
		geosimd::vec_t<int, 4>{-6, 7, 0, -5},
		geosimd::vec_t<int, 4>{5, 8, -1, -4},
		geosimd::vec_t<int, 4>{3, 6, 2, -8}
	};

	auto const C = A - B;
	auto const D = B - A;
	EXPECT_EQ(C, -D);
	EXPECT_EQ(C, A + (-B));
	EXPECT_EQ(A + B - B, A);
	EXPECT_EQ(A - A, zero(geosimd::empty<mat44>{}));

	EXPECT_EQ(C, (mat44{
		geosimd::vec_t<int, 4>{-7, 7, 6, 5},
		geosimd::vec_t<int, 4>{-1, -3, -2, 0},
		geosimd::vec_t<int, 4>{1, -1, 1, 9},
		geosimd::vec_t<int, 4>{-9, -14, -1, 10}
	}));
}