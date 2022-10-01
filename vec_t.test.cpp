//@	{"target":{"name":"vec_t.test"}}

#include "./vec_t.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geosimd_vect_real_inner_product)
{
	geosimd::vec4i32_t a{1, 2, 3, 4};
	geosimd::vec4i32_t b{5, 6, 7, 8};

	EXPECT_EQ(inner_product(a, b), 70);
}

TESTCASE(geosimd_vect_complex_conj)
{
	geosimd::vec_t<std::complex<int>, 4> a
	{
		geosimd::vec4i32_t{1, 2, 3, 4},
		geosimd::vec4i32_t{5, 6, 7, 8}
	};

	auto const b = conj(a);
	for(size_t k = 0; k != 4; ++k)
	{
		EXPECT_EQ(b.real()[k], a.real()[k]);
		EXPECT_EQ(b.imag()[k], -a.imag()[k]);
	}
}