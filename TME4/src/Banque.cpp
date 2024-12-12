#include "Banque.h"

#include <iostream>

namespace pr
{

void Banque::transfert(size_t deb, size_t cred, unsigned int val)
{
    Compte &debiteur = comptes[deb];
    Compte &crediteur = comptes[cred];

    if (deb < cred)
    {
        debiteur.getMutex().lock();
        crediteur.getMutex().lock();
    }
    else
    {
        crediteur.getMutex().lock();
        debiteur.getMutex().lock();
    }

    if (debiteur.debiter(val))
    {
        crediteur.crediter(val);
    }

    crediteur.getMutex().unlock();
    debiteur.getMutex().unlock();
}

size_t Banque::size() const { return comptes.size(); }

bool Banque::comptabiliser(int attendu) const
{
    int bilan = 0;
    int id = 0;
    for (const auto &compte : comptes)
    {
        compte.getMutex().lock();
        if (compte.getSolde() < 0)
        {
            std::cout << "Compte " << id << " en négatif : " << compte.getSolde() << std::endl;
        }
        bilan += compte.getSolde();
        id++;
    }
    if (bilan != attendu)
    {
        std::cout << "Bilan comptable faux : attendu " << attendu << " obtenu : " << bilan << std::endl;
    }

    for (const auto &compte : comptes)
    {
        compte.getMutex().unlock();
    }

    return bilan == attendu;
}

} // namespace pr
