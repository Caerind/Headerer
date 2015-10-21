#ifndef TEST_H
#define TEST_H

void afficher();

void afficherInt(int const& a);

class Test
{
    public:
        Test();
        ~Test();

        virtual bool testPassed() const;

    private:
        bool test;
};

#endif // TEST_H
