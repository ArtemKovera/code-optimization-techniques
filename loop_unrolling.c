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
    clock_t start1, end1, start2, end2, start3, end3, start4, end4;
    clock_t start3x1, end3x1, start3x2, end3x2, start3x3, end3x3, start3x4, end3x4;
    clock_t start5x1, end5x1, start5x2, end5x2, start5x3, end5x3, start5x4, end5x4;  

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
    
    start3x1 = clock();
    multWithLoop3xUnrolling(arr, 1000000);
    end3x1 = clock();
    printf("the number of clock ticks elapsed for function with 3x loop unrolling   - %li\n", end3x1 - start3x1);

    start5x1 = clock();
    multiplyWith5xLoopUnrolling(arr, 1000000);
    end5x1 = clock();
    printf("the number of clock ticks elapsed for function with 5x loop unrolling   - %li\n", end5x1 - start5x1);  

    start2 = clock();
    mult(arr, 1000000);
    end2 = clock();
    printf("the number of clock ticks elapsed for function with NO loop unrolling - %li (second check)\n", end2 - start2);
    
    start3x2 = clock();
    multWithLoop3xUnrolling(arr, 1000000);
    end3x2 = clock();
    printf("the number of clock ticks elapsed for function with 3x loop unrolling   - %li (second check)\n", end3x2 - start3x2);

    start5x2 = clock();
    multiplyWith5xLoopUnrolling(arr, 1000000);
    end5x2 = clock();
    printf("the number of clock ticks elapsed for function with 5x loop unrolling   - %li (second check)\n", end5x2 - start5x2);        


    printf("\nCalling functions with another set of data: \n");
    start3 = clock();
    mult(arr2, SIZE);
    end3 = clock();
    printf("the number of clock ticks elapsed for function with NO loop unrolling - %li\n", end3 - start3);
    
    start3x3 = clock();
    multWithLoop3xUnrolling(arr2, SIZE);
    end3x3 = clock();
    printf("the number of clock ticks elapsed for function with 3x loop unrolling   - %li\n", end3x3 - start3x3);

    start5x3 = clock();
    multiplyWith5xLoopUnrolling(arr2, SIZE);
    end5x3 = clock();
    printf("the number of clock ticks elapsed for function with 5x loop unrolling   - %li\n", end5x3 - start5x3);  

    start4 = clock();
    mult(arr2, SIZE);
    end4 = clock();
    printf("the number of clock ticks elapsed for function with NO loop unrolling - %li (second check)\n", end4 - start4);
    
    start3x4 = clock();
    multWithLoop3xUnrolling(arr2, SIZE);
    end3x4 = clock();
    printf("the number of clock ticks elapsed for function with 3x loop unrolling   - %li (second check)\n", end3x4 - start3x4);

    start5x4 = clock();
    multiplyWith5xLoopUnrolling(arr2, SIZE);
    end5x4 = clock();
    printf("the number of clock ticks elapsed for function with 5x loop unrolling   - %li (second check)\n", end5x4 - start5x4);            
    
    return 0;
}