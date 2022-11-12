#ifndef GEOSIMD_ROTLOC_HPP
#define GEOSIMD_ROTLOC_HPP

#include "./mat_4x4.hpp"
#include "./abstract_spaces.hpp"
#include "./translation.hpp"
#include "./rotation.hpp"

namespace geosimd
{
	template<affine_space V>
	requires std::is_same_v<typename V::scalar_type, float>
		&& (has_homogenous_coordinates<V> && V::vector_type::size() == 4 && has_rotations<V>)
	class rotloc
	{
		public:
			using scalar_type = typename V::scalar_type;
			using storage_type = mat_4x4<float>;
			using column_type = storage_type::column_type;

			GEOSIMD_INLINE_OPT constexpr rotloc():m_value{one(empty<storage_type>{})}{}

			GEOSIMD_INLINE_OPT constexpr rotloc(translation<V> const& T, rotation<V> const& R):
				m_value{T.get() * R.get()}
			{}

			GEOSIMD_INLINE_OPT constexpr auto column_major_elements() const
			{ return m_value.column_major_elements(); }

			GEOSIMD_INLINE_OPT constexpr auto const& get() const
			{ return m_value; }

			constexpr bool operator==(rotloc const&) const = default;

			constexpr bool operator!=(rotloc const&) const = default;

			GEOSIMD_INLINE_OPT constexpr rotloc& invert()
			{
				auto const offset = basic_vector<V>{m_value.col(3)[0], m_value.col(3)[1], m_value.col(3)[2]};
				translation const T{-offset};

				// TODO: Is it possible to simplify this expression
				m_value.leftmul(T.get()).transpose().rightmul(T.get());
				return *this;
			}

		private:
			storage_type m_value;
	};

	template<affine_space V>
	auto to_string(rotloc<V> const& transform)
	{
		return to_string(transform.get());
	}

	template<affine_space V>
	auto inverted(rotloc<V> const& transform)
	{
		auto temp = transform;
		return temp.invert();
	}
}

#endif