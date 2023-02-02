#include "Tun.h"

int Tun::open(bool without_packet_info)
{
	if ((m_fd = ::open("/dev/net/tun", O_RDWR)) == -1)
	{
		perror("open /dev/net/tun");
		_exit(1);
	}

	std::fill_n(reinterpret_cast<char*>(&ifr), sizeof(ifr), 0);
	ifr.ifr_flags = (without_packet_info) ? IFF_TUN | IFF_NO_PI : IFF_TUN;
	m_devname.copy(ifr.ifr_name, IFNAMSIZ);

	if (ioctl(m_fd, TUNSETIFF, &ifr) == -1)
	{
		perror("ioctl TUNSETIFF");
		::close(m_fd);
		_exit(1);
	}

	return m_fd;
}

void Tun::set_ip(IPv4Address ip, IPv4Address subnet)
{
	assert(m_fd != -1 && !ip.is_zero() && !subnet.is_zero());

	int sockfd{ -1 };
	struct sockaddr_in* addr = (struct sockaddr_in*)&ifr.ifr_addr;

	ifr.ifr_addr.sa_family = AF_INET;

	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
	{
		perror("set_ip create socket");
		return;
	}

	inet_pton(AF_INET, ip.to_string().c_str(), &addr->sin_addr);
	if (ioctl(sockfd, SIOCSIFADDR, (void*)&ifr) == -1)
	{
		perror("ioctl SIOCSIFADDR");
		return;
	}

	inet_pton(AF_INET, subnet.to_string().c_str(), &addr->sin_addr);
	if (ioctl(sockfd, SIOCSIFNETMASK, &ifr) == -1)
	{
		perror("ioctl SIOCSIFNETMASK");
		return;
	}

	ifr.ifr_flags |= (IFF_UP | IFF_RUNNING);
	if (ioctl(sockfd, SIOCSIFFLAGS, &ifr) == -1)
	{
		perror("ioctl SIOCSIFFLAGS");
		return;
	}
}

int Tun::close()
{
	int result{ ::close(m_fd) };
	m_fd = -1;
	return result;
}

ssize_t Tun::read(std::vector<uint8_t>& buffer) const
{
	return ::read(m_fd, buffer.data(), buffer.size());
}
