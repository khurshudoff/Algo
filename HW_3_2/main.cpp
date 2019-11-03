#include <iostream>
#include <vector>

void merge(int* arr, int l, int m, int r) {
    int n1 = m - l;
    int n2 = r - m;
    int arr1[n1];
    int arr2[n2];

    for (int i = l; i < m; i++) {
        arr1[i - l] = arr[i];
    }
    for (int i = m; i < r; i++) {
        arr2[i - m] = arr[i];
    }

    int i1 = 0;
    int i2 = 0;

    while (i1 < n1 || i2 < n2) {
        int i = i1 + i2;
        if (i1 == n1) {
            arr[l + i] = arr2[i2++];
            continue;
        }
        if (i2 == n2) {
            arr[l + i] = arr1[i1++];
            continue;
        }
        if (arr1[i1] < arr2[i2]) {
            arr[l + i] = arr1[i1++];
        } else {
            arr[l + i] = arr2[i2++];
        }
    }
}

void mergeSort(int* arr, int l, int r) {
    if (r - l <= 1) {
        return;
    }
    int m = (r+l)/2;
    mergeSort(arr, l, m);
    mergeSort(arr, m, r);
    merge(arr, l, m, r);
}


int main() {
    int n = 0;
    int k = 0;

    std::cin >> n >> k;

    // сколько отрезков длины k уже обработано
    int iter = 2;

    int arr[2 * k];

    // крайний случай, когда n < 2*k обработаем отдельно
    // просто отстортируем его с помощью mergeSort
    if (n < 2*k) {
        for (int i = 0; i < n; i++) {
            std::cin >> arr[i];
        }
        mergeSort(arr, 0, n);
        for (int i = 0; i < n; i++) {
            std::cout << arr[i] << " ";
        }
        std::cout << std::endl;
        return 0;
    }

    for (int i = 0; i < 2*k; i++) {
        std::cin >> arr[i];
    }

    mergeSort(arr, 0, k);
    mergeSort(arr, k, 2*k);
    merge(arr, 0, k, 2*k);

    // обрабатываем по одному отрезку длины k
    while (iter++ < n/k) {
        // выводим левую половину массива arr, она длины k
        // на ее место считаем новые k элементов
        for (int i = 0; i < k; i++) {
            std::cout << arr[i] << " ";
        }

        for (int i = 0; i < k; i++) {
            std::cin >> arr[i];
        }

        // отстортируем левую часть массива длины k
        mergeSort(arr, 0, k);
        // Получились отстортированные массивы а(0),...,a(k-1) и a(k),...,a(2k-1)
        // теперь их можно слить в один
        merge(arr, 0, k, 2*k);
    }
    iter--;

    // После завершения работы предыдущего блока будут
    // обработаны n-(n%k) элементов и напечатаны n-2k

    // Печатаем первые k элементов, тк они уже отсортированы
    for (int i = 0; i < k; i++) {
        std::cout << arr[i] << " ";
    }

    // если мы уже обработали все элементы, то есть n%k==0
    // то можно вывести оставшиеся a(k),...,a(2k-1)

    if (iter*k == n) {
        for (int i = k; i < 2*k; i++) {
            std::cout << arr[i] << " ";
        }
    } else {
        // обрабатываем оставшиеся
        int rest = n%k;
        for (int i = 0; i < k; i++) {
            arr[i] = arr[k+i];
            if (i < rest) {
                std::cin >> arr[k+i];
            }
        }
        mergeSort(arr, k, k+rest);
        merge(arr, 0, k, k+rest);
        for (int i = 0; i < k+rest; i++) {
            std::cout << arr[i] << " ";
        }
    }

    return 0;
}
