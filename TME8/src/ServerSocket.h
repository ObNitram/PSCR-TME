#pragma once

#include "Socket.h"

namespace pr
{

class ServerSocket
{
    int socketfd;

  public:
    ServerSocket(int port);

    [[nodiscard]] int getFD() const { return socketfd; }
    [[nodiscard]] bool isOpen() const { return socketfd != -1; }

    [[nodiscard]] Socket accept() const;

    void close();
};

} // namespace pr
