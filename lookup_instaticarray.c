/*

    This program demonstrates how making an array static
    inside a function increases performance
    
*/

#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int lookUpWithoutStatic(size_t index)
{
    int arr[] =
    {
       1, 2, 3, 4, 5, 8, 2, 1, 3, 4, 5,
       4, 4, 5, 5, 6, 6, 6, 1, 4, 5, 7,
       6, 3, 0, 5, 6, 7, 3, 1, 9, 0, 9,
       3, 4, 5, 6, 7, 8, 8, 9, 9, 4, 7,
       2, 5, 5, 6, 6, 8, 8, 5, 5, 5, 4,
       1, 3, 4, 5, 6, 7, 2, 4, 4, 8, 7,
       3, 5, 5, 3, 3, 5, 6, 7, 7, 1, 0,
       7, 3, 5, 5, 6, 1, 2, 9, 0, 2, 2,
       5, 0, 0, 3, 4, 5, 3, 1, 4, 5, 6
    };

    return arr[index];
}

//this function is identical to the previous one, except the array inside this function is made static
int lookUpWithStatic(size_t index)
{
    static int arr[] =
    {
       1, 2, 3, 4, 5, 8, 2, 1, 3, 4, 5,
       4, 4, 5, 5, 6, 6, 6, 1, 4, 5, 7,
       6, 3, 0, 5, 6, 7, 3, 1, 9, 0, 9,
       3, 4, 5, 6, 7, 8, 8, 9, 9, 4, 7,
       2, 5, 5, 6, 6, 8, 8, 5, 5, 5, 4,
       1, 3, 4, 5, 6, 7, 2, 4, 4, 8, 7,
       3, 5, 5, 3, 3, 5, 6, 7, 7, 1, 0,
       7, 3, 5, 5, 6, 1, 2, 9, 0, 2, 2,
       5, 0, 0, 3, 4, 5, 3, 1, 4, 5, 6
    };

    return arr[index];
}



int main()
{
    srand(time(NULL)); 
    const size_t SIZE = 98;

     
    struct timespec start1, end1, start2, end2, start3, end3, start4, end4;
    double tdiff1, tdiff2, tdiff3, tdiff4;


    clock_gettime(CLOCK_MONOTONIC, &start1);
    for(size_t i = 0; i < 100; i++)
    {
        lookUpWithoutStatic(rand()%SIZE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end1);
    tdiff1 = (end1.tv_sec - start1.tv_sec) + 1e-9*(end1.tv_nsec - start1.tv_nsec);
    printf("100 calls of a function with NONE-static array lasts   %f  seconds\n", tdiff1);


    clock_gettime(CLOCK_MONOTONIC, &start2);
    for(size_t i = 0; i < 100; i++)
    {
        lookUpWithStatic(rand()%SIZE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end2);
    tdiff2 = (end2.tv_sec - start2.tv_sec) + 1e-9*(end2.tv_nsec - start2.tv_nsec);
    printf("100 calls of a function with static array lasts        %f  seconds\n", tdiff2);


    clock_gettime(CLOCK_MONOTONIC, &start3);
    for(size_t i = 0; i < 100; i++)
    {
        lookUpWithoutStatic(rand()%SIZE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end3);
    tdiff3 = (end3.tv_sec - start3.tv_sec) + 1e-9*(end3.tv_nsec - start3.tv_nsec);      
    printf("100 calls of a function with NONE-static array lasts   %f  seconds (second check)\n", tdiff3);


    clock_gettime(CLOCK_MONOTONIC, &start4);
    for(size_t i = 0; i < 100; i++)
    {
        lookUpWithStatic(rand()%SIZE);
    }
    clock_gettime(CLOCK_MONOTONIC, &end4);
    tdiff4 = (end4.tv_sec - start4.tv_sec) + 1e-9*(end4.tv_nsec - start4.tv_nsec);   
    printf("100 calls of a function with static array lasts        %f  seconds (second check)\n", tdiff4);   

    return 0;
}