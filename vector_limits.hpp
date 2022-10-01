#ifndef GEOSIMD_VECTORLIMITS_HPP
#define GEOSIMD_VECTORLIMITS_HPP

#include <bit>
#include <cstddef>
#include <cstdint>

namespace geosimd::vector_limits
{
	constexpr size_t min_vector_byte_size = 16;

#ifdef __SSE__
	constexpr bool has_sse1 = true;
#else
	constexpr bool has_sse1 = false;
#endif

#ifdef __SSE2__
	constexpr bool has_sse2 = true;
#else
	constexpr bool has_sse2 = false;
#endif

#ifdef __SSE3__
	constexpr bool has_sse3 = true;
#else
	constexpr bool has_sse3 = false;
#endif

#ifdef __SSE4__
	constexpr bool has_sse4 = true;
#else
	constexpr bool has_sse4 = false;
#endif

#ifdef __AVX__
	constexpr bool has_avx = true;
#else
	constexpr bool has_avx = false;
#endif

#ifdef __AVX512F__
	constexpr bool has_avx_512 = true;
#else
	constexpr bool has_avx_512 = false;
#endif

	constexpr bool has_extended_sse =
		has_sse1 || has_sse2 || has_sse3 || has_sse4 || has_avx || has_avx_512;

	constexpr bool has_sse = has_sse1 || has_extended_sse;

	constexpr size_t max_vector_byte_size =
		has_avx_512 ? 64 : (has_avx ? 32 : (has_sse? 16 : 0));

	template<class T>
	constexpr bool can_vectorize()
	{
		if(std::is_same_v<T, __int128>)
		{ return false; }

		if(!std::is_arithmetic_v<T>)
		{ return false; }

		if(has_extended_sse)
		{ return true; }

		if(!std::is_same_v<T, float>)
		{ return false; }

		if(has_sse)
		{ return true; }

		return false;
	}

	template<class T>
	constexpr bool can_vectorize(size_t N)
	{
		auto const min_elem_count = min_vector_byte_size / sizeof(T);
		auto const max_elem_count = max_vector_byte_size / sizeof(T);

		return std::has_single_bit(N)
			&& N >= min_elem_count && N <= max_elem_count
			&& can_vectorize<T>();
	}
}
#endif