#ifndef UTILITIES_H
    #define UTILITIES_H

    #include <iostream>

    #define NUM_BITS 8

    /*** <--- Function prototypes ---> ***/
    void print_number_char(unsigned int numChar, FILE *out_ptr);
    int read_bit(
    FILE *in_ptr, 
        unsigned char *bit, 
        unsigned char *current_bit, 
        unsigned char *current_byte
        );
#endif