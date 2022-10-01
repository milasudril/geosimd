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

	template<class T>
	concept arithmetic = std::is_arithmetic_v<T>;

	template<arithmetic T, size_t N>
	using native_vector [[gnu::vector_size(sizeof(T)*N)]] = T;

	template<class T, size_t N>
	struct vector_storage
	{
		using type = std::conditional_t<can_vectorize<T>(N), native_vector<T, N>, emulated_vector<T, N>>;
	};

	template<class T, size_t N>
	using vec_t = vector_storage<T, N>::type;

	template<class T, size_t N>
	class emulated_vector<std::complex<T>, N> : public std::complex<vec_t<T, N>> {};

	template<arithmetic T>
	[[gnu::always_inline]] constexpr auto conj(T val)
	{
		return val;
	};

	template<class T>
	[[gnu::always_inline]] constexpr auto conj(std::complex<T> val)
	{
		return ::std::conj(val);
	}

	template<class T, size_t N>
	constexpr auto inner_product(vec_t<T, N> a, vec_t<T, N> b)
	{
		auto const prod = a*conj(b);
		T ret{};
		for(size_t k = 0; k != N; ++k)
		{ ret += prod; }

		return ret;
	}
}

#endif