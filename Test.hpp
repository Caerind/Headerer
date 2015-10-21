#ifndef TEST_H
#define TEST_H

////////////////////////////////////////////////////////////////////
void afficher()
{
    for (int i = 0; i < 10; i++)
    {
        std::cout << "Hello World" << std::endl;
    }
}

////////////////////////////////////////////////////////////////////
void afficherInt(int const& a)
{
    std::cout << a << std::endl;
}

class Test
{
    public:
        ////////////////////////////////////////////////////////////////////
        Test()
        {
            std::cout << "Hey !" << std::endl;
        }
        ////////////////////////////////////////////////////////////////////
        ~Test()
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

        ////////////////////////////////////////////////////////////////////
        virtual bool testPassed() const
        {
            return true;
        }

    private:
        bool test;
};

#endif // TEST_H
