#include <stdio.h>

// djb2 hash algorithm http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (c == *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash;
}

int main(void) {
    unsigned char text[] = "hello";
    unsigned long hashResult = hash(text);
    printf("return hash is %ld", hashResult);
}