#ifndef GEOSIMD_BOX_SIZE_HPP
#define GEOSIMD_BOX_SIZE_HPP

#include "./scaling.hpp"
#include "./basic_vector.hpp"

#include <cmath>
#include <type_traits>

namespace geosimd
{
	template<vector_space V>
	requires (std::is_floating_point_v<typename V::scalar_type>)
	class box_size
	{
	public:
		using scalar_type = typename V::scalar_type;
		using storage_type = typename V::vector_type;

		GEOSIMD_INLINE_OPT constexpr box_size():
			m_value{zero(empty<storage_type>{})}{}

		GEOSIMD_INLINE_OPT constexpr explicit box_size(storage_type value): m_value{value}
		{}

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
			&& (!has_homogenous_coordinates<V> && !std::is_same_v<scalar_type, storage_type>)
		GEOSIMD_INLINE_OPT constexpr explicit box_size(scalar_type x, Args ... xn):
			m_value{x, xn...}
		{ codecov::function_called(__FILE__, __LINE__); }

		template<class ... Args>
		requires std::conjunction_v<std::is_same<scalar_type, Args>...>
			&& (has_homogenous_coordinates<V>)
		GEOSIMD_INLINE_OPT constexpr explicit box_size(scalar_type x, Args ... xn):
			m_value{x, xn..., zero<scalar_type>()}
		{ }

		GEOSIMD_INLINE_OPT constexpr auto const& get() const
		{ return m_value; }

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

		GEOSIMD_INLINE_OPT scalar_type operator[](size_t index) const
		{ return m_value[index]; }

		GEOSIMD_INLINE_OPT scalar_type& operator[](size_t index)
		{ return m_value[index]; }

		constexpr bool operator==(box_size const&) const = default;

		constexpr bool operator!=(box_size const&) const = default;

		GEOSIMD_INLINE_OPT constexpr box_size& operator/=(scaling<V> other)
		{
			m_value/=other.get();
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr box_size& operator/=(scalar_type other)
		{
			*this/=scaling<V>{other, other, other};
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr box_size& operator*=(scaling<V> other)
		{
			m_value*=other.get();
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr box_size& operator*=(scalar_type other)
		{
			*this *= scaling<V>{other, other, other};
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr box_size max(box_size b) const
		{
			auto const this_value = get().get();
			auto const other_value = b.get().get();
			return box_size{storage_type{this_value > other_value? this_value : other_value}};
		}

		GEOSIMD_INLINE_OPT constexpr box_size min(box_size b) const
		{
			auto const this_value = get().get();
			auto const other_value = b.get().get();
			return box_size{storage_type{this_value < other_value? this_value : other_value}};
		}

		GEOSIMD_INLINE_OPT constexpr box_size operator+=(basic_vector<V> v)
		{
			m_value += v.get();
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr box_size fit_xy_keep_z(box_size target_box) const
		{
			auto const src_val = m_value;
			auto const factors = target_box.m_value/src_val;
			auto const src_rep = shuffle(src_val, 0, 1, 0, 1);
			auto const factors_rep = shuffle(factors, 0, 0, 1, 1);
			auto const options = src_rep*factors_rep;
			auto const alt_a = shuffle(options, src_val, 0, 1, 6, 7);
			auto const alt_b = shuffle(options, src_val, 2, 3, 6, 7);
			auto const areas = shuffle(alt_a, alt_b, 0, 4, 1, 5)*shuffle(alt_a, alt_b, 1, 5, 0, 4);
			auto const area_a_broadcasted = shuffle(areas, 0, 0, 0, 0);
			auto const area_b_broadcasted = shuffle(areas, 1, 1, 1, 1);
			return box_size{area_a_broadcasted.get() < area_b_broadcasted.get()? alt_a.get() : alt_b.get()};
		}

	private:
		storage_type m_value;
	};

	template<vector_space V>
	inline auto to_string(box_size<V> s)
	{ return to_string(s.get()); }

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr auto zero(empty<box_size<V>>)
	{ return box_size<V>{}; }

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr box_size<V> operator*(box_size<V> a, typename V::scalar_type b)
	{
		a*=b;
		return a;
	}

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr box_size<V> operator*(typename V::scalar_type a, box_size<V> b)
	{
		b*=a;
		return b;
	}

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr box_size<V> operator*(box_size<V> a, scaling<V> b)
	{
		a*=b;
		return a;
	}

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr box_size<V> operator*(scaling<V> a, box_size<V> b)
	{
		b*=a;
		return b;
	}

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr box_size<V> operator/(box_size<V> a, typename V::scalar_type b)
	{
		a/=b;
		return a;
	}

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr box_size<V> operator/(box_size<V> a, scaling<V> b)
	{
		a/=b;
		return a;
	}

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr box_size<V> max(box_size<V> a, box_size<V> b)
	{ return a.max(b); }

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr box_size<V> min(box_size<V> a, box_size<V> b)
	{ return a.min(b); }

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr scaling<V> operator/(box_size<V> a, box_size<V> b)
	{ return scaling<V>{a.get()/b.get()}; }

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr scaling<V> to_scaling(box_size<V> a)
	{ return scaling<V>{a.get()}; }

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr box_size<V> operator+(box_size<V> b, basic_vector<V> v)
	{ return b += v; }

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr auto norm(box_size<V> box)
	{
		using scalar_type = typename V::scalar_type;
		auto ret = one(empty<scalar_type>{});
		auto const val = box.get();
		for(size_t k = 0; k != std::size(box); ++k)
		{ ret*=val[k]; }

		return std::pow(ret, one(empty<scalar_type>{})/std::size(box));
	}
}

#endif