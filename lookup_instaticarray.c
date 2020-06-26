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

    clock_t start1, end1, start2, end2, start3, end3, start4, end4;


    start1 = clock();
    for(size_t i = 0; i < 100; i++)
    {
        lookUpWithoutStatic(rand()%SIZE);
    }
    end1 = clock();
    printf("the number of clock ticks elapsed for 100 calls of a function with NONE-static array - %li\n", end1 - start1);

    start2 = clock();
    for(size_t i = 0; i < 100; i++)
    {
        lookUpWithStatic(rand()%SIZE);
    }
    end2 = clock();
    printf("the number of clock ticks elapsed for 100 calls of a function with static array - %li\n", end2 - start2);

    start3 = clock();
    for(size_t i = 0; i < 100; i++)
    {
        lookUpWithoutStatic(rand()%SIZE);
    }
    end3 = clock();
    printf("the number of clock ticks elapsed for 100 calls of a function with NONE-static array (second check) - %li\n", end3 - start3);

    start4 = clock();
    for(size_t i = 0; i < 100; i++)
    {
        lookUpWithStatic(rand()%SIZE);
    }
    end4 = clock();
    printf("the number of clock ticks elapsed for 100 calls of a function with static array (second check) - %li\n", end4 - start4);   

    return 0;
}