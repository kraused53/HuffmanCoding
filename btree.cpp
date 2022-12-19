#include "btree.h"


/*
 * Name:
 *      btree_insert_node_search_tree
 * 
 * Inputs:
 *      btNode *root
 *          - Pointer to the root node of a binary search tree
 *      int data
 *          - The value to be inserted into the tree
 *  
 * Outputs:
 *      btNode *
 *          - Retruns a pointer to the root of a binary search tree with the
 *              given value added
 * 
 * Description:
 *     Recursivly searches a given binary search tree for the proper place to 
 *      add the given value, then adjusts the tree to allow a new node to 
 *      be inserted.
 * 
 */
btNode *btree_insert_node_serach_tree(btNode *root, int data) {

    // If given an empty tree
    if(root == NULL) {
        root = new btNode(data);
        return root;
    }

    // If given value is greater than value of current root,
    //      recursivly search right branch for a spot to insert node
    if(data > root->data) {
        root->right = btree_insert_node_serach_tree(root->right, data);
    }else if(data < root->data) {
        // If given value is less than value of current root,
        //      recursivly search left branch for a spot to insert node
        root->left = btree_insert_node_serach_tree(root->left, data);
    }

    return root;
}


/*
 * Name:
 *      btree_search_search_tree
 * 
 * Inputs:
 *      btNode *root
 *          - Pointer to the root node of a binary search tree
 *      int key
 *          - The value to be searched for
 *  
 * Outputs:
 *      btNode *
 *          - Retruns a pointer to the node with the given search value
 * 
 * Description:
 *     Recursivly searches a given binary search tree for a node containing 
 *          the given value.
 * 
 */
btNode *btree_search_serach_tree(btNode *root, int key) {
    // If given an empty tree or if root->data == key, return root
    if((root == NULL) || (root->data == key)) {
        return root;
    }

    // If key is more than root, search right sub-tree
    if(key > root->data) {
        return btree_search_serach_tree(root->right, key);
    }

    // If key is less than root, search left sub-tree
    return btree_search_serach_tree(root->left, key);
}


/*
 * Name:
 *      btree_print_in_order
 * 
 * Inputs:
 *      btNode *root
 *          - Pointer to the root node of a binary tree
 *  
 * Outputs:
 *      None
 *          - Void function, so no return
 * 
 * Description:
 *     Recursivly print the contents of a binary tree by following the pattern:
 *          left, root, right
 * 
 */
void btree_print_in_order(btNode * root) {
    // If given an empty tree
    if(root == NULL) {
        return;
    }

    // Travel down left branch first
    btree_print_in_order(root->left);

    // Then print root node
    std::cout << root->data << " ";

    // Then travel down right path
    btree_print_in_order(root->right);
}


/*
 * Name:
 *      btree_print_pre_order
 * 
 * Inputs:
 *      btNode *root
 *          - Pointer to the root node of a binary tree
 *  
 * Outputs:
 *      None
 *          - Void function, so no return
 * 
 * Description:
 *     Recursivly print the contents of a binary tree by following the pattern:
 *          root, left, right
 * 
 */
void btree_print_pre_order(btNode * root) {
    // If given an empty tree
    if(root == NULL) {
        return;
    }

    // Then print root node
    std::cout << root->data << " ";

    // Travel down left branch first
    btree_print_pre_order(root->left);

    // Then travel down right path
    btree_print_pre_order(root->right);
}


/*
 * Name:
 *      btree_print_post_order
 * 
 * Inputs:
 *      btNode *root
 *          - Pointer to the root node of a binary tree
 *  
 * Outputs:
 *      None
 *          - Void function, so no return
 * 
 * Description:
 *     Recursivly print the contents of a binary tree by following the pattern:
 *          left, right, root
 * 
 */
void btree_print_post_order(btNode * root) {
    // If given an empty tree
    if(root == NULL) {
        return;
    }

    // Travel down left branch first
    btree_print_post_order(root->left);

    // Then travel down right path
    btree_print_post_order(root->right);

    // Then print root node
    std::cout << root->data << " ";
}