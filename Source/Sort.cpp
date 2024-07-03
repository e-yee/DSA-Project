#include <iostream>
#include <vector>
#include <chrono>

#include "Sort.h"

using namespace std;
using namespace std::chrono;


// -------------------------- count comparisons --------------------------

void selectionSort(int a[], int n, long long &cnt_cmp)
{
    cnt_cmp = 0;

    for (int i = 0; ++cnt_cmp && i < n - 1; i++) {
        int min_id = i;

        for (int j = i + 1; ++cnt_cmp && j < n; j++)
            if (++cnt_cmp && a[j] < a[min_id])
                min_id = j;
        
        swap(a[i], a[min_id]);
    }
}

void insertionSort(int a[], int n, long long &cnt_cmp)
{
    cnt_cmp = 0;

    for (int i = 1; ++cnt_cmp && i < n; i++) {
        int key = a[i];
        int j = i - 1;

        while (++cnt_cmp && j >= 0 && ++cnt_cmp && key < a[j]) {
            a[j + 1] = a[j];
            --j;
        }

        a[j + 1] = key;
    }
}

void bubbleSort(int a[], int n, long long &cnt_cmp)
{
    cnt_cmp = 0;

    for (int i = 0; ++cnt_cmp && i < n - 1; i++) {
        bool do_swap = false;

        for (int j = 0; ++cnt_cmp && j < n - i - 1; j++)
            if (++cnt_cmp && a[j + 1] < a[j]) {
                swap(a[j + 1], a[j]);
                do_swap = true;
            }

        // if no swap operation was performed then array a is sorted
        // no need to do anything further
        if (++cnt_cmp && do_swap == false)
            break;
    }
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
        Heapify(a, n, i, cnt_cmp);

    for (int i = n - 1; ++cnt_cmp && i >= 0; i--) {
        swap(a[0], a[i]);
        Heapify(a, i, 0, ++cnt_cmp);
    }
}

void Merge(int a[], int l, int mid, int r, long long &cnt_cmp)
{
    vector<int> left_part(a + l, a + mid + 1);
    vector<int> right_part(a + mid + 1, a + r + 1);
    int i = 0, j = 0, id = l;
    
    while (++cnt_cmp && i < left_part.size() && ++cnt_cmp && j < right_part.size()) {
        if (++cnt_cmp && left_part[i] < right_part[j]) {
            a[id++] = left_part[i++];
        }
        else if (++cnt_cmp && left_part[i] > right_part[j]) {
            a[id++] = right_part[j++];
        }
        else {
            a[id++] = left_part[i++];
            a[id++] = right_part[j++];
        }
    }

    while (++cnt_cmp && i < left_part.size()) a[id++] = left_part[i++];
    while (++cnt_cmp && j < right_part.size()) a[id++] = right_part[j++];
}

void mergeSortRecursion(int a[], int l, int r, long long &cnt_cmp)
{
    if (++cnt_cmp && l < r) {
        int mid = (l + r) / 2;
        mergeSortRecursion(a, l, mid, cnt_cmp);
        mergeSortRecursion(a, mid + 1, r, cnt_cmp);
        Merge(a, l, mid, r, cnt_cmp);
    }
}

void mergeSort(int a[], int n, long long &cnt_cmp)
{
    cnt_cmp = 0;
    mergeSortRecursion(a, 0, n - 1, cnt_cmp);
}

void countingSort(int a[], int n, long long &cnt_cmp)
{
    cnt_cmp = 0;
    
    int maxA = a[0];
    for (int i = 0; ++cnt_cmp && i < n; i++)
        if (++cnt_cmp && maxA < a[i])
            maxA = a[i];

    int* cnt = new int[maxA + 1];
    for (int x = 0; ++cnt_cmp && x <= maxA; x++)
        cnt[x] = 0;

    for (int i = 0; ++cnt_cmp && i < n; i++)
        ++cnt[a[i]];
    
    for (int x = 0, id = 0; ++cnt_cmp && x <= maxA; x++)
        while (++cnt_cmp && cnt[x]-- > 0)
            a[id++] = x;

    delete[] cnt;
}

int findMaxPos(int a[], int n, long long &cnt_cmp) 
{
    int m = 0;
    for (int i = 1; ++cnt_cmp && i < n; i++)
        if (++cnt_cmp && a[i] > a[m])
            m = i;
    return m;
}

void countSort(int a[], int n, int exp, long long &cnt_cmp) 
{
    int *output = new int[n];
    int cnt[10] = { 0 };

    for (int i = 0; ++cnt_cmp && i < n; i++)
        ++cnt[a[i] / exp % 10];
    
    for (int i = 1; ++cnt_cmp && i < 10; i++)
        cnt[i] += cnt[i - 1];

    for (int i = n - 1; ++cnt_cmp && i >= 0; i--) {
        output[cnt[a[i] / exp % 10] - 1] = a[i];
        --cnt[a[i] /exp % 10];
    }

    for (int i = 0; ++cnt_cmp && i < n; i++)
        a[i] = output[i];

    delete[] output;
}

void radixSort(int a[], int n, long long &cnt_cmp) 
{   
    cnt_cmp = 0;

    int max_pos = findMaxPos(a, n, cnt_cmp);
    int m = a[max_pos];

    for (int exp = 1; ++cnt_cmp && a[max_pos] / exp > 0; exp *= 10)
        countSort(a, n, exp, cnt_cmp);
}

int findMinPos(int a[], int n, long long &cnt_cmp) 
{
    int m = 0;
    for (int i = 1; ++cnt_cmp && i < n; i++)
        if (++cnt_cmp && a[i] < a[m])
            m = i;
    return m;
}

void flashSwap(int a[], int n, int bucket[], int m, int min_pos, int max_pos, double c, long long &cnt_cmp)
{
    int bucket_id = m - 1;
    int flash = 0, move = 0, i = 0, k = 0;

    swap(a[max_pos], a[0]);
    while(++cnt_cmp && move < n - 1) {
        while (++cnt_cmp && i > bucket[bucket_id - 1]) {
            ++i;
            bucket_id = c * (a[i] - a[min_pos]);
        }

        flash = a[i];
        if (++cnt_cmp && bucket_id < 0) break;
        while (++cnt_cmp && i != bucket[bucket_id]) {
            bucket_id = c * (a[i] - a[min_pos]);
            int hold = a[k = --bucket[bucket_id]];
            a[k] = flash;
            flash = hold;
            ++move;
        }
    }
}

void flashSort(int a[], int n, long long &cnt_cmp) 
{
    cnt_cmp = 0;

    int m = 0.45 * n;
    int *bucket = new int[m];
    int max_pos = findMaxPos(a, n, cnt_cmp);
    int min_pos = findMinPos(a, n, cnt_cmp);
    double c = (m - 1) / (a[max_pos] - a[min_pos]);

    for (int i = 0; ++cnt_cmp && i < m; i++)
        bucket[i] = 0;

    for (int i = 0; ++cnt_cmp && i < n; i++) {
        int bucket_id = c * (a[i] - a[min_pos]);
        ++bucket[bucket_id];
    }

    for (int i = 1; ++cnt_cmp && i < m; i++)
        bucket[i] += bucket[i - 1];

    flashSwap(a, n, bucket, m, min_pos, max_pos, c, cnt_cmp);

    for (int i = 1; ++cnt_cmp && i < n; i++) {
        int key = a[i];
        int j = i - 1;

        while (++cnt_cmp && j >= 0 && ++cnt_cmp && key < a[j]) {
            a[j + 1] = a[j];
            --j;
        }

        a[j + 1] = key;
    }

    delete[] bucket;
}

// ----------------------- calculate running time -----------------------

void selectionSort(int a[], int n, double &duration)
{
    duration = 0;
    auto start_time = system_clock::now();

    for (int i = 0; i < n - 1; i++) {
        int min_id = i;

        for (int j = i + 1; j < n; j++)
            if (a[j] < a[min_id])
                min_id = j;
        
        swap(a[i], a[min_id]);
    }

    auto end_time = system_clock::now();
    auto elapsed = end_time - start_time;
    duration = (double)elapsed.count();
}

void insertionSort(int a[], int n, double &duration)
{
    duration = 0;
    auto start_time = system_clock::now();
     
    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && key < a[j]) {
            a[j + 1] = a[j];
            --j;
        }

        a[j + 1] = key;
    }

    auto end_time = system_clock::now();
    auto elapsed = end_time - start_time;
    duration = (double)elapsed.count();
}

void bubbleSort(int a[], int n, double &duration)
{
    duration = 0;
    auto start_time = system_clock::now();

    for (int i = 0; i < n - 1; i++) {
        bool do_swap = false;

        for (int j = 0; j < n - i - 1; j++)
            if (a[j + 1] < a[j]) {
                swap(a[j + 1], a[j]);
                do_swap = true;
            }
    
        // if no swap operation was performed then array a is sorted
        // no need to do anything further
        if (do_swap == false)
            break;
    }

    auto end_time = system_clock::now();
    auto elapsed = end_time - start_time;
    duration = (double)elapsed.count();
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
        swap(a[0], a[i]);
        Heapify(a, i, 0);
    }

    auto end_time = system_clock::now();
    auto elapsed = end_time - start_time;
    duration = (double)elapsed.count();
}

void Merge(int a[], int l, int mid, int r)
{
    vector<int> left_part(a + l, a + mid + 1);
    vector<int> right_part(a + mid + 1, a + r + 1);
    int i = 0, j = 0, id = l;
    
    while (i < left_part.size() && j < right_part.size()) {
        if (left_part[i] < right_part[j]) {
            a[id++] = left_part[i++];
        }
        else if (left_part[i] > right_part[j]) {
            a[id++] = right_part[j++];
        }
        else {
            a[id++] = left_part[i++];
            a[id++] = right_part[j++];
        }
    }

    while (i < left_part.size()) a[id++] = left_part[i++];
    while (j < right_part.size()) a[id++] = right_part[j++];
}

void mergeSortRecursion(int a[], int l, int r)
{
    if (l < r) {
        int mid = (l + r) / 2;
        mergeSortRecursion(a, l, mid);
        mergeSortRecursion(a, mid + 1, r);
        Merge(a, l, mid, r);
    }
}

void mergeSort(int a[], int n, double &duration)
{
    duration = 0;
    auto start_time = system_clock::now();

    mergeSortRecursion(a, 0, n - 1);

    auto end_time = system_clock::now();
    auto elapsed = end_time - start_time;
    duration = (double)elapsed.count();
}

void countingSort(int a[], int n, double &duration)
{
    duration = 0;
    auto start_time = system_clock::now();
    
    int maxA = a[0];
    for (int i = 0; i < n; i++)
        if (maxA < a[i])
            maxA = a[i];

    int* cnt = new int[maxA + 1];
    for (int x = 0; x <= maxA; x++)
        cnt[x] = 0;

    for (int i = 0; i < n; i++)
        ++cnt[a[i]];
    
    for (int x = 0, id = 0; x <= maxA; x++)
        while (cnt[x]-- > 0)
            a[id++] = x;

    delete[] cnt;

    auto end_time = system_clock::now();
    auto elapsed = end_time - start_time;
    duration = (double)elapsed.count();
}

int findMaxPos(int a[], int n) 
{
    int m = 0;
    for (int i = 1; i < n; i++)
        if (a[i] > a[m])
            m = i;
    return m;
}

void countSort(int a[], int n, int exp) 
{
    int *output = new int[n];
    int cnt[10] = { 0 };

    for (int i = 0; i < n; i++)
        ++cnt[a[i] / exp % 10];
    
    for (int i = 1; i < 10; i++)
        cnt[i] += cnt[i - 1];

    for (int i = n - 1; i >= 0; i--) {
        output[cnt[a[i] / exp % 10] - 1] = a[i];
        --cnt[a[i] / exp % 10];
    }

    for (int i = 0; i < n; i++)
        a[i] = output[i];

    delete[] output;
}

void radixSort(int a[], int n, double &duration) 
{
    duration = 0;
    auto start_time = system_clock::now();

    int max_pos = findMaxPos(a, n);
    int m = a[max_pos];

    for (int exp = 1; m / exp > 0; exp *= 10)
        countSort(a, n, exp);

    auto end_time = system_clock::now();
    auto elapsed = end_time - start_time;
    duration = (double)elapsed.count();
}

int findMinPos(int a[], int n) 
{
    int m = 0;
    for (int i = 1; i < n; i++)
        if (a[i] < a[m])
            m = i;
    return m;
}

void flashSwap(int a[], int n, int bucket[], int m, int min_pos, int max_pos, double c) 
{
    int bucket_id = m - 1;
    int flash = 0, move = 0, i = 0, k = 0;

    swap(a[max_pos], a[0]);
    while (move < n - 1) {
        while (i > bucket[bucket_id - 1]) {
            ++i;
            bucket_id = c * (a[i] - a[min_pos]);
        }

        flash = a[i];
        if (bucket_id < 0) break;
        while (i != bucket[bucket_id]) {
            bucket_id = c * (a[i] - a[min_pos]);
            int hold = a[k = --bucket[bucket_id]];
            a[k] = flash;
            flash = hold;
            ++move;
        }
    }
}

void flashSort(int a[], int n, double &duration) 
{
    duration = 0;
    auto start_time = system_clock::now();

    int m = 0.45 * n;
    int *bucket = new int[m];
    int max_pos = findMaxPos(a, n);
    int min_pos = findMinPos(a, n);
    double c = (m - 1) / (a[max_pos] - a[min_pos]);

    for (int i = 0; i < m; i++)
        bucket[i] = 0;

    for (int i = 0; i < n; i++) {
        int bucketId = c * (a[i] - a[min_pos]);
        ++bucket[bucketId];
    }

    for (int i = 1; i < m; i++)
        bucket[i] += bucket[i - 1];

    flashSwap(a, n, bucket, m, min_pos, max_pos, c);

    for (int i = 1; i < n; i++) {
        int key = a[i];
        int j = i - 1;

        while (j >= 0 && key < a[j]) {
            a[j + 1] = a[j];
            --j;
        }

        a[j + 1] = key;
    }

    delete[] bucket;

    auto end_time = system_clock::now();
    auto elapsed = end_time - start_time;
    duration = (double)elapsed.count();
}