#include <stdio.h>
#include <stdlib.h>

struct dataItem {
    char names[2];
    int indexKey;
};



// djb2 hash algorithm http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (0 != (c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}



int main(void) {
    unsigned char text[] = "Hello";
    //unsigned long hashResult = hash(text);

    struct dataItem hashArray[2];
}