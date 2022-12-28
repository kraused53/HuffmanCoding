#ifndef LIST_H
    #define LIST_H

    #include <iostream>
    #include "tree.h"

    class llNode {
        public:
            llNode *next;
            btNode *tree_node;

            /*** <--- Constructors ---> ***/
            // If given no tree node, all pointers a NULL
            llNode() {
                next = NULL;
                tree_node = NULL;
            }

            // If given a tree node, pass it to internal tree node pointer
            llNode(btNode *root) {
                next = NULL;
                tree_node = root;
            }
    };

    /*** <--- Function prototypes ---> ***/
    llNode * llNode_merge(llNode *head);
    llNode *llNode_insert(llNode *head, llNode *node);
#endif