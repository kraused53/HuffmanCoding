#include "decode.h"


/*
 * Name:
 *      read_header
 * Inputs:
 *      FILE *in_ptr
 *          - A file pointer pointing to the open input file
 * Output:
 *      btNode *
 *          - Returns a pointer to the root of a binary tree
 * Description:
 *      This function reads the header of the given compressed huffman file 
 *          and creates the correct decoder tree.
 *      The compressed huffman file header represents the proper decoder tree 
 *          for the compressed text file. It consists of command bits and 
 *          character values
 *       The command bits are:
 *          1
 *              - Indicates that the next 8 bits will be a chacter value
 *          0
 *              - Indicates an internal tree node, merge the last 2 chacters
 * 
 */
btNode *read_header(FILE *in_ptr) {
    // Function flags
    int done = 0;

    // Function variables
    unsigned char current_bit = 0;
    unsigned char current_byte = 0;
    unsigned char single_bit = 0;
    int bit_count;
    unsigned char value = 0;

    // Create an empty linked list
    llNode *head = NULL;

    // Loop until entire decoder tree is constructed
    while(!done) {
        read_bit(in_ptr, &single_bit, &current_bit, &current_byte);

        // If a new node command is found
        if(single_bit == 1) {
            // Read the next 8 bits to get the character value for the new node
            for(bit_count = 0; bit_count < 8; bit_count++) {
                // Shift value left by one
                value <<= 1;
                // Read a bit from the file
                read_bit(in_ptr, &single_bit, &current_bit, &current_byte);
                // Place the read bit into the LSB of value
                value |= single_bit;
            }

            // Create a new binary tree node Node
            //      node->value = value
            //      node->freq = 0
            btNode *new_tree_node = new btNode(value, 0);

            // Make a new llNode and link it to new_tree_node
            llNode *new_list_node = new llNode(new_tree_node);

            // Add new_list_node as the head of the main linked list
            head = llNode_insert(head, new_list_node);
        }else {
            // If the fouund bit was 0, merge the first two nodes of the head

            // If head is NULL, the program has failed, as there are no nodes 
            //      to merge, return NULL. 
            if(head == NULL) {
                std::cout << "ERROR! Failed to merge llNodes!\n";
                return NULL;
            }

            // If there is a single Node left, the tree is complete
            //      Set done flag
            if(head->next == NULL) {
                done = 1;
            }else {
                // Otherwise,  merge the first two nodes of the list
                head = llNode_merge(head);
            }
        }
    }

    // Extract the completed tree
    btNode *root = head->tree_node;

    // Delete the linked list
    delete head;

    // Return the tree
    return root;
}


/*
 * Name:
 *      decode
 * Inputs:
 *      char *in_file
 *          - A string encoded path to the input file
 *      char *out_file
 *          - A string encoded path to the output file
 * Output:
 *      int
 *          - Function returns 1 on success and -1 on failure
 * Description:
 *      This generates the decoder tree for the compressed file and then 
 *          attempts to recreate the original file.
 * 
 */
int decode(char *in_file, char *out_file) {

    // Try to open the input file for read
    FILE *in_ptr = fopen(in_file, "r");
    if(in_ptr == NULL) {
        std::cout << "ERROR! Could not open input file.\n";
        return -1;
    }

    btNode *root = read_header(in_ptr);

    // Open the output file for write
    FILE *out_ptr = fopen(out_file, "w");
    // Write the contents of the tree to the output file
    tree_print(root, out_ptr);

    // After tree is read, the next 4 bytes (unsigned int) contains the
    //  original files char count
    unsigned int numChar = 0;
    fread(&numChar, sizeof(unsigned int), 1, in_ptr);

    unsigned char newLine;
    fread(&newLine, sizeof(unsigned char), 1, in_ptr);

    print_number_char(numChar, out_ptr);

    if(newLine != '\n') {
        std::cout << "Decoding Error!\n";
        return -1;
    }

    unsigned char current_bit = 0;
    unsigned char current_byte = 0;
    unsigned char single_bit = 0;

    while(numChar != 0) {
        btNode *node = root;

        // When a character node is found, print the node's char and
        // Return to the root of the tree.
        while((node->left) != NULL) {
            read_bit(in_ptr, &single_bit, &current_bit, &current_byte);
            // If bit is 0, move to left child
            if(single_bit == 0) {
                node = node->left;
            }else {
                // If 1, move to right child
                node = node->right;
            }
        }

        // Print the found character
        fprintf(out_ptr, "%c", node->value);
        // Decrement numChars
        numChar--;
    }

    // Free used memory
    tree_destroy(root);
    fclose(in_ptr);
    fclose(out_ptr);
    
    return 1;
}