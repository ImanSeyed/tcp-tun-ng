#ifndef TUN_H
#define TUN_H

#include <string>
#include <linux/if.h>
#include <linux/if_tun.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <fmt/core.h>
#include <vector>
#include "IPv4Address.h"
#include "IPv4Header.h"

class Tun
{
private:
	std::string m_devname{ "tun0" };
	int m_fd{ -1 };
	struct ifreq ifr{};

public:
	constexpr Tun() = default;

	constexpr Tun(const std::string& devname)
		: m_devname(devname)
	{
	}

	int open(bool without_packet_info = true);
	int close();
	void set_ip(IPv4Address ip, IPv4Address subnet);
	void fill_in_ipv4_header(IPv4Header& iph,
		const IPv4Address& source_ipv4,
		const IPv4Address& destination_ipv4,
		size_t payload_size,
		uint8_t type_of_service,
		uint8_t ttl) const;
	ssize_t read(std::vector<uint8_t>& buffer) const;
	ssize_t write(std::vector<uint8_t>& buffer) const;
};

#endif //TUN_H
