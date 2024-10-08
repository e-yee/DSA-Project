#include <iostream>
#include <chrono>

using namespace std;
using namespace std::chrono;

// -------------------------- count comparisons --------------------------

int Partition(int a[], int low, int high, long long& cnt_cmp)
{
    int median = a[low] + a[high] + a[(int) ((low + high) / 2)] - max(max(a[low], a[high]), a[(int) ((low + high) / 2)]) - min(min(a[low], a[high]), a[(int) ((low + high) / 2)]);

    cnt_cmp += 4;

    int pos = low;
    if (++cnt_cmp && median == a[high]) pos = high;
    if (++cnt_cmp && median == a[(int) (low + high) / 2]) pos = (int) (low + high) / 2;
    int tmp = a[low];
    a[low] = a[pos];    
    a[pos] = tmp;
    // swap(a[low], a[pos]);

    int pivot = low;
    int lastS1 = low;
    int first_unknown = low + 1;
 
    while (++cnt_cmp && first_unknown <= high) {
        if (++cnt_cmp && a[first_unknown] < a[pivot]) {
            int temp = a[lastS1 + 1];
            a[lastS1 + 1] = a[first_unknown];
            a[first_unknown] = temp;
            // swap(a[lastS1 + 1], a[first_unknown]);
            lastS1++;
        }
        first_unknown++;
    }
    tmp = a[pivot];
    a[pivot] = a[lastS1];
    a[lastS1] = tmp;
    // swap(a[pivot], a[lastS1]);
    
    return lastS1;
}

void quickSortRecursion(int a[], int low, int high, long long& cnt_cmp)
{
    if (low < high) {
        int pivot = Partition(a, low, high, cnt_cmp);
        if (++cnt_cmp && pivot > low + 1) {
            quickSortRecursion(a, low, pivot - 1, cnt_cmp);
        }
        if (++cnt_cmp && pivot < high - 1) {
            quickSortRecursion(a, pivot + 1, high, cnt_cmp);
        }
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
    int median = a[low] + a[high] + a[(int) (low + high) / 2] - max(max(a[low], a[high]), a[(int) (low + high) / 2]) - min(min(a[low], a[high]), a[(int) (low + high) / 2]);
    int pos = low;
    if (median == a[high]) pos = high;
    if (median == a[(int) (low + high) / 2]) pos = (int) (low + high) / 2;
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


long long cnt = 0;

void quickSortRecursion(int a[], int low, int high)
{
    // if (++cnt >= 21570) cout << cnt << '\n';

    if (low < high) {
        int pivot = Partition(a, low, high);
        if (pivot > low + 1) {
            quickSortRecursion(a, low, pivot - 1);
        }
        if (pivot < high - 1) {
            quickSortRecursion(a, pivot + 1, high);
        }
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