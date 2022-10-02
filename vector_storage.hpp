#ifndef GEOSIMD_VECTORSTORAGE_HPP
#define GEOSIMD_VECTORSTORAGE_HPP

#include "./vector_limits.hpp"
#include "./inline.hpp"

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

	template<class T, size_t N, bool Vectorize = false>
	struct vector_storage_impl
	{
		using type = emulated_vector<T, N>;
	};

	template<class T, size_t N>
	struct vector_storage_impl<T, N, true>
	{
		using type = native_vector<T, N>;
	};

	template<class T, size_t N>
	using vector_storage = vector_storage_impl<T, N, vector_limits::can_vectorize<T>(N)>::type;

	template<class T, size_t N>
	struct emulated_vector<std::complex<T>, N> : public std::complex<vector_storage<T, N>>
	{
		using base = std::complex<vector_storage<T, N>>;
		using base::base;
		constexpr emulated_vector() = default;

		GEOSIMD_FULL_INLINE constexpr explicit emulated_vector(base val):base{val}{}
	};
}

#endif