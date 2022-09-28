#ifndef GEOSIMD_POINT_HPP
#define GEOSIMD_POINT_HPP

#include "./affine_space.hpp"
#include "./normed_space.hpp"

#include <string>

namespace geosimd
{
	template<affine_space Space>
	class point
	{
	public:
		using vector_type = typename Space::vector_type;
		using scalar_type = typename Space::scalar_type;
		static constexpr size_t dimension_count = Space::dimension_count();

		constexpr point() = default;

		constexpr explicit point(vector_type vector):m_vector{Space::origin() + vector}{}

		template<size_t index>
		constexpr scalar_type& get()
		{
			static_assert(index >= 0 && index < dimension_count);
			return m_vector[index];
		}

		template<size_t index>
		constexpr scalar_type get () const
		{
			static_assert(index >= 0 && index < dimension_count);
			return m_vector;
		}

		constexpr point& operator+=(vector_type v)
		{
			m_vector += v;
			return *this;
		}

		constexpr point& operator-=(vector_type v)
		{
			m_vector -= v;
			return *this;
		}

		constexpr auto vector() const
		{
			return m_vector;
		}

	private:
		vector_type m_vector;
	};

	template<affine_space Space>
	constexpr auto operator+(point<Space> a, typename Space::vector_type v)
	{
		return a += v;
	}

	template<affine_space Space>
	constexpr auto operator-(point<Space> a, typename Space::vector_type v)
	{
		return a -= v;
	}

	template<affine_space Space>
	constexpr auto operator-(point<Space> a, point<Space> b)
	{
		return a.vector() - b.vector();
	}

	template<affine_space Space>
	constexpr auto origin()
	{
		return point<Space>{typename Space::vector_type{}};
	}

	template<affine_space Space>
	inline std::string to_string(point<Space> a)
	{
		using std::to_string;
		return to_string(a.vector());
	}

	template<normed_space Space>
	constexpr auto distance(point<Space> a, point<Space> b)
	{
		return norm(a - b);
	}
}

#endif