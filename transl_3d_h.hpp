#ifndef GEOSIMD_TRANSL_3D_H_HPP
#define GEOSIMD_TRANSL_3D_H_HPP

#include "./mat_4x4.hpp"
#include "./abstract_spaces.hpp"
#include "./basic_vector.hpp"

namespace geosimd
{
	template<scalar T>
	class transl_3d_h
	{
	public:
		using scalar_type = T;
		using storage_type = mat_4x4<T>;
		using column_type = storage_type::column_type;

		GEOSIMD_INLINE_OPT constexpr transl_3d_h():m_value{one(empty<storage_type>{})}{}

		GEOSIMD_INLINE_OPT constexpr transl_3d_h(basic_vector<T> offset):transl_3d_h{}
		{
			push(offset);
		}

		GEOSIMD_INLINE_OPT constexpr auto column_major_elements() const
		{ return m_value.column_major_elements(); }

		GEOSIMD_INLINE_OPT constexpr auto const& columns() const
		{ return m_value.columns(); }

		GEOSIMD_INLINE_OPT constexpr column_type col(size_t index) const
		{ return m_value.col(index); }

		GEOSIMD_INLINE_OPT constexpr auto const& get() const
		{ return m_value; }

		constexpr bool operator==(transl_3d_h const&) const = default;

		constexpr bool operator!=(transl_3d_h const&) const = default;

		GEOSIMD_INLINE_OPT constexpr transl_3d_h& push(basic_vector<T> offset)
		{
			m_value.col(3) += offset;
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr transl_3d_h& pop(basic_vector<T> offset)
		{
			return push(-offset);
		}

		GEOSIMD_INLINE_OPT constexpr transl_3d_h& invert()
		{
			m_value.col(3) = vec_t<T, 4>{-1, -1, -1, 1} * m_value.col(3);
			return *this;
		}

	private:
		storage_type m_value;
	};

	template<scalar T>
	inline auto to_string(transl_3d_h<T> const& mat)
	{ return to_string(mat.get()); }

	template<scalar T>
	GEOSIMD_INLINE_OPT constexpr auto inverted(transl_3d_h<T> const& mat)
	{
		auto tmp = mat;
		return tmp.invert();
	}
}

#endif