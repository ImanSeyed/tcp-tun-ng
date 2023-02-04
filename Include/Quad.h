#ifndef QUAD_H
#define QUAD_H

#include <utility>
#include <cstdint>
#include "IPv4Address.h"

class Quad
{
private:
	std::pair<IPv4Address, uint16_t> m_src;
	std::pair<IPv4Address, uint16_t> m_dst;

public:
	constexpr Quad(std::pair<IPv4Address, uint16_t> src, std::pair<IPv4Address, uint16_t> dst)
		: m_src(src), m_dst(dst)
	{
	}

	constexpr IPv4Address getSourceIP() const
	{
		return m_src.first;
	}
	constexpr uint16_t getDestinationPort() const
	{
		return m_dst.second;
	}

	constexpr IPv4Address getDestinationIP() const
	{
		return m_dst.first;
	}
	constexpr uint16_t getSourcePort() const
	{
		return m_src.second;
	}

	constexpr auto getSource() const
	{
		return m_src;
	}
	constexpr auto getDestination() const
	{
		return m_dst;
	}

	friend bool operator==(const Quad& q1, const Quad& q2)
	{
		return (q1.m_src == q2.m_src) && (q1.m_dst == q2.m_dst);
	}
};

namespace std
{
	template<>
	struct hash<Quad>
	{
		std::size_t operator()(const Quad& k) const
		{
			using std::hash;
			uint32_t f0 = k.getSourceIP().to_bytes();
			uint32_t f1 = k.getDestinationIP().to_bytes();
			uint32_t f2 = (k.getSourcePort() << 16) | k.getDestinationPort();

			return ((hash<uint32_t>()(f0)
				^ (hash<uint32_t>()(f1) << 1)) >> 1)
				^ (hash<uint32_t>()(f2) << 1);
		}
	};
}

#endif //QUAD_H
