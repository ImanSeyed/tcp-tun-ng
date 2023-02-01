#include <vector>
#include <cstdint>
#include "Tun.h"
#include "IPv4Header.h"
#include "TCPHeader.h"

int main()
{
	std::vector<uint8_t> buffer(1500);
	IPv4Address ip = IPv4Address(192, 168, 20, 1);
	Tun nic = Tun();
	nic.open();

	nic.set_ip(ip);

	for (;;)
	{
		nic.read(buffer);
	}
}
