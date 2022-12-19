#ifndef LLIST_H
    #define LLIST_H

    #include <iostream>
    
    /*** <-- Define Linked List llNode --> ***/
    class llNode {
        public:
            int data;
            llNode *next;

            llNode(int new_data, llNode *new_next) {
                data = new_data;
                next = new_next;
            }
    };

    /*** <-- Function Prototypes --> ***/
    void llist_print(llNode *head);
    void llist_print_for_file(llNode *head);
    void llist_append(llNode **head_ref, int new_data);
    void llist_delete(llNode **head_ref);
    llNode *llist_get_last(llNode *head);
    void llist_sort(llNode **head_ref);
#endif