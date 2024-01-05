#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>

void quicksort(std::vector<int>& arr, int low, int high) 
{
    if (low >= high)
        return;

    int pivot = arr[low];
    int i = low + 1;
    int j = high;

    while (i <= j) 
    {
        while (i <= high && arr[i] <= pivot)
            i++;
        while (j > low && arr[j] > pivot)
            j--;

        if (i < j)
            std::swap(arr[i], arr[j]);
    }

    std::swap(arr[low], arr[j]);

#pragma omp parallel sections
    {
#pragma omp section
        {
            quicksort(arr, low, j - 1);
        }

#pragma omp section
        {
            quicksort(arr, j + 1, high);
        }
    }
}

int main() 
{
    system("chcp 1251");

    int n;
    std::cout << "Введиет размер массива: ";
    std::cin >> n;

    std::vector<int> arr(n);

    srand(1);
    for (int i = 0; i < n; i++) 
    {
        arr[i] = rand() % 100;
    }

    std::cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) 
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    double start_time = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp single
        {
            quicksort(arr, 0, n - 1);
        }
    }

    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    std::cout << "Отсортированный массив: ";
    for (int i = 0; i < n; i++) 
    {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Затраченное время: " << elapsed_time << " seconds" << std::endl;

    return 0;
}