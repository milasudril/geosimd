//@	{"target":{"name":"vector_storage.test"}}

#include "./vector_storage.hpp"

#include "testfwk/testfwk.hpp"

TESTCASE(geosimd_vector_storage_real_inner_product)
{
	geosimd::vec4i32_t a{1, 2, 3, 4};
	geosimd::vec4i32_t b{5, 6, 7, 8};

	EXPECT_EQ(inner_product(a, b), 70);
}

TESTCASE(geosimd_vector_storage_complex_inner_product)
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

	geosimd::vec_t<std::complex<int>, 4> c
	{
		geosimd::vec4i32_t{9, 10, 11, 12},
		geosimd::vec4i32_t{13, 14, 15, 16}
	};

	// TODO: auto const d = inner_product(a, c);
}