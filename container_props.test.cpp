//@	{"target":{"name":"container_props.test"}}

#include "./container_props.hpp"

#include "testfwk/testfwk.hpp"

namespace
{
	template<size_t N, class T>
	decltype(auto) get(T&& obj)
	{ return geosimd::get<N>(std::forward<T>(obj)); }

	struct subscriptable
	{
		constexpr  int operator[](size_t) const
		{ return 0; }
	};

	struct with_size
	{
		size_t size() const
		{ return 0; }
	};

	struct with_constexpr_size
	{
		constexpr size_t size() const
		{ return 0; }
	};

	struct with_static_constexpr_size
	{
		static constexpr size_t size()
		{ return 0; }
	};

	struct subscriptable_with_size
	{
		using value_type = int;

		size_t size() const
		{ return 1; }

		constexpr int operator[](size_t) const
		{ return x; }

	private:
		int x;
	};

	struct subscriptable_with_constexpr_size
	{
		using value_type = int;

		explicit subscriptable_with_constexpr_size(int x):m_x{x}{}

		constexpr size_t size() const
		{ return 1; }

		constexpr int operator[](size_t) const
		{ return m_x; }

	private:
		int m_x;
	};

	template<size_t>
	inline auto get(subscriptable_with_constexpr_size obj)
	{ return obj[0]; }

	struct subscriptable_with_static_constexpr_size
	{
		using value_type = int;

		explicit subscriptable_with_static_constexpr_size(int x):m_x{x}{}

		static constexpr size_t size()
		{ return 1; }

		constexpr int operator[](size_t) const
		{ return m_x; }

	private:
		int m_x;
	};
}

static_assert(!geosimd::subscriptable<int>);
static_assert(geosimd::subscriptable<subscriptable>);
static_assert(!geosimd::supports_size<subscriptable>);
static_assert(!geosimd::subscriptable<with_size>);
static_assert(geosimd::supports_size<with_size>);
static_assert(!geosimd::supports_constexpr_size<with_size>);
static_assert(geosimd::supports_constexpr_size<with_constexpr_size>);
static_assert(!geosimd::supports_static_constexpr_size<with_constexpr_size>);
static_assert(geosimd::supports_static_constexpr_size<with_static_constexpr_size>);

#ifdef FAIL_geosimd_container_props_sb_non_constexpr_size
TESTCASE(geosimd_container_props_sb_non_constexpr_size)
{
	subscriptable_with_size a{};
	auto [x] = a;
	(void)x;
}
#endif

#ifdef FAIL_geosimd_container_props_sb_non_constexpr_size
TESTCASE(geosimd_subscriptable_with_constexpr_size)
{
	subscriptable_with_constexpr_size a{3};
	auto [x] = a;
	(void)x;
}
#endif

TESTCASE(geosimd_subscriptable_with_static_constexpr_size)
{
	subscriptable_with_static_constexpr_size a{3};
	auto [x] = a;
	(void)x;
}