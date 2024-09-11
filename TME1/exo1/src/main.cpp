#include "List.h"
#include <string>
#include <iostream>
#include <cstring>

int main()
{
    std::string abc = "abc";
    char* str = new char [4];
    str[0] = 'a';
    str[1] = 'b';
    str[2] = 'c';

    //FAUTE : Need to add the \0 char to use strcmp
    str[3] = '\0';

    if (0 == strcmp(str, abc.c_str()))
    {
        std::cout << "Equal !" << std::endl; // ADD endl
    }

    pr::List list;
    list.push_front(abc);
    list.push_front(abc);

    std::cout << "Liste : " << list << std::endl;
    std::cout << "Taille : " << list.size() << std::endl;

    int i = 0;
    // Affiche à l'envers
    for (i = static_cast<int>(list.size()) - 1; i >= 0; i--)
    {
        std::cout << "elt " << i << ": " << list[i] << std::endl;
    }

    //FAUTE : no need to free the char, it's handle by the List destructor
    /*
    // liberer les char de la chaine
    for (char* cp = str; *cp; cp++)
    {
        delete cp;
    }
    */

    // et la chaine elle meme
    //FAUTE : We need tu use delete[] because we use new[], it's an array !
    delete[] str;
}
