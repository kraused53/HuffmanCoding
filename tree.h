#ifndef TREE_H
    #define TREE_H

    #include <iostream> // Allows use of NULL and others
    #include <stdio.h>  // Allows the use of FILE pointers

    class btNode{
        public:
            btNode *left;
            btNode *right;
            char value;
            int freq;

            /*** <--- Constructors ---> ***/
            // If given nothing, all pointers are set to NULL, everything 
            //      else is 0
            btNode() {
                left = NULL;
                right = NULL;
                value = 0;
                freq = 0;
            }

            // If given a char and an int, create a new node with no pointers
            btNode(char new_value, int new_freq) {
                left = NULL;
                right = NULL;
                value = new_value;
                freq = new_freq;
            }

            // If given two pointers to tree nodes:
            //      The first node becomes left child and second becomes right
            //      new root node has a char of 0
            //      new root has a freq = left.freq + right.freq
            btNode(btNode *new_left, btNode *new_right) {
                left = new_left;
                right = new_right;
                value = 0;
                freq = new_left->freq + new_right->freq;
            }
    };

    /*** <--- Function prototypes ---> ***/
    void tree_print(btNode *root, FILE *output_dir);
    void tree_destroy(btNode *root);
#endif