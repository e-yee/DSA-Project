#include <iostream>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <iomanip>

#include "Mode.h"
#include "Sort.h"
#include "Checker.h"
#include "Sort_KP.h"
#include "DataGenerator.h"

#define DEBUG_MODE 0
#define OUTFILE "output.txt"

using namespace std;

int* readFile(string filename, int &n)
{
    n = 0;
    ifstream fin(filename.c_str());

    if (!fin.is_open())
        quit("Fail to read \"" + filename + "\"");
    
    fin >> n;

    int* a = new int[n];
    for (int i = 0; i < n; i++)
        fin >> a[i];
    
    fin.close();
    return a;
}

void writeFile(string filename, int a[], int n)
{
    ofstream fout(filename.c_str());

    if (!fout.is_open())
        quit("Fail to open \"" + filename + "\"");

    fout << n << '\n';
    for (int i = 0; i < n; i++)
        fout << a[i] << " \n"[i == n - 1];

    fout.close();
}

void algMode(int argc, char* argv[], int cmd)
{
    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << argv[2] << '\n';
    
    if (cmd == 1) {
        bool para_time = false;
        bool para_comp = false;

        for (int i = 4; i < argc; i++) {
            para_time |= (strcmp(argv[i], "-time") == 0) | (strcmp(argv[i], "-both") == 0);
            para_comp |= (strcmp(argv[i], "-comp") == 0) | (strcmp(argv[i], "-both") == 0);
        }

        int n = 0;
        int* a1 = readFile(argv[3], n);
        int* a2 = readFile(argv[3], n); // may need to sort the data twice

        cout << "Input file: " << argv[3] << '\n';
        cout << "Input size: " << n << '\n';
        cout << "-----------------------------\n";


        if (para_time) {
            double duration;
            calcTime(a1, n, argv[2], duration);
            cout << setprecision(4) << fixed;
            cout << "Running time: " << duration / 1e6 << " (milliseconds)\n";

            if (!is_sorted(a1, a1 + n))
                quit("The array is not sorted!");
            
            /* For debugging */
            if (DEBUG_MODE) {
                if (is_sorted(a2, a2 + n))
                    cerr << "[DEBUG]: The array a1[] is sorted!\n";
            }

            writeFile(OUTFILE, a1, n);
        }

        if (para_comp) {
            long long cnt_cmp;
            countCmp(a2, n, argv[2], cnt_cmp);
            cout << "Comparisons: " << cnt_cmp << '\n';

            if (!is_sorted(a2, a2 + n))
                quit("The array is not sorted!");

            /* For debugging */
            if (DEBUG_MODE) {
                if (is_sorted(a2, a2 + n))
                    cerr << "[DEBUG]: The array a1[] is sorted!\n";
            }

            writeFile(OUTFILE, a2, n);
        }

        delete[] a1;
        delete[] a2;
    }
    else if (cmd == 2) {
        bool para_time = false;
        bool para_comp = false;
    }

    /* For debugging */
    if (DEBUG_MODE) {
       cerr << "\ncmd: " << cmd << '\n';
    }    
}

void cmpMode(int argc, char* argv[], int cmd)
{
    cout << "COMPARISION MODE\n";
    cout << "Algorithm: " << argv[2] << " | " << argv[3] << '\n';

    double duration1, duration2;
    long long cnt_cmp1, cnt_cmp2;

    if (cmd == 4) {
        return;
    }
    else if (cmd == 5) {
        int n = stoi(argv[4]);
        int *a = new int[n];
        int data_type = find(orders.begin(), orders.end(), argv[5]) - orders.begin();
        
        generateData(a, n, data_type);

        string filename = "input.txt";
        writeFile(filename, a, n);

        calcTime(a, n, argv[2], duration1);
        calcTime(a, n, argv[3], duration2);

        countCmp(a, n, argv[2], cnt_cmp1);
        countCmp(a, n, argv[3], cnt_cmp2);

        cout << "Input size: " << n << "\n";
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
            cout << "reversed data\n";
            break;
        }
        cout << "-------------------------\n";
        cout << setprecision(4) << fixed;
        cout << "Running time: " << duration1 / 1e6 << " (milliseconds)"
                        << " | " << duration2 / 1e6 << " (milliseconds)\n";
        cout << "Comparisons: " << cnt_cmp1 << " | " << cnt_cmp2 << "\n";

        delete[] a;
    }

    if (DEBUG_MODE) {
       cerr << "\ncmd: " << cmd << '\n';
    }    
}


void calcTime(int a[], int n, const string alg, double &duration)
{
    int type = find(algs.begin(), algs.end(), alg) - algs.begin();
    
    if (type == 0) selectionSort(a, n, duration); 
    if (type == 1) insertionSort(a, n, duration);
    if (type == 2) bubbleSort(a, n, duration);
    if (type == 3) shakerSort(a, n, duration);
    if (type == 4) shellSort(a, n, duration);
    if (type == 5) heapSort(a, n, duration);
    if (type == 6) mergeSort(a, n, duration);
    if (type == 7) quickSort(a, n, duration);
    if (type == 8) countingSort(a, n, duration);
    if (type == 9) radixSort(a, n, duration);
    if (type == 10) flashSort(a, n, duration);
}

void countCmp(int a[], int n, const string alg, long long &cnt_cmp)
{
    int type = find(algs.begin(), algs.end(), alg) - algs.begin();
    
    if (type == 0) selectionSort(a, n, cnt_cmp); 
    if (type == 1) insertionSort(a, n, cnt_cmp);
    if (type == 2) bubbleSort(a, n, cnt_cmp);
    if (type == 3) shakerSort(a, n, cnt_cmp);
    if (type == 4) shellSort(a, n, cnt_cmp);
    if (type == 5) heapSort(a, n, cnt_cmp);
    if (type == 6) mergeSort(a, n, cnt_cmp);
    if (type == 7) quickSort(a, n, cnt_cmp);
    if (type == 8) countingSort(a, n, cnt_cmp);
    if (type == 9) radixSort(a, n, cnt_cmp);
    if (type == 10) flashSort(a, n, cnt_cmp);
}