#ifndef GEOSIMD_MAT4X4_HPP
#define GEOSIMD_MAT4X4_HPP

#include "./vec_t.hpp"
#include "./adl_factories.hpp"

namespace geosimd
{
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

		GEOSIMD_INLINE_OPT constexpr auto const* data() const
		{
			return m_cols[0].data();
		}

		GEOSIMD_INLINE_OPT constexpr auto const& columns() const
		{
			return m_cols;
		}

		GEOSIMD_INLINE_OPT constexpr column_type col(int index) const
		{
			return m_cols[index];
		}

		GEOSIMD_INLINE_OPT constexpr mat_4x4& col(int index, column_type val)
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

		GEOSIMD_FLATTEN constexpr mat_4x4& leftmul_by(mat_4x4 const& left)
		{
			auto left_transposed = transposed(left);
			for(auto k = 0; k < 4; ++k)
			{
				m_cols[k] = inner_product_raw({left_transposed.m_cols[0], m_cols[k]},
					{left_transposed.m_cols[1], m_cols[k]},
					{left_transposed.m_cols[2], m_cols[k]},
					{left_transposed.m_cols[3], m_cols[k]});
			}
			return *this;
		}

		GEOSIMD_FLATTEN constexpr mat_4x4& rightmul_by(mat_4x4 const& right)
		{
			auto left_transposed = transposed(*this);
			for(auto k = 0; k < 4; ++k)
			{
				m_cols[k] = inner_product_raw({left_transposed.m_cols[0], right.m_cols[k]},
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

		constexpr mat_4x4& transpose()
		{
			m_cols = transposed(m_cols);
			return *this;
		}

	private:
		std::array<column_type, 4> m_cols;
	};

	template<class T>
	GEOSIMD_INLINE_OPT constexpr auto operator*(typename mat_4x4<T>::scalar_type c, mat_4x4<T>& A)
	{
		auto ret = A;
		return ret *= c;
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
		return ret.leftmul_by(A);
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
	GEOSIMD_INLINE_OPT constexpr auto transposed(mat_4x4<T> const& A)
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
}
#endif