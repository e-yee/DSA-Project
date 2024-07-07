#include <iostream>
#include <string.h>
#include <algorithm>
#include <fstream>
#include <iomanip>

#include "Mode.h"
#include "Sort.h"
#include "Checker.h"
#include "DataGenerator.h"

#define DEBUG_MODE 0
#define INPUTFILE "input.txt"
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

void copyArray(int* dest, int* source, int n)
{
    for (int i = 0; i < n; i++) {
        dest[i] = source[i];
    }
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

        for (int i = 5; i < argc; i++) {
            para_time |= (strcmp(argv[i], "-time") == 0) | (strcmp(argv[i], "-both") == 0);
            para_comp |= (strcmp(argv[i], "-comp") == 0) | (strcmp(argv[i], "-both") == 0);
        }

        string order_type;
        int n = atoi(argv[3]);
        int* a1 = new int[n];
        int* a2 = new int[n];

        if (strcmp(argv[4], "-rand") == 0) {
            order_type = "Randomized";
            generateRandomData(a1, n);
        } else if (strcmp(argv[4], "-nsorted") == 0) {
            order_type = "Nearly Sorted";
            generateNearlySortedData(a1, n);
        } else if (strcmp(argv[4], "-sorted") == 0) {
            order_type = "Sorted";
            generateSortedData(a1, n);
        } else if (strcmp(argv[4], "-rev") == 0) {
            order_type = "Reversed Sorted";
            generateReverseData(a1, n);
        }

        copyArray(a2, a1, n);
        writeFile(INPUTFILE, a1, n);

        cout << "Input size: " << argv[3] << '\n';
        cout << "Input order: " << order_type << '\n';
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
                if (is_sorted(a1, a1 + n))
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

    } else if (cmd == 3) {
        bool para_time = false;
        bool para_comp = false;

        for (int i = 4; i < argc; i++) {
            para_time |= (strcmp(argv[i], "-time") == 0) | (strcmp(argv[i], "-both") == 0);
            para_comp |= (strcmp(argv[i], "-comp") == 0) | (strcmp(argv[i], "-both") == 0);
        }

        int n = atoi(argv[3]);
        int* a1 = new int[n];
        int* a2 = new int[n];

        cout << "Input size: " << argv[3] << '\n';

        string order_type[4] = {"Randomize", "Nearly Sorted", "Sorted", "Reversed"};

        for (int idx = 0; idx < 4; idx++) {
            cout << '\n' << "Input order: " << order_type[idx] << '\n';
            cout << "-----------------------------\n";

            if (idx == 0) {
                generateRandomData(a1, n);
            } else if (idx == 1) {
                generateNearlySortedData(a1, n);
            } else if (idx == 2) {
                generateSortedData(a1, n);
            } else {
                generateReverseData(a1, n);
            }

            copyArray(a2, a1, n);
            string file_name = "input_" + toString(idx + 1) + ".txt";
            writeFile(file_name, a1, n);

            if (para_time) {
                double duration;
                calcTime(a1, n, argv[2], duration);
                cout << setprecision(4) << fixed;
                cout << "Running time: " << duration / 1e6 << " (milliseconds)\n";

                if (!is_sorted(a1, a1 + n))
                    quit("The array is not sorted!");
                
                /* For debugging */
                if (DEBUG_MODE) {
                    if (is_sorted(a1, a1 + n))
                        cerr << "[DEBUG]: The array a1[] is sorted!\n";
                }
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
                        cerr << "[DEBUG]: The array a2[] is sorted!\n";
                }
            }
        }
        delete[] a1;
        delete[] a2;
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

    if (cmd == 4) {
        int n = 0;
        int* a1 = readFile(argv[4], n); //sort_time 1
        int* a2 = readFile(argv[4], n); //sort_comp 1
        int* a3 = readFile(argv[4], n); //sort_time 2
        int* a4 = readFile(argv[4], n); //sort_comp 2

        cout << "Input file: " << argv[4] << '\n';
        cout << "Input size: " << n << '\n';
        cout << "-----------------------------\n";
        
        //time
        double duration_1, duration_2;
        calcTime(a1, n, argv[2], duration_1);
        calcTime(a3, n, argv[3], duration_2);
        cout << setprecision(4) << fixed;
        cout << "Running time: " << duration_1 / 1e6 << " (milliseconds) | " << 
                                    duration_2 / 1e6 << " (milliseconds)\n";

        if (!is_sorted(a1, a1 + n))
            quit("The array is not sorted!");
        
        /* For debugging */
        if (DEBUG_MODE) {
            if (is_sorted(a1, a1 + n))
                cerr << "[DEBUG]: The array a1[] is sorted!\n";
        }

        //compare
        long long cnt_cmp_1, cnt_cmp_2;
                countCmp(a2, n, argv[2], cnt_cmp_1);
                countCmp(a4, n, argv[3], cnt_cmp_2);
                cout << "Comparisons: " << cnt_cmp_1 << " | " << cnt_cmp_2 << '\n';

        if (!is_sorted(a2, a2 + n))
            quit("The array is not sorted!");
        
        /* For debugging */
        if (DEBUG_MODE) {
            if (is_sorted(a2, a2 + n))
                cerr << "[DEBUG]: The array a2[] is sorted!\n";
        }

        delete[] a1;
        delete[] a2;
        delete[] a3;
        delete[] a4;

    } else if (cmd == 5) {
        int n = stoi(argv[4]);
        int *a1 = new int[n];
        int *a2 = new int[n];
        int *a3 = new int[n];
        int *a4 = new int[n];
        int data_type = find(orders.begin(), orders.end(), argv[5]) - orders.begin();

        generateData(a1, n, data_type);
        for (int i = 0; i < n; i++) {
            a2[i] = a1[i];
            a3[i] = a1[i];
            a4[i] = a1[i];
        }

        string filename = "input.txt";
        writeFile(filename, a1, n);

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
        

        double duration_1, duration_2;
        calcTime(a1, n, argv[2], duration_1);
        calcTime(a2, n, argv[3], duration_2);
        cout << setprecision(4) << fixed;
        cout << "Running time: " << duration_1 / 1e6 << " (milliseconds)" 
                        << " | " << duration_2 / 1e6 << " (milliseconds)\n";

        if (!is_sorted(a1, a1 + n))
            quit("The array is not sorted!");
        
        /* For debugging */
        if (DEBUG_MODE) {
            if (is_sorted(a1, a1 + n))
                cerr << "[DEBUG]: The array a1[] is sorted!\n";
        }

        long long cnt_cmp_1, cnt_cmp_2;
        countCmp(a3, n, argv[2], cnt_cmp_1);
        countCmp(a4, n, argv[3], cnt_cmp_2);
        cout << "Comparisons: " << cnt_cmp_1 << " | " << cnt_cmp_2;

        if (!is_sorted(a3, a3 + n))
            quit("The array is not sorted!");
        
        /* For debugging */
        if (DEBUG_MODE) {
            if (is_sorted(a3, a3 + n))
                cerr << "[DEBUG]: The array a3[] is sorted!\n";
        }

        delete[] a1;
        delete[] a2;
        delete[] a3;
        delete[] a4;
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