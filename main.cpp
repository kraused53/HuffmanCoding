#include <iostream>
#include <fstream>
#include "decode.h"


int main(int argc, char **argv) {
    if(argc != 3) {
        std::cout << "Please provide input and output file paths.\n";
    }

    decode(argv[1], argv[2]);
    
    return 0;
}

