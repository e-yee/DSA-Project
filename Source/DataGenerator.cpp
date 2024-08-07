﻿#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>

#include "DataGenerator.h"

using namespace std;

template <class T>
void Swap(T &a, T &b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void generateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
		a[i] = rand() % n;
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void generateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
		a[i] = i;
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void generateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
		a[i] = n - 1 - i;
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void generateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
		a[i] = i;

	srand((unsigned int)time(NULL));

	// for (int i = 0; i < 10; i++) {
	// 	int r1 = rand() % n;
	// 	int r2 = rand() % n;
	// 	Swap(a[r1], a[r2]);
	// }

	int r1, r2;
	r1 = r2 = 0;
	do {
		r1 = rand() % n;
        r2 = rand() % n;
	} while (r1 == r2);

	swap(a[r1], a[r2]);
}

void generateData(int a[], int n, int data_type)
{
	switch (data_type)
	{
	case 0: // ngẫu nhiên
		generateRandomData(a, n);
		break;
	case 1: // có thứ tự
		generateSortedData(a, n);
		break;
	case 2: // có thứ tự ngược
		generateReverseData(a, n);
		break;
	case 3: // gần như có thứ tự
		generateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}

int* createArray(int n)
{
    int* a = new int[n];
    return a;
}

void deleteArray(int* a)
{
    delete[] a;
}

void generateDataA(int* a, int n, int data_type, string filename)
{
    a = createArray(n);
	switch (data_type)
	{
	case 0: // ngẫu nhiên
		generateRandomData(a, n);
		break;
	case 1: // có thứ tự
		generateSortedData(a, n);
		break;
	case 2: // có thứ tự ngược
		generateReverseData(a, n);
		break;
	case 3: // gần như có thứ tự
		generateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
        return;
	}

    ofstream output_file(filename.c_str());
    if (output_file.is_open()) {
        output_file << n << endl;
        for (int i = 0; i < n; i++) {
            output_file << a[i] << " ";
        }
        output_file.close();
        cout << "Data written to file successfully." << endl;
    } else {
        cout << "Error opening file." << endl;
    }
    deleteArray(a);
}