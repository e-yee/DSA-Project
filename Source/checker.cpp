#include <algorithm>
#include <iostream>

#include "checker.h"

using namespace std;

const vector<string> modes = {"-a", "-c"};
const vector<string> algs = {"selection-sort", "insertion-sort", "bubble-sort", "shaker-sort", "shell-sort", "heap-sort", "merge-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort"};
const vector<string> inps = {"input.txt", "input_1.txt", "input_2.txt", "input_3.txt", "input_4.txt"};
const vector<string> paras = {"-time", "-comp", "-both"};
const vector<string> orders = {"-rand", "-nsorted", "-sorted", "-rev"};

int toInt(string s)
{
    int n = 0;
    for (int i = 0; i < s.size(); i++)
        n = n * 10 + s[i] - 48;
    return n;
}   

bool isInt(string s)
{
    if (s.size() < 1 || s.size() > 9)
        return false;

    for (int i = 0; i < s.size(); i++)
        if (s[i] < '0' || s[i] > '9')
            return false;

    bool check = false;
    for (int i = 0; i < s.size(); i++) {
        if ('1' <= s[i] && s[i] <= '9')
            check = true;        
        if (s[i] == '0' && check == false)
            return false;
    }
    
    return true;
}

bool isExist(const vector<string> &v, const string s)
{
    if (find(v.begin(), v.end(), s) == v.end())
        return false;
    return true;
}

bool isMode(const string s)
{
    return isExist(modes, s);
}

bool isAlg(const string s)
{
    return isExist(algs, s);
}

bool isFile(const string s)
{
    return isExist(inps, s);
}

bool isSize(const string s)
{
    if (!isInt(s))
        return false;

    int n = toInt(s);

    if (n < 1 || (int)1e6 < n)
        return false;
    return true;
}

bool isPara(int argc, char* argv[], int startId)
{
    if (argc <= startId)
        return false;

    for (int i = startId; i < argc; i++)
        if (!isExist(paras, argv[i]))
            return false;
            
    return true;
}

bool isOrder(const string s)
{
    return isExist(orders, s);
}