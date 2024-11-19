#pragma once

#include <cstring>     // size_t, memset
#include <semaphore.h> // sem_t

namespace pr
{

#define STACKSIZE 100

template <typename T> class Stack
{
    T tab[STACKSIZE];
    size_t sz;
    sem_t sem_empty{}; // Pour contrôler les éléments disponibles
    sem_t sem_full{};  // Pour contrôler l'espace disponible

  public:
    // Constructeur
    Stack() : sz(0)
    {
        memset(tab, 0, sizeof(tab));
        // Initialiser les sémaphores
        sem_init(&sem_empty, 1, 0);        // Commence à 0 (aucun élément disponible)
        sem_init(&sem_full, 1, STACKSIZE); // Commence à STACKSIZE (plein d'espace libre)
    }

    // Destructeur
    ~Stack()
    {
        // Détruire les sémaphores
        sem_destroy(&sem_empty);
        sem_destroy(&sem_full);
    }

    T pop()
    {
        // Bloquer si la pile est vide
        sem_wait(&sem_empty);

        // Accéder en toute sécurité à la pile
        T toret = tab[--sz];

        // Signaler qu'un espace est disponible
        sem_post(&sem_full);

        return toret;
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
