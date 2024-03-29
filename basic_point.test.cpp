//@	{"target":{"name":"basic_point.test"}}

#include "./basic_point.hpp"

#include "testfwk/testfwk.hpp"

namespace
{
	struct my_1d_vector_space
	{
		using scalar_type = int;
		using vector_type = int;
		using point_type = int;
	};

	using point_1d = geosimd::basic_point<my_1d_vector_space>;
	using vector_1d = geosimd::basic_vector<my_1d_vector_space>;
}

TESTCASE(geosimd_basic_point_1d_default_construct)
{
	point_1d x;
	EXPECT_EQ(x.get(), 0);
}

TESTCASE(geosimd_basic_point_1d_origin)
{
	point_1d x;
	EXPECT_EQ(x, geosimd::origin<my_1d_vector_space>());
}

TESTCASE(geosimd_basic_point_1d_construct)
{
	static_assert(std::is_same_v<point_1d::vector_type, geosimd::basic_vector<my_1d_vector_space>>);
	static_assert(std::is_same_v<point_1d::scalar_type, int>);
	static_assert(std::is_same_v<point_1d::value_type, int>);
	static_assert(std::is_same_v<point_1d::storage_type, int>);

	point_1d x{2};
	EXPECT_EQ(x.get(), 2);
}

TESTCASE(geosimd_basic_point_1d_size)
{
	EXPECT_EQ(point_1d::size(), 1);
}

#ifdef FAIL_geosimd_basic_point_1d_index
TESTCASE(FAIL_geosimd_basic_point_1d_index)
{
	point_1d x;
	(void)x[0];
}
#endif

TESTCASE(geosimd_basic_point_1d_add_vector)
{
	point_1d x{2};
	x += vector_1d{3};
	EXPECT_EQ(x, point_1d{5});
}

TESTCASE(geosimd_basic_point_1d_subtract_vector)
{
	point_1d x{2};
	x -= vector_1d{3};
	EXPECT_EQ(x, point_1d{-1});
}

TESTCASE(geosimd_basic_point_1d_add_vector_no_assign)
{
	point_1d const x1{2};
	auto x2 = x1 + vector_1d{3};
	static_assert(std::is_same_v<decltype(x2), point_1d>);
	EXPECT_EQ(x1, point_1d{2});
	EXPECT_EQ(x2, point_1d{5});
}

TESTCASE(geosimd_basic_point_1d_subtract_vector_no_assign)
{
	point_1d const x1{2};
	auto x2 = x1 - vector_1d{3};
	static_assert(std::is_same_v<decltype(x2), point_1d>);
	EXPECT_EQ(x1, point_1d{2});
	EXPECT_EQ(x2, point_1d{-1});
}

TESTCASE(geosimd_basic_point_1d_difference)
{
	point_1d const x1{2};
	point_1d const x2{5};
	auto diff = x1 - x2;
	static_assert(std::is_same_v<decltype(diff), vector_1d>);
	EXPECT_EQ(diff, vector_1d{-3});
}

TESTCASE(geosimd_basic_point_1d_distance)
{
	point_1d const x1{2};
	point_1d const x2{5};
	auto d1 = distance(x1, x2);
	auto d2 = distance(x2, x1);
	static_assert(std::is_same_v<decltype(d1), typename my_1d_vector_space::scalar_type>);
	EXPECT_EQ(d1, d2);
	EXPECT_EQ(d1, 3);
}

TESTCASE(geosimd_basic_point_1d_radius_vector)
{
	point_1d const x{5};
	auto r = radius_vector(x);
	static_assert(std::is_same_v<decltype(r), vector_1d>);
	EXPECT_EQ(r, vector_1d{5});
}

TESTCASE(geosimd_basic_point_1d_midpoint)
{
	point_1d const x1{5};
	point_1d const x2{9};
	auto mid = midpoint(x1, x2);
	static_assert(std::is_same_v<decltype(mid), point_1d>);
	EXPECT_EQ(mid, point_1d{7});
}

#ifdef FAIL_geosimd_basic_point_1d_lerp
TESTCASE(geosimd_basic_point_1d_lerp)
{
	point_1d const x1{5};
	point_1d const x2{9};
	(void)lerp(x1, x2, 1);
}
#endif

TESTCASE(geosimd_basic_point_1d_to_string)
{
	point_1d const x1{5};
	auto const str = to_string(x1);
	EXPECT_EQ(str, "5");
}

TESTCASE(geosimd_basic_point_1d_point_pair_distance)
{
	geosimd::point_pair const p{point_1d{5}, point_1d{9}};
	auto d = p.distance();
	static_assert(std::is_same_v<decltype(d), typename my_1d_vector_space::scalar_type>);
	EXPECT_EQ(d, 4);
}

namespace
{
	struct my_1d_vector_space_float
	{
		using scalar_type = float;
		using vector_type = float;
		using point_type = float;
	};

	using point_1d_float = geosimd::basic_point<my_1d_vector_space_float>;
	using vector_1d_float = geosimd::basic_vector<my_1d_vector_space_float>;
}

TESTCASE(geosimd_basic_point_1d_float_lerp)
{
	point_1d_float const x1{5.0f};
	point_1d_float const x2{9.0f};
	auto val = lerp(x1, x2, 0.75f);
	static_assert(std::is_same_v<decltype(val), point_1d_float>);
	EXPECT_EQ(val, point_1d_float{8.0f});
}

namespace
{
	struct my_4d_vector_space_float
	{
		using scalar_type = float;
		using vector_type = geosimd::vec_t<float, 4>;
		using point_type = geosimd::vec_t<float, 4>;
	};

	using point_4d_float = geosimd::basic_point<my_4d_vector_space_float>;
	using vector_4d_float = geosimd::basic_vector<my_4d_vector_space_float>;
}

TESTCASE(geosimd_basic_point_4d_construct_from_scalars)
{
	static_assert(std::is_same_v<point_4d_float::vector_type, geosimd::basic_vector<my_4d_vector_space_float>>);
	static_assert(std::is_same_v<point_4d_float::scalar_type, float>);
	static_assert(std::is_same_v<point_4d_float::value_type, float>);
	static_assert(std::is_same_v<point_4d_float::storage_type, geosimd::vec_t<float, 4>>);

	point_4d_float x{1.0f, 2.0f, 4.0f, 8.0f};
	EXPECT_EQ(x.get(), (geosimd::vec_t{1.0f, 2.0f, 4.0f, 8.0f}));
}

TESTCASE(geosimd_basic_point_4d_construct_from_value)
{
	point_4d_float x{geosimd::vec_t{1.0f, 2.0f, 4.0f, 8.0f}};
	EXPECT_EQ(x.get(), (geosimd::vec_t{1.0f, 2.0f, 4.0f, 8.0f}));
}

TESTCASE(geosimd_basic_point_4d_subscript)
{
	point_4d_float x{1.0f, 2.0f, 4.0f, 8.0f};
	EXPECT_EQ(x[0], 1.0f);
	EXPECT_EQ(x[1], 2.0f);
	EXPECT_EQ(x[2], 4.0f);
	EXPECT_EQ(x[3], 8.0f);
}

TESTCASE(geosimd_basic_point_4d_size)
{
	EXPECT_EQ(point_4d_float::size(), 4);
}

TESTCASE(geosimd_basic_point_4d_origin)
{
	point_4d_float x;
	EXPECT_EQ(x, geosimd::origin<my_4d_vector_space_float>());
}

namespace
{
	struct my_3d_vector_space_float_homo_coords
	{
		using scalar_type = float;
		using vector_type = geosimd::vec_t<float, 4>;
		using point_type = geosimd::vec_t<float, 4>;
		using enable_homogenous_coordinates_t = void;
		using enable_rotations_t = void;

		static constexpr scalar_type distance(point_type a, point_type b)
		{
			return std::sqrt(inner_product(a - b));
		}
	};

	static_assert(geosimd::has_homogenous_coordinates<my_3d_vector_space_float_homo_coords>);
	using point_3d_float = geosimd::basic_point<my_3d_vector_space_float_homo_coords>;
	using vector_3d_float = geosimd::basic_vector<my_3d_vector_space_float_homo_coords>;
}

#ifdef FAIL_geosimd_basic_point_3d_construct_from_value
TESTCASE(geosimd_basic_point_3d_construct_from_value)
{
	point_3d_float x{geosimd::vec_t{1.0f, 2.0f, 4.0f, 8.0}};
}
#endif

TESTCASE(geosimd_basic_point_3d_construct_from_scalars)
{
	static_assert(std::is_same_v<point_3d_float::vector_type, geosimd::basic_vector<my_3d_vector_space_float_homo_coords>>);
	static_assert(std::is_same_v<point_3d_float::scalar_type, float>);
	static_assert(std::is_same_v<point_3d_float::value_type, float>);
	static_assert(std::is_same_v<point_3d_float::storage_type, geosimd::vec_t<float, 4>>);

	point_3d_float x{1.0f, 2.0f, 4.0f};
	EXPECT_EQ(x.get(), (geosimd::vec_t{1.0f, 2.0f, 4.0f, 1.0f}));
}

TESTCASE(geosimd_basic_point_3d_size)
{
	EXPECT_EQ(point_3d_float::size(), 3);
}

TESTCASE(geosimd_basic_point_3d_origin)
{
	point_3d_float x;
	EXPECT_EQ(x, geosimd::origin<my_3d_vector_space_float_homo_coords>());
}

TESTCASE(geosimd_basic_point_3d_to_string)
{
	point_3d_float  const x{1.0f, 2.0f, 4.0f};
	auto const str = to_string(x);
	EXPECT_EQ(str, "(1.000000, 2.000000, 4.000000)");
}

TESTCASE(geosimd_basic_point_3d_apply_transation)
{
	point_3d_float x{1.0f, 2.0f, 4.0f};
	x.apply(geosimd::translation{vector_3d_float{2.0f, 4.0f, 8.0f}});
	EXPECT_EQ(x, (point_3d_float{3.0f, 6.0f, 12.0f}));
}

TESTCASE(geosimd_basic_point_3d_apply_rotation)
{
	point_3d_float x{1.0f, 2.0f, 4.0f};
	geosimd::rotation<point_3d_float::vector_space> const
		R{geosimd::rotation_angle{geosimd::turns{0.25}}, geosimd::dimension_tag<2>{}};
	x.apply(R, point_3d_float{0.5f, 1.0f, 2.0f});
	EXPECT_LT(geosimd::distance(x, point_3d_float{-0.5f, 1.5f, 4.0f}), 1e-7f);
}

TESTCASE(geosimd_basic_point_3d_apply_locrot)
{
	point_3d_float x{1.0f, 2.0f, 4.0f};
	geosimd::rotation<point_3d_float::vector_space> const
		R{geosimd::rotation_angle{geosimd::turns{0.25}}, geosimd::dimension_tag<2>{}};
	geosimd::translation const T{vector_3d_float{2.0f, 4.0f, 8.0f}};
	x.apply(geosimd::locrot{T, R}, point_3d_float{0.5f, 1.0f, 2.0f});
	EXPECT_EQ(x, (point_3d_float{1.5f, 5.5f, 12.0f}));
}

TESTCASE(geosimd_basic_point_3d_structured_binding)
{
	point_3d_float  const p{1.0f, 2.0f, 4.0f};
	auto [x, y, z] = p;
	auto x2 = get<0>(p);
	EXPECT_EQ(x2, x);
	EXPECT_EQ(x, 1.0f);
	EXPECT_EQ(y, 2.0f);
	EXPECT_EQ(z, 4.0f);
}

TESTCASE(geosimd_basic_point_3d_lerp)
{
	point_3d_float const a{1.0f, 2.0f, 3.0f};
	point_3d_float const b{2.0f, 3.0f, 4.0f};

	{
		auto const p = lerp(a, b, 0.5f);
		EXPECT_EQ(p[0], 1.5f);
		EXPECT_EQ(p[1], 2.5f);
		EXPECT_EQ(p[2], 3.5f);
	}

	{
		auto const p = lerp(a, b, 0.0f);
		EXPECT_EQ(p[0], 1.0f);
		EXPECT_EQ(p[1], 2.0f);
		EXPECT_EQ(p[2], 3.0f);
	}

	{
		auto const p = lerp(a, b, 1.0f);
		EXPECT_EQ(p[0], 2.0f);
		EXPECT_EQ(p[1], 3.0f);
		EXPECT_EQ(p[2], 4.0f);
	}
}

namespace
{
	struct my_3d_vector_space_disabled_rotations
	{
		using scalar_type = float;
		using vector_type = geosimd::vec_t<float, 4>;
		using point_type = geosimd::vec_t<float, 4>;
		using enable_homogenous_coordinates_t = void;

		static constexpr scalar_type distance(point_type a, point_type b)
		{
			return std::sqrt(inner_product(a - b));
		}
	};

	static_assert(geosimd::has_homogenous_coordinates<my_3d_vector_space_disabled_rotations>);
	using point_3d_float_norot = geosimd::basic_point<my_3d_vector_space_disabled_rotations>;
	using vector_3d_float_norot = geosimd::basic_vector<my_3d_vector_space_disabled_rotations>;
}

#ifdef FAIL_my_3d_vector_space_disabled_rotations
TESTCASE(my_3d_vector_space_disabled_rotations)
{
	geosimd::rotation<my_3d_vector_space_disabled_rotations> const
		R{geosimd::rotation_angle{geosimd::turns{0.25}}, geosimd::dimension_tag<2>{}};
}
#endif