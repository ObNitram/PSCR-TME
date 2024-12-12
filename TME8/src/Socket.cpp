#include "Socket.h"
#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netdb.h>
#include <stdexcept>
#include <unistd.h>

namespace pr
{

void Socket::connect(const std::string &host, const int port)
{
    if (fileDescriptor != -1)
    {
        close();
    }

    // Crée un socket
    fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (fileDescriptor == -1)
    {
        throw std::runtime_error("Failed to create socket");
    }

    // Résolution de l'hôte
    const hostent *hostInfo = gethostbyname(host.c_str());
    if (!hostInfo)
    {
        close();
        throw std::runtime_error("Host resolution failed: " + host);
    }

    // Configuration de l'adresse
    sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    std::memcpy(&serverAddr.sin_addr, hostInfo->h_addr, hostInfo->h_length);

    // Tentative de connexion
    if (::connect(fileDescriptor, reinterpret_cast<sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
    {
        close();
        throw std::runtime_error("Connection to " + host + ":" + std::to_string(port) + " failed");
    }
}

void Socket::connect(in_addr ipv4, int port)
{
    if (fileDescriptor != -1)
    {
        close();
    }

    // Crée un socket
    fileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (fileDescriptor == -1)
    {
        throw std::runtime_error("Failed to create socket");
    }

    // Configuration de l'adresse
    struct sockaddr_in serverAddr = {};
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr = ipv4;

    // Tentative de connexion
    if (::connect(fileDescriptor, reinterpret_cast<struct sockaddr *>(&serverAddr), sizeof(serverAddr)) == -1)
    {
        close();
        throw std::runtime_error("Connection to " + std::string(inet_ntoa(ipv4)) + ":" + std::to_string(port) +
                                 " failed");
    }
}

void Socket::close()
{
    if (fileDescriptor != -1)
    {
        ::close(fileDescriptor);
        fileDescriptor = -1;
    }
}

std::ostream &operator<<(std::ostream &os, const struct sockaddr_in &addr)
{
    char ip[INET_ADDRSTRLEN];
    char hostname[NI_MAXHOST];
    char service[NI_MAXSERV];

    // const char *ip = inet_ntoa(addr.sin_addr); // deprecated so we use inet_ntop

    if (!inet_ntop(AF_INET, &(addr.sin_addr), ip, sizeof(ip)))
    {
        os << "Invalid IP";
        return os;
    }

    // Conversion de la structure sockaddr_in vers sockaddr générique
    const auto *sockAddrPtr = reinterpret_cast<const struct sockaddr *>(&addr);

    // Taille de la structure sockaddr_in
    socklen_t addrLen = sizeof(addr);

    // Appel à getnameinfo pour récupérer le nom d'hôte et le port
    int result = getnameinfo(sockAddrPtr, addrLen, hostname, sizeof(hostname), service, sizeof(service), 0);

    // Vérification du succès ou de l'échec de getnameinfo
    if (result == 0)
    {
        // Succès : Affichage de l'IP, du nom d'hôte et du port
        os << "IP: " << ip << ", Hostname: " << hostname << ", Port: " << ntohs(addr.sin_port);
    }
    else
    {
        // Échec : Affichage de l'IP, [Unknown] pour le nom d'hôte, et le port
        os << "IP: " << ip << ", Hostname: [Unknown]"
           << ", Port: " << ntohs(addr.sin_port);
    }

    return os;
}

} // namespace pr
