#ifndef GEOSIMD_STORAGE_HPP
#define GEOSIMD_STORAGE_HPP

#include <cstdint>
#include <type_traits>

namespace GeoSIMD
	{
#ifdef __SSE__
	static constexpr bool HAS_SSE=1;
#else
	static constexpr bool HAS_SSE=0;
#endif

#ifdef __SSE2__
	static constexpr bool HAS_SSE2=1;
#else
	static constexpr bool HAS_SSE2=0;
#endif

#ifdef __SSE3__
	static constexpr bool HAS_SSE3=1;
#else
	static constexpr bool HAS_SSE3=0;
#endif

#ifdef __SSE4__
	static constexpr bool HAS_SSE4=1;
#else
	static constexpr bool HAS_SSE4=0;
#endif

#ifdef __AVX__
	static constexpr bool HAS_AVX=1;
#else
	static constexpr bool HAS_AVX=0;
#endif

	template<class T>
	struct is_vectorizable
		{static constexpr bool value=0;};

	template<>
	struct is_vectorizable<float>
		{static constexpr bool value=HAS_SSE||HAS_SSE2||HAS_SSE3||HAS_SSE4||HAS_AVX;};

	template<>
	struct is_vectorizable<int32_t>
		{static constexpr bool value=HAS_SSE2||HAS_SSE3||HAS_SSE4||HAS_AVX;};

	template<>
	struct is_vectorizable<double>
		{static constexpr bool value=HAS_AVX;};

	template<>
	struct is_vectorizable<int64_t>
		{static constexpr bool value=HAS_AVX;};

	template<class T>
	using vec4_t __attribute__ ((vector_size (4*sizeof(T))))=
		std::enable_if_t<is_vectorizable<T>::value,T>;

	template<class T>
	constexpr std::enable_if_t<is_vectorizable<T>::value,T> dot(vec4_t<T> a,vec4_t<T> b) noexcept
		{
		a*=b;
		return a[0] + a[1] + a[2] + a[3];
		}
	}

#endif