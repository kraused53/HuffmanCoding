#include "llist.h"

// Function prototypes for internal use functions
llNode *llist_sort_internal(llNode *head, llNode *end);
llNode *llist_partition_internal(
    llNode *head,
    llNode *end, 
    llNode **new_head,
    llNode **new_end
);

/*
 * Name:
 *      llist_print
 * 
 * Inputs:
 *      llNode *head
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
void llist_print(llNode *head) {
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
 *      llNode *head
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
void llist_print_for_file(llNode *head) {
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
 *      llNode **head_ref
 *          - Reference to the first element in linked list
 *      int new_data
 *          - Value of llNode to be added to the list
 *  
 * Outputs:
 *      None
 *          - This is a void function, there is nothing returned
 * 
 * Description:
 *     
 * 
 */
void llist_append(llNode **head_ref, int new_data) {
    // Allocate new llNode and add new data value
    // It does not point to anything yet
    llNode *new_llNode = new llNode(new_data, NULL);

    // If head is empty, the new llNode is now head
    if(*head_ref == NULL) {
        *head_ref = new_llNode;
        return;
    }

    // Otherwise, find the last llNode in the list
    llNode *last = llist_get_last(*head_ref);

    // Place the new llNode at the end of the list
    last->next = new_llNode;
}


/*
 * Name:
 *      llist_delete
 * 
 * Inputs:
 *      llNode **head_ref
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
void llist_delete(llNode **head_ref) {
    // These will be used to walk through the list element by element
    llNode *current = *head_ref;
    llNode *next = NULL;

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
 *      llNode *head
 *          - First element in a list
 *  
 * Outputs:
 *      llNode*
 *          - Returns a pointer to the last emelent in the list
 * 
 * Description:
 *      This function will find and return the last emelent in a list
 * 
 */
llNode *llist_get_last(llNode *head) {
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
 *      llNode **head_ref
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
void llist_sort(llNode **head_ref) {
    *head_ref = llist_sort_internal(*head_ref, llist_get_last(*head_ref));
    return;
}




/**** INTERNAL FUNCTIONS, NOT VISIBLE TO OTHER FILES ****/


/*
 * Name:
 *      llist_sort_internal
 * 
 * Inputs:
 *      llNode *head
 *          - Pointer the the fist element in the list
 *      llNode *end
 *          - Pointer to the last element in the list
 *  
 * Outputs:
 *      llNode *
 *          - Returns a pointer to the sorted list
 * 
 * Description:
 *     This function uses the quick sort algorithm to sort the given list \
 *          recursively
 * 
 */
llNode *llist_sort_internal(llNode *head, llNode *end) {
    // Base condition
    if((!head) || (head == end)) {
        return head;
    }

    llNode *new_head = NULL;
    llNode *new_end = NULL;

    // Partition the list. new_head and new_end will be updated by the 
    //      partition function
    llNode *pivot = llist_partition_internal(
        head,
        end,
        &new_head,
        &new_end
    );

    // If the pivot is the smalles element, no need to sort left half
    if(new_head != pivot) {
        llNode *tmp = new_head;
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
 *     llNode *head
 *          - Pointer the the fist element in the list
 *     llNode *end
 *          - Pointer to the last element in the list
 *     llNode *new_head
 *          - Pointer the the fist element in the new partition
 *     llNode *new_end
 *          - Pointer to the last element in the new partition
 *  
 * Outputs:
 *     llNode *
 *          - Returns a pointer to the pivot llNode
 * 
 * Description:
 *     This function breaks a given list into  a sub partition
 * 
 */
llNode *llist_partition_internal(
    llNode *head,
    llNode *end, 
    llNode **new_head,
    llNode **new_end
) {
    // Create llNodes for internal data handeling
    llNode *pivot = end;
    llNode *prev = NULL;
    llNode *cur = head;
    llNode *tail = pivot;

    while(cur != pivot) {
        // The fist llNode that has a value less than the pivot 
        //      becomes the new head
        if(cur->data < pivot->data) {
            if(*new_head == NULL) {
                *new_head = cur;
            }
            prev = cur;
            cur = cur->next;
        }else {     // If the current llNode is greater than the pivot
            // Move cur llNode to tail->next and change tail
            if(prev) {
                prev->next = cur->next;
            }

            llNode *tmp = cur->next;
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