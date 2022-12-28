#include "tree.h"


/*
 * Name:
 *      tree_print
 * Inputs:
 *      btNode *root
 *          - A pointer to the root of a binary tree
 *      FILE *output_dir
 *          - A file pointer that allows writing to file
 * Output:
 *      None
 *          - This is a void function, so nothing is returned
 * Description:
 *      This function recursively prints the contents of a given binary tree.
 *          This function uses post-order traversal to walk through the tree.
 *          Leaf nodes are printed with a preceding '1' and non-leaf nodes are 
 *          printed simply as '0'.
 */
void tree_print(btNode *root, FILE *output_dir) {
    // If given root is NULL, return
    if(root == NULL) {
        return;
    }

    // Print left branch first
    tree_print(root->left, output_dir);
    // Print right branch second
    tree_print(root->right, output_dir);

    // If current nod is a leaf node
    if((root->left == NULL) && (root->right == NULL)) {
        // Print a 1 followed by the value of the node
        fprintf(output_dir, "1%c", root->value);
        return;
    }

    // Otherwise print a 0
    fprintf(output_dir, "0");
}


/*
 * Name:
 *      tree_destroy
 * Inputs:
 *      btNode *root
 *          - A pointer to the root of a binary tree
 * Output:
  *      None
 *          - This is a void function, so nothing is returned
 * Description:
 *      This function recursively deletes a binary tree and frees it's memory.
 *          Using post-order traversal, the function finds leaf nodes and 
 *          deletes them until the entire tree is destroyed.
 * 
 */
void tree_destroy(btNode *root) {
    // If the current node is NULL, return
    if(root == NULL) {
        return;
    }

    // Find left most leaf
    tree_destroy(root->left);
    // Find right most leaf
    tree_destroy(root->right);

    // Delete the current node
    delete root;
}