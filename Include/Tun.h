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
	void set_ip(IPv4Address ip);
	ssize_t read(std::vector<uint8_t>& buffer) const;
};

#endif //TUN_H
