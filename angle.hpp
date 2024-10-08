#ifndef GEOSIMD_ANGLE_HPP
#define GEOSIMD_ANGLE_HPP

#include "./inline.hpp"
#include "./factories.hpp"
#include "./vectorops_mixin.hpp"

#include <cmath>
#include <numbers>
#include <limits>
#include <cstdint>
#include <string>
#include <algorithm>

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
			m_value{static_cast<int64_t>(x.value * full_turn)}
		{}

		GEOSIMD_INLINE_OPT constexpr turn_angle(rad x):
			turn_angle{static_cast<turns>(x)}
		{ codecov::function_called(__FILE__, __LINE__); }

		GEOSIMD_INLINE_OPT constexpr auto get() const
		{ return m_value; }

		GEOSIMD_INLINE_OPT constexpr auto& get(vectorops_magic)
		{ return m_value; }

		GEOSIMD_INLINE_OPT constexpr auto& operator*=(double val)
		{
			m_value = static_cast<int64_t>(val*static_cast<double>(m_value));
			return *this;
		}

		GEOSIMD_INLINE_OPT constexpr auto& operator/=(double val)
		{
			m_value = static_cast<int64_t>(static_cast<double>(m_value)/val);
			return *this;
		}

	private:
		int64_t m_value;
	};

	GEOSIMD_INLINE_OPT constexpr auto abs(turn_angle x)
	{
		return turn_angle{x.get() >= 0 ? x.get() : -x.get()};
	}

	GEOSIMD_INLINE_OPT constexpr auto min(turn_angle x, turn_angle y)
	{
		return turn_angle{std::min(x.get(), y.get())};
	}

	GEOSIMD_INLINE_OPT constexpr auto max(turn_angle x, turn_angle y)
	{
		return turn_angle{std::max(x.get(), y.get())};
	}

	GEOSIMD_INLINE_OPT constexpr auto clamp(turn_angle x, turn_angle min, turn_angle max)
	{
		return turn_angle{std::clamp(x.get(), min.get(), max.get())};
	}

	inline auto to_string(turn_angle x)
	{ return std::to_string(x.get()); }

	GEOSIMD_INLINE_OPT constexpr auto zero(geosimd::empty<turn_angle>)
	{ return turn_angle{0}; }

	GEOSIMD_INLINE_OPT constexpr auto to_turns(turn_angle x)
	{
		return turns{static_cast<double>(x.get())/static_cast<double>(turn_angle::full_turn)};
	}

	GEOSIMD_INLINE_OPT constexpr auto to_rad(turn_angle x)
	{
		return rad{to_turns(x)};
	}

	class rotation_angle
	{
	public:
		using scalar_type = double;
		using vector_type = turn_angle;

		GEOSIMD_INLINE_OPT constexpr rotation_angle() = default;

		GEOSIMD_INLINE_OPT constexpr explicit rotation_angle(uint32_t value) : m_value{value}
		{}

		GEOSIMD_INLINE_OPT constexpr explicit rotation_angle(turns x):
			m_value{static_cast<uint32_t>(turn_angle{x}.get())}
		{ codecov::function_called(__FILE__, __LINE__); }

		GEOSIMD_INLINE_OPT constexpr explicit rotation_angle(rad x):
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

	template<std::floating_point RetType = float>
	constexpr auto sin(rotation_angle x)
	{
		switch(x.get())
		{
			case 0:
				return zero<RetType>();
			case 0x4000'0000:
				return one<RetType>();
			case 0x8000'0000:
				return zero<RetType>();
			case 0xc000'0000:
				return -one<RetType>();
			default:
				return static_cast<RetType>(std::sin(to_rad(x).value));
		}
	}

	template<std::floating_point RetType = float>
	constexpr auto cos(rotation_angle x)
	{
		switch(x.get())
		{
			case 0:
				return one<RetType>();
			case 0x4000'0000:
				return zero<RetType>();
			case 0x8000'0000:
				return -one<RetType>();
			case 0xc000'0000:
				return zero<RetType>();
			default:
				return static_cast<RetType>(std::cos(to_rad(x).value));
		}
	}

	template<std::floating_point RetType = float>
	constexpr auto sin(turn_angle x)
	{
		return sin<RetType>(rotation_angle{turns{0.0}} + x);
	}

	template<std::floating_point RetType = float>
	constexpr auto cos(turn_angle x)
	{
		return cos<RetType>(rotation_angle{turns{0.0}} + x);
	}

	template<std::floating_point T>
	class cossin_pair
	{
	public:
		constexpr explicit cossin_pair(T x):m_cos{std::cos(x)}, m_sin{std::sin(x)}
		{}

		template<class U>
		constexpr explicit cossin_pair(U x):
			m_cos{geosimd::cos<T>(x)}, m_sin{geosimd::sin<T>(x)}
		{}

		constexpr auto cos() const { return m_cos; }

		constexpr auto sin() const { return m_sin; }

	private:
		T m_cos;
		T m_sin;
	};

	template<std::floating_point T = float, class U>
	constexpr auto cossin(U val)
	{
		return cossin_pair<T>{val};
	}

}

#endif
