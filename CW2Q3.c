#include <stdio.h>
#include <stdlib.h>

// own bool type
typedef int bool;
#define true 1
#define false 0

struct dataItem {
    unsigned char* charValue;
};

// checks for terminating value and returns the length
int stringLength(unsigned char* ptr) {
    int length = 0;
    while (ptr[length] != '\0') {
        length++;
    }
    return length;
}

// djb2 hash algorithm http://www.cse.yorku.ca/~oz/hash.html
unsigned long hash(unsigned char *str)
{
    unsigned long hash = 5381;
    int c;

    while (0 != (c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash / 100;
}

/* bool search(unsigned char name[], struct dataItem* hasharray[]) {
    int hashIndex = hash(name);
    if (hasharray[hashIndex] != NULL) {
        return true;
    }
    return false;
}  */

void setupDataItem(unsigned char name[], struct dataItem *firstChar) {
    int len = stringLength(name);
    int count = 0;
    firstChar->charValue = (unsigned char*) malloc(stringLength(name) * sizeof(unsigned char));
    for (int i = 0; i < stringLength(name); i++) {
        firstChar->charValue[i] = name[i];
    }
}

void addName(unsigned char name[], struct dataItem* hashArray, int tableSize) {
    unsigned long hashResult = hash(name);
    if (hashResult > tableSize) {
        hashArray = (struct dataItem*) malloc(sizeof(struct dataItem) * hashResult);
        printf("Increased size to %lu\n", hashResult);
    }
    struct dataItem *firstChar = (struct dataItem*) malloc(sizeof(struct dataItem));
    setupDataItem(name, firstChar);
    hashArray[hashResult] = *firstChar;
}

void removeName(unsigned char name[], struct dataItem* hasharray) {
    
}


int main(void) {
    unsigned char text[] = "Freddie";
    int tableSize = 1;
    printf("%s\n", text);

    struct dataItem hashArray[tableSize];
    addName(text, hashArray, tableSize);
    //printf("Is there a value for Freddie? %d", search(text, hashArray));

}