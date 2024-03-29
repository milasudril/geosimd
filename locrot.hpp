#ifndef GEOSIMD_LOCROT_HPP
#define GEOSIMD_LOCROT_HPP

#include "./mat_4x4.hpp"
#include "./abstract_spaces.hpp"
#include "./translation.hpp"
#include "./rotation.hpp"

namespace geosimd
{
	template<affine_space V>
	requires std::is_same_v<typename V::scalar_type, float>
		&& (has_homogenous_coordinates<V> && V::vector_type::size() == 4 && has_rotations<V>)
	class locrot
	{
		public:
			using scalar_type = typename V::scalar_type;
			using storage_type = mat_4x4<float>;
			using column_type = storage_type::column_type;

			GEOSIMD_INLINE_OPT constexpr locrot():m_value{one(empty<storage_type>{})}{}

			GEOSIMD_INLINE_OPT constexpr locrot(translation<V> const& T, rotation<V> const& R):
				m_value{T.get() * R.get()}
			{}

			GEOSIMD_INLINE_OPT constexpr locrot(rotation<V> const& R, translation<V> const& T):
				m_value{R.get() * T.get()}
			{}

			GEOSIMD_INLINE_OPT constexpr auto column_major_elements() const
			{ return m_value.column_major_elements(); }

			GEOSIMD_INLINE_OPT constexpr auto const& get() const
			{ return m_value; }

			constexpr bool operator==(locrot const&) const = default;

			constexpr bool operator!=(locrot const&) const = default;

			GEOSIMD_INLINE_OPT constexpr auto translation_part() const
			{
				auto const z = zero(geosimd::empty<scalar_type>{});
				auto const o = one(geosimd::empty<scalar_type>{});
				return m_value.col(3) - vec_t<scalar_type, 4>{z, z, z, o};
			}

			GEOSIMD_INLINE_OPT constexpr auto rotation_part() const
			{
				auto ret = m_value;
				ret.col(3) -= translation_part();
				return ret;
			}

			GEOSIMD_INLINE_OPT constexpr locrot& invert()
			{
				auto const offs = -translation_part();
				using vec = basic_vector<V>;
				m_value.col(3) += offs;
				m_value.self_transposed_rightmul(translation{vec{offs[0], offs[1], offs[2]}}.get());
				return *this;
			}

		private:
			storage_type m_value;
	};

	template<affine_space V>
	auto to_string(locrot<V> const& transform)
	{
		return to_string(transform.get());
	}

	template<affine_space V>
	auto inverted(locrot<V> const& transform)
	{
		auto temp = transform;
		return temp.invert();
	}
}

#endif