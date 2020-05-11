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
    return hash / 1000000;
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

// setup dataItem so it stores the name to input as struct which contains a char array
void setupDataItem(unsigned char name[], struct dataItem *firstChar) {
    int len = stringLength(name);
    int count = 0;
    firstChar->charValue = (unsigned char*) malloc(stringLength(name) * sizeof(unsigned char));
    for (int i = 0; i < stringLength(name); i++) {
        firstChar->charValue[i] = name[i];
    }
}

// add method, needs to return pointer to start of array as it may resize depending on the input to dynamicly adjust the amount of memory needed
struct dataItem *addName(unsigned char name[], struct dataItem *hashArray, unsigned long *tableSize) {
    unsigned long hashResult = hash(name);
    //printf("Hash result: %lu, vs table size %lu\n", hashResult, *tableSize);
    if (hashResult > *tableSize) {
        hashArray = realloc(hashArray, sizeof(struct dataItem) * hashResult);
        *tableSize = hashResult;
    }
    struct dataItem *firstChar = (struct dataItem*) malloc(sizeof(struct dataItem));
    setupDataItem(name, firstChar);
    hashArray[hashResult - 1] = *firstChar;
    printf("Data item %s has been added.\n", name);
    return hashArray;
}

// remove method, removes a value from the hash table
void removeName(unsigned char name[], struct dataItem* hashArray, unsigned long tableSize) {
    unsigned long hashIndex = hash(name) - 1;
    if (hashIndex > tableSize) {
        printf("Name does not exist in table.\n");
    } else if (hashArray[hashIndex].charValue == NULL) {
        printf("Name does not exist in table.\n");       
    } else {
        hashArray[hashIndex].charValue = NULL;
        printf("Data item %s has been removed.\n", name);
    }
}


int main(void) {
    // hash table declaration
    unsigned long tableSize = 1;
    struct dataItem *hashArray = (struct dataItem*) malloc(tableSize * sizeof(struct dataItem));
    
    // READ NAMES.TXT
    char c;
    FILE *file = fopen("Files/Names/names.txt", "r");
    // finds the length of the file
    fseek(file, 0L, SEEK_END);
    int fileLength = ftell(file);
    fseek(file, 0L, SEEK_SET);
    int currentSize = sizeof(char);
    // resizes text to the size of the file + 1 (plus 1 as need to add a newline at the end of the char)
    unsigned char *name = malloc (currentSize);
    //printf("length %d, Size 1 %lu, size 2 %lu, sizeOf(char) %lu\n", stringLength(redactWords), sizeof(redactWords) * sizeof(char), sizeof(char) * (fileLength + 1), sizeof(char));
    // counts position in file and position in text
    int fileCounter = 0;
    int textCounter = 0;
    if (file) {
        // while not at end of file
        while (fileCounter < fileLength) {
            c = getc(file);
            if (c == ',') {
                //printf("Current string %s\n", name);
                // add the current name to the hash table
                hashArray = addName(name, hashArray, &tableSize);
                // deallocate memory as new word to add
                free(name);
                // resize back to one char
                currentSize = sizeof(char);
                // allocate space for the next char
                name = calloc (1, currentSize);
                // reset textcounter to 0 as new word starts at 0
                textCounter = 0;
                // continue with the next character
                continue;
            } else if (c == '"') {
                // if speechmarks do not add to the word, move to next character in file
                fileCounter ++;
                continue;
            } else {
                // update currentSize to add the extra character
                currentSize += sizeof(char);
                // otherwise allocte space for the character
                name = realloc(name, currentSize);
                // add it to the name
                name[textCounter++] = c;
            }
            fileCounter++;
        }
        // close file reader
        fclose(file);
    }
    unsigned char nameTest[] = "MARY";


    printf("Is there a value for %s? %d\n", nameTest, search(nameTest, hashArray, tableSize));
    removeName(nameTest, hashArray, tableSize);
    printf("Is there a value for %s? %d\n", nameTest, search(nameTest, hashArray, tableSize));
}
