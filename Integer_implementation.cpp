#include "Integer.h"

void Integer::InitFromString(const char *stevilo)
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

Integer::Integer()
{
    integer.push_back(0);
}

Integer::Integer(const char *stevilo)
{
    InitFromString(stevilo);
};

Integer::Integer(const long long int stevilo)
{
    char buffer[20]; // mislim da je max velikost inta okoli 10^18
    sprintf(buffer, "%lld", stevilo);
    InitFromString(buffer);
};

Integer::Integer(Integer &ref)
{
    integer = ref.integer;
}

//--------------------------------------------------------------------------------------------

int Integer::size() const
{
    return integer.size();
}

void Integer::push_back(int stevka)
{
    integer.push_back(stevka);
}

char Integer::back()
{
    return integer.back();
}

//--------------------------------------------------------------------------------------------
// operatorji

Integer Integer::operator++(int)
{
    // tuki mi je mogu pomagat AI, nevem kako ne razumem kako deluje ta operator
    Integer temp = *this; // Save the current value
    Integer int1("1");
    *this = *this + int1; // Increment the current object
    return temp;          // Return the original value
}

Integer Integer::operator+(const Integer &other)
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

    // coppying the rest of the bigger int and adding the carry
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

Integer Integer::operator*(Integer const &other)
{
    int i, j, carry, zmnozek;
    Integer answer;
    answer.integer.reserve(this->size() + other.size() + 1);
    Integer pristevek;
    pristevek.integer.reserve(other.size() + 1);
    for (i = 0; i < this->size(); i++) // desna stevilka pri pisnem sestevanju
    {
        pristevek.integer.clear();
        for (j = 0; j < i; j++)
        {
            pristevek.push_back(0);
        }

        carry = 0;

        for (j = 0; j < other.size(); j++) // leva stevilka pri pisnem sestevanju
        {
            zmnozek = this->integer[i] * other.integer[j] + carry;
            if (zmnozek > 9)
            {
                carry = zmnozek / 10;
                zmnozek = zmnozek % 10;
            }
            else
                carry = 0;
            pristevek.push_back(zmnozek);
        }

        answer = answer + pristevek;
    }
    return answer;
}

//--------------------------------------------------------------------------------------------
// other
void Integer::print()
{
    for (int i = 0; i < integer.size(); i++)
    {
        printf("%c", *(integer.end() - i - 1) + 48);
    }
}