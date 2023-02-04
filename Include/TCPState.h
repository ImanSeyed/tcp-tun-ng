#ifndef TCPSTATE_H
#define TCPSTATE_H

#include <cstdint>
#include <vector>
#include "IPv4Header.h"
#include "TCPHeader.h"

class TCPState
{
private:
	enum State
	{
		Closed,
		Listen,
		SynRecv,
		Estab,
	};

	State m_state{ Listen };
public:
	constexpr TCPState()
	{
	}

	void on_packet(const IPv4Header& iph, const TCPHeader& tcph);
	operator State() const
	{
		return m_state;
	}
	TCPState& operator=(const State state)
	{
		m_state = state;
		return *this;
	}
	bool operator==(const State state) const
	{
		return m_state == state;
	}
	bool operator!=(const State state) const
	{
		return m_state != state;
	}
};

#endif //TCPSTATE_H
