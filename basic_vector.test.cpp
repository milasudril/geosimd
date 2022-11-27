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

#ifdef FAIL_geosimd_basic_vector_1d_lerp
TESTCASE(geosimd_basic_vector_1d_lerp)
{
	vector_1d const x1{5};
	vector_1d const x2{9};
	(void)lerp(x1, x2, 1);
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

TESTCASE(geosimd_basic_vector_1d_to_string)
{
	vector_1d const a{-2};
	auto str = to_string(a);
	EXPECT_EQ(str, "-2");
}

namespace
{
	struct my_1d_vector_space_float
	{
		using scalar_type = float;
		using vector_type = float;
	};

	using vector_1d_float = geosimd::basic_vector<my_1d_vector_space_float>;
}

TESTCASE(geosimd_basic_vector_1d_float_lerp)
{
	vector_1d_float const x1{5.0f};
	vector_1d_float const x2{9.0f};
	auto val = lerp(x1, x2, 0.75f);
	static_assert(std::is_same_v<decltype(val), vector_1d_float>);
	EXPECT_EQ(val, vector_1d_float{8.0f});
}


namespace
{
	struct my_4d_vector_space_float
	{
		using scalar_type = float;
		using vector_type = geosimd::vec_t<float, 4>;
		using point_type = geosimd::vec_t<float, 4>;
	};

	using vector_4d_float = geosimd::basic_vector<my_4d_vector_space_float>;
}

TESTCASE(geosimd_basic_vector_4d_construct_from_scalars)
{
	static_assert(std::is_same_v<vector_4d_float::vector_type, geosimd::basic_vector<my_4d_vector_space_float>>);
	static_assert(std::is_same_v<vector_4d_float::scalar_type, float>);
	static_assert(std::is_same_v<vector_4d_float::value_type, float>);
	static_assert(std::is_same_v<vector_4d_float::storage_type, geosimd::vec_t<float, 4>>);

	vector_4d_float x{1.0f, 2.0f, 4.0f, 8.0f};
	EXPECT_EQ(x.get(), (geosimd::vec_t{1.0f, 2.0f, 4.0f, 8.0f}));
}

TESTCASE(geosimd_basic_vector_4d_construct_from_value)
{
	vector_4d_float x{geosimd::vec_t{1.0f, 2.0f, 4.0f, 8.0f}};
	EXPECT_EQ(x.get(), (geosimd::vec_t{1.0f, 2.0f, 4.0f, 8.0f}));
}

TESTCASE(geosimd_basic_vector_4d_subscript)
{
	vector_4d_float x{1.0f, 2.0f, 4.0f, 8.0f};
	EXPECT_EQ(x[0], 1.0f);
	EXPECT_EQ(x[1], 2.0f);
	EXPECT_EQ(x[2], 4.0f);
	EXPECT_EQ(x[3], 8.0f);
}

TESTCASE(geosimd_basic_vector_4d_size)
{
	EXPECT_EQ(vector_4d_float::size(), 4);
}


namespace
{
	struct my_3d_vector_space_float_homo_coords
	{
		using scalar_type = float;
		using vector_type = geosimd::vec_t<float, 4>;
		using enable_homogenous_coordinates_t = void;
		using enable_rotations_t = void;
	};

	static_assert(geosimd::has_homogenous_coordinates<my_3d_vector_space_float_homo_coords>);
	using vector_3d_float = geosimd::basic_vector<my_3d_vector_space_float_homo_coords>;
}

TESTCASE(geosimd_basic_vector_3d_construct_from_scalars)
{
	static_assert(std::is_same_v<vector_3d_float::scalar_type, float>);
	static_assert(std::is_same_v<vector_3d_float::value_type, float>);
	static_assert(std::is_same_v<vector_3d_float::storage_type, geosimd::vec_t<float, 4>>);

	vector_3d_float const x{1.0f, 2.0f, 4.0f};
	EXPECT_EQ(x.get(), (geosimd::vec_t{1.0f, 2.0f, 4.0f, 0.0f}));
}

TESTCASE(geosimd_basic_vector_3d_size)
{
	EXPECT_EQ(vector_3d_float::size(), 3);
}

TESTCASE(geosimd_basic_vector_3d_to_string)
{
	vector_3d_float  const x{1.0f, 2.0f, 4.0f};
	auto const str = to_string(x);
	EXPECT_EQ(str, "(1.000000, 2.000000, 4.000000)");
}

TESTCASE(geosimd_basic_vector_3d_apply_rotation)
{
	vector_3d_float x{1.0f, 2.0f, 4.0f};
	geosimd::rotation<vector_3d_float::vector_space> const
		R{geosimd::rotation_angle{geosimd::turns{0.25}}, geosimd::dimension_tag<2>{}};
	x.apply(R);
	EXPECT_EQ(x, (vector_3d_float{-2.0f, 1.0f, 4.0f}));
}

TESTCASE(geosimd_basic_vector_3d_inner_product)
{
	vector_3d_float const x{1.0f, 2.0f, 4.0f};
	vector_3d_float const y{3.0f, 5.0f, 7.0f};
	auto res = inner_product(x, y);
	static_assert(std::is_same_v<decltype(res), float>);
	EXPECT_EQ(res, 41.0f);

	auto res2 = inner_product(x);
	static_assert(std::is_same_v<decltype(res2), float>);
	EXPECT_EQ(res2, 21.0f);
}

namespace
{
	struct my_3d_vector_space_disabled_rotations
	{
		using scalar_type = float;
		using vector_type = geosimd::vec_t<float, 4>;
		using enable_homogenous_coordinates_t = void;
	};
}

#ifdef FAIL_my_3d_vector_space_disabled_rotations
TESTCASE(my_3d_vector_space_disabled_rotations)
{
	geosimd::rotation<my_3d_vector_space_disabled_rotations> const
		R{geosimd::rotation_angle{geosimd::turns{0.25}}, geosimd::dimension_tag<2>{}};
}
#endif