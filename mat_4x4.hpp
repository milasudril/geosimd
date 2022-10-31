#ifndef GEOSIMD_MAT4X4_HPP
#define GEOSIMD_MAT4X4_HPP

#include "./vec_t.hpp"
#include "./adl_factories.hpp"

#include <span>

namespace geosimd
{
	namespace mat_4x4_detail
	{
		template<class T>
		GEOSIMD_FLATTEN constexpr std::array<vec_t<T, 4>, 4>
		transposed(std::array<vec_t<T, 4>, 4> const& input)
		{
			auto const upper_left =	shuffle(input[0], input[1],  0, 4, 1, 5);
			auto const lower_left =	shuffle(input[0], input[1],  2, 6, 3, 7);
			auto const upper_right = shuffle(input[2], input[3], 0, 4, 1, 5);
			auto const lower_right = shuffle(input[2], input[3], 2, 6, 3, 7);

			return std::array<vec_t<T, 4>, 4>{
				shuffle(upper_left, upper_right, 0, 1, 4, 5),
				shuffle(upper_left, upper_right, 2, 3, 6, 7),
				shuffle(lower_left, lower_right, 0, 1, 4, 5),
				shuffle(lower_left, lower_right, 2, 3, 6, 7)};
		}

		template<class T>
		using twins = std::pair<T, T>;

		template<class T>
		GEOSIMD_FLATTEN
		constexpr vec_t<T, 4>
		multi_inner_prod_raw(twins<vec_t<T, 4>> a,
			twins<vec_t<T, 4>> b,
			twins<vec_t<T, 4>> c,
			twins<vec_t<T, 4>> d)
		{
			std::array<vec_t<T, 4>, 4> elem_prods{
				a.first * a.second, b.first * b.second, c.first * c.second, d.first * d.second};

			auto sumvecs = transposed(elem_prods);
			return sumvecs[0] + sumvecs[1] + sumvecs[2] + sumvecs[3];
		}

	}

	template<class T>
	class mat_4x4;

	template<class T>
	constexpr mat_4x4<T> transposed(mat_4x4<T> const& A);

	template<class T>
	class mat_4x4
	{
	public:
		using column_type = vec_t<T, 4>;
		using scalar_type = column_type::scalar_type;

		constexpr mat_4x4() = default;

		GEOSIMD_INLINE_OPT constexpr explicit mat_4x4(column_type a,
			column_type b,
			column_type c,
			column_type d):
			m_cols{a, b, c, d}
		{
		}

		GEOSIMD_INLINE_OPT constexpr explicit mat_4x4(std::array<column_type, 4> const& cols):
			m_cols{cols}
		{
		}

		GEOSIMD_INLINE_OPT constexpr auto column_major_elements() const
		{
			return std::span{m_cols[0].data(), 16};
		}

		GEOSIMD_INLINE_OPT constexpr auto const& columns() const
		{
			return m_cols;
		}

		GEOSIMD_INLINE_OPT constexpr column_type col(size_t index) const
		{
			return m_cols[index];
		}

		GEOSIMD_INLINE_OPT constexpr mat_4x4& assign(size_t index, column_type val)
		{
			m_cols[index] = val;
			return *this;
		}

		GEOSIMD_FLATTEN constexpr mat_4x4& operator+=(mat_4x4 const& other)
		{
			for(int k = 0; k < 4; ++k)
			{
				m_cols[k] += other.m_cols[k];
			}
			return *this;
		}

		GEOSIMD_FLATTEN constexpr mat_4x4& operator-=(mat_4x4 const& other)
		{
			for(int k = 0; k < 4; ++k)
			{
				m_cols[k] -= other.m_cols[k];
			}
			return *this;
		}

		GEOSIMD_FLATTEN constexpr mat_4x4& leftmul(mat_4x4 const& left)
		{
			using mat_4x4_detail::transposed;
			auto left_transposed = transposed(left);
			for(auto k = 0; k < 4; ++k)
			{
				using mat_4x4_detail::multi_inner_prod_raw;
				m_cols[k] = multi_inner_prod_raw<T>({left_transposed.m_cols[0], m_cols[k]},
					{left_transposed.m_cols[1], m_cols[k]},
					{left_transposed.m_cols[2], m_cols[k]},
					{left_transposed.m_cols[3], m_cols[k]});
			}
			return *this;
		}

		GEOSIMD_FLATTEN constexpr mat_4x4& rightmul(mat_4x4 const& right)
		{
			using mat_4x4_detail::transposed;
			auto left_transposed = transposed(*this);
			for(auto k = 0; k < 4; ++k)
			{
				using mat_4x4_detail::multi_inner_prod_raw;
				m_cols[k] = multi_inner_prod_raw<T>({left_transposed.m_cols[0], right.m_cols[k]},
					{left_transposed.m_cols[1], right.m_cols[k]},
					{left_transposed.m_cols[2], right.m_cols[k]},
					{left_transposed.m_cols[3], right.m_cols[k]});
			}
			return *this;
		}

		GEOSIMD_FLATTEN constexpr mat_4x4& operator*=(scalar_type c)
		{
			for(int k = 0; k < 4; ++k)
			{
				m_cols[k] *= c;
			}
			return *this;
		}

		GEOSIMD_FLATTEN constexpr mat_4x4& operator/=(scalar_type c)
		{
			for(int k = 0; k < 4; ++k)
			{
				m_cols[k] /= c;
			}
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr mat_4x4& transpose()
		{
			using mat_4x4_detail::transposed;
			m_cols = transposed(m_cols);
			return *this;
		}

	private:
		std::array<column_type, 4> m_cols;
	};

	template<class T>
	GEOSIMD_INLINE_OPT constexpr auto operator*(typename mat_4x4<T>::scalar_type c, mat_4x4<T> const& A)
	{
		auto ret = A;
		return ret *= c;
	}

	template<class T>
	GEOSIMD_INLINE_OPT constexpr auto operator*(mat_4x4<T> const& A, typename mat_4x4<T>::scalar_type c)
	{
		auto ret = A;
		return ret *= c;
	}

	template<class T>
	GEOSIMD_INLINE_OPT constexpr auto operator-(mat_4x4<T> const& A)
	{
		using scalar_type = typename mat_4x4<T>::scalar_type;
		return (-one(geosimd::empty<scalar_type>{})) * A;
	}

	template<class T>
	GEOSIMD_INLINE_OPT constexpr auto operator/(mat_4x4<T> const& A, typename mat_4x4<T>::scalar_type c)
	{
		auto ret = A;
		return ret /= c;
	}

	template<class T>
	GEOSIMD_INLINE_OPT constexpr auto operator+(mat_4x4<T> const& A, mat_4x4<T> const& B)
	{
		auto ret = A;
		return ret += B;
	}

	template<class T>
	GEOSIMD_INLINE_OPT constexpr auto operator-(mat_4x4<T> const& A, mat_4x4<T> const& B)
	{
		auto ret = A;
		return ret -= B;
	}

	template<class T>
	GEOSIMD_INLINE_OPT constexpr auto operator*(mat_4x4<T> const& A, mat_4x4<T> const& B)
	{
		auto ret = B;
		return ret.leftmul(A);
	}

	template<class T>
	constexpr auto operator*(mat_4x4<T> const& A, typename mat_4x4<T>::column_type x)
	{
		using column_type = typename mat_4x4<T>::column_type;
		return column_type{
			inner_product_raw(column_type{A.col(0)[0], A.col(1)[0], A.col(2)[0], A.col(3)[0]}, x),
			inner_product_raw(column_type{A.col(0)[1], A.col(1)[1], A.col(2)[1], A.col(3)[1]}, x),
			inner_product_raw(column_type{A.col(0)[2], A.col(1)[2], A.col(2)[2], A.col(3)[2]}, x),
			inner_product_raw(column_type{A.col(0)[3], A.col(1)[3], A.col(2)[3], A.col(3)[3]}, x)};
	}

	template<class T>
	GEOSIMD_FLATTEN constexpr bool operator==(mat_4x4<T> const& A, mat_4x4<T> const& B)
	{
		for(auto k = 0; k < 4; ++k)
		{
			if(A.col(k) != B.col(k)) { return false; }
		}
		return true;
	}

	template<class T>
	GEOSIMD_INLINE GEOSIMD_FLATTEN constexpr bool operator!=(mat_4x4<T> const& A, mat_4x4<T> const& B)
	{
		return !(A == B);
	}

	template<class T>
	GEOSIMD_INLINE_OPT constexpr mat_4x4<T> transposed(mat_4x4<T> const& A)
	{
		auto temp = A;
		return temp.transpose();
	}

	template<class T>
	GEOSIMD_FLATTEN constexpr auto zero(empty<mat_4x4<T>>)
	{
		using column_type = typename mat_4x4<T>::column_type;
		auto const nul = zero(empty<column_type>{});
		return mat_4x4<T>{nul, nul, nul, nul};
	}

	template<class T>
	GEOSIMD_FLATTEN constexpr auto one(empty<mat_4x4<T>>)
	{
		using column_type = typename mat_4x4<T>::column_type;
		using scalar_type = typename mat_4x4<T>::scalar_type;
		auto const nul = zero(empty<scalar_type>{});
		auto const a = one(empty<scalar_type>{});

		return mat_4x4<T>{column_type{a, nul, nul, nul},
			column_type{nul, a, nul, nul},
			column_type{nul, nul, a, nul},
			column_type{nul, nul, nul, a}
		};
	}

	template<class T>
	GEOSIMD_FLATTEN constexpr auto to_string(mat_4x4<T> const& mat)
	{
		auto const tmp = transposed(mat);
		std::string ret{"["};
		for(size_t k = 0; k != 4; ++k)
		{
			ret.append(to_string(tmp.col(k))).append("\n");
		}
		ret.append("]");
		return ret;
	}
}
#endif