#include "Test.h"
#include <iostream>

void afficher()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Hello World" << std::endl;
    }
}

void afficherInt(int const& a)
{
    std::cout << a << std::endl;
}

Test::Test()
{
    std::cout << "Hey !" << std::endl;
}

Test::~Test()
{
    std::cout << "Bye !" << std::endl;
    if (testPassed())
    {
        for (std::size_t i = 0; i < 2; i++)
        {
            std::cout << "testing braces" << std::endl;
        }
    }
}

bool Test::testPassed() const
{
    return true;
}
