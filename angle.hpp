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
		constexpr explicit rad(double x):value{x}{}
		GEOSIMD_INLINE_OPT explicit constexpr rad(turns x):value{2.0f*std::numbers::pi_v<double>*x.value}{}
		GEOSIMD_INLINE_OPT explicit constexpr operator turns() const { return turns{0.5*value/std::numbers::pi_v<double>}; }
		double value;
	};

	inline auto to_string(rad x)
	{
		return std::to_string(x.value).append(" rad");
	}

	class angle
	{
	public:
		static constexpr auto full_turn =
			static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) + one(empty<uint64_t>{});

		GEOSIMD_INLINE_OPT explicit constexpr angle(uint32_t value) : m_value{value}
		{}

		GEOSIMD_INLINE_OPT explicit constexpr angle(turns x):
			m_value{static_cast<uint32_t>(static_cast<int64_t>(x.value * full_turn))}
		{}

		GEOSIMD_INLINE_OPT explicit constexpr angle(rad x):angle{static_cast<turns>(x)}{}

		GEOSIMD_INLINE_OPT constexpr angle& operator+=(angle a)
		{
			m_value += a.m_value;
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr angle& operator-=(angle a)
		{
			m_value -= a.m_value;
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr auto get() const
		{
			return m_value;
		}

		bool operator==(angle const&) const = default;
		bool operator!=(angle const&) const = default;

	private:
		uint32_t m_value;
	};

	GEOSIMD_INLINE_OPT constexpr auto to_turns(angle x)
	{
		return turns{static_cast<double>(x.get())/static_cast<double>(angle::full_turn)};
	}

	GEOSIMD_INLINE_OPT constexpr auto to_rad(angle x)
	{
		return rad{to_turns(x)};
	}

	constexpr auto sin(angle x)
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

	constexpr auto cos(angle x)
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