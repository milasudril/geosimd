#ifndef GEOSIMD_VECTORSTORAGE_HPP
#define GEOSIMD_VECTORSTORAGE_HPP

#include "./vector_limits.hpp"

#include <complex>

#include <array>

namespace geosimd
{
	template<class T, size_t N>
	class emulated_vector
	{
	public:
		// TODO: Implement when needed
	private:
		std::array<T, N> m_data;
	};

	template<std::arithmetic T, size_t N>
	using native_vector [[gnu::vector_size(sizeof(T)*N)]] = T;

	template<class T, size_t N>
	struct vector_storage
	{
		using type = std::conditional_t<can_vectorize<T>(N), native_vector<T, N>, emulated_vector<T, N>>;
	};

	template<class T, size_t N>
	using vec_t = vector_storage<T, N>::type;

	template<std::arithmetic T>
	[[gnu::always_inline]] constexpr auto conj(T val)
	{
		return val;
	};

	template<std::arithmetic T>
	[[gnu::always_inline]] constexpr auto conj(std::complex<T> val)
	{
		return ::std::conj(val);
	}

	template<class T, size_t N>
	constexpr auto inner_product(vec_t<T, N> a, vec_t<T, N> a)
	{
		T ret{};
		for(size_t k = 0; k != N; ++k)
		{ ret += a[k]*conj(b[k]); }

		return ret;
	}
};

#endif