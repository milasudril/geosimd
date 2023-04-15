#ifndef GEOSIMD_TRIANGLE_HPP
#define GEOSIMD_TRIANGLE_HPP

#include "./basic_point.hpp"
#include "./hilbert_space.hpp"

#include <algorithm>

namespace geosimd
{
	template<affine_space V>
	struct triangle
	{
		basic_point<V> p1;
		basic_point<V> p2;
		basic_point<V> p3;

		auto points() const
		{ return std::array<basic_point<V>, 3>{p1, p2, p3}; }
	};

	template<affine_space V>
	auto normal(triangle<V> const& T)
	{
		return cross(T.p2 - T.p1, T.p3 - T.p1);
	}

	template<class Func, class V, class ... Params>
	concept point_visitation_function =
	affine_space<V> && requires(Func f, basic_point<V> p, Params ... params)
	{
		{f(p, params...)} -> std::same_as<void>;
	};

	template<affine_space V, class Z, class Func, class ... FuncParams>
	requires point_visitation_function<Func, V, FuncParams...>
	void project_from_above(typename V::scalar_type x_a,
		typename V::scalar_type x_b,
		typename V::scalar_type y,
		Z&& z,
		Func&& f,
		FuncParams&& ... params)
	{
		using scalar_type = typename V::scalar_type;

		auto const col_count = static_cast<size_t>(std::abs(x_a - x_b) + static_cast<scalar_type>(0.5));
		auto const x_0 = std::min(x_a, x_b);
		for(size_t l = 0; l != col_count + 1; ++l)
		{
			auto const x = x_0 + static_cast<scalar_type>(l);
			f(basic_point<V>{x, y, z(x, y)}, params...);
		}
	}

	template<affine_space V, class Func, class ... FuncParams>
	requires point_visitation_function<Func, V, FuncParams...>
	void project_from_above(triangle<V> const& T, Func&& f, FuncParams&& ... params)
	{
		using scalar_type = typename V::scalar_type;

		auto by_y = [](basic_point<V> a, basic_point<V> b) {
			return a[1] < b[1];
		};

		auto points = T.points();
		std::ranges::sort(points, by_y);

		auto const bottom_corner = points[0];
		auto const mid_corner = points[1];
		auto const top_corner = points[2];

		auto const n = normal(T);

		if(n[2] <= static_cast<scalar_type>(0) || top_corner[1] == bottom_corner[1])
		{ return; }

		auto const d = -inner_product(n, T.p1 - origin<V>());
		auto z = [n, d](scalar_type x, scalar_type y){
			return -(d + n[0]*x + n[1]*y)/n[2];
		};

		// loop from "bottom" to "top"

		if(mid_corner[1] == bottom_corner[1])
		{
			auto const line_count = static_cast<size_t>(top_corner[1] - bottom_corner[1]);
			for(size_t k = 0; k != line_count + 1; ++k)
			{
				auto const y = bottom_corner[1] + static_cast<scalar_type>(k);

				auto const x_a = std::lerp(mid_corner[0], top_corner[0], (y - bottom_corner[1])
					/(top_corner[1] - bottom_corner[1]));
				auto const x_b = std::lerp(bottom_corner[0], top_corner[0], (y - bottom_corner[1])
					/(top_corner[1] - bottom_corner[1]));

				project_from_above<V>(x_a, x_b, y, z, f, params...);
			}

			return;
		}

		if(mid_corner[1] == top_corner[1])
		{
			auto const line_count = static_cast<size_t>(top_corner[1] - bottom_corner[1]);
			for(size_t k = 0; k != line_count + 1; ++k)
			{
				auto const y = bottom_corner[1] + static_cast<scalar_type>(k);

				auto const x_a = std::lerp(bottom_corner[0], top_corner[0], (y - bottom_corner[1])
					/(top_corner[1] - bottom_corner[1]));
				auto const x_b = std::lerp(bottom_corner[0], mid_corner[0], (y - bottom_corner[1])
					/(top_corner[1] - bottom_corner[1]));

				project_from_above<V>(x_a, x_b, y, z, f, params...);
			}

			return;
		}

		{
			auto const line_count_1 = static_cast<size_t>(mid_corner[1] - bottom_corner[1]);
			auto const line_count_2 = static_cast<size_t>(top_corner[1] - mid_corner[1]);

			for(size_t k = 0; k != line_count_1; ++k)
			{
				auto const y = bottom_corner[1] + static_cast<scalar_type>(k);

				auto const x_a = std::lerp(bottom_corner[0], top_corner[0], (y - bottom_corner[1])
					/(top_corner[1] - bottom_corner[1]));
				auto const x_b = std::lerp(bottom_corner[0], mid_corner[0], (y - bottom_corner[1])
					/(mid_corner[1] - bottom_corner[1]));

				project_from_above<V>(x_a, x_b, y, z, f, params...);
			}

			for(size_t k = 0; k != line_count_2 + 1; ++k)
			{
				auto const y = mid_corner[1] + static_cast<scalar_type>(k);

				auto const x_a = std::lerp(mid_corner[0], top_corner[0], (y - mid_corner[1])
					/(top_corner[1] - mid_corner[1]));
				auto const x_b = std::lerp(bottom_corner[0], top_corner[0], (y - bottom_corner[1])
					/(top_corner[1] - bottom_corner[1]));

				project_from_above<V>(x_a, x_b, y, z, f, params...);
			}
		}
	}

	template<class VertexIndex>
	struct indirect_triangle
	{
		VertexIndex v1;
		VertexIndex v2;
		VertexIndex v3;

		auto vertex_indices() const
		{ return std::array<VertexIndex, 3>{v1, v2, v3}; }
	};

	namespace detail
	{
		template<class T>
		concept associative_container = requires()
		{
			typename T::mapped_type;
		};

		template<class T>
		concept regular_container = !associative_container<T> && requires()
		{
			typename T::value_type;
		};

		template<class T>
		struct get_mapped_type;

		template<associative_container T>
		struct get_mapped_type<T>
		{
			using type = typename T::mapped_type;
		};

		template<regular_container T>
		struct get_mapped_type<T>
		{
			using type = typename T::value_type;
		};

		template<class T>
		using mapped_type = typename get_mapped_type<T>::type;

		template<class T, class IndexType>
		concept index_operator_is_const = requires(T const& c, IndexType i)
		{
			{c[i]};
		};
	};

	template<class Resolver, class Container, class VertexIndex>
	concept vertex_resolver = requires(Resolver const& r,
		Container const& c,
		VertexIndex vi)
	{
		{r(c, vi)} -> std::same_as<detail::mapped_type<Container>>;
	};

	template<class Container, class IndexType>
	struct default_vertex_resolver
	{
		auto operator()(Container const& c, IndexType i) const
		{
			if constexpr (detail::index_operator_is_const<Container, IndexType>)
			{ return c[i]; }
			else
			{ return c.at(i); }
		}
	};

	template<class VertexIndex,
		class Container,
		vertex_resolver<Container, VertexIndex> resolver = default_vertex_resolver<Container, VertexIndex>>
	auto resolve(indirect_triangle<VertexIndex> const& T,
		Container const& c,
		resolver&& res = resolver{})
	{
		return triangle{res(c, T.v1), res(c, T.v2), res(c, T.v3)};
	}

}

#endif
