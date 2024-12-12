#include "ServerSocket.h"
#include <iostream>
#include <unistd.h>

int main00()
{
    pr::ServerSocket ss(1664);

    while (true)
    {
        pr::Socket sc = ss.accept();

        const int fd = sc.getFD();

        int lu;
        read(fd, &lu, sizeof(int));
        std::cout << "lu =" << lu << std::endl;
        lu++;
        write(fd, &lu, sizeof(int));
        sc.close();
    }
    ss.close();
    return 0;
}

[[noreturn]] int main()
{
    pr::ServerSocket ss(1664);

    while (true)
    {
        pr::Socket sc = ss.accept();

        const int file_descriptor = sc.getFD();

        while (true)
        {
            constexpr ssize_t msz = sizeof(int);
            int lu;
            if (const auto nombre_lu = read(file_descriptor, &lu, msz); nombre_lu == 0)
            {
                std::cout << "Fin connexion par client" << std::endl;
                break;
            }
            else if (nombre_lu < msz)
            {
                perror("read");
                break;
            }
            std::cout << "lu =" << lu << std::endl;

            if (lu == 0)
            {
                break;
            }
            lu++;
            if (write(file_descriptor, &lu, msz) < msz)
            {
                perror("write");
                break;
            }
            std::cout << "envoyé =" << lu << std::endl;
        }
        sc.close();
    }

    ss.close();
    return 0;
}
