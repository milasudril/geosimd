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

		GEOSIMD_INLINE_OPT constexpr explicit emulated_vector(base val):base{val}{}

		template<class U>
		friend constexpr bool operator==(emulated_vector<std::complex<T>, N> const&, U const&) = delete;

		template<class U>
		friend constexpr bool operator==(U const&, emulated_vector<std::complex<T>, N>&) = delete;

		template<class U>
		friend constexpr bool operator!=(emulated_vector<std::complex<T>, N> const&, U const&) = delete;

		template<class U>
		friend constexpr bool operator!=(U const&, emulated_vector<std::complex<T>, N>&) = delete;
	};

	template<class T, size_t N, class ... Indices>
	requires (!vector_limits::can_vectorize<T>(N))
	GEOSIMD_INLINE_OPT constexpr auto shuffle(vector_storage<T, N> a,
		vector_storage<T, N> b,
		Indices ... vals) = delete;

	template<class T, size_t N, class ... Indices>
	requires (std::conjunction_v<std::is_same<int, Indices>...>
		&& sizeof...(Indices) == N
		&& vector_limits::can_vectorize<T>(N))
	GEOSIMD_INLINE_OPT constexpr auto shuffle(vector_storage<T, N> a,
		vector_storage<T, N> b,
		Indices ... vals)
	{
		return __builtin_shuffle(a, b, vector_storage<int, N>{vals...});
	}
}

#endif