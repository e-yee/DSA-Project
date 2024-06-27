#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// -------------------------- count comparisons --------------------------

int Partition(int a[], int low, int high, long long& cnt_cmp)
{
    int pos = low;

    if ((++cnt_cmp && a[high / 2] >= min(a[low], a[high - 1])) && (++cnt_cmp && a[high / 2] <= max(a[low], a[high])))
        pos = high / 2;
    if ((++cnt_cmp && a[high] >= min(a[low], a[high / 2])) && (++cnt_cmp && a[high] <= max(a[low], a[high / 2])))
        pos = high;

    swap(a[low], a[pos]);

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
    
    while (swapped) {
        swapped = false;

        for (int i = start; ++cnt_cmp && i < end; i++) {
            if (++cnt_cmp && a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

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
            for (j = i; ++cnt_cmp && j >= gap && arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }
}



// ----------------------- calculate running time -----------------------

int Partition(int a[], int low, int high)
{
    int pos = low;

    if (a[high / 2] >= min(a[low], a[high - 1]) && a[high / 2] <= max(a[low], a[high]))
        pos = high / 2;
    if (a[high] >= min(a[low], a[high / 2]) && a[high] <= max(a[low], a[high / 2]))
        pos = high;

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

    while (swapped) {
        swapped = false;

        for (int i = start; i < end; i++) {
            if (a[i] > a[i + 1]) {
                swap(a[i], a[i + 1]);
                swapped = true;
            }
        }

        if (!swapped) break;

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
            for (j = i; arr[j - gap] > temp; j -= gap) {
                arr[j] = arr[j - gap];
            }
            arr[j] = temp;
        }
    }

    auto time_end = system_clock::now();
    auto elapsed = time_end - time_start;
    duration = (double)elapsed.count();
}