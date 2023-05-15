// Please note this is a C program
// It compiles without warnings with gcc
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <iostream>
#include "huffmanTree.h"



int main(int argc, char *argv[])
{
    huffmanTree obj1;
    obj1.readCompressedFile(argv[3]);
    obj1.getMessageThreads(argc,argv);
    obj1.printMessage();

    return 0;
}
