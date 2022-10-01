#ifndef GEOSIMD_VECTORSTORAGE_HPP
#define GEOSIMD_VECTORSTORAGE_HPP

#include "./vector_limits.hpp"

#include <array>

namespace geosimd
{
	template<class T, size_t N>
	class emulated_vector
	{
	public:
	private:
		std::array<T, N> m_data;
	};

	template<class T, size_t N>
	using native_vector [[gnu::vector_size(sizeof(T)*N)]] = T;

	template<class T, size_t N>
	struct vector_storage
	{
		using type = std::conditional_t<can_vectorize<T>(N), native_vector<T, N>, emulated_vector<T, N>>;
	};

	template<class T, size_t N>
	using vec_t = vector_storage<T, N>::type;
};

#endif