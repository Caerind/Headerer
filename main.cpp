#include <iostream>

#include "Headerer.hpp"

int main()
{
    Headerer h(false);
    /*
    std::cout << "Entrez le nom du header : ";
    std::string header;
    std::cin >> header;
    std::cout << "Entrez le nom de l'implementation : ";
    std::string impl;
    std::cin >> impl;
    std::cout << "Entrez le nom du header final : ";
    std::string output;
    std::cin >> output;
    */
    std::string header = "Test.h", impl = "Test.cpp", output = "Test.hpp";
    if (h.create(header,impl,output))
    {
        std::cout << "Fichier genere avec succes !" << std::endl;
    }
    else
    {
        std::cerr << "Erreur" << std::endl;
    }
    return 0;
}
