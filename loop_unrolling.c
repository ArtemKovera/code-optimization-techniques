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
double multWithLoop3xUnrolling(const double a[], const size_t size)
{
    size_t i, s;
    s = size - 2;
    double x, y, z;
    double result = 1;
    

    for (i = 0; i < s; i+= 3)
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

//function for computing the product of an array of n double-precision numbers
//utilizing 5x loop unrolling
double multiplyWith5xLoopUnrolling(const double array[], const size_t size)
{
    size_t i, s;
    s = size - 4;
    double a, b, c, d, e;
    double result = 1;

    for(i = 0; i < s; i += 5)
    {
        a = array[i];
        b = array[i+1];
        c = array[i+2];
        d = array[i+3];
        e = array[i+4];

        result = result * a * b * c * d * e;
    }

    for(; i < size; i++)
    {
        result *= array[i];
    }

    return result;
}

int main ()
{
    struct timespec start1, end1, start2, end2, start3, end3, start4, end4;
    struct timespec start3x1, end3x1, start3x2, end3x2, start3x3, end3x3, start3x4, end3x4;
    struct timespec start5x1, end5x1, start5x2, end5x2, start5x3, end5x3, start5x4, end5x4;  

    double tdiff1, tdiff2, tdiff3, tdiff4, tdiff3x1, tdiff3x2, tdiff3x3, tdiff3x4,
    tdiff5x1, tdiff5x2, tdiff5x3, tdiff5x4;

    double result;

    const size_t SIZE = 1000000;
    const size_t SIZE2 = 1000;
        
    static double arr [] = {[0 ... 999999] = 1.00001}; //works only with gcc

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
                        8.1, 1.3, 3.2, 0.4, 1.1, 2.3, 3,4, 0.6,
                        1.4, 0.4, 2, 0.2, 0.5, 3, 0.01, 0.34, 2, 
                        2.3, 3.4, 5.5, 5.3, 5.4, 7.4, 1.4, 0.77,
                        2.1, 3.4, 1.1, 3.0, 0.4, 0.1, 0.2, 0.9,
                        0.3, 9.2, 4.2, 0.2, 0.3, 2.1, 3.2, 1.01,
                        0.01, 0.2, 2.3, 7.2, 9.1, 0.4, 4.2, 0.3,
                        9.2, 1.3, 3.2, 8.1, 3.1, 9.1, 0.2, 0.02,
                        0.03, 0.1, 9.2, 2.1, 3.4, 9.1, 0.3, 0.2,
                        0.2, 0.3, 0.1, 4.5, 8.2, 9.3, 5.1, 9.0, 
                        0.4, 8.2, 0.1, 9.4, 0.4, 0.3, 8.7, 3.3,
                        5.7, 8.2, 7.3, 0.4, 0.03, 0.2, 9.5, 9.2,
                        0.7, 0.2, 0.02, 5.4, 8.1, 1.3, 3.2, 0.4,
                        1.2, 0.02, 1.2, 0.02, 0.7, 0.2, 7.2, 5.4,
                        1.1, 2.3, 3,4, 0.6, 1.4, 2.2, 0.02, 2.7, 
                        1.4, 0.4, 2, 0.2, 0.5, 3, 0.01, 0.34, 2, 
                        2.3, 3.4, 5.5, 5.3, 5.4, 7.4, 1.4, 0.77,
                        2.1, 3.4, 1.1, 3.0, 0.4, 0.1, 0.2, 0.9,
                        0.3, 9.2, 4.2, 0.2, 0.3, 2.1, 3.2, 1.01,
                        0.01, 0.2, 2.3, 7.2, 9.1, 0.4, 4.2, 0.3,
                        9.2, 1.3, 8.2, 8.1, 3.1, 9.1, 0.2, 0.02,
                        0.03, 0.1, 1.2, 2.1, 3.4, 9.1, 0.3, 0.2,
                        0.2, 0.3, 0.1, 4.5, 8.2, 9.3, 5.1, 9.0, 
                        0.4, 1.2, 0.1, 0.4, 0.4, 0.3, 1.7, 3.3,
                        5.7, 1.2, 7.3, 0.4, 0.03, 0.2, 9.5, 0.2,
                        8.1, 1.3, 3.2, 0.4, 1.4, 2.2, 0.02, 2.7, 
                        1.1, 2.1, 3,4, 0.6, 1.4, 2.2, 0.02, 2.7, 
                        1.4, 0.4, 2, 0.2, 0.5, 3, 0.01, 0.34, 2, 
                        2.3, 3.4, 5.5, 5.3, 5.4, 7.4, 1.4, 0.77,
                        2.1, 3.4, 1.1, 3.0, 0.4, 0.1, 0.2, 0.9,
                        0.3, 3.2, 1.2, 0.2, 0.3, 2.1, 3.2, 1.01,
                        0.01, 0.2, 0.3, 7.2, 9.1, 0.4, 4.2, 0.3,
                        9.2, 1.3, 8.2, 8.1, 3.1, 9.1, 0.2, 0.02,
                        0.03, 0.1, 9.2, 2.1, 3.4, 9.1, 0.3, 0.2,
                        0.2, 0.3, 0.1, 4.5, 8.2, 9.3, 5.1, 9.0, 
                        0.4, 0.2, 0.1, 7.4, 0.4, 0.3, 8.7, 3.3,
                        5.7, 0.2, 0.3, 0.4, 0.03, 0.2, 9.5, 9.2,
                        0.7, 0.2, 7.2, 5.4, 8.1, 1.3, 3.2, 0.4,
                        1.2, 0.02, 1.2, 0.02, 0.7, 0.2, 7.2, 5.4,
                        1.1, 2.3, 1,4, 0.6, 1.4, 2.2, 0.02, 2.7, 
                        1.4, 0.4, 2, 0.2, 0.5, 3, 0.01, 0.34, 2, 
                        2.3, 3.4, 5.5, 5.3, 5.4, 7.4, 1.4, 0.77,
                        2.1, 3.4, 1.1, 3.0, 0.4, 0.1, 0.2, 0.9,
                        0.3, 9.2, 4.2, 0.2, 0.3, 2.1, 3.2, 1.01,
                        0.01, 0.2, 2.3, 7.2, 2.1, 0.4, 4.2, 0.3,
                        9.2, 1.3, 8.2, 8.1, 3.1, 0.1, 0.2, 0.02,
                        0.03, 0.1, 9.2, 2.1, 3.4, 1.1, 0.3, 0.2,
                        0.2, 0.3, 0.1, 4.5, 8.2, 9.3, 5.1, 9.0, 
                        0.4, 8.2, 0.1, 9.4, 0.4, 0.3, 8.7, 3.3,
                        2.7, 8.2, 7.3, 0.4, 0.03, 0.2, 9.5, 9.2,
                        8.1, 1.3, 3.2, 0.4, 1.1, 2.3, 3,4, 0.6,
                        1.4, 0.4, 2, 0.2, 0.5, 3, 0.01, 0.34, 2, 
                        2.3, 3.4, 2.5, 3.3, 5.4, 7.4, 1.4, 0.77,
                        2.1, 3.4, 1.1, 3.0, 0.4, 0.1, 0.2, 0.9,
                        0.3, 9.2, 4.2, 0.2, 0.3, 2.1, 3.2, 1.01,
                        0.01, 0.2, 2.3, 7.2, 9.1, 0.4, 4.2, 0.3,
                        9.2, 1.3, 8.2, 8.1, 3.1, 9.1, 0.2, 0.02,
                        0.03, 0.1, 0.2, 2.1, 3.4, 9.1, 0.3, 0.2,
                        0.2, 0.3, 0.1, 4.5, 8.2, 9.3, 5.1, 9.0, 
                        0.4, 0.01, 0.1, 9.4, 0.4, 0.3, 8.7, 3.3,
                        5.7, 0.2, 7.3, 0.4, 0.03, 0.2, 9.5, 9.2,
                        0.7, 0.2, 3.2, 5.4, 0.01, 1.3, 3.2, 0.4,
                        1.2, 0.02, 1.2, 0.02, 0.7, 0.2, 7.2, 5.4,
                        1.1, 2.3, 3,4, 0.6, 1.4, 2.2, 0.02, 2.7, 
                        1.4, 0.4, 2, 0.2, 0.5, 3, 0.01, 0.34, 2, 
                        2.3, 3.4, 5.5, 5.3, 5.4, 7.4, 1.4, 0.77,
                        2.1, 3.4, 1.1, 3.0, 0.4, 0.1, 0.2, 0.9,
                        0.3, 0.2, 4.2, 0.2, 0.3, 2.1, 3.2, 1.01,
                        0.01, 0.2, 2.3, 7.2, 9.1, 0.4, 4.2, 0.3,
                        0.02, 1.3, 0.2, 8.1, 3.1, 9.1, 0.2, 0.02,
                        0.03, 0.1, 9.2, 2.1, 3.4, 9.1, 0.3, 0.2,
                        0.2, 0.3, 0.1, 4.5, 8.2, 9.3, 5.1, 9.0, 
                        0.4, 5.2, 0.1, 6.4, 0.4, 0.3, 8.7, 3.3,
                        1.7, 4.2, 7.3, 0.4, 0.03, 0.2, 9.5, 9.2,
                        0.1, 1.3, 3.2, 0.4, 1.4, 2.2, 0.02, 2.7,
                        1.1, 2.3, 1,4, 0.6, 1.4, 2.2, 0.02, 2.7, 
                        1.4, 0.4, 2, 0.2, 0.5, 3, 0.01, 0.34, 2, 
                        2.3, 3.4, 2.25, 5.3, 5.4, 7.4, 1.4, 0.77,
                        2.1, 3.4, 1.1, 3.0, 0.4, 0.1, 0.2, 0.9,
                        0.3, 1.2, 3.2, 0.2, 0.3, 2.1, 3.2, 1.01,
                        0.01, 0.2, 2.3, 7.2, 9.1, 0.4, 4.2, 0.3,
                        0.2, 1.3, 3.2, 8.1, 3.1, 0.1, 0.2, 0.02,
                        0.03, 0.1, 9.2, 2.1, 3.4, 0.1, 0.3, 0.2,
                        0.2, 0.3, 0.1, 4.5, 8.2, 9.3, 5.1, 9.0, 
                        0.4, 8.2, 0.1, 9.4, 0.4, 0.3, 8.7, 3.3,
                        5.7, 8.2, 7.3, 0.4, 0.03, 0.2, 9.5, 9.2,
                        0.7, 0.2, 7.2, 5.4, 8.1, 1.3, 3.2, 0.4,
                        1.2, 0.02, 1.2, 1.1, 2.3, 3,4, 0.6, 1.4, 
                        1.4, 0.4, 2.02, 0.2, 0.5, 3, 0.01, 0.34, 2, 
                        2.3, 3.4, 5.5, 5.3, 5.4, 7.4, 1.4, 0.77,
                        2.1, 3.4, 1.1, 3.0, 0.4, 0.1, 0.2, 0.9,
                        0.3, 9.2, 4.2, 0.2, 0.3, 2.1, 3.2, 1.01,
                        1.01, 0.2, 2.3, 7.2, 9.1, 0.4, 4.2, 0.3,
                        9.2, 1.3, 8.2, 8.1, 3.1, 0.1, 0.2, 0.02,
                        0.03, 0.1, 9.2, 2.1, 3.4, 0.1, 0.3, 0.2,
                        0.2, 0.3, 0.1, 4.5, 8.2, 0.3, 5.1, 9.0, 
                        0.4, 8.2, 0.1, 4.4, 0.4, 0.3, 0.7, 3.3,
                        0.7, 8.2, 7.3, 0.4, 0.03, 0.2, 0.5, 9.2,
                        0.7, 0.2, 1.2, 2.4, 3.1, 1.3, 3.2, 0.4,
                        1.2, 0.02, 1.2, 1.2, 0.02, 2.7
                     };


    printf("Calling functions with first set of data: \n");
    clock_gettime(CLOCK_MONOTONIC, &start1);
    mult(arr, SIZE);
    clock_gettime(CLOCK_MONOTONIC, &end1);
    tdiff1 = (end1.tv_sec - start1.tv_sec) + 1e-9*(end1.tv_nsec - start1.tv_nsec);
    printf("  %f  seconds elapsed  for function with NO loop unrolling \n", tdiff1);
    
    
    clock_gettime(CLOCK_MONOTONIC, &start3x1);
    multWithLoop3xUnrolling(arr, SIZE);
    clock_gettime(CLOCK_MONOTONIC, &end3x1);
    tdiff3x1 = (end3x1.tv_sec - start3x1.tv_sec) + 1e-9*(end3x1.tv_nsec - start3x1.tv_nsec);
    printf("  %f  seconds elapsed for function with 3x loop unrolling\n", tdiff3x1);

    
    clock_gettime(CLOCK_MONOTONIC, &start5x1);
    multiplyWith5xLoopUnrolling(arr, SIZE);
    clock_gettime(CLOCK_MONOTONIC, &end5x1);
    tdiff5x1 = (end5x1.tv_sec - start5x1.tv_sec) + 1e-9*(end5x1.tv_nsec - start5x1.tv_nsec);
    printf("  %f  seconds elapsed for function with 5x loop unrolling\n", tdiff5x1);  


    clock_gettime(CLOCK_MONOTONIC, &start2);
    mult(arr, SIZE);
    clock_gettime(CLOCK_MONOTONIC, &end2);
    tdiff2 = (end2.tv_sec - start2.tv_sec) + 1e-9*(end2.tv_nsec - start2.tv_nsec);
    printf("  %f  seconds elapsed for function with NO loop unrolling (second check)\n", tdiff2);
    
    clock_gettime(CLOCK_MONOTONIC, &start3x2);
    multWithLoop3xUnrolling(arr, SIZE);
    clock_gettime(CLOCK_MONOTONIC, &end3x2);
    tdiff3x2 = (end3x2.tv_sec - start3x2.tv_sec) + 1e-9*(end3x2.tv_nsec - start3x2.tv_nsec);
    printf("  %f  seconds elapsed for function with 3x loop unrolling (second check)\n", tdiff3x2);

    clock_gettime(CLOCK_MONOTONIC, &start5x2);
    multiplyWith5xLoopUnrolling(arr, SIZE);
    clock_gettime(CLOCK_MONOTONIC, &end5x2);
    tdiff5x2 = (end5x2.tv_sec - start5x2.tv_sec) + 1e-9*(end5x2.tv_nsec - start5x2.tv_nsec);
    printf("  %f  seconds elapsed for function with 5x loop unrolling (second check)\n", tdiff5x2);        


    printf("\nCalling functions with another set of data: \n");
    
    clock_gettime(CLOCK_MONOTONIC, &start3);
    result = mult(arr2, SIZE2);
    clock_gettime(CLOCK_MONOTONIC, &end3);
    tdiff3 = (end3.tv_sec - start3.tv_sec) + 1e-9*(end3.tv_nsec - start3.tv_nsec);
    printf("  %f  seconds elapsed for function with NO loop unrolling | result = %e\n", tdiff3, result);
    
    clock_gettime(CLOCK_MONOTONIC, &start3x3);
    result = multWithLoop3xUnrolling(arr2, SIZE2);
    clock_gettime(CLOCK_MONOTONIC, &end3x3);
    tdiff3x3 = (end3x3.tv_sec - start3x3.tv_sec) + 1e-9*(end3x3.tv_nsec - start3x3.tv_nsec);
    printf("  %f seconds elapsed for function with 3x loop unrolling | result = %e\n", tdiff3x3, result);

    clock_gettime(CLOCK_MONOTONIC, &start5x3);
    result = multiplyWith5xLoopUnrolling(arr2, SIZE2);
    clock_gettime(CLOCK_MONOTONIC, &end5x3);
    tdiff5x3 = (end5x3.tv_sec - start5x3.tv_sec) + 1e-9*(end5x3.tv_nsec - start5x3.tv_nsec);
    printf("  %f seconds elapsed for function with 5x loop unrolling | result = %e\n", tdiff5x3, result);
    
    
    clock_gettime(CLOCK_MONOTONIC, &start4);
    result = mult(arr2, SIZE2);
    clock_gettime(CLOCK_MONOTONIC, &end4);
    tdiff4 = (end4.tv_sec - start4.tv_sec) + 1e-9*(end4.tv_nsec - start4.tv_nsec);
    printf("  %f  seconds elapsed for function with NO loop unrolling (second check) | result = %e\n", tdiff4, result);
    
    clock_gettime(CLOCK_MONOTONIC, &start3x4);
    result = multWithLoop3xUnrolling(arr2, SIZE2);
    clock_gettime(CLOCK_MONOTONIC, &end3x4);
    tdiff3x4 = (end3x4.tv_sec - start3x4.tv_sec) + 1e-9*(end3x4.tv_nsec - start3x4.tv_nsec);
    printf("  %f  seconds elapsed for function with 3x loop unrolling (second check) | result = %e\n", tdiff3x4, result);

    clock_gettime(CLOCK_MONOTONIC, &start5x4);
    result = multiplyWith5xLoopUnrolling(arr2, SIZE2);
    clock_gettime(CLOCK_MONOTONIC, &end5x4);
    tdiff5x4 = (end5x4.tv_sec - start5x4.tv_sec) + 1e-9*(end5x4.tv_nsec - start5x4.tv_nsec);
    printf("  %f  seconds elapsed for function with 5x loop unrolling (second check) | result = %e\n", tdiff5x4, result);          
    

    return 0;
}