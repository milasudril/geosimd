//@	{"target":{"name":"vec_t.test"}}

#include "./vec_t.hpp"

#include "testfwk/testfwk.hpp"

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