#pragma once

#include <cstring>
#include <semaphore.h>

namespace pr
{

#define STACKSIZE 100

template <typename T>
class Stack
{
    T tab[STACKSIZE];
    size_t sz;
    sem_t sem_empty{};
    sem_t sem_full{};
    sem_t sem_size{};

  public:
    Stack() : sz(0)
    {
        memset(tab, 0, sizeof(tab));

        sem_init(&sem_empty, 1, 0);
        sem_init(&sem_full, 1, STACKSIZE);
        sem_init(&sem_size, 1, 1);
    }

    ~Stack()
    {
        sem_destroy(&sem_empty);
        sem_destroy(&sem_full);
        sem_destroy(&sem_size);
    }

    T pop()
    {
        // Bloquer si la pile est vide
        sem_wait(&sem_empty);

        // Protéger l'accès à la taille
        sem_wait(&sem_size);
        T value = tab[--sz];
        sem_post(&sem_size);

        // Signaler qu'un espace est disponible
        sem_post(&sem_full);

        return value;
    }

    void push(T elt)
    {
        // Bloquer si la pile est pleine
        sem_wait(&sem_full);

        // Protéger l'accès à la taille
        sem_wait(&sem_size);
        tab[sz++] = elt;
        sem_post(&sem_size);

        // Signaler qu'un élément est disponible
        sem_post(&sem_empty);
    }

    size_t size() const
    {
        // Obtenir une copie sûre de la taille
        sem_wait(const_cast<sem_t*>(&sem_size));
        size_t current_size = sz;
        sem_post(const_cast<sem_t*>(&sem_size));
        return current_size;
    }
};

} // namespace pr
