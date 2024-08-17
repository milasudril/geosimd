//@	{"target":{"name":"hilbert_space.test"}}

#include "./hilbert_space.hpp"

#include "testfwk/testfwk.hpp"

namespace
{
	static_assert(std::totally_ordered<float>);

	static size_t inner_product_2_called = 0;
	static size_t inner_product_called = 0;

	struct my_vector_type
	{
		using scalar_type = float;
		float value;

		bool operator==(my_vector_type const&) const = default;
		bool operator!=(my_vector_type const&) const = default;
	};

	constexpr my_vector_type operator+(my_vector_type a, my_vector_type b)
	{ return my_vector_type{a.value + b.value}; }

	constexpr my_vector_type operator-(my_vector_type a, my_vector_type b)
	{ return my_vector_type{a.value - b.value}; }

	constexpr my_vector_type operator*(float a, my_vector_type b)
	{ return my_vector_type{a * b.value}; }

	constexpr my_vector_type operator*(my_vector_type a, float b)
	{ return my_vector_type{a.value * b}; }

	constexpr my_vector_type operator/(my_vector_type a, float b)
	{ return my_vector_type{a.value / b}; }

	constexpr my_vector_type operator-(my_vector_type a)
	{ return my_vector_type{-a.value}; }

	constexpr auto inner_product(my_vector_type a, my_vector_type b)
	{
		if(!std::is_constant_evaluated())
		{ ++inner_product_2_called; }
		return a.value*b.value;
	}

	constexpr auto inner_product(my_vector_type a)
	{
		if(!std::is_constant_evaluated())
		{ ++inner_product_called; }
		return a.value*a.value;
	}

	using my_hilbert_space_mixin = geosimd::hilbert_space_mixin<my_vector_type>;
}

TESTCASE(geosimd_hilbert_space_norm)
{
//	if(!std::is_constant_evaluated())
	{
		inner_product_called = 0;
		inner_product_2_called = 0;
	}

	auto val = my_hilbert_space_mixin::norm(my_vector_type{-2.0f});
	static_assert(std::is_same_v<decltype(val), float>);
	EXPECT_EQ(val, 2.0f);

//	if(!std::is_constant_evaluated())
	{
		EXPECT_EQ(inner_product_called, 1);
		EXPECT_EQ(inner_product_2_called, 0);
		inner_product_called = 0;
	}
}

TESTCASE(geosimd_hilbert_space_norm_squared)
{
//	if(!std::is_constant_evaluated())
	{
		inner_product_called = 0;
		inner_product_2_called = 0;
	}

	auto val = my_hilbert_space_mixin::norm_squared(my_vector_type{-2.0f});
	static_assert(std::is_same_v<decltype(val), float>);
	EXPECT_EQ(val, 4.0f);

//	if(!std::is_constant_evaluated())
	{
		EXPECT_EQ(inner_product_called, 1);
		EXPECT_EQ(inner_product_2_called, 0);
		inner_product_called = 0;
	}
}

namespace
{
	struct my_vector_space:geosimd::hilbert_space_mixin<my_vector_type>
	{
		using vector_type = my_vector_type;
		using scalar_type = my_vector_type::scalar_type;
	};

	static_assert(geosimd::hilbert_space<my_vector_space>);
	static_assert(geosimd::normed_space<my_vector_space>);
}