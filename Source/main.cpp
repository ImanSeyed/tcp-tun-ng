#include <vector>
#include <cstdint>
#include <map>
#include <utility>
#include "Tun.h"
#include "IPv4Header.h"
#include "TCPState.h"
#include "TCPHeader.h"

struct Quad {
	std::pair<IPv4Address, uint16_t> source;
	std::pair<IPv4Address, uint16_t> destination;
};

int main()
{
	std::vector<uint8_t> buffer(1500);
	std::map<Quad, TCPState> connections;
	Tun nic = Tun();
	nic.open();

	nic.set_ip(IPv4Address(192, 168, 20, 1));

	for (;;)
	{
		nic.read(buffer);

		/* Ignore everything except IPv4 packets */
		if (buffer[0] < 0x45 || buffer[0] > 0x4f)
			continue;

		const auto& ipv4_packet = *(IPv4Header const*)(buffer.data());

		/* Ignore everything except TCP packets */
		if (ipv4_packet.protocol() != 0x06)
			continue;

		const auto& tcp_packet = *static_cast<TCPHeader const*>(ipv4_packet.payload());
	}
}
