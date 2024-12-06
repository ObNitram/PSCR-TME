#pragma once

#include <cstring>
#include <semaphore.h>

namespace pr
{

#define STACKSIZE 100

template <typename T> class Stack
{
    T tab[STACKSIZE];
    size_t sz;
    sem_t sem_empty{};
    sem_t sem_full{};

  public:
    Stack() : sz(0)
    {
        memset(tab, 0, sizeof(tab));

        sem_init(&sem_empty, 1, 0);
        sem_init(&sem_full, 1, STACKSIZE);
    }

    ~Stack()
    {
        sem_destroy(&sem_empty);
        sem_destroy(&sem_full);
    }

    T pop()
    {
        // Bloquer si la pile est vide
        sem_wait(&sem_empty);

        // Accéder en toute sécurité à la pile
        T value = tab[--sz];

        // Signaler qu'un espace est disponible
        sem_post(&sem_full);

        return value;
    }

    void push(T elt)
    {
        // Bloquer si la pile est pleine
        sem_wait(&sem_full);

        // Accéder en toute sécurité à la pile
        tab[sz++] = elt;

        // Signaler qu'un élément est disponible
        sem_post(&sem_empty);
    }
};

} // namespace pr
