#include <iostream>

using namespace std;

void algMode(int argc, char* argv[], int cmd)
{
    cout << "ALGORITHM MODE\n";
    cout << "Algorithm: " << argv[2] << '\n';
    



    // for debugging
    cout << "\ncmd: " << cmd << '\n';
}

void cmpMode(int argc, char* argv[], int cmd)
{
    cout << "COMPARISION MODE\n";
    cout << "Algorithm: " << argv[2] << " | " << argv[3] << '\n';




    // for debugging
    cout << "\ncmd: " << cmd << '\n';
}