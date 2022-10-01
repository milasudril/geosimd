//@	{"target":{"name":"point.test"}}

#include "./point.hpp"

#include "testfwk/testfwk.hpp"

#include <array>
#include <chrono>

namespace testcases
{
	struct writable_address_space
	{
		using vector_type = intptr_t;
		using scalar_type = intptr_t;
		using point_type = std::byte*;
	};

	static_assert(geosimd::vector_space<writable_address_space>);
	static_assert(geosimd::affine_space<writable_address_space>);
	static_assert(geosimd::metric_space<writable_address_space>);
	static_assert(geosimd::normed_space<writable_address_space>);

	constexpr std::array<std::byte, 4> testarray{};
	static_assert(geosimd::distance(std::data(testarray), std::data(testarray) + std::size(testarray))
		== std::ssize(testarray));

	struct number_line
	{
		using vector_type = intptr_t;
		using scalar_type = intptr_t;
		using point_type = intptr_t;
	};

	static_assert(geosimd::vector_space<number_line>);
	static_assert(geosimd::affine_space<number_line>);
	static_assert(geosimd::metric_space<number_line>);
	static_assert(geosimd::normed_space<number_line>);

	struct complex_plane
	{
		using vector_type = std::complex<double>;
		using scalar_type = double;
		using point_type = std::complex<double>;
	};

	static_assert(geosimd::vector_space<complex_plane>);
	static_assert(geosimd::affine_space<complex_plane>);
	static_assert(geosimd::metric_space<complex_plane>);
	static_assert(geosimd::normed_space<complex_plane>);

	struct timeline
	{
		using vector_type = std::chrono::steady_clock::duration;
		using scalar_type = std::chrono::steady_clock::duration::rep;
		using point_type = std::chrono::steady_clock::time_point;
	};
	static_assert(geosimd::supports_abs<timeline::vector_type>);

	static_assert(geosimd::vector_space<timeline>);
	static_assert(geosimd::affine_space<timeline>);
	static_assert(geosimd::metric_space<timeline>);
	static_assert(geosimd::normed_space<timeline>);
}


