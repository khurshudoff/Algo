/*
Даны неотрицательные целые числа n,k и массив целых чисел из [0..10^9] размера n. Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k (0..n-1) в отсортированном массиве. Напишите нерекурсивный алгоритм.
Требования к дополнительной памяти: O(n). Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении. Описание для случая прохода от начала массива к концу
*/

#include <iostream>
#include <algorithm>

int find_pivot_index(int *arr, int l, int r);
int find_k_stat(int *arr, int n, int k);
int partition(int *arr, int l, int r);

int find_pivot_index(int *arr, int l, int r) {
    int m[3] = {arr[l], arr[(r+l)/2], arr[r-1]};
    if ((m[0] >= m[1] >= m[2]) || (m[0] <= m[1] <= m[2])) return (r+l)/2;
    if ((m[1] >= m[0] >= m[2]) || (m[1] <= m[0] <= m[2])) return l;
    if ((m[0] >= m[2] >= m[1]) || (m[0] <= m[2] <= m[1])) return r-1;
}
int find_k_stat(int *arr, int n, int k) {
    int l = 0;
    int r = n;
    while (true) {
        int current_k_stat_idx = partition(arr, l, r);

        if (current_k_stat_idx == k) return arr[k];

        if (current_k_stat_idx > k)
            r = current_k_stat_idx;
        else
            l = current_k_stat_idx;
    }
}
int partition(int *arr, int l, int r) {
    int pivot_index = find_pivot_index(arr, l, r);
    std::swap(arr[r-1], arr[pivot_index]);

    int i = l;
    int j = l;

    for ( ; j < r-1; j++)
        if (arr[j] <= arr[r-1])
            std::swap(arr[j], arr[i++]);
    std::swap(arr[r-1], arr[i]);

    return i;
}

int main() {
    int n = 0;
    int k = 0;
    std::cin >> n >> k;
    int *arr = new int[n];

    for (int i = 0; i < n; i++) {
        std::cin >> arr[i];
    }

    std::cout << find_k_stat(arr, n, k);

    delete[] arr;

    return 0;
}
