#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

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
unsigned long hash(unsigned char *str) {
    int len = stringLength(str);
    unsigned long hash = 5381;
    int c;
    while (0 != (c = *str++)) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    // To avoid memory issues reduce the number size
    return hash % (len * 2000003);
}

// search function
bool search(unsigned char name[], struct dataItem* hashArray, unsigned long maxTableSize) {
    // get the hash index of the data
    unsigned long hashIndex = hash(name) - 1;
    // if the hash index is larger than the max table size return false
    if (hashIndex > maxTableSize) {
        return false;
        // otherwise check if the value at the hash index is null, if it is return false
    } else if (hashArray[hashIndex].charValue == NULL) {
        return false;
    }
    // otherwise return true as it must be there then
    return true;
} 

// setup dataItem so it stores the name to input as struct which contains a char array
void setupDataItem(unsigned char name[], struct dataItem *item) {
    int len = stringLength(name);
    // allocate enough space for the string
    item->charValue = (unsigned char*) malloc(sizeof(unsigned char) * len);
    // loop through setting each index to the name
    for (int i = 0; i < len; i++) {
        item->charValue[i] = name[i];
    }
}

// add method, needs to return pointer to start of array as it may resize depending on the input to dynamicly adjust the amount of memory needed
struct dataItem *addName(unsigned char name[], struct dataItem *hashArray, unsigned long *tableSize) {
    unsigned long hashResult = hash(name);
    // resizes hashtable to new hash result if it is larger than the current size
    if (hashResult > *tableSize) {
        hashArray = realloc(hashArray, sizeof(struct dataItem) * hashResult);
        if (hashArray == NULL) {
            printf("Error allocating memory\n");
            exit(1);
        }
        *tableSize = hashResult;
    }
    // create the dataItem to place in the hashIndex
    struct dataItem *item = malloc(sizeof(struct dataItem));
    // put the name in the dataItem
    setupDataItem(name, item);
    // put the dataitem in the correct location in the hashtable
    hashArray[hashResult - 1] = *item;
    // tell user it has been added
    printf("Data item %s has been added.\n", name);
    return hashArray;
}

// remove method, removes a value from the hash table
void removeName(unsigned char name[], struct dataItem* hashArray, unsigned long tableSize) {
    unsigned long hashIndex = hash(name) - 1;
    // if hash index is larger than table size then name isn't in the table
    if (hashIndex > tableSize) {
        printf("Name does not exist in table.\n");
        // if there is no value at the hash index then the name isn't in the table
    } else if (hashArray[hashIndex].charValue == NULL) {
        printf("Name does not exist in table.\n");       
    } else {
        // otherwise set the char value to null
        hashArray[hashIndex].charValue = NULL;
        // tell the user it has been removed
        printf("Data item %s has been removed.\n", name);
    }
}

int main(void) {
    // hash table declaration
    unsigned long tableSize = 1;
    struct dataItem *hashArray = malloc(sizeof(struct dataItem) * tableSize);
    if (hashArray == NULL) {
        printf("Error allocating memory\n");
        exit(1);
    }
    
    // READ NAMES.TXT
    char c;
    FILE *file = fopen("Files/Names/names.txt", "r");
    // finds the length of the file
    fseek(file, 0L, SEEK_END);
    int fileLength = ftell(file);
    fseek(file, 0L, SEEK_SET);
    int currentSize = sizeof(char);
    // resizes text to the size of the file + 1 (plus 1 as need to add a newline at the end of the char)
    unsigned char *name = malloc(currentSize);
    // counts position in file and position in text
    int fileCounter = 0;
    int textCounter = 0;
    if (file) {
        // while not at end of file
        while (fileCounter < fileLength) {
            c = getc(file);
            if (c == ',') {
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
            } else if (c == '"') {
                // if speechmarks do not add to the word, do nothing
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
        // add final value 
        hashArray = addName(name, hashArray, &tableSize);
    }
    unsigned char nameTest[] = "MARY";
    printf("Is there a value for %s? %d\n", nameTest, search(nameTest, hashArray, tableSize));
    removeName(nameTest, hashArray, tableSize);
    printf("Is there a value for %s? %d\n", nameTest, search(nameTest, hashArray, tableSize));
}
