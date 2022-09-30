#ifndef GEOSIMD_POINT_HPP
#define GEOSIMD_POINT_HPP

#include "./affine_space.hpp"
#include "./normed_space.hpp"
#include "./hilbert_space.hpp"

#include <string>

namespace geosimd
{
	template<affine_space Space>
	class location
	{
	public:
		using vector_type = typename Space::vector_type;
		using scalar_type = typename Space::scalar_type;
		static constexpr size_t dimension_count = Space::dimension_count();

		constexpr location() = default;

		constexpr explicit location(vector_type vector):m_vector{Space::origin() + vector}{}

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

		constexpr location& operator+=(vector_type v)
		{
			m_vector += v;
			return *this;
		}

		constexpr location& operator-=(vector_type v)
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
	constexpr auto operator+(location<Space> a, typename Space::vector_type v)
	{
		return a += v;
	}

	template<affine_space Space>
	constexpr auto operator-(location<Space> a, typename Space::vector_type v)
	{
		return a -= v;
	}

	template<affine_space Space>
	constexpr auto operator-(location<Space> a, location<Space> b)
	{
		return a.vector() - b.vector();
	}

	template<affine_space Space>
	constexpr auto origin()
	{
		return location<Space>{typename Space::vector_type{}};
	}

	template<affine_space Space>
	inline std::string to_string(location<Space> a)
	{
		using std::to_string;
		return to_string(a.vector());
	}

	template<class T>
	concept normed_affine_space = normed_space<T> && affine_space<T>;

	template<normed_affine_space Space>
	constexpr auto distance(location<Space> a, location<Space> b)
	{
		return norm(a - b);
	}

	template<class T>
	concept affine_hilbert_space = hilbert_space<T> && affine_space<T>;

	template<affine_hilbert_space H>
	constexpr auto distance_squared(location<H> a, location<H> b)
	{
		auto const dx = a- b;
		return inner_product(dx, dx);
	}

	template<affine_hilbert_space H>
	constexpr auto distance(location<H> a, location<H> b)
	{
		return std::sqrt(distance_squared(a, b));
	}

}

#endif