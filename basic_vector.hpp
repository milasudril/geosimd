#ifndef GEOSIMD_BASICVECTOR_HPP
#define GEOSIMD_BASICVECTOR_HPP

#include "./abstract_spaces.hpp"
#include "./vectorops_mixin.hpp"
#include "./hilbert_space.hpp"
#include "./container_props.hpp"
#include "./rotation.hpp"
#include "./scaling.hpp"

#include <utility>
#include <numeric>

namespace geosimd
{
	template<vector_space V>
	class basic_vector:public vectorops_mixin<basic_vector<V>>
	{
		using vectorops_magic = typename vectorops_mixin<basic_vector<V>>::magic;
	public:
		using scalar_type = typename V::scalar_type;
		using value_type = scalar_type;
		using storage_type = typename V::vector_type;
		using vector_type = basic_vector<V>;
		using vector_space = V;

		GEOSIMD_INLINE_OPT constexpr basic_vector():m_value{make_origin()}{}

		GEOSIMD_INLINE_OPT constexpr explicit basic_vector(storage_type val):m_value{val}
		{ codecov::function_called(__FILE__, __LINE__); }

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
			&& (!has_homogenous_coordinates<V>)
		GEOSIMD_INLINE_OPT constexpr explicit basic_vector(scalar_type x, Args ... xn):
			m_value{x, xn...}
		{ codecov::function_called(__FILE__, __LINE__); }

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
			&& (has_homogenous_coordinates<V>)
		GEOSIMD_INLINE_OPT constexpr explicit basic_vector(scalar_type x, Args ... xn):
			m_value{x, xn..., zero(empty<scalar_type>{})}
		{ }

		template<class T = void>
		requires(subscriptable<storage_type>)
		GEOSIMD_INLINE_OPT constexpr scalar_type operator[](size_t n) const
		{ return m_value[n]; }

		template<class = void>
		requires(!supports_static_constexpr_size<storage_type> && supports_size<storage_type>)
		GEOSIMD_INLINE_OPT constexpr size_t size() const
		{ return std::size(m_value) - static_cast<size_t>(has_homogenous_coordinates<V>); }

		template<class = void>
		requires(supports_static_constexpr_size<storage_type>)
		GEOSIMD_INLINE_OPT static constexpr size_t size()
		{ return storage_type::size() - static_cast<size_t>(has_homogenous_coordinates<V>); }

		template<class = void>
		requires(!supports_size<storage_type>)
		GEOSIMD_INLINE_OPT static constexpr size_t size()
		{ return 1; }

		GEOSIMD_INLINE_OPT constexpr auto get() const
		{ return m_value; }

		GEOSIMD_INLINE_OPT constexpr auto& get(vectorops_magic)
		{ return m_value; }

		template<class T = V>
		requires(std::is_same_v<T, V> && has_rotations<T>)
		GEOSIMD_INLINE_OPT constexpr auto& apply(rotation<T> const& mat)
		{
			m_value = mat.get() * m_value;
			return *this;
		}

		template<class T = V>
		requires(std::is_floating_point_v<typename T::scalar_type>)
		GEOSIMD_INLINE_OPT constexpr auto& apply(scaling<T> scale)
		{
			m_value = scale.get() * m_value;
			return *this;
		}
		template<class T = V>
		requires(std::is_same_v<T, V> && has_rotations<T>)
		GEOSIMD_INLINE_OPT constexpr auto apply(rotation<T> const& mat) const
		{ return basic_vector{*this}.apply(mat); }

		template<class T = V>
		requires(std::is_floating_point_v<typename T::scalar_type>)
		GEOSIMD_INLINE_OPT constexpr auto apply(scaling<T> scale) const
		{ return basic_vector{*this}.apply(scale); }

	private:
		storage_type m_value;

		template<size_t ... Is>
		GEOSIMD_INLINE_OPT static constexpr auto make_origin(std::index_sequence<Is...>)
		{
			return storage_type
			{
				(static_cast<void>(Is), zero(empty<scalar_type>{}))...,
				zero(empty<scalar_type>{})
			};
		}

		GEOSIMD_INLINE_OPT static constexpr auto make_origin()
		{
			if constexpr(supports_static_constexpr_size<storage_type>)
			{
				return make_origin(std::make_index_sequence<storage_type::size() - 1>());
			}
			else
			{ return zero(empty<storage_type>{}); }
		}
	};

	template<normed_space V>
	GEOSIMD_INLINE_OPT constexpr auto norm(basic_vector<V> a)
	{
		if constexpr(overrides_norm<V>)
		{ return V::norm(a.get()); }
		else
		{ return norm(a.get()); }
	}

	template<hilbert_space V>
	GEOSIMD_INLINE_OPT constexpr auto norm_squared(basic_vector<V> a)
	{
		return V::norm_squared(a.get());
	}

	template<inner_product_space V>
	GEOSIMD_INLINE_OPT constexpr auto inner_product(basic_vector<V> a, basic_vector<V> b)
	{
		return inner_product(a.get(), b.get());
	}

	template<inner_product_space V>
	GEOSIMD_INLINE_OPT constexpr auto inner_product(basic_vector<V> a)
	{
		return inner_product(a.get());
	}

	template<vector_space V>
	requires(basic_vector<V>::size() == 3)
	GEOSIMD_FLATTEN constexpr auto cross(basic_vector<V> a, basic_vector<V> b)
	{
		auto const vals_a = a.get();
		auto const vals_b = b.get();

		auto const a120 = shuffle(vals_a, 1, 2, 0, 3);
		auto const a201 = shuffle(vals_a, 2, 0, 1, 3);

		auto const b201 = shuffle(vals_b, 2, 0, 1, 3);
		auto const b120 = shuffle(vals_b, 1, 2, 0, 3);

		auto const result = a120 * b201 - a201 * b120;

		return basic_vector<V>{result[0], result[1], result[2]};
	}

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr auto mean(basic_vector<V> a, basic_vector<V> b)
	{
		if constexpr(std::is_integral_v<typename V::vector_type>)
		{
			return basic_vector<V>{std::midpoint(a.get(), b.get())};
		}
		else
		{
			return (a + b)/static_cast<typename V::scalar_type>(2);
		}
	}

	template<vector_space V>
	requires std::floating_point<typename V::scalar_type>
	GEOSIMD_INLINE_OPT constexpr auto lerp(basic_vector<V> a, basic_vector<V> b, typename V::scalar_type t)
	{
		return t*b + (one(empty<typename V::scalar_type>{}) - t)*a;
	}

	template<vector_space V>
	auto to_string(basic_vector<V> a)
	{
		if constexpr(has_homogenous_coordinates<V>)
		{ return to_string(a.get(), std::integral_constant<size_t, 1>{}); }
		else
		{
			using std::string;
			return to_string(a.get());
		}
	}
}

#endif
