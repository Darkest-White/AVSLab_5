#include <iostream>
#include <omp.h>
using namespace std;

#define VECTOR_SIZE 10

int main() 
{
    system("chcp 1251");
    int vectorA[VECTOR_SIZE];
    int vectorB[VECTOR_SIZE];
    int result[VECTOR_SIZE];

    for (int i = 0; i < VECTOR_SIZE; i++) 
    {
        vectorA[i] = i;
        vectorB[i] = i * 2;
    }

    for (int i = 0; i < VECTOR_SIZE; i++)
    {
        cout << vectorA[i] << "\t";
    }
    cout << endl;
    for (int i = 0; i < VECTOR_SIZE; i++)
    {
        cout << vectorB[i] << "\t";
    }
    cout << endl;

#pragma omp parallel
    {
#pragma omp sections
        {
#pragma omp section
            {
                for (int i = 0; i < VECTOR_SIZE / 2; i++) 
                {
                    result[i] = vectorA[i] + vectorB[i];
                }
            }

#pragma omp section
            {
                for (int i = VECTOR_SIZE / 2; i < VECTOR_SIZE; i++) 
                {
                    result[i] = vectorA[i] + vectorB[i];
                }
            }
        }
    }

    cout << "Результирующий вектор: " << endl;
    for (int i = 0; i < VECTOR_SIZE; i++) 
    {
        cout << result[i] << "\t";
    }
    cout << endl;

    return 0;
}