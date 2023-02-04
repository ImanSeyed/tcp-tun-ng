#include "TCPState.h"

void TCPState::on_packet(const IPv4Header& iph, const TCPHeader& tcph)
{
	const auto dataSize = iph.payload_size() - tcph.header_size();
	switch (m_state)
	{
	case Closed:
		return;
	case Listen:
		if (!tcph.has_syn())
			return;
	}
}