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

bool search(unsigned char name[], struct dataItem* hashArray, unsigned long maxTableSize) {
    unsigned long hashIndex = hash(name) - 1;
    if (hashIndex > maxTableSize) {
        return false;
    } else if (hashArray[hashIndex].charValue == NULL) {
        return false;
    }
    return true;
} 

void setupDataItem(unsigned char name[], struct dataItem *firstChar) {
    int len = stringLength(name);
    int count = 0;
    firstChar->charValue = (unsigned char*) malloc(stringLength(name) * sizeof(unsigned char));
    for (int i = 0; i < stringLength(name); i++) {
        firstChar->charValue[i] = name[i];
    }
}

struct dataItem *addName(unsigned char name[], struct dataItem *hashArray, unsigned long *tableSize) {
    unsigned long hashResult = hash(name);
    if (hashResult > *tableSize) {
        hashArray = (struct dataItem*) realloc(hashArray, sizeof(struct dataItem) * hashResult);
        *tableSize = hashResult;
    }
    struct dataItem *firstChar = (struct dataItem*) malloc(sizeof(struct dataItem));
    setupDataItem(name, firstChar);
    hashArray[hashResult - 1] = *firstChar;
    return hashArray;
}

void removeName(unsigned char name[], struct dataItem* hashArray) {
        unsigned long hashIndex = hash(name) - 1;
        hashArray[hashIndex].charValue = NULL;
}


int main(void) {
    unsigned char text[] = "Freddie";
    unsigned long tableSize = 1;
    printf("Text to add: %s\n", text);

    struct dataItem *hashArray = (struct dataItem*) malloc(tableSize * sizeof(struct dataItem));
    hashArray = addName(text, hashArray, &tableSize);
    printf("Is there a value for Freddie? %d\n", search(text, hashArray, tableSize));
    removeName(text, hashArray);
    unsigned long hashIndex = hash(text) - 1;
    printf("Is there a value for Freddie? %d", search(text, hashArray, tableSize));
}
