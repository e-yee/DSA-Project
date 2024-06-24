#include <string>

using namespace std;

void algMode(int argc, char* argv[], int cmd);
void cmpMode(int argc, char* argv[], int cmd);\

void calcTime(int a[], int n, const string alg, double &duration);
void countCmp(int a[], int n, const string alg, long long &cnt_cmp);