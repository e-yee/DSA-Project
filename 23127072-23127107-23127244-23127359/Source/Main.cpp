#include <iostream>
#include <string.h>

#include "Checker.h"
#include "Mode.h"

using namespace std;

int classifyCmd(int argc, char* argv[])
{
    if (!isMode(argv[1]))
        return -1;

    if (strcmp(argv[1], "-a") == 0) {

        if (!isAlg(argv[2]))
            return -1;

        if (isFile(argv[3]) && isPara(argc, argv, 4))
            return 1;
        
        if (isSize(argv[3]) && isOrder(argv[4]) && isPara(argc, argv, 5))
            return 2;

        if (isSize(argv[3]) && isPara(argc, argv, 4))
            return 3;
        
        return -1;
    }

    if (!isAlg(argv[2]) && !isAlg(argv[3]))
        return -1;
    
    if (argc == 5 && isFile(argv[4]))
        return 4;
    
    if (argc == 6 && isSize(argv[4]) && isOrder(argv[5]))
        return 5;
    
    return -1;
}

int main(int argc, char* argv[])
{
    if (argc < 5)
        quit("Invalid number of arguments!");

    int cmd = classifyCmd(argc, argv);

    if (cmd == -1)
        quit("Invalid arguments!");

    if (1 <= cmd && cmd <= 3)
        algMode(argc, argv, cmd);
    else
        cmpMode(argc, argv, cmd);

    return 0;
}