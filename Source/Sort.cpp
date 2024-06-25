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

    for (int i = 0; ++cnt_cmp && i < n - 1; i++)
        for (int j = 0; ++cnt_cmp && j < n - i - 1; j++)
            if (++cnt_cmp && a[j + 1] < a[j])
                swap(a[j + 1], a[j]);
}

void Merge(int a[], int l, int mid, int r, long long &cnt_cmp)
{
    vector<int> left_part(a + l, a + mid + 1);
    vector<int> right_part(a + mid + 1, a + r + 1);
    int i = 0, j = 0, id = l;
    
    while (++cnt_cmp && i < left_part.size() && ++cnt_cmp && j < right_part.size()) {
        if (++cnt_cmp && left_part[i] < right_part[j]) {
            a[id++] = left_part[i];
            ++i;
        }
        else if (++cnt_cmp && left_part[i] > right_part[j]) {
            a[id++] = right_part[j];
            ++j;
        }
        else {
            a[id++] = left_part[i];
            a[id++] = right_part[j];
            ++i;
            ++j;
        }
    }
}

void megreSortRecursion(int a[], int l, int r, long long &cnt_cmp)
{
    if (++cnt_cmp && l < r) {
        int mid = (l + r) >> 1;
        megreSortRecursion(a, l, mid, cnt_cmp);
        megreSortRecursion(a, mid + 1, r, cnt_cmp);
        Merge(a, l, mid, r, cnt_cmp);
    }
}

void mergeSort(int a[], int n, long long &cnt_cmp)
{
    cnt_cmp = 0;
    megreSortRecursion(a, 0, n, cnt_cmp);
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

    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (a[j + 1] < a[j])
                swap(a[j + 1], a[j]);

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
            a[id++] = left_part[i];
            ++i;
        }
        else if (left_part[i] > right_part[j]) {
            a[id++] = right_part[j];
            ++j;
        }
        else {
            a[id++] = left_part[i];
            a[id++] = right_part[j];
            ++i;
            ++j;
        }
    }
}

void megreSortRecursion(int a[], int l, int r)
{
    if (l < r) {
        int mid = (l + r) >> 1;
        megreSortRecursion(a, l, mid);
        megreSortRecursion(a, mid + 1, r);
        Merge(a, l, mid, r);
    }
}

void mergeSort(int a[], int n, double &duration)
{
    duration = 0;
    auto start_time = system_clock::now();

    megreSortRecursion(a, 0, n);

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