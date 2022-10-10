#ifndef GEOSIMD_ANGLE_HPP
#define GEOSIMD_ANGLE_HPP

#include "./inline.hpp"
#include "./adl_factories.hpp"

#include <cmath>
#include <numbers>
#include <limits>
#include <cstdint>

namespace geosimd
{
	struct rad{};

	struct turns{};

	class angle
	{
	public:
		static constexpr auto full_turn =
			static_cast<uint64_t>(std::numeric_limits<uint32_t>::max()) + one(empty<uint64_t>{});

		GEOSIMD_INLINE_OPT explicit constexpr angle(uint32_t value) : m_value{value}
		{}

		GEOSIMD_INLINE_OPT explicit constexpr angle(float value, turns):
			m_value{static_cast<uint32_t>(static_cast<int64_t>(value * full_turn))}
		{}

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

		GEOSIMD_INLINE_OPT constexpr auto in_turns() const
		{
			return static_cast<float>(m_value)/static_cast<float>(full_turn);
		}

		bool operator==(angle const&) const = default;
		bool operator!=(angle const&) const = default;

	private:
		uint32_t m_value;
	};
}

#endif