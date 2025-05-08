#include "Integer.h"

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
    printf("\n");
    int4++;
    int4 = int4 + 1;
    int4++;
    int4.print();

    return 0;
}