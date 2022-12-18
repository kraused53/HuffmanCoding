#ifndef LLIST_H
    #define LLIST_H

    #include <iostream>
    
    /*** <-- Define Linked List Node --> ***/
    class Node {
        public:
            int data;
            Node *next;

            Node(int new_data, Node *new_next) {
                data = new_data;
                next = new_next;
            }
    };

    /*** <-- Function Prototypes --> ***/
    void llist_print(Node *head);
    void llist_print_for_file(Node *head);
    void llist_append(Node **head_ref, int new_data);
    void llist_delete(Node **head_ref);
    Node *llist_get_last(Node *head);
    void llist_sort(Node **head_ref);
#endif