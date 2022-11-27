//@	{"target":{"name":"basic_vector.test"}}

#include "./basic_vector.hpp"

#include "testfwk/testfwk.hpp"

namespace
{
	struct my_1d_vector_space
	{
		using scalar_type = int;
		using vector_type = int;
	};

	using vector_1d = geosimd::basic_vector<my_1d_vector_space>;
}

TESTCASE(geosimd_basic_vector_1d_default_construct)
{
	vector_1d x;
	EXPECT_EQ(x.get(), 0);
}

TESTCASE(geosimd_basic_vector_1d_construct)
{
	static_assert(std::is_same_v<vector_1d::scalar_type, int>);
	static_assert(std::is_same_v<vector_1d::value_type, int>);
	static_assert(std::is_same_v<vector_1d::storage_type, int>);
	static_assert(geosimd::uses_vectorops_mixin_v<vector_1d>);

	vector_1d x{2};
	EXPECT_EQ(x.get(), 2);
}

TESTCASE(geosimd_basic_vector_1d_size)
{
	EXPECT_EQ(vector_1d::size(), 1);
}


#ifdef FAIL_geosimd_basic_vector_1d_index
TESTCASE(FAIL_geosimd_basic_vector_1d_index)
{
	vector_1d x;
	(void)x[0];
}
#endif

TESTCASE(geosimd_basic_vector_1d_add_vector)
{
	vector_1d x{2};
	x += vector_1d{3};
	EXPECT_EQ(x, vector_1d{5});
}

TESTCASE(geosimd_basic_vector_1d_subtract_vector)
{
	vector_1d x{2};
	x -= vector_1d{3};
	EXPECT_EQ(x, vector_1d{-1});
}

TESTCASE(geosimd_basic_vector_1d_add_vector_no_assign)
{
	vector_1d const x1{2};
	auto x2 = x1 + vector_1d{3};
	static_assert(std::is_same_v<decltype(x2), vector_1d>);
	EXPECT_EQ(x1, vector_1d{2});
	EXPECT_EQ(x2, vector_1d{5});
}

TESTCASE(geosimd_basic_vector_1d_subtract_vector_no_assign)
{
	vector_1d const x1{2};
	auto x2 = x1 - vector_1d{3};
	static_assert(std::is_same_v<decltype(x2), vector_1d>);
	EXPECT_EQ(x1, vector_1d{2});
	EXPECT_EQ(x2, vector_1d{-1});
}

TESTCASE(geosimd_basic_vector_1d_norm)
{
	vector_1d const x1{-3};
	auto val = norm(x1);
	static_assert(std::is_same_v<decltype(val), int>);
	EXPECT_EQ(val, 3);
}

#ifdef FAIL_geosimd_basic_vector_1d_inner_product
TESTCASE(geosimd_basic_vector_1d_inner_product)
{
	vector_1d const a{-3};
	vector_1d const b{6};
	(void)inner_product(a, b);
}
#endif

TESTCASE(geosimd_basic_vector_1d_mean)
{
	vector_1d const a{-2};
	vector_1d const b{6};
	auto val = mean(a, b);
	static_assert(std::is_same_v<decltype(val), vector_1d>);
	EXPECT_EQ(val, vector_1d{2});
}