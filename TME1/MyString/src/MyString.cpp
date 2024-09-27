#include "MyString.hpp"

#include <cstring>

namespace pr
{
MyString::MyString(const char *src)
{
    if (src)
    {
        str = new char[strlen(src) + 1];
        strcpy(str, src);
    }
    else { str = nullptr; }
}

MyString::MyString(const MyString &other)
{
    if (other.str)
    {
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    }
    else { str = nullptr; }
}

MyString::MyString(MyString &&other) noexcept : str(other.str) { other.str = nullptr; }

MyString &
MyString::operator=(const MyString &other)
{
    if (this != &other)
    {
        delete[] str; // Libérer l'ancienne mémoire
        str = new char[strlen(other.str) + 1];
        strcpy(str, other.str);
    }
    return *this;
}

MyString &
MyString::operator=(MyString &&other) noexcept
{
    if (this != &other)
    {
        delete[] str; // Libérer l'ancienne mémoire
        str = other.str;
        other.str = nullptr;
    }
    return *this;
}

MyString::~MyString()
{
    delete[] str; // Libérer la mémoire allouée
}
}