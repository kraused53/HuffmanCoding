#include "utilities.h"


/*
 * Name:
 *      print_number_char
 * Inputs:
 *      FILE *inptr
 *          - A file pointer pointing to the open output file
 *      unsigned int numChar
 *          - A 4-byte integer that represents the number of chars in the file
 * Output:
 *      None
 *          - This is a void function
 * Description:
 *      This function prints the given into to the output file
 * 
 */
void print_number_char(unsigned int numChar, FILE *out_ptr) {
    fprintf(out_ptr, "\nnumChar = %d\n", numChar);
}


/*
 * Name:
 *      read_bit
 * Inputs:
 *      FILE *in_ptr
 *          - A file pointer pointing to the open input file
 *      unsigned char *bit
 *          - A pointer to the single_bit variable in read_header()
 *      unsigned char *current_bit
 *          - A pointer to the current_bit variable in read_header()
 *      unsigned char *current_byte
 *          - A pointer to the current_byte variable in read_header()
 * Output:
 *      int
 *          - Function returns 1 on success and -1 on failure
 * Description:
 *      This function reads the contents of the input file one bit at a time 
 *          by reading a byte at a time and using bit-wise operations to 
 *          isolate the correct bit.
 * 
 */
int read_bit(
    FILE *in_ptr, 
    unsigned char *bit, 
    unsigned char *current_bit, 
    unsigned char *current_byte
    ) {
        int ret = 1;

        // If starting a new byte
        if((*current_bit) == 0) {
            // Read the next byte from the file
            ret = fread(current_byte, sizeof(unsigned char), 1, in_ptr);
        }

        // If reading a byte failed
        if(ret != 1) {
            // Failed
            return -1;
        }

        // Shift the bit to the correct location and make a copy
        unsigned char tmp = (*current_byte) >> (7-(*current_bit));
        // Isolate the LSB
        tmp &= 0x01;

        // Increment the value of current bit, use modulo to keep the value of
        //      current bit between 0 and 7
        (*current_bit) = ((*current_bit) + 1) % 8;
        
        // Bass the isolated bit back to the calling function
        (*bit) = tmp;
        return 1;
    }