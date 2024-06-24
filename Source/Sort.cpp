#include <iostream>
#include <vector>

#include "Sort.h"

#define CHARBIT 8 

using namespace std;

void Fill(int a[], int n, int val)
{
    while (n) a[--n] = val;
}

int Max(int x, int y) 
{ 
    return x - ((x - y) & ((x - y) >> (sizeof(int) * CHARBIT - 1))); 
}

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

        while (++cnt_cmp && key < a[j] && ++cnt_cmp && j >= 0) {
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

void megreSort(int a[], int l, int r, long long &cnt_cmp)
{
    if (++cnt_cmp && l < r) {
        int mid = (l + r) >> 1;
        megreSort(a, l, mid, cnt_cmp);
        megreSort(a, mid + 1, r, cnt_cmp);
        Merge(a, l, mid, r, cnt_cmp);
    }
}

void countingSort(int a[], int n, long long &cnt_cmp)
{
    int maxA = a[0];
    for (int i = n; i; i--)
        maxA = Max(maxA, a[i - 1]);
    
    int* cnt = new int[maxA + 1];
    Fill(cnt, maxA + 1, 0);

    for (int i = n; i; i--)
        ++cnt[a[i - 1]];

    int id = n - 1;
    while (maxA) {
        while (cnt[maxA]) {
            a[id--] = maxA;
            --cnt[maxA];
        }
        --maxA;
    }
    while (cnt[0]) {
        a[id--] = 0;
        --cnt[0];
    }
    
    delete[] cnt;
}   