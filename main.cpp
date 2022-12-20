#include <iostream>
#include <fstream>
#include <string>
#include "llist.h"
#include "btree.h"

int main(int argc, char **argv) {
    if(argc != 2) {
        std::cout << "Please provide the path to a .txt file.\n";
    }

    // Create new, empty binary tree
    btNode *root = NULL;
    int val_to_delete = -1;

    // Open file
    std::ifstream dataFile;
    dataFile.open(argv[1]);

    std::string line;
     // First line will be the value to delete
    std::getline(dataFile, line);
    val_to_delete = stoi(line);

    // Walk through rest of file line by line
    while(std::getline(dataFile, line)) {
        root = btree_insert_node_serach_tree(root, stoi(line));
    }

    // Close data file
    dataFile.close();

    // Delete given value
    root = btree_delete_node_serach_tree(root, val_to_delete);

    // Print remaining tree
    std::cout << "inorder: ";
    btree_print_in_order(root);

    // print a newline before pre-order
    std::cout << '\n';

    std::cout << "preorder: ";
    btree_print_pre_order(root);

    // print a newline before post-order
    std::cout << '\n';

    std::cout << "postorder: ";
    btree_print_post_order(root);

    // print a newline before exiting
    std::cout << '\n';

    return 0;
}