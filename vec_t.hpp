#ifndef GEOSIMD_VECT_HPP
#define GEOSIMD_VECT_HPP

#include "./vector_storage.hpp"
#include "./inline.hpp"

namespace geosimd
{
	template<class T, size_t N>
	class vec_t
	{
	public:
		using element_type = vector_storage<T, N>;

		template<class ... U>
		GEOSIMD_INLINE constexpr explicit vec_t(T first, U... args):m_value{first, args...}{}

		GEOSIMD_INLINE constexpr vec_t(element_type val):m_value{val}{}

		GEOSIMD_INLINE constexpr vec_t& operator*=(vec_t other)
		{
			m_value*=other.m_value;
			return *this;
		}

		GEOSIMD_INLINE constexpr vec_t& operator/=(vec_t other)
		{
			m_value/=other.m_value;
			return *this;
		}

		GEOSIMD_INLINE constexpr vec_t& operator+=(vec_t other)
		{
			m_value+=other.m_value;
			return *this;
		}

		GEOSIMD_INLINE constexpr vec_t& operator-=(vec_t other)
		{
			m_value-=other.m_value;
			return *this;
		}

		GEOSIMD_INLINE constexpr T& operator[](size_t n)
		{
			return m_value[n];
		}

		GEOSIMD_INLINE constexpr T operator[](size_t n) const
		{
			return m_value[n];
		}

		auto get() const
		{ return m_value; }

	private:
		element_type m_value;
	};

	template<class T, size_t N>
	GEOSIMD_INLINE constexpr auto operator*(vec_t<T, N> a, vec_t<T, N> b)
	{
		return a *= b;
	}

	template<class T, size_t N>
	GEOSIMD_INLINE constexpr auto operator/(vec_t<T, N> a, vec_t<T, N> b)
	{
		return a /= b;
	}

	template<class T, size_t N>
	GEOSIMD_INLINE constexpr auto operator+(vec_t<T, N> a, vec_t<T, N> b)
	{
		return a += b;
	}

	template<class T, size_t N>
	GEOSIMD_INLINE constexpr auto operator-(vec_t<T, N> a, vec_t<T, N> b)
	{
		return a -= b;
	}

	template<class T, size_t N>
	GEOSIMD_INLINE constexpr auto conj(vec_t<T, N> val)
	{ return val; }

	template<class T, size_t N>
	class vec_t<std::complex<T>, N> : public vector_storage<std::complex<T>, N>
	{
	public:
		using element_type = vector_storage<std::complex<T>, N>;

		GEOSIMD_INLINE constexpr explicit vec_t(vec_t<T, N> real, vec_t<T, N> imag):
			m_value{real.get(), imag.get()}{}

		GEOSIMD_INLINE constexpr vec_t(element_type::base val):m_value{val}{}

		auto get() const
		{ return m_value; }

	private:
		element_type m_value;
	};

	template<class T, size_t N>
	GEOSIMD_INLINE constexpr auto conj(vec_t<std::complex<T>, N> val)
	{ return vec_t<std::complex<T>, N>{conj(val.get())}; }

	template<class T, size_t N>
	constexpr auto inner_product(vec_t<T, N> a, vec_t<T, N> b)
	{
		auto const prod = a * conj(b);
		T ret{};
		for(size_t k = 0; k != N; ++k)
		{ ret += prod[k]; }

		return ret;
	}

	using vec4f32_t = vec_t<float, 4>;
	using vec4i32_t = vec_t<int32_t, 4>;
	using vec2i64_t = vec_t<int64_t, 2>;
	using vec2f64_t = vec_t<double, 2>;
}
#endif