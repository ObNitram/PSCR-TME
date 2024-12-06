#include "src/ServerSocket.h"
#include <arpa/inet.h>
#include <stdexcept>
#include <unistd.h>

namespace pr
{

ServerSocket::ServerSocket(const int port) : socketfd(-1)
{
    // Création du socket
    socketfd = socket(AF_INET, SOCK_STREAM, 0);
    if (socketfd == -1)
    {
        throw std::runtime_error("Failed to create socket");
    }

    // Configuration de l'adresse
    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY; // Écoute sur toutes les interfaces

    // Réutilisation de l'adresse (pour éviter "Address already in use")
    constexpr int opt = 1;
    if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1)
    {
        close();
        throw std::runtime_error("Failed to set socket options");
    }

    // Liaison du socket à l'adresse et au port
    if (bind(socketfd, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
    {
        close();
        throw std::runtime_error("Failed to bind socket to port " + std::to_string(port));
    }

    // Mise en écoute
    if (listen(socketfd, SOMAXCONN) == -1)
    {
        close();
        throw std::runtime_error("Failed to listen on socket");
    }
}

Socket ServerSocket::accept() const
{
    struct sockaddr_in clientAddr = {};
    socklen_t clientAddrLen = sizeof(clientAddr);

    // Acceptation d'une connexion
    int clientSocket = ::accept(socketfd, reinterpret_cast<struct sockaddr *>(&clientAddr), &clientAddrLen);
    if (clientSocket == -1)
    {
        throw std::runtime_error("Failed to accept connection");
    }

    // Création d'un objet Socket avec le descripteur du client
    return {clientSocket};
}

void ServerSocket::close()
{
    if (socketfd != -1)
    {
        ::close(socketfd);
        socketfd = -1;
    }
}

} // namespace pr
