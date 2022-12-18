#include "llist.h"

// Function prototypes for internal use functions
Node *llist_sort_internal(Node *head, Node *end);
Node *llist_partition_internal(
    Node *head,
    Node *end, 
    Node **new_head,
    Node **new_end
);

/*
 * Name:
 *      llist_print
 * 
 * Inputs:
 *      Node *head
 *          - A pointer to the first emelent in the linked list
 * 
 * Outputs:
 *      None
 *          - This is a void function, there is nothing returned
 * 
 * Description:
 *      Given a pointer to the first element in the linked list, this function 
 *          will print the contents of the list in a structured format.
 */
void llist_print(Node *head) {
    // Check to see if given head is NULL
    if(head == NULL) {
        std::cout << "The given linked list is empty!\n";
        return;
    }

    // Loop until the end of the list
    while(head != NULL) {
        std::cout << "[" << head->data << "]";

        if(head->next != NULL) {
            std::cout << "->";
        }

        head = head->next;
    }
    std::cout << '\n';
}


/*
 * Name:
 *      llist_print_for_file
 * 
 * Inputs:
 *      Node *head
 *          - A pointer to the first emelent in the linked list
 * 
 * Outputs:
 *      None
 *          - This is a void function, there is nothing returned
 * 
 * Description:
 *      Given a pointer to the first element in the linked list, this function 
 *          will print the contents of the list in a structured format. Each
 *          element gets printed to a new line with no extra visuals
 */
void llist_print_for_file(Node *head) {
    // Check to see if given head is NULL
    if(head == NULL) {
        std::cout << "The given linked list is empty!\n";
        return;
    }

    // Loop until the end of the list
    while(head != NULL) {
        std::cout << head->data << '\n';
        head = head->next;
    }
}


/*
 * Name:
 *      llist_append
 * 
 * Inputs:
 *      Node **head_ref
 *          - Reference to the first element in linked list
 *      int new_data
 *          - Value of node to be added to the list
 *  
 * Outputs:
 *      None
 *          - This is a void function, there is nothing returned
 * 
 * Description:
 *     
 * 
 */
void llist_append(Node **head_ref, int new_data) {
    // Allocate new node and add new data value
    // It does not point to anything yet
    Node *new_node = new Node(new_data, NULL);

    // If head is empty, the new node is now head
    if(*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    // Otherwise, find the last node in the list
    Node *last = llist_get_last(*head_ref);

    // Place the new node at the end of the list
    last->next = new_node;
}


/*
 * Name:
 *      llist_delete
 * 
 * Inputs:
 *      Node **head_ref
 *          - Reference to the first element in a list
 *  
 * Outputs:
 *      None
 *          - This is a void function, there is nothing returned
 * 
 * Description:
 *      This function will delete the contents of the given list and free it 
 *          from memory.
 *     
 * 
 */
void llist_delete(Node **head_ref) {
    // These will be used to walk through the list element by element
    Node *current = *head_ref;
    Node *next = NULL;

    // Cycle through every element in the list
    while(current != NULL) {
        // Find the next element in the list
        next = current->next;
        // Delete the current element
        free(current);
        // Step to the next element
        current = next;
    }

    // Delete the original list reference
    *head_ref = NULL;
}


/*
 * Name:
 *      llist_get_last
 * 
 * Inputs:
 *      Node *head
 *          - First element in a list
 *  
 * Outputs:
 *      Node*
 *          - Returns a pointer to the last emelent in the list
 * 
 * Description:
 *      This function will find and return the last emelent in a list
 * 
 */
Node *llist_get_last(Node *head) {
    while((head != NULL) && (head->next != NULL)) {
        head = head->next;
    }

    return head;
}


/*
 * Name:
 *      llist_sort
 * 
 * Inputs:
 *      Node **head_ref
 *          - Reference to the first element in a list
 *  
 * Outputs:
 *      None
 *          - This is a void function, there is nothing returned
 * 
 * Description:
 *      This function will sort a given linked list using quicksort
 * 
 */
void llist_sort(Node **head_ref) {
    *head_ref = llist_sort_internal(*head_ref, llist_get_last(*head_ref));
    return;
}




/**** INTERNAL FUNCTIONS, NOT VISIBLE TO OTHER FILES ****/


/*
 * Name:
 *      llist_sort_internal
 * 
 * Inputs:
 *      Node *head
 *          - Pointer the the fist element in the list
 *      Node *end
 *          - Pointer to the last element in the list
 *  
 * Outputs:
 *      Node *
 *          - Returns a pointer to the sorted list
 * 
 * Description:
 *     This function uses the quick sort algorithm to sort the given list \
 *          recursively
 * 
 */
Node *llist_sort_internal(Node *head, Node *end) {
    // Base condition
    if((!head) || (head == end)) {
        return head;
    }

    Node *new_head = NULL;
    Node *new_end = NULL;

    // Partition the list. new_head and new_end will be updated by the 
    //      partition function
    Node *pivot = llist_partition_internal(
        head,
        end,
        &new_head,
        &new_end
    );

    // If the pivot is the smalles element, no need to sort left half
    if(new_head != pivot) {
        Node *tmp = new_head;
        while(tmp->next != pivot) {
            tmp = tmp->next;
        }

        tmp->next = NULL;

        new_head = llist_sort_internal(new_head, tmp);

        tmp = llist_get_last(new_head);
        tmp->next = pivot;
    }

    pivot->next = llist_sort_internal(pivot->next, new_end);

    return new_head;
}


/*
 * Name:
 *      llist_partition_internal
 * 
 * Inputs:
 *     Node *head
 *          - Pointer the the fist element in the list
 *     Node *end
 *          - Pointer to the last element in the list
 *     Node *new_head
 *          - Pointer the the fist element in the new partition
 *     Node *new_end
 *          - Pointer to the last element in the new partition
 *  
 * Outputs:
 *     Node *
 *          - Returns a pointer to the pivot node
 * 
 * Description:
 *     This function breaks a given list into  a sub partition
 * 
 */
Node *llist_partition_internal(
    Node *head,
    Node *end, 
    Node **new_head,
    Node **new_end
) {
    // Create Nodes for internal data handeling
    Node *pivot = end;
    Node *prev = NULL;
    Node *cur = head;
    Node *tail = pivot;

    while(cur != pivot) {
        // The fist node that has a value less than the pivot 
        //      becomes the new head
        if(cur->data < pivot->data) {
            if(*new_head == NULL) {
                *new_head = cur;
            }
            prev = cur;
            cur = cur->next;
        }else {     // If the current node is greater than the pivot
            // Move cur node to tail->next and change tail
            if(prev) {
                prev->next = cur->next;
            }

            Node *tmp = cur->next;
            cur->next = NULL;
            tail->next = cur;
            tail = cur;
            cur = tmp;
        }
    }

    // If the pivot has the smallest element in the current list,
    //      pivot becomes new head
    if(*new_head == NULL) {
        *new_head = pivot;
    }
    *new_end = tail;

    return pivot;
}

/*
 * Name:
 *      
 * 
 * Inputs:
 *      
 *  
 * Outputs:
 *      
 * 
 * Description:
 *     
 * 
 */