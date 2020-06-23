/*

    This program demonstrates loop unrolling
    It is analogous to one of the exampels from the book "Computer Systems: A Programmer's Perspective"

*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

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
    clock_t start1, end1, start2, end2, start3, end3, start4, end4;
    clock_t start5, end5, start6, end6, start7, end7, start8, end8;
    
    const size_t SIZE = 200;
        
    double arr [] = {[0 ... 999999] = 1.00001}; //works only with gcc

    double arr2 [] = {
                        1.1, 2.3, 3,4, 0.6, 1.4, 2.2, 0.02, 2.7, 
                        1.4, 0.4, 2, 0.2, 0.5, 3, 0.01, 0.34, 2, 
                        2.3, 3.4, 5.5, 5.3, 5.4, 7.4, 1.4, 0.77,
                        2.1, 3.4, 1.1, 3.0, 0.4, 0.1, 0.2, 0.9,
                        0.3, 9.2, 4.2, 0.2, 0.3, 2.1, 3.2, 1.01,
                        0.01, 0.2, 2.3, 7.2, 9.1, 0.4, 4.2, 0.3,
                        9.2, 1.3, 8.2, 8.1, 3.1, 9.1, 0.2, 0.02,
                        0.03, 0.1, 9.2, 2.1, 3.4, 9.1, 0.3, 0.2,
                        0.2, 0.3, 0.1, 4.5, 8.2, 9.3, 5.1, 9.0, 
                        0.4, 8.2, 0.1, 9.4, 0.4, 0.3, 8.7, 3.3,
                        5.7, 8.2, 7.3, 0.4, 0.03, 0.2, 9.5, 9.2,
                        0.7, 0.2, 7.2, 5.4, 8.1, 1.3, 3.2, 0.4,
                        1.2, 0.02, 1.2, 0.02, 0.7, 0.2, 7.2, 5.4,
                        1.1, 2.3, 3,4, 0.6, 1.4, 2.2, 0.02, 2.7, 
                        1.4, 0.4, 2, 0.2, 0.5, 3, 0.01, 0.34, 2, 
                        2.3, 3.4, 5.5, 5.3, 5.4, 7.4, 1.4, 0.77,
                        2.1, 3.4, 1.1, 3.0, 0.4, 0.1, 0.2, 0.9,
                        0.3, 9.2, 4.2, 0.2, 0.3, 2.1, 3.2, 1.01,
                        0.01, 0.2, 2.3, 7.2, 9.1, 0.4, 4.2, 0.3,
                        9.2, 1.3, 8.2, 8.1, 3.1, 9.1, 0.2, 0.02,
                        0.03, 0.1, 9.2, 2.1, 3.4, 9.1, 0.3, 0.2,
                        0.2, 0.3, 0.1, 4.5, 8.2, 9.3, 5.1, 9.0, 
                        0.4, 8.2, 0.1, 9.4, 0.4, 0.3, 8.7, 3.3,
                        5.7, 8.2, 7.3, 0.4, 0.03, 0.2, 9.5, 9.2,
                        8.1, 1.3, 3.2, 0.4   
                     };

    printf("Calling functions with first set of data: \n");
    start1 = clock();
    mult(arr, 1000000);
    end1 = clock();
    printf("the number of clock ticks elapsed for function with NO loop unrolling - %li\n", end1 - start1);
    
    start2 = clock();
    multWithLoopUnrolling(arr, 1000000);
    end2 = clock();
    printf("the number of clock ticks elapsed for function with loop unrolling   - %li\n", end2 - start2);

    start3 = clock();
    mult(arr, 1000000);
    end3 = clock();
    printf("the number of clock ticks elapsed for function with NO loop unrolling - %li  (second check)\n", end3 - start3); 

    start4 = clock();
    multWithLoopUnrolling(arr, 1000000);
    end4 = clock();
    printf("the number of clock ticks elapsed for function with loop unrolling   - %li  (second check)\n", end4 - start4);  
    
    
    printf("\nCalling functions with another set of data: \n");
    start5 = clock();
    mult(arr2, SIZE);
    end5 = clock();
    printf("the number of clock ticks elapsed for function with NO loop unrolling - %li\n", end5 - start5);    

    start6 = clock();
    multWithLoopUnrolling(arr2, SIZE);
    end6 = clock();
    printf("the number of clock ticks elapsed for function with loop unrolling - %li\n", end6 - start6);  

    start7 = clock();
    mult(arr2, SIZE);
    end7 = clock();
    printf("the number of clock ticks elapsed for function with NO loop unrolling - %li (second check)\n", end7 - start7);    

    start8 = clock();
    multWithLoopUnrolling(arr2, SIZE);
    end8 = clock();
    printf("the number of clock ticks elapsed for function with loop unrolling - %li (second check)\n", end8 - start8);         
    
    return 0;
}