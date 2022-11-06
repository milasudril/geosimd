#ifndef GEOSIMD_ROT_3_HPP
#define GEOSIMD_ROT_3_HPP

#include "./angle.hpp"
#include "./mat_4x4.hpp"
#include "./abstract_spaces.hpp"

namespace geosimd
{
	namespace rot_3_detail
	{
		constexpr auto create_matrix(rotation_angle theta, dimension_tag<0>)
		{
			auto const param = cossin(theta);
			using col = mat_4x4<float>::column_type;

			return mat_4x4{
				col{1.0f, 0.0f, 0.0f, 0.0f},
				col{0.0f,  param.cos, param.sin, 0.0f},
				col{0.0f, -param.sin, param.cos, 0.0f},
				col{0.0f, 0.0f, 0.0f, 1.0f},
			};
		}

		constexpr auto create_matrix(rotation_angle theta, dimension_tag<1>)
		{
			auto const param = cossin(theta);
			using col = mat_4x4<float>::column_type;

			return mat_4x4{
				col{param.cos, 0.0f, -param.sin, 0.0f},
				col{0.0f, 1.0f, 0.0f, 0.0f},
				col{param.sin, 0.0f, param.cos, 0.0f},
				col{0.0f, 0.0f, 0.0f, 1.0f},
			};
		}

		constexpr auto create_matrix(rotation_angle theta, dimension_tag<2>)
		{
			auto const param = cossin(theta);
			using col = mat_4x4<float>::column_type;

			return mat_4x4{
				col{param.cos, param.sin, 0.0f, 0.0f},
				col{-param.sin, param.cos, 0.0f, 0.0f},
				col{0.0f, 0.0f, 1.0f, 0.0f},
				col{0.0f, 0.0f, 1.0f, 1.0f}
			};
		}
	}

	class rot_3
	{
	public:
		using scalar_type = float;
		using storage_type = mat_4x4<float>;
		using column_type = storage_type::column_type;

		GEOSIMD_INLINE_OPT constexpr rot_3():m_value{one(empty<storage_type>{})}{}

		template<size_t N>
		GEOSIMD_INLINE_OPT constexpr rot_3(rotation_angle theta, dimension_tag<N>):
			m_value{rot_3_detail::create_matrix(theta, dimension_tag<N>{})}
		{}

		GEOSIMD_INLINE_OPT constexpr auto column_major_elements() const
		{ return m_value.column_major_elements(); }

		GEOSIMD_INLINE_OPT constexpr auto const& columns() const
		{ return m_value.columns(); }

		GEOSIMD_INLINE_OPT constexpr column_type col(size_t index) const
		{ return m_value.col(index); }

		GEOSIMD_INLINE_OPT constexpr auto const& get() const
		{ return m_value; }

		constexpr bool operator==(rot_3 const&) const = default;

		constexpr bool operator!=(rot_3 const&) const = default;

	private:
		storage_type m_value;
	};
}

#endif