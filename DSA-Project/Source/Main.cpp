#include <iostream>
#include <string.h>

#include "Checker.h"
#include "Mode.h"

using namespace std;

/*
    Sorting algorithms: (Please use the following algorithm names exactly when using the command)
    - selection-sort
    - insertion-sort
    - bubble-sort
    - shaker-sort
    - shell-sort
    - heap-sort
    - merge-sort
    - quick-sort
    - counting-sort
    - radix-sort
    - flash-sort
*/

/*
Algorithm mode

    Cmd 1: (5 arguments)
    - Prototype: [Execution file] -a [Algorithm] [Given input] [Output parameter(s)]
    - Ex: a.exe -a radix-sort input.txt -both

    Cmd 2: (6-7 arguments)
    – Prototype: [Execution file] -a [Algorithm] [Input size] [Input order] [Output parameter(s)]
    – Ex: a.exe -a selection-sort 50 -rand -time

    Cmd 3: (5-6 arguments)
    – Prototype: [Execution file] -a [Algorithm] [Input size] [Output parameter(s)]
    – Ex: a.exe -a binary-insertion-sort 70000 -comp

Comparision mode

    Cmd 4: (5 arguments)
    – Prototype: [Execution file] -c [Algorithm 1] [Algorithm 2] [Given input]
    – Ex: a.exe -c heap-sort merge-sort input.txt

    Cmd 5: (6 arguments)
    – Prototype: [Execution file] -c [Algorithm 1] [Algorithm 2] [Input size] [Input order]
    – Ex: a.exe -c quick-sort merge-sort 100000 -nsorted
*/


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