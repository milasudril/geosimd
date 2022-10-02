//@	{"target":{"name":"vec_t.test"}}

#include "./vec_t.hpp"

#include "testfwk/testfwk.hpp"

static_assert(std::is_trivial_v<geosimd::vec4i32_t>);

static_assert(std::is_trivially_copyable_v<geosimd::vec_t<std::complex<int>, 4>>);

TESTCASE(geosimd_vect_real_inner_product)
{
	geosimd::vec4i32_t const a{1, 2, 3, 4};
	geosimd::vec4i32_t const b{5, 6, 7, 8};

	EXPECT_EQ(inner_product(a, b), 70);
}

TESTCASE(geosimd_vect_complex_conj)
{
	geosimd::vec_t<std::complex<int>, 4> const a
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
	geosimd::vec_t<std::complex<int>, 4> const a
	{
		geosimd::vec4i32_t{1, 2, 3, 4},
		geosimd::vec4i32_t{5, 6, 7, 8}
	};

	geosimd::vec_t<std::complex<int>, 4> const b
	{
		geosimd::vec4i32_t{9, 10, 11, 12},
		geosimd::vec4i32_t{13, 14, 15, 16}
	};

	EXPECT_EQ(inner_product(a, b), (std::complex<int>{492, 128}));
}

TESTCASE(geosimd_vect_real_add)
{
	geosimd::vec4i32_t const a{1, 2, 3, 4};
	geosimd::vec4i32_t const b{5, 6, 7, 8};
	auto const c = a + b;
	EXPECT_EQ(c, (geosimd::vec4i32_t{6, 8, 10, 12}));
}

TESTCASE(geosimd_vect_real_sub)
{
	geosimd::vec4i32_t const a{1, 3, 6, 10};
	geosimd::vec4i32_t const b{5, 6, 7, 8};
	auto const c = a - b;
	EXPECT_EQ(c, (geosimd::vec4i32_t{-4, -3, -1, 2}));
}

TESTCASE(geosimd_vect_complex_sub)
{
	geosimd::vec_t<std::complex<int>, 4> const a
	{
		geosimd::vec4i32_t{1, 3, 6, 10},
		geosimd::vec4i32_t{5, 6, 7, 8}
	};

	geosimd::vec_t<std::complex<int>, 4> const b
	{
		geosimd::vec4i32_t{15, 21, 28, 36},
		geosimd::vec4i32_t{13, 15, 18, 22}
	};

	auto const c = a - b;

	geosimd::vec_t<std::complex<int>, 4> const expected
	{
		geosimd::vec4i32_t{-14, -18, -22, -26},
		geosimd::vec4i32_t{-8, -9, -11, -14}
	};

	EXPECT_EQ(c, expected);
}