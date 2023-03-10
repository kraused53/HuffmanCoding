#include "list.h"


/*
 * Name:
 *      llNode_merge
 * Inputs:
 *      llNode *head
 *          - A pointer to the head of a linked list
 * Output:
 *      llNode *
 *          - A pointer to the new head of the llinked list
 * Description:
 *      This function removes the first two nodes of the given linked list and 
 *          merges their binary trees. This new binary tree is then added to 
 *          a new linked list element, and this new element is added as the 
 *          head of the given linekd list.
 * 
 */
llNode * llNode_merge(llNode *head) {
    // Get the second and third nodes of the list
    llNode *second_node = head->next;
    llNode *third_node = second_node->next;

    // Get the binary trees of the first two elements
    btNode *becomes_right = head->tree_node;
    btNode *becomes_left = second_node->tree_node;

    // Merge the two trees
    btNode *merge = new btNode(becomes_left, becomes_right);

    // Create a new list node with the merged tree
    llNode *new_node = new llNode(merge);

    // Delete the first two elements of the linked list WITHOUT deleting trees
    delete head;
    delete second_node;

    // Move head to the previously third element CAN BE NULL
    head = third_node;

    // Insert newly created node as the new head node of the list
    head = llNode_insert(head, new_node);

    return head;
}


/*
 * Name:
 *      llNode_insert
 * Inputs:
 *      llNode *head
 *          - A pointer to the head of a linked list
 *      llNode *node
 *          - A pointer to a linked list node to be added to the given 
 *              linked list. This element will be added as the head element
 * Output:
 *      llNode *
 *          - A pointer to the new head of the llinked list
 * Description:
 *      This function takes a linked list node and adds it to the given linked 
 *          list as the new head node.
 * 
 */
llNode *llNode_insert(llNode *head, llNode *node) {
    // If given node is NULL, print an error and return NULL
    if(node == NULL) {
        std::cout << "ERROR! The given node was NULL";
        return NULL;
    }

    // "node" should be a single list elemnt. If given a linked list, ERROR
    if((node->next) != NULL) {
        std::cout << "ERROR! node given was a linked list";
        return NULL;
    }

    // If the given linked list is NULL, simply return node
    if(head == NULL) {
        return node;
    }

    // Otherwise, place the node before the current head and return the node
    node->next = head;
    return node;
}