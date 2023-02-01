#ifndef IPV4HEADER_H
#define IPV4HEADER_H

#include "Endian.h"
#include "IPv4Address.h"

BigEndian<uint16_t> internet_checksum(void const* ptr, std::size_t count);

class __attribute__((packed)) IPv4Header
{
private:
	uint8_t m_version_and_ihl{ 0 };
	uint8_t m_dscp_and_ecn{ 0 };
	BigEndian<uint16_t> m_length;
	BigEndian<uint16_t> m_ident;
	BigEndian<uint16_t> m_flags_and_fragment;
	uint8_t m_ttl{ 0 };
	BigEndian<uint8_t> m_protocol;
	BigEndian<uint16_t> m_checksum;
	IPv4Address m_source;
	IPv4Address m_destination;

	enum class Protocol : uint16_t
	{
		ICMP = 1,
		TCP = 6,
		UDP = 17,
	};

	enum class Flags : uint16_t
	{
		DontFragment = 0x4000,
		MoreFragments = 0x2000,
	};

public:
	uint8_t version() const
	{
		return (m_version_and_ihl >> 4) & 0xf;
	}
	void set_version(uint8_t version)
	{
		m_version_and_ihl = (m_version_and_ihl & 0x0f) | (version << 4);
	}

	uint8_t dscp_and_ecn() const
	{
		return m_dscp_and_ecn;
	}
	void set_dscp_and_ecn(uint8_t dscp_and_ecn)
	{
		m_dscp_and_ecn = dscp_and_ecn;
	}

	uint8_t internet_header_length() const
	{
		return m_version_and_ihl & 0xf;
	}
	void set_internet_header_length(uint8_t ihl)
	{
		m_version_and_ihl = (m_version_and_ihl & 0xf0) | (ihl & 0x0f);
	}

	uint16_t length() const
	{
		return m_length;
	}
	void set_length(uint16_t length)
	{
		m_length = length;
	}

	uint16_t ident() const
	{
		return m_ident;
	}
	void set_ident(uint16_t ident)
	{
		m_ident = ident;
	}

	uint8_t ttl() const
	{
		return m_ttl;
	}
	void set_ttl(uint8_t ttl)
	{
		m_ttl = ttl;
	}

	uint8_t protocol() const
	{
		return m_protocol;
	}
	void set_protocol(uint8_t protocol)
	{
		m_protocol = protocol;
	}

	uint16_t checksum() const
	{
		return m_checksum;
	}
	void set_checksum(uint16_t checksum)
	{
		m_checksum = checksum;
	}

	IPv4Address const& source() const
	{
		return m_source;
	}
	void set_source(IPv4Address const& address)
	{
		m_source = address;
	}

	IPv4Address const& destination() const
	{
		return m_destination;
	}
	void set_destination(IPv4Address const& address)
	{
		m_destination = address;
	}

	void* payload()
	{
		return this + 1;
	}
	void const* payload() const
	{
		return this + 1;
	}

	uint16_t flags_and_fragment() const
	{
		return m_flags_and_fragment;
	}
	uint16_t fragment_offset() const
	{
		return ((uint16_t)m_flags_and_fragment & 0x1fff);
	}
	uint16_t flags() const
	{
		return (((uint16_t)m_flags_and_fragment) & (((uint16_t)Flags::MoreFragments) |
			((uint16_t)Flags::DontFragment)));
	}

	void set_has_more_fragments(bool more_fragments)
	{
		if (more_fragments)
			m_flags_and_fragment = (uint16_t)m_flags_and_fragment | ((uint16_t)Flags::MoreFragments);
		else
			m_flags_and_fragment = (uint16_t)m_flags_and_fragment & ((uint16_t)Flags::MoreFragments);
	}
	void set_fragment_offset(uint16_t offset)
	{
		m_flags_and_fragment = flags() | (offset & 0x1fff);
	}

	bool is_a_fragment() const
	{
		return (((uint16_t)m_flags_and_fragment) & ((uint16_t)Flags::MoreFragments))
			|| ((uint16_t)m_flags_and_fragment & 0x1fff);
	}

	uint16_t payload_size() const
	{
		return m_length - sizeof(IPv4Header);
	}

	BigEndian<uint16_t> compute_checksum() const
	{
		assert(!m_checksum);
		return internet_checksum(this, sizeof(IPv4Header));
	}
};

inline BigEndian<uint16_t> internet_checksum(void const* ptr, std::size_t count)
{
	uint32_t checksum = 0;
	auto* w = (uint16_t const*)ptr;
	while (count > 1)
	{
		checksum += convert_between_host_and_big_endian(*w++);
		if (checksum & 0x80000000)
			checksum = (checksum & 0xffff) | (checksum >> 16);
		count -= 2;
	}
	while (checksum >> 16)
		checksum = (checksum & 0xffff) + (checksum >> 16);
	return ~checksum & 0xffff;
}

#endif //IPV4HEADER_H
