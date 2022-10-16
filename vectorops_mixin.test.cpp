//@	{"target":{"name":"vectorops_mixin.test"}}

#include "./vectorops_mixin.hpp"

#include "./vector_storage.hpp"

#include "testfwk/testfwk.hpp"

namespace geosimd_test
{
	struct vectorops_mixin_tester:geosimd::vectorops_mixin<vectorops_mixin_tester>
	{
		using vectorops_magic = geosimd::vectorops_mixin<vectorops_mixin_tester>::magic;

		using scalar_type = int;

		using enable_hadamard_product_t = void;

		constexpr vectorops_mixin_tester() = default;

		constexpr explicit vectorops_mixin_tester(geosimd::vector_storage<int, 4> vec):
			m_value{vec}
		{}

		constexpr explicit vectorops_mixin_tester(int x, int y, int z, int w):
			m_value{x, y, z, w}
		{}

		geosimd::vector_storage<int, 4> m_value;

		static constexpr size_t size() { return 4; }

		auto operator[](size_t n) const { return m_value[n]; }

		auto& get(vectorops_magic) { return m_value; }

		auto get() const { return m_value; }

	};

	static_assert(std::is_trivial_v<vectorops_mixin_tester>);

	static_assert(geosimd::uses_vectorops_mixin_v<vectorops_mixin_tester>);

	static_assert(!std::totally_ordered<vectorops_mixin_tester>);

	std::string to_string(vectorops_mixin_tester val)
	{
		auto N = std::size(val);
		std::string ret{"("};
		for(size_t k = 0; k != N - 1; ++k)
		{
			ret.append(std::to_string(val[k])).append(", ");
		}
		ret.append(std::to_string(val[N - 1])).append(")");
		return ret;
	}
}

TESTCASE(geosimd_vectorops_mixin_mult_vec)
{
	geosimd_test::vectorops_mixin_tester a{1, 2, 3, 4};

	geosimd_test::vectorops_mixin_tester const b{2, 3, 4, 5};

	auto const c = a * b;

	a *= b;

	EXPECT_EQ(c, (geosimd_test::vectorops_mixin_tester{2, 6, 12, 20}));
	EXPECT_EQ(a, c);
}

TESTCASE(geosimd_vectorops_mixin_mult_scalar)
{
	geosimd_test::vectorops_mixin_tester a{1, 2, 3, 4};

	auto const c = a*2;

	a *= 2;

	EXPECT_EQ(c, (geosimd_test::vectorops_mixin_tester{2, 4, 6, 8}));
	EXPECT_EQ(a, c);
}

TESTCASE(geosimd_vectorops_mixin_div_vec)
{
	geosimd_test::vectorops_mixin_tester a{2, 6, 30, 210};

	geosimd_test::vectorops_mixin_tester const b{2, 3, 5, 7};

	auto const c = a / b;

	a /= b;

	EXPECT_EQ(c, (geosimd_test::vectorops_mixin_tester{1, 2, 6, 30}));
	EXPECT_EQ(a, c);
}

TESTCASE(geosimd_vectorops_mixin_div_scalar)
{
	geosimd_test::vectorops_mixin_tester a{2, 4, 6, 8};

	auto const c = a/2;

	a /= 2;

	EXPECT_EQ(c, (geosimd_test::vectorops_mixin_tester{1, 2, 3, 4}));
	EXPECT_EQ(a, c);
}

TESTCASE(geosimd_vectorops_mixin_add_vec)
{
	geosimd_test::vectorops_mixin_tester a{1, 2, 3, 4};

	geosimd_test::vectorops_mixin_tester const b{2, 3, 4, 5};

	auto const c = a + b;

	a += b;

	EXPECT_EQ(c, (geosimd_test::vectorops_mixin_tester{3, 5, 7, 9}));
	EXPECT_EQ(a, c);
}

TESTCASE(geosimd_vectorops_mixin_sub_vec)
{
	geosimd_test::vectorops_mixin_tester a{3, 5, 7, 9};

	geosimd_test::vectorops_mixin_tester const b{2, 3, 4, 5};

	auto const c = a - b;

	a -= b;

	EXPECT_EQ(c, (geosimd_test::vectorops_mixin_tester{1, 2, 3, 4}));
	EXPECT_EQ(a, c);
}

TESTCASE(geosimd_vectorops_mixin_unary_minus)
{
	geosimd_test::vectorops_mixin_tester a{3, 5, 7, 9};
	auto const b = -a;
	EXPECT_EQ(b, (geosimd_test::vectorops_mixin_tester{-3, -5, -7, -9}));
	EXPECT_NE(b, a);
}

TESTCASE(geosimd_vectorops_mixin_unary_plus)
{
	geosimd_test::vectorops_mixin_tester a{3, 5, 7, 9};
	auto const b = +a;
	EXPECT_EQ(b, a);
}