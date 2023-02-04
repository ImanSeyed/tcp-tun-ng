#include <vector>
#include <cstdint>
#include <unordered_map>
#include <utility>
#include "Tun.h"
#include "Quad.h"
#include "IPv4Header.h"
#include "TCPState.h"
#include "TCPHeader.h"


int main()
{
	std::vector<uint8_t> buffer(1500);
	std::unordered_map<Quad, TCPState> connections;
	Tun nic = Tun();
	nic.open();

	nic.set_ip(IPv4Address(192, 168, 20, 1), IPv4Address(255, 255, 255, 0));

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
		const auto quad = Quad({ ipv4_packet.source(), tcp_packet.source_port() },
			{ ipv4_packet.destination(), tcp_packet.destination_port() });

		auto connection = connections.find(quad);
		if (connection == connections.end())
			connections.emplace(std::make_pair(quad, TCPState()));
		else
			connection->second
				.on_packet(ipv4_packet, tcp_packet);
	}
}
