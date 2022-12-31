//@	{"target":{"name":"unit_vector.test.cpp"}}

#include "./unit_vector.hpp"

#include "testfwk/testfwk.hpp"

namespace
{
	struct my_1d_vector_space
	{
		using scalar_type = float;
		using vector_type = float;
	};

	static_assert(geosimd::normed_space<my_1d_vector_space>);
	using unit_vector_1d = geosimd::unit_vector<my_1d_vector_space>;
	static_assert(!geosimd::vector<unit_vector_1d>);
}

#ifdef FAIL_geosimd_unit_vector_1d_default_construct
TESTCASE(geosimd_unit_vector_1d_default_construct)
{
	unit_vector_1d x{};
	EXPECT_EQ(x.get(), 0);
}
#endif

TESTCASE(geosimd_unit_vector_1d_construct_from_value)
{
	static_assert(std::is_same_v<unit_vector_1d::scalar_type, float>);
	static_assert(std::is_same_v<unit_vector_1d::value_type, float>);
	static_assert(std::is_same_v<unit_vector_1d::vector_type, geosimd::basic_vector<my_1d_vector_space>>);

	unit_vector_1d x{geosimd::basic_vector<my_1d_vector_space>{10.0f}};
	EXPECT_EQ(x.get(), geosimd::basic_vector<my_1d_vector_space>{1.0f});
}

TESTCASE(geosimd_unit_vector_1d_size)
{
	EXPECT_EQ(unit_vector_1d::size(), 1);
}

TESTCASE(geosimd_unit_vector_1d_scale_mul)
{
	unit_vector_1d x{geosimd::basic_vector<my_1d_vector_space>{10.0f}};

	auto y1 = 2.0f*x;
	auto y2 = x*2.0f;
	static_assert(std::is_same_v<decltype(y1), geosimd::basic_vector<my_1d_vector_space>>);
	static_assert(std::is_same_v<decltype(y2), geosimd::basic_vector<my_1d_vector_space>>);

	EXPECT_EQ(y1, geosimd::basic_vector<my_1d_vector_space>{2.0f});
	EXPECT_EQ(y2, geosimd::basic_vector<my_1d_vector_space>{2.0f});
}

TESTCASE(geosimd_unit_vector_1d_scale_div)
{
	unit_vector_1d x{geosimd::basic_vector<my_1d_vector_space>{10.0f}};

	auto y1 = x/2.0f;
	static_assert(std::is_same_v<decltype(y1), geosimd::basic_vector<my_1d_vector_space>>);

	EXPECT_EQ(y1, geosimd::basic_vector<my_1d_vector_space>{0.5f});
}


namespace
{
	struct my_4d_vector_space
	{
		using scalar_type = float;
		using vector_type = geosimd::vec_t<float, 4>;

		static constexpr float norm(vector_type a)
		{
			return std::abs(a[0]) + std::abs(a[1]) + std::abs(a[2]) + std::abs(a[3]);
		}
	};

	static_assert(geosimd::normed_space<my_4d_vector_space>);
	using unit_vector_4d = geosimd::unit_vector<my_4d_vector_space>;
	static_assert(!geosimd::vector<unit_vector_4d>);
}

TESTCASE(geosimd_unit_vector_4d_subscript)
{
	unit_vector_4d vec{unit_vector_4d::vector_type{-1.0f, 4.0f, 6.0f, 5.0f}};
	EXPECT_EQ(vec[0], -1.0f/16.0f);
	EXPECT_EQ(vec[1], 4.0f/16.0f);
	EXPECT_EQ(vec[2], 6.0f/16.0f);
	EXPECT_EQ(vec[3], 5.0f/16.0f);
	EXPECT_EQ(std::size(vec), 4);
	EXPECT_EQ(norm(vec.get()), 1.0f);
}

namespace
{
	struct my_3d_vector_space_float_homo_coords
	{
		using scalar_type = float;
		using vector_type = geosimd::vec_t<float, 4>;
		using enable_homogenous_coordinates_t = void;
		using enable_rotations_t = void;

		static constexpr float norm(vector_type a)
		{
			return std::sqrt(inner_product(a));
		}
	};

	static_assert(geosimd::normed_space<my_3d_vector_space_float_homo_coords>);
	static_assert(geosimd::inner_product_space<my_3d_vector_space_float_homo_coords>);

	using unit_vector_3d = geosimd::unit_vector<my_3d_vector_space_float_homo_coords>;
}

TESTCASE(geosimd_unit_vector_3d_rotate)
{
	unit_vector_3d vec{unit_vector_3d::vector_type{4.0f, 0.0f, 0.0f}};
	EXPECT_EQ(std::size(vec), 3);

	static_assert(std::is_same_v<unit_vector_3d::vector_type,
		geosimd::basic_vector<my_3d_vector_space_float_homo_coords>>);

	auto val = vec.get();
	static_assert(std::is_same_v<decltype(val), unit_vector_3d::vector_type>);

	EXPECT_EQ(norm(vec.get()), 1.0f);

	geosimd::rotation<my_3d_vector_space_float_homo_coords> R{geosimd::rotation_angle{geosimd::turns{0.25f}}, geosimd::dimension_tag<2>{}};

	vec.apply(R);
	EXPECT_EQ(vec[0], 0.0f);
	EXPECT_EQ(vec[1], 1.0f);
	EXPECT_EQ(vec[2], 0.0f);
}

TESTCASE(geosimd_unit_vector_inner_product)
{
	using vector_type = unit_vector_3d::vector_type;
	unit_vector_3d n{vector_type{1.0f, 0.0f, 0.0f}};
	vector_type v{3.0f, 2.0f, 1.0f};
	auto proj = inner_product(v, n);
	static_assert(std::is_same_v<decltype(proj), vector_type::scalar_type>);
	EXPECT_EQ(proj, 3.0f);

	unit_vector_3d n1{vector_type{-1.0f, 0.0f, 0.0f}};
	EXPECT_EQ(inner_product(n, n1), -1.0f);
}

TESTCASE(geosimd_unit_vector_angular_difference)
{
	using vector_type = unit_vector_3d::vector_type;

	std::array<unit_vector_3d, 8> vals{
		unit_vector_3d{vector_type{1.0f, 0.0f, 0.0f}},
		unit_vector_3d{vector_type{1.0f, 1.0f, 0.0f}},
		unit_vector_3d{vector_type{0.0f, 1.0f, 0.0f}},
		unit_vector_3d{vector_type{-1.0f, 1.0f, 0.0f}},
		unit_vector_3d{vector_type{-1.0f, 0.0f, 0.0f}},
		unit_vector_3d{vector_type{-1.0f, -1.0f, 0.0f}},
		unit_vector_3d{vector_type{0.0f, -1.0f, 0.0f}},
		unit_vector_3d{vector_type{1.0f, -1.0f, 0.0f}}
	};

	for(size_t k = 0; k != std::size(vals); ++k)
	{
		for(size_t l = 0; l != k; ++l)
		{
			// Anti-commutative test
			if(l != (k + 4)%8)
			{ EXPECT_EQ(angular_difference(vals[k], vals[l]), angular_difference(vals[k], vals[l]));}
			else
			{
				// For opposite vertices, expect half-a-turn (sign is ambiguous in this case)
				EXPECT_EQ(angular_difference(vals[k], vals[l]), geosimd::turn_angle{geosimd::turns{0.5}});
			}

			printf("%zu %zu %.3g\n", k, l, to_turns(angular_difference(vals[k], vals[l])).value);
		}

		putchar('\n');
	}
}
