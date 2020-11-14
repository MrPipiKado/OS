#include <stdio.h>
#include <stdlib.h>

long long  factorial(long long  n)
{
    if(n > 1)
    {
        printf("%llu\n", n);
        return n * factorial(n - 1);
    }
    else
        return 1;
}

// kaka factorial
int main(int argc, char* argv[])
{
    long long fac = atoll(argv[1]);
    long long  result = factorial(fac);
    printf("N is %llu \nResult is %llu", fac, result);
    scanf("%llu", &fac);
    return 0;
}