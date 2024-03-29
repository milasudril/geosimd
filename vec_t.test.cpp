//@	{"target":{"name":"vec_t.test"}}

#include "./vec_t.hpp"

#include "./abstract_spaces.hpp"

#include "testfwk/testfwk.hpp"

static_assert(std::is_trivial_v<geosimd::vec4i32_t>);
static_assert(geosimd::vector<geosimd::vec4i32_t>);
static_assert(geosimd::uses_vectorops_mixin_v<geosimd::vec4i32_t>);
static_assert(!std::totally_ordered<geosimd::vec4i32_t>);

static_assert(std::is_trivially_copyable_v<geosimd::vec_t<std::complex<int32_t>, 4>>);
static_assert(geosimd::vector<geosimd::vec_t<std::complex<int32_t>, 4>>);
static_assert(geosimd::uses_vectorops_mixin_v<geosimd::vec_t<std::complex<int32_t>, 4>>);

TESTCASE(geosimd_vect_real_inner_product)
{
	geosimd::vec4i32_t const a{1, 2, 3, 4};
	geosimd::vec4i32_t const b{5, 6, 7, 8};

	EXPECT_EQ(inner_product(a, b), 70);
}

TESTCASE(geosimd_vect_real_shuffle)
{
	geosimd::vec4i32_t const a{1, 2, 3, 4};
	geosimd::vec4i32_t const b{5, 6, 7, 8};

	auto const c = shuffle(a, b, 0, 4, 1, 5);
	auto const d = shuffle(a, b, 2, 6, 3, 7);

	EXPECT_EQ(c, (geosimd::vec4i32_t{1, 5, 2, 6}));
	EXPECT_EQ(d, (geosimd::vec4i32_t{3, 7, 4, 8}));
}


TESTCASE(geosimd_vect_complex_shuffle)
{
	geosimd::vec_t<std::complex<int32_t>, 4> const a
	{
		geosimd::vec4i32_t{1, 2, 3, 4},
		geosimd::vec4i32_t{5, 6, 7, 8}
	};

	geosimd::vec_t<std::complex<int32_t>, 4> const b
	{
		geosimd::vec4i32_t{9, 10, 11, 12},
		geosimd::vec4i32_t{13, 14, 15, 16}
	};

	auto const c = shuffle(a, b, 0, 4, 1, 5);
	auto const d = shuffle(a, b, 2, 6, 3, 7);

	EXPECT_EQ(c, (geosimd::vec_t<std::complex<int32_t>, 4>
		{
			geosimd::vec4i32_t{1, 9, 2, 10},
			geosimd::vec4i32_t{5, 13, 6, 14}
		}));

	EXPECT_EQ(d, (geosimd::vec_t<std::complex<int32_t>, 4>
		{
			geosimd::vec4i32_t{3, 11, 4, 12},
			geosimd::vec4i32_t{7, 15, 8, 16}
		}));
}

TESTCASE(geosimd_vect_complex_conj)
{
	geosimd::vec_t<std::complex<int32_t>, 4> const a
	{
		geosimd::vec4i32_t{1, 2, 3, 4},
		geosimd::vec4i32_t{5, 6, 7, 8}
	};

	auto const b = conj(a);
	static_assert(std::is_same_v<decltype(b), decltype(a)>);
	for(size_t k = 0; k != 4; ++k)
	{
		EXPECT_EQ(b[k], std::conj(a[k]));
	}
}

TESTCASE(geosimd_vect_complex_inner_product)
{
	geosimd::vec_t<std::complex<int32_t>, 4> const a
	{
		geosimd::vec4i32_t{1, 2, 3, 4},
		geosimd::vec4i32_t{5, 6, 7, 8}
	};

	geosimd::vec_t<std::complex<int32_t>, 4> const b
	{
		geosimd::vec4i32_t{9, 10, 11, 12},
		geosimd::vec4i32_t{13, 14, 15, 16}
	};

	EXPECT_EQ(inner_product(a, b), (std::complex<int32_t>{492, 128}));
}

TESTCASE(geosimd_vect_real_mul_scalar)
{
	geosimd::vec4i32_t const a{1, 2, 3, 4};
	auto const c = 2*a;
	EXPECT_EQ(c, (geosimd::vec4i32_t{2, 4, 6, 8}));
}

TESTCASE(geosimd_vect_complex_mul_scalar)
{
	geosimd::vec_t<std::complex<int32_t>, 4> const a
	{
		geosimd::vec4i32_t{1, 2, 3, 4},
		geosimd::vec4i32_t{5, 6, 7, 8},
	};

	std::complex<int32_t> const b{2, 3};

	auto const c = a*b;
	geosimd::vec_t<std::complex<int32_t>, 4> const expected
	{
		geosimd::vec4i32_t{-13, -14, -15, -16},
		geosimd::vec4i32_t{13, 18, 23, 28},
	};

	EXPECT_EQ(c, expected);
}

TESTCASE(geosimd_vect_complex_mul_vector)
{
	geosimd::vec_t<std::complex<int32_t>, 4> const a
	{
		geosimd::vec4i32_t{1, 2, 3, 4},
		geosimd::vec4i32_t{5, 6, 7, 8},
	};

	geosimd::vec_t<std::complex<int32_t>, 4> const b
	{
		geosimd::vec4i32_t{9, 10, 11, 12},
		geosimd::vec4i32_t{13, 14, 15, 16},
	};

	auto const c = a*b;
	geosimd::vec_t<std::complex<int32_t>, 4> const expected
	{
		geosimd::vec4i32_t{-56, -64, -72, -80},
		geosimd::vec4i32_t{58, 88, 122, 160},
	};

	EXPECT_EQ(c, expected);
}

TESTCASE(geosimd_vect_complex_div_scalar)
{
	geosimd::vec_t<std::complex<int32_t>, 4> const a
	{
		geosimd::vec4i32_t{-11, -10, -9, -8},
		geosimd::vec4i32_t{23, 30, 37, 44},
	};

	std::complex<int32_t> const c{4, 3};

	auto const b = a/c;
	geosimd::vec_t<std::complex<int32_t>, 4> const expected
	{
		geosimd::vec4i32_t{1, 2, 3, 4},
		geosimd::vec4i32_t{5, 6, 7, 8},
	};

	EXPECT_EQ(b, expected);
}

TESTCASE(geosimd_vect_complex_div_complex)
{
	geosimd::vec_t<std::complex<int32_t>, 4> const a
	{
		geosimd::vec4i32_t{-56, -64, -72, -80},
		geosimd::vec4i32_t{58, 88, 122, 160},
	};

	geosimd::vec_t<std::complex<int32_t>, 4> const b
	{
		geosimd::vec4i32_t{9, 10, 11, 12},
		geosimd::vec4i32_t{13, 14, 15, 16},
	};

	auto const c = a/b;
	geosimd::vec_t<std::complex<int32_t>, 4> const expected
	{
		geosimd::vec4i32_t{1, 2, 3, 4},
		geosimd::vec4i32_t{5, 6, 7, 8},
	};

	EXPECT_EQ(c, expected);
}