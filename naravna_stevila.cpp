#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <stdio.h>

class Integer
{
private:
    // the actual integer is saved in a vector of chars, each representing one digit
    std::vector<char> integer;

    void InitFromString(const char *stevilo)
    {
        int i = 0;
        int length = strlen(stevilo);
        integer.reserve(length); // for better performance

        for (i = 0; i < length; i++)
        {
            // the digits are saved in reverse order,
            // because integers must be aligned with the right most digit for addition
            integer.push_back(stevilo[length - 1 - i] - 48);
        }
    }

public:
    // initialization from char array
    Integer()
    {
        integer.push_back(0);
    }

    Integer(const char *stevilo)
    {
        InitFromString(stevilo);
    };

    Integer(const int stevilo)
    {
        char buffer[20]; // mislim da je max velikost inta okoli 10^18
        sprintf(buffer, "%d", stevilo);
        InitFromString(buffer);
    };

    Integer(Integer &ref)
    {
        integer = ref.integer;
    }

    int size() const
    {
        return integer.size();
    }

    // operatorji
    Integer operator++(int)
    {
        Integer temp = *this;
        Integer int1("1");
        temp = temp + int1;
        return temp;
    }

    Integer operator+(const Integer &other)
    {
        Integer new_int(""); // initialize the return value
        int min_length, max_length;
        std::vector<char>::const_iterator itr, end;
        // copy from ITR to END from the bigger integer to the new_integer and push back carry

        if (this->size() > other.size()) // determine which is larger and reserve space for better performance
        {
            new_int.integer.reserve(this->size() + 1);
            min_length = other.size();
            itr = this->integer.begin() + min_length; // after the addition comes copying
            end = this->integer.end();
        }
        else
        {
            new_int.integer.reserve(other.integer.size() + 1);
            min_length = this->integer.size();
            itr = other.integer.begin() + min_length; // after the addition comes copying
            end = other.integer.end();
        }

        char carry = 0;

        for (int i = 0; i < min_length; i++)
        {
            new_int.integer.push_back(this->integer[i] + other.integer[i] + carry);
            carry = 0;
            if (new_int.integer.back() > 9)
            {
                carry = new_int.integer.back() / 10;
                new_int.integer.back() -= 10;
            }
        }

        // coppying the rest of the bigger int and addung the carry
        for (itr; itr < end; itr++)
        {
            new_int.integer.push_back(*itr + carry);
            carry = 0;
            if (new_int.integer.back() > 9)
            {
                carry = new_int.integer.back() % 10;
                new_int.integer.back() -= 10;
            }
        }
        if (carry > 0)
            new_int.integer.push_back(carry);

        return new_int;
    }

    Integer operator*(Integer const& other)
    {
        return Integer(1);
    }

    /*
        Integer& operator=(const std::string& string) {
            Integer temp(string.c_str());
            *this = temp;
            return *this; // Return a reference to the current object
        }

        Integer& operator=(const int& integer) {
            char buffer[20];
            sprintf(buffer, "%d", integer);
            Integer temp(buffer);
            *this = temp;
            return *this; // Return a reference to the current object
        }
    */
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
    Integer integer("6574839565");
    Integer int2("3673895734534");
    integer.print();
    printf("\n+");
    int2.print();
    printf("\n");
    integer = integer + int2;
    integer.print();
    printf("\n");
    integer++;
    integer.print();
    printf("\n----------------\n");
    Integer int3 = "123";
    int3.print();
    printf("\n----------------\n");
    Integer int4;
    int4.print();
    printf("\n");
    int4 = 456;
    int4.print();
    printf("\n");
    int4 = int4 * int3;
    int4.print();
    return 0;
}