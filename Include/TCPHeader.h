#ifndef TCPHEADER_H
#define TCPHEADER_H

#include <cstdint>
#include "Endian.h"

class __attribute__((packed)) TCPHeader
{
private:
	BigEndian<uint16_t> m_source_port;
	BigEndian<uint16_t> m_destination_port;
	BigEndian<uint32_t> m_sequence_number;
	BigEndian<uint32_t> m_ack_number;
	BigEndian<uint16_t> m_flags_and_data_offset;
	BigEndian<uint16_t> m_window_size;
	BigEndian<uint16_t> m_checksum;
	BigEndian<uint16_t> m_urgent;

	struct Flag
	{
		enum : uint16_t
		{
			FIN = 0x01,
			SYN = 0x02,
			RST = 0x04,
			PSH = 0x08,
			ACK = 0x10,
			URG = 0x20
		};
	};


public:
	TCPHeader() = default;
	~TCPHeader() = default;

	std::size_t header_size() const
	{
		return data_offset() * sizeof(uint32_t);
	}

	uint16_t source_port() const
	{
		return m_source_port;
	}
	void set_source_port(uint16_t port)
	{
		m_source_port = port;
	}

	uint16_t destination_port() const
	{
		return m_destination_port;
	}
	void set_destination_port(uint16_t port)
	{
		m_destination_port = port;
	}

	uint32_t sequence_number() const
	{
		return m_sequence_number;
	}
	void set_sequence_number(uint32_t number)
	{
		m_sequence_number = number;
	}

	uint32_t ack_number() const
	{
		return m_ack_number;
	}
	void set_ack_number(uint32_t number)
	{
		m_ack_number = number;
	}

	uint16_t flags() const
	{
		return m_flags_and_data_offset & 0x1ff;
	}
	void set_flags(uint16_t flags)
	{
		m_flags_and_data_offset = (m_flags_and_data_offset & ~0x1ff) | (flags & 0x1ff);
	}

	bool has_syn() const
	{
		return flags() & Flag::SYN;
	}
	bool has_ack() const
	{
		return flags() & Flag::ACK;
	}
	bool has_fin() const
	{
		return flags() & Flag::FIN;
	}
	bool has_rst() const
	{
		return flags() & Flag::RST;
	}

	uint8_t data_offset() const
	{
		return (m_flags_and_data_offset & 0xf000) >> 12;
	}
	void set_data_offset(uint16_t data_offset)
	{
		m_flags_and_data_offset = (m_flags_and_data_offset & ~0xf000) | data_offset << 12;
	}

	uint16_t window_size() const
	{
		return m_window_size;
	}
	void set_window_size(uint16_t window_size)
	{
		m_window_size = window_size;
	}

	uint16_t checksum() const
	{
		return m_checksum;
	}
	void set_checksum(uint16_t checksum)
	{
		m_checksum = checksum;
	}

	uint16_t urgent() const
	{
		return m_urgent;
	}
	void set_urgent(uint16_t urgent)
	{
		m_urgent = urgent;
	}

	void const* payload() const
	{
		return ((uint8_t const*)this) + header_size();
	}
	void* payload()
	{
		return ((uint8_t*)this) + header_size();
	}
};

#endif //TCPHEADER_H
