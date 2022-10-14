#ifndef GEOSIMD_ANGLE_HPP
#define GEOSIMD_ANGLE_HPP

#include "./inline.hpp"
#include "./adl_factories.hpp"

#include <cmath>
#include <numbers>
#include <limits>
#include <cstdint>
#include <string>

namespace geosimd
{
	struct turns
	{
		constexpr auto operator<=>(turns const&) const = default;
		double value;
	};

	inline auto to_string(turns x)
	{
		return std::to_string(x.value).append(" τ");
	}

	struct rad
	{
		constexpr auto operator<=>(rad const&) const = default;
		constexpr rad() = default;
		GEOSIMD_INLINE_OPT constexpr explicit rad(double x):value{x}{}
		GEOSIMD_INLINE_OPT explicit constexpr rad(turns x):value{2.0f*std::numbers::pi_v<double>*x.value}{}
		GEOSIMD_INLINE_OPT explicit constexpr operator turns() const { return turns{0.5*value/std::numbers::pi_v<double>}; }
		double value;
	};

	inline auto to_string(rad x)
	{
		return std::to_string(x.value).append(" rad");
	}

	class turn_angle
	{
		public:
			static constexpr auto full_turn =
				static_cast<int64_t>(std::numeric_limits<uint32_t>::max()) + one(empty<int64_t>{});
		
			GEOSIMD_INLINE_OPT constexpr turn_angle(turns x):
				m_value{static_cast<uint32_t>(static_cast<int64_t>(x.value * full_turn))}
			{}

			GEOSIMD_INLINE_OPT constexpr turn_angle(rad x):
				turn_angle{static_cast<turns>(x)}
			{}

			GEOSIMD_INLINE_OPT constexpr auto get() const 
			{ return m_value; }

		private:
			int64_t m_value;
	};

	class rotation_angle
	{
	public:
		GEOSIMD_INLINE_OPT explicit constexpr rotation_angle(uint32_t value) : m_value{value}
		{}

		GEOSIMD_INLINE_OPT explicit constexpr rotation_angle(turns x):
			m_value{static_cast<uint32_t>(turn_angle{x}.get())}
		{}

		GEOSIMD_INLINE_OPT explicit constexpr rotation_angle(rad x):
			rotation_angle{static_cast<turns>(x)}
		{}

		template<class T>
		GEOSIMD_INLINE_OPT constexpr rotation_angle& operator+=(T x)
		{
			m_value += rotation_angle{x}.m_value;
			return *this;
		}

		template<class T>
		GEOSIMD_INLINE_OPT constexpr rotation_angle& operator-=(T x)
		{
			m_value -= rotation_angle{x}.m_value;
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr auto get() const
		{
			return m_value;
		}

		bool operator==(rotation_angle const&) const = default;
		bool operator!=(rotation_angle const&) const = default;

	private:
		uint32_t m_value;
	};

	GEOSIMD_INLINE_OPT constexpr auto to_turns(rotation_angle x)
	{
		return turns{static_cast<double>(x.get())/static_cast<double>(turn_angle::full_turn)};
	}

	GEOSIMD_INLINE_OPT constexpr auto to_rad(rotation_angle x)
	{
		return rad{to_turns(x)};
	}

	template<class T>
	GEOSIMD_INLINE_OPT constexpr auto operator+(rotation_angle a, T b)
	{
		return a += b;
	}

	template<class T>
	GEOSIMD_INLINE_OPT constexpr auto operator-(rotation_angle a, T b)
	{
		return a -= b;
	}

	constexpr auto sin(rotation_angle x)
	{
		switch(x.get())
		{
			case 0:
				return 0.0f;
			case 0x4000'0000:
				return 1.0f;
			case 0x8000'0000:
				return 0.0f;
			case 0xc000'0000:
				return -1.0f;
			default:
				return static_cast<float>(std::sin(to_rad(x).value));
		}
	}

	constexpr auto cos(rotation_angle x)
	{
		switch(x.get())
		{
			case 0:
				return 1.0f;
			case 0x4000'0000:
				return 0.0f;
			case 0x8000'0000:
				return -1.0f;
			case 0xc000'0000:
				return 0.0f;
			default:
				return static_cast<float>(std::cos(to_rad(x).value));
		}
	}
}

#endif