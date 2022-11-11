#ifndef GEOSIMD_TRANSLATION_HPP
#define GEOSIMD_TRANSLATION_HPP

#include "./mat_4x4.hpp"
#include "./abstract_spaces.hpp"
#include "./basic_vector.hpp"

namespace geosimd
{
	template<affine_space V>
	requires has_homogenous_coordinates<V> && (basic_vector<V>::size() == 3)
	class translation
	{
	public:
		using scalar_type = typename V::scalar_type;
		using storage_type = mat_4x4<scalar_type>;
		using column_type = storage_type::column_type;

		GEOSIMD_INLINE_OPT constexpr translation():m_value{one(empty<storage_type>{})}{}

		GEOSIMD_INLINE_OPT explicit constexpr translation(basic_vector<V> offset):translation{}
		{
			push(offset);
		}

		GEOSIMD_INLINE_OPT constexpr auto column_major_elements() const
		{ return m_value.column_major_elements(); }

		GEOSIMD_INLINE_OPT constexpr auto const& get() const
		{ return m_value; }

		GEOSIMD_INLINE_OPT constexpr auto offset() const
		{
			auto const z = zero(empty<scalar_type>{});
			auto const o = one(empty<scalar_type>{});
			return m_value.col(3) - vec_t<scalar_type, 4>{z, z, z, o};
		}

		constexpr bool operator==(translation const&) const = default;

		constexpr bool operator!=(translation const&) const = default;

		GEOSIMD_INLINE_OPT constexpr translation& push(basic_vector<V> offset)
		{
			m_value.col(3) += offset.get();
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr translation& pop(basic_vector<V> offset)
		{
			return push(-offset);
		}

		GEOSIMD_INLINE_OPT constexpr translation& invert()
		{
			auto const val = one(empty<scalar_type>{});
			m_value.col(3) = vec_t<scalar_type, 4>{-val, -val, -val, val} * m_value.col(3);
			return *this;
		}

	private:
		storage_type m_value;
	};

	template<affine_space V>
	inline auto to_string(translation<V> const& mat)
	{ return to_string(mat.get()); }

	template<affine_space V>
	GEOSIMD_INLINE_OPT constexpr auto inverted(translation<V> const& mat)
	{
		auto tmp = mat;
		return tmp.invert();
	}
}

#endif