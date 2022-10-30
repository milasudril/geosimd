#ifndef GEOSIMD_VECT_HPP
#define GEOSIMD_VECT_HPP

#include "./vector_storage.hpp"
#include "./vectorops_mixin.hpp"

namespace geosimd
{
	template<class T, size_t N>
	class vec_t:public vectorops_mixin<vec_t<T, N>>
	{
		using vectorops_magic = typename vectorops_mixin<vec_t<T, N>>::magic;
	public:
		using enable_hadamard_product_t = void;

		using scalar_type = T;

		using element_type = vector_storage<T, N>;

		constexpr vec_t() = default;

		template<class ... Args>
		requires (std::conjunction_v<std::is_same<scalar_type, Args>...> && sizeof...(Args) == N - 1)
		GEOSIMD_INLINE_OPT constexpr explicit vec_t(scalar_type x, Args... xn):m_value{x, xn...}{}

		GEOSIMD_INLINE_OPT constexpr vec_t(element_type val):m_value{val}{}

		GEOSIMD_INLINE_OPT static constexpr size_t size() { return N; }

		GEOSIMD_INLINE_OPT constexpr T& operator[](size_t n)
		{ return m_value[n]; }

		GEOSIMD_INLINE_OPT constexpr T operator[](size_t n) const
		{ return m_value[n]; }

		GEOSIMD_INLINE_OPT constexpr auto get() const
		{ return m_value; }

		GEOSIMD_INLINE_OPT constexpr auto& get(vectorops_magic)
		{ return m_value; }

	private:
		element_type m_value;
	};

	template<class T, size_t N, class ... Indices>
	requires (std::conjunction_v<std::is_same<int, Indices>...> && sizeof...(Indices) == N)
	GEOSIMD_INLINE_OPT constexpr auto shuffle(vec_t<T, N> a, vec_t<T, N> b, Indices ... vals)
	{
		return vec_t<T, N>{shuffle<T, N>(a.get(), b.get(), vals...)};
	}

	template<class T, size_t N>
	GEOSIMD_FULL_INLINE constexpr auto conj(vec_t<T, N> val)
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

	template<class T, size_t N, size_t Trim = 0>
	std::string to_string(vec_t<T, N> val, std::integral_constant<size_t, Trim> = std::integral_constant<size_t, Trim>{})
	{
		static_assert(N > Trim);
		static constexpr auto length = N - Trim;
		static_assert(length != 0);
		std::string ret{"("};
		for(size_t k = 0; k != length - 1; ++k)
		{
			ret.append(to_string(val[k])).append(", ");
		}
		ret.append(to_string(val[length - 1])).append(")");
		return ret;
	}

	template<class T, size_t N>
	GEOSIMD_FULL_INLINE constexpr auto conj(vec_t<std::complex<T>, N> val);

	template<class T, size_t N>
	class vec_t<std::complex<T>, N>:public vectorops_mixin<vec_t<std::complex<T>, N>>
	{
		using vectorops_magic = typename vectorops_mixin<vec_t<std::complex<T>, N>>::magic;
	public:
		using enable_hadamard_product_t= void;

		using scalar_type = std::complex<T>;

		using element_type = vector_storage<std::complex<T>, N>;

		constexpr vec_t() = default;

		GEOSIMD_INLINE_OPT constexpr explicit vec_t(vec_t<T, N> real, vec_t<T, N> imag):
			m_value{real.get(), imag.get()}{}

		GEOSIMD_INLINE_OPT constexpr vec_t(element_type::base val):m_value{val}{}

		GEOSIMD_INLINE_OPT static constexpr size_t size() { return N; }

		GEOSIMD_FULL_INLINE constexpr auto operator[](size_t n) const
		{
			auto const real_val = m_value.real()[n];
			auto const imag_val = m_value.imag()[n];
			return std::complex<T>{real_val, imag_val};
		}

		GEOSIMD_INLINE_OPT constexpr auto get() const
		{ return m_value; }

		GEOSIMD_INLINE_OPT constexpr auto& get(vectorops_magic)
		{ return m_value; }

		constexpr auto real() const
		{ return m_value.real(); }

		constexpr auto imag() const
		{ return m_value.imag(); }

		GEOSIMD_FLATTEN GEOSIMD_FORCE_OPT auto& operator/=(scalar_type x)
		{
			auto const conj_x = std::conj(x);
			m_value *= conj_x;
			auto const tmp = x.real()*x.real() + x.imag()*x.imag();
			m_value = element_type{m_value.real()/tmp, m_value.imag()/tmp};
			return *this;
		}

		GEOSIMD_FLATTEN GEOSIMD_FORCE_OPT auto& operator/=(vec_t x)
		{
			auto const conj_x = conj(x);
			m_value *= conj_x.get();
			m_value /= x.real()*x.real() + x.imag()*x.imag();
			return *this;
		}

	private:
		element_type m_value;
	};

	template<class T, size_t N, class ... Indices>
	requires (std::conjunction_v<std::is_same<int, Indices>...> && sizeof...(Indices) == N)
	GEOSIMD_INLINE_OPT constexpr auto shuffle(
		vec_t<std::complex<T>, N> const& a,
		vec_t<std::complex<T>, N> const& b,
		Indices ... vals)
	{
		auto const real = shuffle<T, N>(a.real(), b.real(), vals...);
		auto const imag = shuffle<T, N>(a.imag(), b.imag(), vals...);
		return vec_t<std::complex<T>, N>{real, imag};
	}

	template<class T, size_t N>
	GEOSIMD_INLINE_OPT constexpr auto conj(vec_t<std::complex<T>, N> val)
	{ return vec_t<std::complex<T>, N>{conj(val.get())}; }

	template<class T, size_t N>
	GEOSIMD_FLATTEN constexpr auto inner_product_raw(vec_t<T, N> a, vec_t<T, N> b)
	{
		auto const prod = a * b;
		T ret{};
		for(size_t k = 0; k != N; ++k)
		{ ret += prod[k]; }

		return ret;
	}

	template<class T, size_t N>
	GEOSIMD_FLATTEN constexpr auto inner_product(vec_t<T, N> a, vec_t<T, N> b)
	{
		return inner_product_raw(a, conj(b));
	}

	template<class T, size_t N>
	GEOSIMD_INLINE_OPT constexpr auto inner_product(vec_t<T, N> a)
	{
		return inner_product(a, a);
	}

	template<class T, size_t N>
	GEOSIMD_FLATTEN constexpr auto inner_product(vec_t<std::complex<T>, N> a)
	{
		auto const prod = a.real() * a.real() + a.imag() * a.imag();
		T ret{};
		for(size_t k = 0; k != N; ++k)
		{ ret += prod[k]; }

		return ret;
	}

	template<class T>
	constexpr std::array<vec_t<T, 4>, 4> transposed(std::array<vec_t<T, 4>, 4> const& input)
	{
		auto const upper_left =	shuffle(input[0], input[1],  0, 4, 1, 5);
		auto const lower_left =	shuffle(input[0], input[1],  2, 6, 3, 7);
		auto const upper_right = shuffle(input[2], input[3], 0, 4, 1, 5);
		auto const lower_right = shuffle(input[2], input[3], 2, 6, 3, 7);

		return std::array<vec_t<T, 4>, 4>{
			shuffle(upper_left, upper_right, 0, 1, 4, 5),
			shuffle(upper_left, upper_right, 2, 3, 6, 7),
			shuffle(lower_left, lower_right, 0, 1, 4, 5),
			shuffle(lower_left, lower_right, 2, 3, 6, 7)};
	}

	using vec4f32_t = vec_t<float, 4>;
	using vec4i32_t = vec_t<int32_t, 4>;
	using vec2i64_t = vec_t<int64_t, 2>;
	using vec2f64_t = vec_t<double, 2>;
}
#endif