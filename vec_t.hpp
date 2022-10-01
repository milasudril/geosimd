#ifndef GEOSIMD_VECT_HPP
#define GEOSIMD_VECT_HPP

#include "./vector_storage.hpp"

namespace geosimd
{
	template<class T, size_t N>
	class vec_t
	{
	public:
		using element_type = vector_storage<T, N>;

		template<class ... U>
		[[gnu::always_inline]] constexpr vec_t(T first, U... args):m_value{first, args...}{}

		[[gnu::always_inline]] constexpr vec_t(element_type val):m_value{val}{}

		[[gnu::always_inline]] constexpr operator element_type() const { return get(); }

		[[gnu::always_inline]] constexpr auto get() const { return m_value; }

	private:
		element_type m_value;
	};

	template<class T, size_t N>
	[[gnu::always_inline]] constexpr auto conj(vec_t<T, N> val)
	{ return val.get(); }

	template<class T, size_t N>
	class vec_t<std::complex<T>, N>
	{
	public:
		using element_type = vector_storage<std::complex<T>, N>;

		[[gnu::always_inline]]
		vec_t(vector_storage<T, N> real, vector_storage<T, N> imag):m_value{real, imag}{}

		[[gnu::always_inline]] constexpr vec_t(element_type val):m_value{val}{}

		[[gnu::always_inline]] constexpr operator element_type() const { return get();}

		[[gnu::always_inline]] constexpr auto real() const { return m_value.real(); }

		[[gnu::always_inline]] constexpr auto imag() const { return m_value.imag(); }

		[[gnu::always_inline]] constexpr auto get() const { return m_value; }

	private:
		element_type m_value;
	};

	template<class T, size_t N>
	[[gnu::always_inline]] constexpr auto conj(vec_t<std::complex<T>, N> val)
	{ return conj(val.get()); }

	template<class T, size_t N>
	constexpr auto inner_product(vec_t<T, N> a, vec_t<T, N> b)
	{
		auto const prod = a.get() * conj(b);
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