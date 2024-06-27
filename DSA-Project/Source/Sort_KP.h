#pragma once

// -------------------------- count comparisons --------------------------
void quickSort(int a[], int n, long long& cnt_cmp)
void shakerSort(int a[], int n, long long& cnt_cmp);
void shellSort(int arr[], int n, long long& cnt_cmp);

// ----------------------- calculate running time -----------------------
void quickSort(int a[], int n, double& duration);
void shakerSort(int a[], int n, double& duration);
void shellSort(int arr[], int n, double& duration);