#include <vector>
#include <string>

using namespace std;

const vector<string> modes = {"-a", "-c"};
const vector<string> algs = {"selection-sort", "insertion-sort", "bubble-sort", "shaker-sort", "shell-sort", "heap-sort", "merge-sort", "quick-sort", "counting-sort", "radix-sort", "flash-sort"};
const vector<string> inps = {"input.txt", "input_1.txt", "input_2.txt", "input_3.txt", "input_4.txt"};
const vector<string> paras = {"-time", "-comp", "-both"};
const vector<string> orders = {"-rand", "-nsorted", "-sorted", "-rev"};

void quit(const string message);

bool isMode(const string s);
bool isAlg(const string s);
bool isFile(const string s);
bool isSize(const string s);
bool isPara(int argc, char* argv[], int startId);
bool isOrder(const string s);