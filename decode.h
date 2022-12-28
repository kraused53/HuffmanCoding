#ifndef DECODE_H

    #include "list.h"
    #include "tree.h"
    #include "utilities.h"

    /*** <--- Function prototypes ---> ***/
    btNode *read_header(FILE *fp);
    int decode(char *in_file, char *out_file);
#endif