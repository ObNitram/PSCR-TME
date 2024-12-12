//FAUTE : need to include List.h

#include "List.h"

namespace pr
{
    // ******************* Chainon
    Chainon::Chainon(const std::string& data, Chainon* next): data(data), next(next)
    {
    };

    size_t Chainon::length()
    {
        size_t len = 1;
        if (next != nullptr)
        {
            len += next->length();
        }

        //FAUTE : must return len
        return len;
    }

    //FAUTE : need to add const like in List.h
    void Chainon::print(std::ostream& os) const
    {
        os << data;
        if (next != nullptr)
        {
            os << ", ";

            //FAUTE : need to be inside if
            next->print(os);
        }
    }

    // ******************  List
    const std::string& List::operator[](size_t index) const
    {
        Chainon* it = tete;
        for (size_t i = 0; i < index; i++)
        {
            it = it->next;
        }
        return it->data;
    }

    void List::push_back(const std::string& val)
    {
        if (tete == nullptr)
        {
            tete = new Chainon(val);
        }
        else
        {
            Chainon* fin = tete;
            while (fin->next)
            {
                fin = fin->next;
            }
            fin->next = new Chainon(val);
        }
    }

    void List::push_front(const std::string& val)
    {
        tete = new Chainon(val, tete);
    }

    //FAUTE : It's missing  List::
    bool List::empty()
    {
        return tete == nullptr;
    }

    size_t List::size() const
    {
        if (tete == nullptr)
        {
            return 0;
        }
        else
        {
            return tete->length();
        }
    }

    //FAUTE : operator need to be in pr namespace
    std::ostream& operator<<(std::ostream& os, const pr::List& vec)
    {
        os << "[";
        if (vec.tete != nullptr)
        {
            vec.tete->print(os);
        }
        os << "]";
        return os;
    }
} // namespace pr

