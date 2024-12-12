#pragma once

#include <iosfwd>
#include <netinet/ip.h>
#include <string>

namespace pr
{

class Socket
{
    int fileDescriptor;

  public:
    Socket() : fileDescriptor(-1) {}
    Socket(int fd) : fileDescriptor(fd) {}

    void connect(const std::string &host, int port);
    void connect(in_addr ipv4, int port);

    [[nodiscard]] bool isOpen() const { return fileDescriptor != -1; }
    [[nodiscard]] int getFD() const { return fileDescriptor; }

    void close();
};

std::ostream &operator<<(std::ostream &os, struct sockaddr_in *addr);

} // namespace pr
