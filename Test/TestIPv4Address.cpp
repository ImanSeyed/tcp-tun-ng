#include <gtest/gtest.h>
#include <cstdint>
#include "IPv4Address.h"
#include "Endian.h"

TEST(IPv4AddressTest, should_default_contructor_with_0s)
{
	constexpr IPv4Address addr{};

	static_assert(addr.is_zero());

	EXPECT_TRUE(addr.is_zero());
}

TEST(IPv4AddressTest, should_construct_from_c_array)
{
	constexpr auto addr = []
	{
		const uint8_t a[4] = { 1, 2, 3, 4 };
		return IPv4Address(a);
	}();

	static_assert(!addr.is_zero());

	EXPECT_FALSE(addr.is_zero());
}

TEST(IPv4AddressTest, should_construct_from_uint32)
{
	constexpr auto addr = []
	{
		const BigEndian<uint32_t> a = 0x11'22'33'44;
		return IPv4Address(a);
	}();

	static_assert(!addr.is_zero());

	EXPECT_FALSE(addr.is_zero());
}

TEST(IPv4AddressTest, should_get_octets_by_byte_offset)
{
	constexpr IPv4Address addr(11, 22, 33, 44);

	static_assert(11 == addr[0]);
	static_assert(22 == addr[1]);
	static_assert(33 == addr[2]);
	static_assert(44 == addr[3]);

	EXPECT_EQ(11, addr[0]);
	EXPECT_EQ(22, addr[1]);
	EXPECT_EQ(33, addr[2]);
	EXPECT_EQ(44, addr[3]);
}

TEST(IPv4AddressTest, should_convert_to_string)
{
	constexpr IPv4Address addr(11, 22, 33, 44);

	EXPECT_EQ(std::string("11.22.33.44"), addr.to_string());
}

TEST(IPv4AddressTest, should_compare)
{
	constexpr IPv4Address addr_a(11, 22, 33, 44);
	constexpr IPv4Address addr_b(11, 22, 33, 55);

	static_assert(addr_a != addr_b);
	static_assert(addr_a == addr_a);

	EXPECT_TRUE(addr_a != addr_b);
	EXPECT_TRUE(addr_a == addr_a);
}