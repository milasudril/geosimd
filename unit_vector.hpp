#ifndef GEOSIMD_UNITVECTOR_HPP
#define GEOSIMD_UNITVECTOR_HPP

#include "./abstract_spaces.hpp"
#include "./vectorops_mixin.hpp"
#include "./basic_vector.hpp"

namespace geosimd
{
	template<normed_space V>
	class unit_vector:public vectorops_mixin<unit_vector<V>>
	{
		using vectorops_magic = typename vectorops_mixin<unit_vector<V>>::magic;
	public:
		//TODO: Add unit vectors for coordinate axis
		
		using vector_type = basic_vector<V>;
		using scalar_type = vector_type::scalar_type;
		using value_type = vector_type::value_type;

		GEOSIMD_INLINE_OPT constexpr explicit unit_vector(vector_type val):
			m_value{val/norm(val)}
		{}

		template<class T = void>
		requires(subscriptable<vector_type>)
		GEOSIMD_INLINE_OPT constexpr scalar_type operator[](size_t n) const
		{ return m_value[n]; }

		template<class = void>
		requires(!supports_static_constexpr_size<vector_type> && supports_size<vector_type>)
		GEOSIMD_INLINE_OPT constexpr size_t size() const
		{ return std::size(m_value); }

		template<class = void>
		requires(supports_static_constexpr_size<vector_type>)
		GEOSIMD_INLINE_OPT static constexpr size_t size()
		{ return vector_type::size(); }

		template<class = void>
		requires(!supports_size<vector_type>)
		GEOSIMD_INLINE_OPT static constexpr size_t size()
		{ return 1; }

		auto get() const
		{ return m_value; }

		void get(vectorops_magic) = delete;

		GEOSIMD_INLINE_OPT friend constexpr auto operator*(scalar_type c, unit_vector v)
		{
			return c*v.m_value;
		}

		GEOSIMD_INLINE_OPT friend constexpr auto operator*(unit_vector v, scalar_type c)
		{
			return v.m_value*c;
		}

		GEOSIMD_INLINE_OPT friend constexpr auto operator/(unit_vector v, scalar_type c)
		{
			return v.m_value/c;
		}

		template<class T = V>
		requires(std::is_same_v<T, V> && has_rotations<T>)
		GEOSIMD_INLINE_OPT constexpr auto& apply(rotation<T> const& mat)
		{
			m_value.apply(mat);;
			return *this;
		}

	private:
		vector_type m_value;
	};

	template<normed_space V>
	inline auto to_string(unit_vector<V> val)
	{
		using std::to_string;
		return to_string(val.get());
	}

	template<inner_product_space V>
	GEOSIMD_INLINE_OPT constexpr auto inner_product(basic_vector<V> a, unit_vector<V> b)
	{
		return inner_product(a, b.get());
	}

	template<inner_product_space V>
	GEOSIMD_INLINE_OPT constexpr auto inner_product(unit_vector<V> a, unit_vector<V> b)
	{
		return inner_product(a.get(), b.get());
	}
	
	template<hilbert_space V>
	constexpr auto angular_difference(unit_vector<V> a, unit_vector<V> b)
	{
		return turn_angle{rad{std::acos(inner_product(a, b))}};
	}
}

#endif
