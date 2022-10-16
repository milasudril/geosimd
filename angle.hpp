#ifndef GEOSIMD_ANGLE_HPP
#define GEOSIMD_ANGLE_HPP

#include "./inline.hpp"
#include "./adl_factories.hpp"
#include "./vectorops_mixin.hpp"

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

	class turn_angle:public vectorops_mixin<turn_angle>
	{
		using vectorops_magic=vectorops_mixin<turn_angle>::magic;
	public:
		using scalar_type = double;

		static constexpr auto full_turn =
			static_cast<int64_t>(std::numeric_limits<uint32_t>::max()) + one(empty<int64_t>{});

		GEOSIMD_INLINE_OPT constexpr turn_angle() = default;

		GEOSIMD_INLINE_OPT constexpr explicit turn_angle(int64_t x):m_value{x}{}
	
		GEOSIMD_INLINE_OPT constexpr turn_angle(turns x):
			m_value{static_cast<uint32_t>(static_cast<int64_t>(x.value * full_turn))}
		{}

		GEOSIMD_INLINE_OPT constexpr turn_angle(rad x):
			turn_angle{static_cast<turns>(x)}
		{}

		GEOSIMD_INLINE_OPT constexpr auto get() const 
		{ return m_value; }

		GEOSIMD_INLINE_OPT constexpr auto& get(vectorops_magic)
		{ return m_value; }

	private:
		int64_t m_value;
	};

	inline auto to_string(turn_angle x)
	{ return std::to_string(x.get()); }

	GEOSIMD_INLINE_OPT constexpr auto zero(geosimd::empty<turn_angle>)
	{ return turn_angle{0}; }

	class rotation_angle
	{
	public:
		using scalar_type = double;
		using vector_type = turn_angle;

		GEOSIMD_INLINE_OPT constexpr rotation_angle() = default;

		GEOSIMD_INLINE_OPT explicit constexpr rotation_angle(uint32_t value) : m_value{value}
		{}

		GEOSIMD_INLINE_OPT explicit constexpr rotation_angle(turns x):
			m_value{static_cast<uint32_t>(turn_angle{x}.get())}
		{}

		GEOSIMD_INLINE_OPT explicit constexpr rotation_angle(rad x):
			rotation_angle{static_cast<turns>(x)}
		{}

		GEOSIMD_INLINE_OPT constexpr rotation_angle& operator+=(turn_angle x)
		{
			m_value += static_cast<uint32_t>(x.get());
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr rotation_angle& operator-=(turn_angle x)
		{
			m_value -= static_cast<uint32_t>(x.get());
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

	GEOSIMD_INLINE_OPT constexpr auto zero(geosimd::empty<rotation_angle>)
	{ return rotation_angle{0}; }

	GEOSIMD_INLINE_OPT constexpr auto to_turns(rotation_angle x)
	{
		return turns{static_cast<double>(x.get())/static_cast<double>(turn_angle::full_turn)};
	}

	GEOSIMD_INLINE_OPT constexpr auto to_rad(rotation_angle x)
	{
		return rad{to_turns(x)};
	}

	GEOSIMD_INLINE_OPT constexpr auto operator+(rotation_angle a, turn_angle b)
	{
		return a += b;
	}

	GEOSIMD_INLINE_OPT constexpr auto operator-(rotation_angle a, turn_angle b)
	{
		return a -= b;
	}

	GEOSIMD_INLINE_OPT constexpr auto operator-(rotation_angle a, rotation_angle b)
	{
		return turn_angle{static_cast<int64_t>(a.get()) - static_cast<int64_t>(b.get())};
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