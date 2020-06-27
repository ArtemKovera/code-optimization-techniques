/*

    This program demonstrates how different ways of quadratic matrix multiplication
    affect performance due to exploiting different temporal and spatial locality

    This program is somewhat analogous to some of the exampels from the book "Computer Systems: A Programmer's Perspective"

*/

#include<iostream>
#include<ctime>


int main ()
{
    clock_t start1, end1, start2, end2, start3, end3;

    const int SIZE = 700;
    
    int n = SIZE;
    int i, j, k, sum, temp;
    
    //allocating matrix1 
    int** matrix1 = new int* [SIZE];
    for(i = 0; i < SIZE; i++)
        matrix1[i] = new int [SIZE];
    
    
    //allocating matrix2
    int** matrix2 = new int* [SIZE];
    for(i = 0; i < SIZE; i++)
        matrix2[i] = new int [SIZE];


    //allocating matrix3, which is the product matrix
    int** matrix3 = new int* [SIZE];
    for(i = 0; i < SIZE; i++)
        matrix3[i] = new int [SIZE];  


    //setting the matrices' values
    for(i = 0; i < SIZE - 1; i++)
    {
        for(j = 0; j < SIZE -1; j++)
        {
            matrix1[i][j] = rand()%10;
            matrix2[i][j] = rand()%10;
            matrix3[i][j] = 0;
        }
    }

    ////////////////////////////////////////////////////////////
    //first way of multiplying matrices
    start1 = clock();
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            sum = 0;
            for (k = 0; k < n; k++)
            {
                sum += matrix1[i][k]*matrix2[k][j];
            }
                
            matrix3[i][j] += sum;
        }
    }
    end1 = clock();

    
    ////////////////////////////////////////////////////////////
    //resetting matrix3's elements to 0
    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
        {
            matrix3[i][j] = 0;
        }
    }
 
    //second way of multiplying matrices - (most cache-unfriendly on tested machine)
    start2 = clock();
    for (j = 0; j < n; j++)
    {
        for (k = 0; k < n; k++)
        {
            temp = matrix2[k][j];
            for (i = 0; i < n; i++)
            {
                matrix3[i][j] += matrix1[i][k]*temp;
            }   
        }        
    }
    end2 = clock();    


    ////////////////////////////////////////////////////////////
    //resetting matrix3's elements to 0
    for(i = 0; i < SIZE; i++)
    {
        for(j = 0; j < SIZE; j++)
        {
            matrix3[i][j] = 0;
        }
    }

    //third way of multiplying matrices - (most cache-friendly on tested machine) 
    start3 = clock();    
    for (k = 0; k < n; k++)
    {
        for (i = 0; i < n; i++)
        {
            temp = matrix1[i][k];
            for (j = 0; j < n; j++)
            {
                matrix3[i][j] += temp*matrix2[k][j];
            }
        } 
    }
    end3 = clock(); 


    //freeing up memory
    for(i = 0; i < SIZE; i++)
    {
        delete [] matrix1[i];
        delete [] matrix2[i];
        delete [] matrix3[i];
    }
    delete [] matrix1;
    delete [] matrix2;
    delete [] matrix3;

    std::cout << "the number of clock ticks elapsed for the first way  - " << end1 - start1 << std::endl;                
    std::cout << "the number of clock ticks elapsed for the second way - " << end2 - start2 << std::endl;                
    std::cout << "the number of clock ticks elapsed for the third way  - " << end3 - start3 << std::endl;                
          

    return 0;
}