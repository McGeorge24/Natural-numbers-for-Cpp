#include <iostream>
#include <vector>
#include <string>
#include <string.h>

class InfiniteInt
{
private:
    // the actual integer is saved in a vector of chars, each representing one digit
    std::vector<char> integer;

public:
    // initialization from char array
    InfiniteInt(const char *stevilo)
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
    };
    InfiniteInt(InfiniteInt &ref)
    {
        integer = ref.integer;
    }

    int size() const
    {
        return integer.size();
    }
    
    // operatorji
    /*InfiniteInt operator++()
    {
    }*/

    InfiniteInt operator+(const InfiniteInt &other)
    {
        InfiniteInt new_int(""); // initialize the return value
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

    InfiniteInt& operator=(const InfiniteInt& other) {
        if (this == &other) {
            return *this; // Handle self-assignment
        }
        return *this; // Return a reference to the current object
    }

    InfiniteInt& operator=(const std::string& other) {
        

        return *this; // Return a reference to the current object
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
    InfiniteInt integer("6574839565");
    InfiniteInt int2("3673895734534");
    integer.print();
    printf("\n+");
    int2.print();
    printf("\n");
    integer = int2 + integer;
    integer.print();
    return 0;
}