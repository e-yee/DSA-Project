#include <iostream>
#include <chrono>
#include <fstream>

#include "checker.h"
#include "DataGenerator.h"
#include "mode.h"

using namespace std;
using namespace std::chrono;


// -------------------------- count comparisons --------------------------

int findMaxPos(int a[], int n, long long &cnt_cmp) 
{
    int m = 0;

    for (int i = 0; ++cnt_cmp && i < n; i++)
        if (++cnt_cmp && a[i] > a[m])
            m = i;
    
    return m;
}

int findMinPos(int a[], int n, long long &cnt_cmp) 
{
    int m = 0;
    
    for (int i = 0; ++cnt_cmp && i < n; i++)
        if (++cnt_cmp && a[i] < a[m])
            m = i;

    return m;
}

void Heapify(int a[], int n, int i, long long &cnt_cmp) 
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (++cnt_cmp && left < n && ++cnt_cmp && a[largest] < a[left])
        largest = left;
    if (++cnt_cmp && right < n && ++cnt_cmp && a[largest] < a[right])
        largest = right;
    if (++cnt_cmp && largest != i) {
        swap(a[largest], a[i]);
        Heapify(a, n, largest, cnt_cmp);
    }
}

void heapSort(int a[], int n, long long &cnt_cmp)
{
    cnt_cmp = 0;

    for (int i = n / 2 - 1; ++cnt_cmp && i >= 0; i--)
        Heapify(a, n, i);
    
    for (int i = n - 1; ++cnt_cmp && i >= 0; i--) {
        swap(a[i], a[0]);
        Heapify(a, i, 0, cnt_cmp);
    }
}

void countSort(int a[], int n, int exp, long long &cnt_cmp) 
{
    vector<int> output(n);
    int count[10] = { 0 };

    for (int i = 0; ++cnt_cmp && i < n; i++)
        ++count[(a[i] / exp) % 10];
    
    for (int i = 1; ++cnt_cmp && i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; ++cnt_cmp && i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        --count[(a[i] / exp) % 10];
    }

    for (int i = 0; ++cnt_cmp && i < n; i++)
        a[i] = output[i];
}

void radixSort(int a[], int n, long long &cnt_cmp)
{
    cnt_cmp = 0;
    int m = findMaxPos(a, n, cnt_cmp);

    for (int exp = 1; ++cnt_cmp && a[m] / exp > 0; exp *= 10)
        countSort(a, n, exp, cnt_cmp);
}

void flashSwap(int a[], vector<int> bucket, int n, int max_pos, int min_pos, double c, long long &cnt_cmp) 
{
    int move = 0;
    int bucket_idx = bucket.size() - 1;
    int flash;
    int i = 0;

    swap(a[max_pos], a[0]);
    while (++cnt_cmp && move < n - 1) {
        while (++cnt_cmp && i > bucket[bucket_idx] - 1) {
            ++i;
            bucket_idx = c * (a[i] - a[min_pos]);
        }

        flash = a[i];
        while (++cnt_cmp && i != bucket[bucket_idx]) {
            bucket_idx = c * (a[i] - a[min_pos]);
            --bucket_idx;
            swap(flash, a[bucket[bucket_idx]]);
            ++move;
        }
    }
}

void flashSort(int a[], int n, long long &cnt_cmp)
{
    cnt_cmp = 0;

    int length = 0.45 * n;
    vector<int> bucket(length, 0);
    int max_pos = findMaxPos(a, n, cnt_cmp);
    int min_pos = findMinPos(a, n, cnt_cmp);
    double c = (length - 1) / (a[max_pos] - a[min_pos]);

    for (int i = 0; ++cnt_cmp && i < n; i++) {
        int bucket_idx = c * (a[i] - a[min_pos]);
        ++bucket[bucket_idx];
    }

    for (int i = 1; ++cnt_cmp && i < length; i++)
        bucket[i] += bucket[i - 1];

    flashSwap(a, bucket, n, max_pos, min_pos, c, cnt_cmp);

    for (int i = 1; ++cnt_cmp && i < n; i++) {
        int key = a[i];
        int j = i - 1;

        while (++cnt_cmp && a[j] > key && ++cnt_cmp && j >= 0) {
            a[j + 1] = a[j];
            --j;
        }

        a[j + 1] = key;
    }
}

// ----------------------- calculate running time -----------------------

int findMaxPos(int a[], int n) 
{
    int m = 0;

    for (int i = 0; i < n; i++)
        if (a[i] > a[m])
            m = i;

    return m;
}

int findMinPos(int a[], int n) 
{
    int m = 0;
    
    for (int i = 0; i < n; i++)
        if (a[i] < a[m])
            m = i;

    return m;
}

void Heapify(int a[], int n, int i) 
{
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && a[largest] < a[left])
        largest = left;
    if (right < n && a[largest] < a[right])
        largest = right;
    if (largest != i) {
        swap(a[largest], a[i]);
        Heapify(a, n, largest);
    }
}

void heapSort(int a[], int n, double &duration) 
{
    duration = 0;
    auto start_time = system_clock::now();

    for (int i = n / 2 - 1; i >= 0; i--)
        Heapify(a, n, i);

    for (int i = n - 1; i >= 0; i--) {
        swap(a[i], a[0]);
        Heapify(a, i, 0);
    }

    auto end_time = system_clock::now();
    auto elapsed = end_time - start_time;
    duration = (double)elapsed.count();
}

void countSort(int a[], int n, int exp) 
{
    vector<int> output(n);
    int count[10] = { 0 };

    for (int i = 0; i < n; i++)
        ++count[(a[i] / exp) % 10];
    
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        --count[(a[i] / exp) % 10];
    }

    for (int i = 0; i < n; i++)
        a[i] = output[i];
}

void radixSort(int a[], int n, double &duration)
{
    duration = 0;
    auto start_time = system_clock::now();

    int m = findMaxPos(a, n);

    for (int exp = 1; a[m] / exp > 0; exp *= 10)
        countSort(a, n, exp);

    auto end_time = system_clock::now();
    auto elapsed = start_time - end_time;
    duration = (double)elapsed.count();
}


void flashSwap(int a[], vector<int> bucket, int n, int max_pos, int min_pos, double c)
{
    int bucket_idx = bucket.size() - 1;
    int flash;
    int move = 0;
    int i = 0;

    swap(a[max_pos], a[0]);
    while (move < n - 1) {
        while (i > bucket[bucket_idx] - 1) {
            ++i;
            bucket_idx = c * (a[i] - a[min_pos]);
        }

        flash = a[i];
        while (i != bucket[bucket_idx]) {
            bucket_idx = c * (a[i] - a[min_pos]);
            --bucket[bucket_idx];
            swap(flash, a[bucket[bucket_idx]]);
            ++move;
        }
    }
}

void flashSort(int a[], int n, double &duration)
{
    duration = 0;
    auto start_time = system_clock::now();

    int length = 0.45 * n;
    vector<int> bucket(length, 0);
    int max_pos = findMaxPos(a, n);
    int min_pos = findMinPos(a, n);
    double c = (length - 1) / (a[max_pos] - a[min_pos]);

    for (int i = 0; i < n; i++) {
        int bucket_idx = c * (a[i] - a[min_pos]);
        ++bucket[bucket_idx];
    }

    for (int i = 1; i < length; i++)
        bucket[i] += bucket[i - 1];

    flashSwap(a, bucket, n, max_pos, min_pos, c);

    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        while (a[j] > key && j >= 0) {
            a[j + 1] = a[j];
            --j;
        }

        a[j + 1] = key;
    }

    auto end_time = system_clock::now();
    auto elapsed = start_time - end_time;
    duration = (double)elapsed.count();
}

// ----------------------- command line -----------------------
// Cmd 5: (6 arguments)
//     – Prototype: [Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]
//     – Ex: a.exe -c quick-sort merge-sort 100000 -nsorted

int toInt(const string s) 
{
    int num = 0;
    for (int i = 0; i < s.size(); i++)
        num = num * 10 + s[i] - 48;
    return num;
}

void writeFile(string filename, int a[], int n) 
{
    ofstream ofs(filename.c_str());
    if (!ofs.is_open()) {
        cout << "Open file unsuccessfully!";
        return;
    }

    ofs << n << "\n";
    for (int i = 0; i < n; i++)
        ofs << a[i] << " ";

    ofs.close();
}

void printOutput(char* argv[], int data_type, long long cnt_cmp1, long long cnt_cmp2, double duration1, double duration2)
{
    cout << "COMPARISON MODE\n";
    cout << "Algorithm: " << argv[2] << " | " << argv[3] << "\n";
    cout << "Input size: " << argv[4] << "\n";
    cout << "Input order: ";
    switch (data_type) {
    case 0:
        cout << "randomized data\n";
        break;
    case 1:
        cout << "nearly sorted data\n";
        break;
    case 2:
        cout << "sorted data\n";
        break;
    case 3:
        cout << " reverse sorted data\n";
        break;
    }
    cout << "-------------------------\n";
    cout << "Running time: " << duration1 << " | " << duration2 << "\n";
    cout << "Comparisons: " << cnt_cmp1 << " | " << cnt_cmp2 << "\n";
}

void theFifthCmd(int argc, char* argv[], int cmd) 
{
    int data_type;
    for (int i = 0; i < orders.size(); i++) 
        if (orders[i] == argv[5]) {
            data_type = i;
            break;
        }
    
    int n = toInt(argv[4]);
    int *a = new int[n];
    generateData(a, n, data_type);

    string filename = "input.txt";
    writeFile(filename, a, n);

    long long cnt_cmp1, cnt_cmp2;
    countCmp(a, n, argv[2], cnt_cmp1);
    countCmp(a, n, argv[3], cnt_cmp2);

    double duration1, duration2;
    calcTime(a, n, argv[2], duration1);
    calcTime(a, n, argv[3], duration2);

    printOutput(argv, data_type, cnt_cmp1, cnt_cmp2, duration1, duration2);
}
/* 

----------------------- references -----------------------

- Heap Sort: https://www.geeksforgeeks.org/heap-sort/
- Radix Sort: https://www.geeksforgeeks.org/radix-sort/
- Flash Sort: https://www.youtube.com/watch?v=CAaDJJUszvE
              https://github.com/HaiDuc0147/sortingAlgorithm/blob/main/reportSort/Sort.cpp 
              (from line 279 to line 330)

*/
