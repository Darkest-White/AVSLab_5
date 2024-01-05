#include <iostream>
#include <vector>
#include <cstdlib>
#include <omp.h>

void merge(std::vector<int>& arr, std::vector<int>& left, std::vector<int>& right) {
    int left_size = left.size();
    int right_size = right.size();
    int i = 0, j = 0, k = 0;

    while (i < left_size && j < right_size) 
    {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        }
        else 
        {
            arr[k++] = right[j++];
        }
    }

    while (i < left_size) 
    {
        arr[k++] = left[i++];
    }

    while (j < right_size) 
    {
        arr[k++] = right[j++];
    }
}

void merge_sort(std::vector<int>& arr) {
    int n = arr.size();
    if (n <= 1)
        return;

    int mid = n / 2;
    std::vector<int> left(arr.begin(), arr.begin() + mid);
    std::vector<int> right(arr.begin() + mid, arr.end());

#pragma omp parallel sections
    {
#pragma omp section
        {
            merge_sort(left);
        }

#pragma omp section
        {
            merge_sort(right);
        }
    }

    merge(arr, left, right);
}

int main()
{
    system("chcp 1251");
    int n;
    std::cout << "Введите размер массива: ";
    std::cin >> n;

    std::vector<int> arr(n);

    srand(1);
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 100;
    }

    std::cout << "Исходный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    double start_time = omp_get_wtime();

#pragma omp parallel
    {
#pragma omp single
        {
            merge_sort(arr);
        }
    }

    double end_time = omp_get_wtime();
    double elapsed_time = end_time - start_time;

    std::cout << "Отсортированный массив: ";
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Затраченное на расчеты процессорное время: " << elapsed_time << " сек" << std::endl;

    return 0;
}