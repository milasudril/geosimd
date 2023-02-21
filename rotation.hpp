#ifndef GEOSIMD_ROTATION_HPP
#define GEOSIMD_ROTATION_HPP

#include "./angle.hpp"
#include "./mat_4x4.hpp"
#include "./abstract_spaces.hpp"

namespace geosimd
{
	namespace rotation_detail
	{
		constexpr auto create_matrix(rotation_angle theta, dimension_tag<0>)
		{
			auto const param = cossin(theta);
			using col = mat_4x4<float>::column_type;

			return mat_4x4{
				col{1.0f, 0.0f, 0.0f, 0.0f},
				col{0.0f,  param.cos(), param.sin(), 0.0f},
				col{0.0f, -param.sin(), param.cos(), 0.0f},
				col{0.0f, 0.0f, 0.0f, 1.0f},
			};
		}

		constexpr auto create_matrix(rotation_angle theta, dimension_tag<1>)
		{
			auto const param = cossin(theta);
			using col = mat_4x4<float>::column_type;

			return mat_4x4{
				col{param.cos(), 0.0f, -param.sin(), 0.0f},
				col{0.0f, 1.0f, 0.0f, 0.0f},
				col{param.sin(), 0.0f, param.cos(), 0.0f},
				col{0.0f, 0.0f, 0.0f, 1.0f},
			};
		}

		constexpr auto create_matrix(rotation_angle theta, dimension_tag<2>)
		{
			auto const param = cossin(theta);
			using col = mat_4x4<float>::column_type;

			return mat_4x4{
				col{param.cos(), param.sin(), 0.0f, 0.0f},
				col{-param.sin(), param.cos(), 0.0f, 0.0f},
				col{0.0f, 0.0f, 1.0f, 0.0f},
				col{0.0f, 0.0f, 0.0f, 1.0f}
			};
		}
	}

	template<vector_space V>
	requires std::is_same_v<typename V::scalar_type, float>
		&& (has_homogenous_coordinates<V> && V::vector_type::size() == 4 && has_rotations<V>)
	class rotation
	{
	public:
		using scalar_type = typename V::scalar_type;
		using storage_type = mat_4x4<float>;
		using column_type = storage_type::column_type;

		GEOSIMD_INLINE_OPT constexpr rotation():m_value{one(empty<storage_type>{})}{}

		template<size_t N>
		GEOSIMD_INLINE_OPT constexpr rotation(rotation_angle theta, dimension_tag<N>):
			m_value{rotation_detail::create_matrix(theta, dimension_tag<N>{})}
		{}

		GEOSIMD_INLINE_OPT constexpr auto column_major_elements() const
		{ return m_value.column_major_elements(); }

		GEOSIMD_INLINE_OPT constexpr auto const& get() const
		{ return m_value; }

		constexpr bool operator==(rotation const&) const = default;

		constexpr bool operator!=(rotation const&) const = default;

		template<size_t N>
		GEOSIMD_INLINE_OPT constexpr rotation& push(turn_angle angle, dimension_tag<N>)
		{
			m_value.rightmul(rotation_detail::create_matrix(rotation_angle{0} + angle, dimension_tag<N>{}));
			return *this;
		}

		template<size_t N>
		GEOSIMD_INLINE_OPT constexpr rotation& pop(turn_angle angle, dimension_tag<N>)
		{
			return push(-angle, dimension_tag<N>{});
		}

		GEOSIMD_INLINE_OPT constexpr rotation& invert()
		{
			m_value.transpose();
			return *this;
		}

	private:
		storage_type m_value;
	};

	template<vector_space V>
	inline auto to_string(rotation<V> const& mat)
	{ return to_string(mat.get()); }

	template<vector_space V>
	GEOSIMD_INLINE_OPT constexpr auto inverted(rotation<V> const& mat)
	{
		auto tmp = mat;
		return tmp.invert();
	}
}

#endif