#ifndef IPV4ADDRESS_H
#define IPV4ADDRESS_H

#include <cstdint>
#include <assert.h>
#include <fmt/core.h>
#include "Endian.h"

class __attribute__((packed)) IPv4Address
{
private:
	uint32_t m_data{};

	enum class Field : int
	{
		A = 0,
		B,
		C,
		D
	};

	constexpr uint32_t octet(const Field field) const
	{
		constexpr auto bits_per_byte = 8;
		auto const bits_to_shift = bits_per_byte * int(field);
		return (m_data >> bits_to_shift) & 0x0000'00FF;
	}

public:
	constexpr IPv4Address() = default;

	constexpr IPv4Address(uint32_t a, uint32_t b, uint32_t c, uint32_t d)
	{
		m_data = (d << 24) | (c << 16) | (b << 8) | a;
	}

	constexpr IPv4Address(const uint8_t data[4])
	{
		m_data = (uint32_t(data[3]) << 24) | (uint32_t(data[2]) << 16) |
			(uint32_t(data[1]) << 8) | uint32_t(data[0]);
	}

	constexpr IPv4Address(BigEndian<uint32_t> address)
		: m_data(address)
	{
	}

	constexpr uint32_t to_bytes() const
	{
		return m_data;
	}

	constexpr bool is_zero() const
	{
		return m_data == 0u;
	}

	std::string to_string() const
	{
		return fmt::format("{}.{}.{}.{}",
			octet(Field::A),
			octet(Field::B),
			octet(Field::C),
			octet(Field::D));
	}

	constexpr uint8_t operator[](int i) const
	{
		assert(i >= 0 && i < 4);
		return octet(Field(i));
	}
	constexpr bool operator==(IPv4Address const& other) const = default;
	constexpr bool operator!=(IPv4Address const& other) const = default;
};

#endif //IPV4ADDRESS_H
