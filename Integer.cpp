#include "Integer.h"

void Integer::InitFromString(const char *stevilo)
{
    int i = 0;
    int length = strlen(stevilo);
    int length_excl_minus = length;
    if (stevilo[0] == '-')
    {
        sign = '-';
        length_excl_minus--;
    }
    else
        sign = '+';

    integer.reserve(length_excl_minus); // for better performance

    for (i = 0; i < length_excl_minus; i++)
    {
        // the digits are saved in reverse order,
        // because integers must be aligned with the right most digit for addition
        integer.push_back(stevilo[strlen(stevilo) - 1 - i] - 48);
    }
}

Integer Integer::AdditionHelperFunction(const Integer &ref, char (Integer::*operation)(char, char))
{
    Integer answer(""); // initialize the return value
    Integer first = *this, second = ref;
    int delta_length;
    std::vector<char>::const_iterator itr, end;

    delta_length = first.size() - second.size();
    first.push_back(0);
    second.push_back(0);
    if (delta_length < 0)
    {
        delta_length *= -1;
        for (int i = 0; i < delta_length; i++)
            first.push_back(0);
    }
    else
        for (int i = 0; i < delta_length; i++)
            second.push_back(0);

    int length = first.size();
    answer.integer.reserve(length);

    char carry = 0;
    for (int i = 0; i < length; i++)
    {
        // if it aint broke dont fix it
        answer.push_back((this->*operation)((this->*operation)(first.integer[i], second.integer[i]), carry));
        carry = 0;
        if (answer.back() > 9)
        {
            carry = 1;
            answer.integer.back() -= 10; // back returns a read/write reference to the last element
        }
    }

    if (answer.back() == 0)
        answer.integer.pop_back();

    return answer;
}

char Integer::add(char a, char b)
{
    return a + b;
}
char Integer::subtract(char a, char b)
{
    return a - b;
}

Integer::Integer()
{
    integer.push_back(0);
    sign = '+';
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

Integer::Integer(const Integer &ref)
{
    integer = ref.integer;
    sign = ref.sign;
}

//--------------------------------------------------------------------------------------------
// wrapperji za std::vector funkcije
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
    if ((this->sign == other.sign))
    {
        if (this->sign == '-')
        {
            Integer odgovor = AdditionHelperFunction(other, add);
            odgovor.sign = '-';
            return odgovor;
        }
        return AdditionHelperFunction(other, add);
    }
    if ((this->sign == '+') && (other.sign == '-'))
    {
        Integer temp = other;
        return AdditionHelperFunction(other, subtract);
    }
    if ((this->sign == '-') && (other.sign == '+'))
    {
        Integer temp = *this;
        *this = other;
        temp.sign = '+';
        return AdditionHelperFunction(other, subtract);
    }
    return Integer(112);
}

Integer Integer::operator-(const Integer &other)
{
    Integer temp = other;
    if (temp.sign == '-')
        temp.sign = '+';
    else
        temp.sign = '-';
    return *this + temp;
}

Integer Integer::operator*(Integer const &other)
{
    int i, j, carry, zmnozek;
    Integer answer;
    answer.integer.reserve(this->size() + other.size() + 1);
    Integer pristevek;
    pristevek.integer.reserve(other.size() + 1);
    for (i = 0; i < this->size(); i++) // desna stevilka pri pisnem mnozenju
    {
        pristevek.integer.clear();
        for (j = 0; j < i; j++)
        {
            pristevek.push_back(0);
        }

        carry = 0;

        for (j = 0; j < other.size(); j++) // leva stevilka pri pisnem mnozenju
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

        if (carry > 0)
            pristevek.push_back(carry);

        answer = answer + pristevek;
    }

    if (this->sign == other.sign)
        answer.sign = '+';
    else
        answer.sign = '-';

    return answer;
}

//--------------------------------------------------------------------------------------------
// other
void Integer::print()
{
    if (sign == '-')
        printf("-");
    for (int i = 0; i < integer.size(); i++)
    {
        printf("%c", *(integer.end() - i - 1) + 48);
        if (((integer.size() - i + 2) % 3 == 0) && (i != integer.size() - 1))
            printf("\'");
    }
}