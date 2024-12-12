#include "Compte.h"

namespace pr
{

void Compte::crediter(unsigned int val)
{
    std::unique_lock g(m);
    solde += val;
}

bool Compte::debiter(unsigned int val)
{
    std::unique_lock g(m);
    bool doit = solde >= val;
    if (doit)
    {
        solde -= val;
    }
    return doit;
}

int Compte::getSolde() const
{
    std::unique_lock g(m);
    return solde;
}

// NB : vector exige Copyable, mais mutex ne l'est pas...
Compte::Compte(const Compte &other)
{
    other.m.lock();
    solde = other.solde;
    other.m.unlock();
}

} // namespace pr
