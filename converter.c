/*
 * Trivial implementation of converter function.
 * You may override this file or create your own.
 */


#include <string.h>
#include <stdlib.h>
#include "converter.h"


unsigned int convert(const char *str){
    unsigned int value = 0;
    while(*str) {
        value = (value << 1) + (value << 3) + *(str++) - 48;
    }
    return value;
}

void convert_all(unsigned nlines, char *lines[], quote_t nums[])
{
    for (unsigned i = 0; i < nlines; i++) {
        nums[i] = convert(lines[i]);
    }
}
