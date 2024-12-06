#include "rsleep.h"
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

int vie = 3;
std::string name;

void defense()
{
    struct sigaction action = {nullptr};
    action.sa_handler = SIG_IGN;
    if (sigaction(SIGINT, &action, nullptr) == -1)
    {
        perror("sigaction");
        _exit(1);
    }
}

void attaque(pid_t adversaire)
{

    waitpid(adversaire, nullptr, WNOHANG);

    struct sigaction action = {nullptr};
    action.sa_handler = [](int)
    {
        vie -= 1;
        std::cout << name << " : Coup reçu ! Points de vie restants : " << vie << std::endl;
        if (vie <= 0)
        {
            std::cout << name << " est mort." << std::endl;
            exit(0);
        }
    };

    if (sigaction(SIGINT, &action, nullptr) == -1)
    {
        perror("sigaction");
        exit(1);
    }

    if (kill(adversaire, SIGINT) == -1)
    {
        std::cout << name << " gagne !\n";
        exit(0);
    }

    std::cout << name << " attaque l'adversaire !\n";
}

[[noreturn]] void combat(pid_t adversaire)
{
    while (true)
    {
        defense();
        randsleep();

        attaque(adversaire);
        randsleep();
    }
}

int main()
{

    pid_t child = fork();

    if (child < 0)
    {
        perror("fork");
        return 1;
    }

    if (child == 0)
    {
        // Luke
        srand(time(nullptr) ^ getpid());

        std::cout << "Luke entre dans le combat !\n";
        name = std::string("Luke");
        combat(getppid());
    }

    // Vador
    srand(time(nullptr) ^ getpid());
    std::cout << "Vador entre dans le combat !\n";
    name = std::string("Vador");
    combat(child);
}
