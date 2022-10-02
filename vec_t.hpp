#ifndef GEOSIMD_VECT_HPP
#define GEOSIMD_VECT_HPP

#include "./vector_storage.hpp"
#include "./inline.hpp"

namespace geosimd
{
	template<class Derived>
	struct arithmetic_mixin
	{
		GEOSIMD_INLINE GEOSMID_FLATTEN constexpr Derived& operator*=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.get() *= other.get();
			return derived;
		}

		GEOSIMD_INLINE GEOSMID_FLATTEN constexpr Derived& operator/=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.get() /= other.get();
			return derived;
		}

		GEOSIMD_INLINE GEOSMID_FLATTEN constexpr Derived& operator+=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.get() += other.get();
			return derived;
		}

		GEOSIMD_INLINE GEOSMID_FLATTEN constexpr Derived& operator-=(Derived other)
		{
			auto& derived = static_cast<Derived&>(*this);
			derived.get() -= other.get();
			return derived;
		}

		constexpr bool operator==(Derived other) const
		{
			auto const diff = static_cast<Derived const&>(*this) - other;
			for(size_t k = 0; k != std::size(diff); ++k)
			{
				if(diff[k] != typename Derived::scalar_type{})
				{ return false; }
			}
			return true;
		}

		GEOSIMD_INLINE constexpr bool operator!=(Derived other) const
		{
			return !(*this == other);
		}
	};

	template<class T, size_t N>
	class vec_t:public arithmetic_mixin<vec_t<T, N>>
	{
	public:
		GEOSIMD_INLINE static constexpr size_t size() { return N; }

		using element_type = vector_storage<T, N>;

		using scalar_type = T;

		template<class ... U>
		GEOSIMD_INLINE constexpr explicit vec_t(T first, U... args):m_value{first, args...}{}

		GEOSIMD_INLINE constexpr vec_t(element_type val):m_value{val}{}

		GEOSIMD_INLINE constexpr T& operator[](size_t n)
		{ return m_value[n]; }

		GEOSIMD_INLINE constexpr T operator[](size_t n) const
		{ return m_value[n]; }

		GEOSIMD_INLINE constexpr auto get() const
		{ return m_value; }

		GEOSIMD_INLINE constexpr auto& get()
		{ return m_value; }

	private:
		element_type m_value;
	};

	template<class T, size_t N>
	GEOSIMD_INLINE constexpr auto operator*(vec_t<T, N> a, vec_t<T, N> b)
	{ return a *= b; }

	template<class T, size_t N>
	GEOSIMD_INLINE constexpr auto operator/(vec_t<T, N> a, vec_t<T, N> b)
	{ return a /= b; }

	template<class T, size_t N>
	GEOSIMD_INLINE constexpr auto operator+(vec_t<T, N> a, vec_t<T, N> b)
	{ return a += b; }

	template<class T, size_t N>
	GEOSIMD_INLINE constexpr auto operator-(vec_t<T, N> a, vec_t<T, N> b)
	{ return a -= b; }

	template<class T, size_t N>
	GEOSIMD_INLINE constexpr auto conj(vec_t<T, N> val)
	{ return val; }

	template<class T>
	std::string to_string(T val)
	{
		using std::to_string;
		return to_string(val);
	}

	template<class T>
	std::string to_string(std::complex<T> val)
	{
		using std::to_string;
		return std::string{to_string(val.real())}
			.append(" + ")
			.append(to_string(val.imag()))
			.append("i");
	}

	template<class T, size_t N>
	std::string to_string(vec_t<T, N> val)
	{
		static_assert(N != 0);
		std::string ret{"("};
		for(size_t k = 0; k != N - 1; ++k)
		{
			ret.append(to_string(val[k])).append(", ");
		}
		ret.append(to_string(val[N - 1])).append(")");
		return ret;
	}

	template<class T, size_t N>
	class vec_t<std::complex<T>, N>:public arithmetic_mixin<vec_t<std::complex<T>, N>>
	{
	public:
		using scalar_type = T;

		GEOSIMD_INLINE static constexpr size_t size() { return N; }

		using element_type = vector_storage<std::complex<T>, N>;

		GEOSIMD_INLINE constexpr explicit vec_t(vec_t<T, N> real, vec_t<T, N> imag):
			m_value{real.get(), imag.get()}{}

		GEOSIMD_INLINE constexpr vec_t(element_type::base val):m_value{val}{}

		GEOSIMD_INLINE constexpr auto get() const
		{ return m_value; }

		GEOSIMD_INLINE constexpr auto& get()
		{ return m_value; }

		GEOSIMD_INLINE constexpr auto operator[](size_t n) const
		{
			auto const real_val = m_value.real()[n];
			auto const imag_val = m_value.imag()[n];
			return std::complex<T>{real_val, imag_val};
		}

	private:
		element_type m_value;
	};

	template<class T, size_t N>
	GEOSIMD_INLINE GEOSMID_FLATTEN constexpr auto conj(vec_t<std::complex<T>, N> val)
	{ return vec_t<std::complex<T>, N>{conj(val.get())}; }

	template<class T, size_t N>
	GEOSMID_FLATTEN constexpr auto inner_product(vec_t<T, N> a, vec_t<T, N> b)
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