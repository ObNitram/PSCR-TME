#include <iostream>
#include "src/MyString.hpp"

int main()
{
    // Test 1: Création d'une chaîne à partir d'une chaîne littérale
    {
        pr::MyString str1("Hello, World!");
        std::cout << "Test 1: " << str1 << std::endl;
    }

    // Test 2: Création d'une chaîne vide
    {
        pr::MyString str2("");
        std::cout << "Test 2: " << str2 << std::endl;
    }

    // Test 3: Création d'une chaîne à partir de nullptr
    {
        pr::MyString str3(nullptr);
        std::cout << "Test 3: " << str3 << std::endl;
    }

    // Test 4: Constructeur de copie
    {
        pr::MyString str4("Copy Test");
        pr::MyString str5(str4);
        std::cout << "Test 4 (copie): " << str4 << str5 << std::endl;
    }

    // Test 5: Test d'auto-assignation
    {
        pr::MyString str6("Auto-assign");
        str6 = str6;
        std::cout << "Test 5 (auto-assignation): " << str6 << std::endl;
    }

    // Test 6: Affectation de chaîne
    {
        pr::MyString str7("Original");
        pr::MyString str8("New");
        str7 = str8;
        std::cout << "Test 6 (affectation): " << str7 << std::endl;
    }

    // Test 7: Constructeur de déplacement
    {
        pr::MyString str9("Move Test");
        pr::MyString str10(std::move(str9));
        std::cout << "Test 7 (déplacement): " << str10 << std::endl;
        std::cout << "Test 7 (après déplacement de str9): " << str9 <<
            std::endl;
    }

    // Test 8: Affectation par déplacement
    {
        pr::MyString str11("Temporary");
        pr::MyString str12("Move Assign");
        str11 = std::move(str12);
        std::cout << "Test 8 (affectation par déplacement): " << str11 <<
            std::endl;
    }

    // Test 9: Libération de mémoire après destruction
    {
        pr::MyString str13("Should be released");
        std::cout << "Test 9 (dans le bloc): " << str13 << std::endl;
    }
    std::cout << "Test 9 (après le bloc): Aucun accès à str13" << std::endl;

    // Test 10: Vérification de la chaîne nulle dans le constructeur
    {
        pr::MyString str14(nullptr);
        std::cout << "Test 10: " << str14 << std::endl;
    }

    // Test 11: Vérification d'une chaîne vide après copie
    {
        pr::MyString str15("");
        pr::MyString str16(str15);
        std::cout << "Test 11: " << str16 << std::endl;
    }

    // Test 12: Affectation d'une chaîne vide
    {
        pr::MyString str17("");
        pr::MyString str18("Non-empty");
        str17 = str18;
        std::cout << "Test 12: " << str17 << std::endl;
    }

    // Test 13: Test d'auto-assignation sur une chaîne vide
    {
        pr::MyString str19("");
        str19 = str19;
        std::cout << "Test 13 (auto-assignation sur une chaîne vide): " << str19
            << std::endl;
    }

    // Test 14: Test d'auto-assignation sur une chaîne non vide
    {
        pr::MyString str20("Non-empty");
        str20 = str20;
        std::cout << "Test 14 (auto-assignation sur une chaîne non vide): " <<
            str20 << std::endl;
    }

    // Test 15: Déplacement d'une chaîne vide
    {
        pr::MyString str21("Source");
        pr::MyString str22 = std::move(str21);
        std::cout << "Test 15 (déplacement de str22): " << str22 << std::endl;
        std::cout << "Test 15 (après déplacement de str21): " << str21 <<
            std::endl;
    }

    // Test 16: Affectation avec une chaîne vide
    {
        pr::MyString str23("");
        str23 = "Filled";
        std::cout << "Test 16: " << str23 << std::endl;
    }

    // Test 17: Affectation avec une chaîne nulle
    {
        pr::MyString str24(nullptr);
        str24 = "Assigned";
        std::cout << "Test 17: " << str24 << std::endl;
    }

    // Test 18: Vérification de la chaîne après destruction
    {
        pr::MyString str25("Temp");
        std::cout << "Test 18 (dans le bloc): " << str25 << std::endl;
    }
    std::cout << "Test 18 (après le bloc): Aucun accès à str25" << std::endl;

    // Test 19: Réassignation après déplacement
    {
        pr::MyString str26("First");
        pr::MyString str27("Second");
        str26 = std::move(str27);
        std::cout << "Test 19: " << str26 << std::endl;
    }

    // Test 20: Copie d'une chaîne contenant des espaces
    {
        pr::MyString str28("Hello World with spaces");
        pr::MyString str29(str28);
        std::cout << "Test 20: " << str29 << std::endl;
    }

    // Tests 21 à 50 : répétition avec différentes chaînes
    const char *testStrings[] = {
        "String 1", "String 2", "String 3", "String 4", "String 5",
        "String 6", "String 7", "String 8", "String 9", "String 10",
        "String 11", "String 12", "String 13", "String 14", "String 15",
        "String 16", "String 17", "String 18", "String 19", "String 20",
        "String 21", "String 22", "String 23", "String 24", "String 25",
        "String 26", "String 27", "String 28", "String 29", "String 30",
        "String 31", "String 32", "String 33", "String 34", "String 35",
        "String 36", "String 37", "String 38", "String 39", "String 40",
        "String 41", "String 42", "String 43", "String 44", "String 45",
        "String 46", "String 47", "String 48", "String 49", "String 50"
    };

    for (int i = 0; i < 50; ++i)
    {
        {
            pr::MyString testStr(testStrings[i]);
            std::cout << "Test " << (21 + i) << ": " << testStr << std::endl;
        }
    }

    return 0;
}