/*

    This program demonstrates loop unrolling
    It is analogous to one of the exampels from the book "Computer Systems: A Programmer's Perspective"

*/
#include<stdio.h>
#include<stdlib.h>

//function for computing the product of an array of n double-precision numbers
//NO loop unrolling
double mult(const double a[], const size_t size)
{
    size_t i;
    double result = 1;

    for (i = 0; i < size; i++)
    {
        result *= a[i];
    }

    return result;
}

//function for computing the product of an array of n double-precision numbers
//utilizing 3x loop unrolling
double multWithLoopUnrolling(const double a[], const size_t size)
{
    size_t i;
    double x, y, z;
    double result = 1;

    for (i = 0; i < size-2; i+= 3)
    {
        x = a[i];
        y = a[i+1];
        z = a[i+2];
        result = result * x * y * z; 
    }

    for (;i < size; i++)
        result *= a[i];

    return result;
}

int main ()
{
    const size_t SIZE = 40;
    
    double arr [] = {
                        1.1, 2.3, 3,4, 0.6, 1.4, 2.2, 0.02, 2.7, 
                        1.4, 0.4, 2, 0.2, 0.5, 3, 0.01, 0.34, 2, 
                        2.3, 3.4, 5.5, 5.3, 5.4, 7.4, 1.4, 0.77,
                        2.1, 3.4, 1.1, 3.0, 0.4, 0.1, 0.2, 0.9,
                        0.3, 9.2, 4.2, 0.2, 0.3, 2.1, 3.2
                     };

    
    double arr2 [] = {[0 ... 999999] = 1.00001}; //works only with gcc

    printf("the result is %f\n", multWithLoopUnrolling(arr2, 1000000));

    return 0;
}