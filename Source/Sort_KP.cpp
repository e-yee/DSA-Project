#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// -------------------------- count comparisons --------------------------

int Partition(int a[], int low, int high, long long& cnt_cmp)
{
    int median = a[low] + a[high] + a[(low + high) / 2] - max(max(a[low], a[high]), a[(low + high) / 2]) - min(min(a[low], a[high]), a[(low + high) / 2]);
    int pos = low;
    if (a[median] == high) pos = high;
    if (a[median] == (low + high) / 2) pos = (low + high) / 2;
    swap(a[low], a[pos]);

    cnt_cmp += 4;

    int pivot = low;
    int lastS1 = low;
    int first_unknown = low + 1;
 
    while (++cnt_cmp && first_unknown <= high) {
        if (++cnt_cmp && a[first_unknown] < a[pivot]) {
            swap(a[lastS1 + 1], a[first_unknown]);
            lastS1++;
        }
        first_unknown++;
    }
    swap(a[pivot], a[lastS1]);
    
    return lastS1;
    // int pivot = low;

    // int k = high;
    // for (int i = high; ++cnt_cmp && i >= low; i--) {
    //     if (++cnt_cmp && a[i] > a[pivot])
    //         swap(a[i], a[k--]);
    // }
    // swap(a[low], a[k]);
    // return k;
}

void quickSortRecursion(int a[], int low, int high, long long& cnt_cmp)
{
    if (low < high) {
        int pivot = Partition(a, low, high, cnt_cmp);
        quickSortRecursion(a, low, pivot - 1, cnt_cmp);
        quickSortRecursion(a, pivot + 1, high, cnt_cmp);
    }
}

void quickSort(int a[], int n, long long& cnt_cmp)
{
    cnt_cmp = 0;
    quickSortRecursion(a, 0, n - 1, cnt_cmp);
}

void shakerSort(int a[], int n, long long& cnt_cmp)
{
    cnt_cmp = 0;
    bool swapped = true;
    int start = 0, end = n - 1;
    
    while (++cnt_cmp && swapped == true) {
        swapped = false;

        for (int i = start; ++cnt_cmp && i < end; i++) {
            if (++cnt_cmp && a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        if (++cnt_cmp && swapped == false) break;

        swapped = false;
        end--;

        for (int i = end - 1; ++cnt_cmp && i >= start; i--) {
            if (++cnt_cmp && a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        start++;
    }
}

void shellSort(int arr[], int n, long long& cnt_cmp) {
    cnt_cmp = 0;

    for (int gap = n / 2; ++cnt_cmp && gap > 0; gap /= 2) {
        for (int i = gap; ++cnt_cmp && i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; (++cnt_cmp && j >= gap) && (++cnt_cmp && arr[j - gap] > temp); j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}



// ----------------------- calculate running time -----------------------

int Partition(int a[], int low, int high)
{
    int median = a[low] + a[high] + a[(low + high) / 2] - max(max(a[low], a[high]), a[(low + high) / 2]) - min(min(a[low], a[high]), a[(low + high) / 2]);
    int pos = low;
    if (a[median] == high) pos = high;
    if (a[median] == (low + high) / 2) pos = (low + high) / 2;
    swap(a[low], a[pos]);

    int pivot = low;
    int lastS1 = low;
    int first_unknown = low + 1;
    
    while (first_unknown <= high) {
        if (a[first_unknown] < a[pivot]) {
            swap(a[lastS1 + 1], a[first_unknown]);
            lastS1++;
        }
        first_unknown++;
    }
    swap(a[pivot], a[lastS1]);

    return lastS1;

    // int pivot = low;
    // int k = high;
    // for (int i = high; i >= low; i--) {
    //     if (a[i] > a[pivot])
    //         swap(a[i], a[k--]);
    // }
    // swap(a[low], a[k]);
    // return k;
}

void quickSortRecursion(int a[], int low, int high)
{
    if (low < high) {
        int pivot = Partition(a, low, high);
        quickSortRecursion(a, low, pivot - 1);
        quickSortRecursion(a, pivot + 1, high);
    }
}

void quickSort(int a[], int n, double& duration)
{
    duration = 0;
    auto time_start = system_clock::now();

    quickSortRecursion(a, 0, n - 1);

    auto time_end = system_clock::now();
    auto elapsed = time_end - time_start;
    duration = (double)elapsed.count();
}

void shakerSort(int a[], int n, double& duration)
{
    duration = 0;
    auto time_start = system_clock::now();

    bool swapped = true;
    int start = 0, end = n - 1;

    while (swapped == true) {
        swapped = false;

        for (int i = start; i < end; i++) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        if (swapped == false) break;

        swapped = false;
        end--;

        for (int i = end - 1; i >= start; i--) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        start++;
    }

    auto time_end = system_clock::now();
    auto elapsed = time_end - time_start;
    duration = (double)elapsed.count();
}

void shellSort(int arr[], int n, double& duration)
{
    duration = 0;
    auto time_start = system_clock::now();

    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }

    auto time_end = system_clock::now();
    auto elapsed = time_end - time_start;
    duration = (double)elapsed.count();
}