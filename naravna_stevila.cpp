#include <iostream>
#include <vector>
#include <string>
#include <string.h>

class NaturalInt
{
private:
    std::vector<char> integer;

public:
    NaturalInt(const char *stevilo)
    {
        int i = 0;
        int length = strlen(stevilo);
        integer.reserve(length);
        for (i = 0; i < length; i++)
        {
            integer.push_back(stevilo[length - 1 - i] - 48);
        }
    };
    NaturalInt(NaturalInt &ref)
    {
        integer = ref.integer;
    }

    // operatorji
    /*NaturalInt operator++()
    {
    }*/

    NaturalInt operator+(const NaturalInt &other)
    {
        NaturalInt new_int("");
        int min_length;
        bool bigger_integer;
        if (this->integer.size() > other.integer.size())
        {
            new_int.integer.reserve(this->integer.size() + 1);
            bigger_integer = true;
            min_length = other.integer.size();
        }
        else
        {
            new_int.integer.reserve(other.integer.size() + 1);
            bigger_integer = false;
            min_length = this->integer.size();
        }

        int carry = 0;
        ;
        for (int i = 0; i < min_length; i++)
        {
            new_int.integer.push_back(this->integer[i] + other.integer[i] + carry);
            if (new_int.integer.back() > 9)
            {
                carry = new_int.integer.back() - 9;
                new_int.integer.back() = new_int.integer.back() % 10;
            }
        }
        if (bigger_integer)
        {
            for (int i = min_length; i < this->integer.size(); i++)
            {
                new_int.integer.push_back(this->integer[i] + carry);
                if (new_int.integer.back() > 9)
                {
                    carry = new_int.integer.back() - 9;
                    new_int.integer.back() = new_int.integer.back() % 10;
                }
            }
        }
        else
        {
            for (int i = min_length; i < other.integer.size(); i++)
            {
                new_int.integer.push_back(other.integer[i] + carry);
                if (new_int.integer.back() > 9)
                {
                    carry = new_int.integer.back() - 9;
                    new_int.integer.back() = new_int.integer.back() % 10;
                }
            }
        }

        return new_int;
    }

    void print()
    {
        for (int i = 0; i < integer.size(); i++)
        {
            printf("%c", *(integer.end() - i - 1) + 48);
        }
    }
};

int main()
{
    NaturalInt integer("1234567890123456789012345678901234567890");
    NaturalInt int2("1234567890123456789012345678901234567890");
    integer = int2 + integer;
    integer.print();
    printf("\n");
    int2.print();
    return 0;
}