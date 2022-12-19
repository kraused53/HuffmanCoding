#include <iostream>
#include <fstream>
#include <string>
#include "llist.h"

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cout << "Please provide the path to a .txt file.\n";
    }

    // Create new, empty list
    llNode *head = NULL;

    // Open file
    std::ifstream dataFile;
    dataFile.open(argv[1]);

    // Walk throug file line by line
    std::string line;
    while(std::getline(dataFile, line)) {
        llist_append(&head, stoi(line));
    }

    // Close data file
    dataFile.close();

    // Sort the list
    llist_sort(&head);

    // Print the unsorted list
    llist_print_for_file(head);

    // Free the list
    llist_delete(&head);

    return 0;
}