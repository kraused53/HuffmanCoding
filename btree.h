#ifndef BTREE_H
    #define BTREE_H

    #include <iostream>

    // Define Binary Tree btNode
    class btNode {
        public:
            int data;
            btNode *left;
            btNode *right;

            btNode(int new_data) {
                data = new_data;
                left = NULL;
                right = NULL;
            }
    };

    /*** <-- Function Prototypes --> ***/
    btNode *btree_insert_node_serach_tree(btNode *root, int data);
    btNode *btree_search_serach_tree(btNode *root, int key);
    void btree_print_in_order(btNode * root);
    void btree_print_pre_order(btNode * root);
    void btree_print_post_order(btNode * root);
#endif