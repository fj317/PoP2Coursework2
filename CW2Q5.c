#include <stdio.h>
#include <stdlib.h>

// own bool type
typedef int bool;
#define true 1
#define false 0

struct RedactedListItem {
    int charIndex;
    int item;
    struct RedactedListItem* nextItem;
};

// checks for terminating value and returns the length
int stringLength(char* ptr) {
    int length = 0;
    while (ptr[length] != '\0') {
        length++;
    }
    return length;
}

void setupRedactedList(struct RedactedListItem* firstItem, char* redactedWords) {
    int len = stringLength(redactedWords);
    int count = 0;
    firstItem->charIndex = 0;
    firstItem->item = count++;
    struct RedactedListItem *thisItem = firstItem;
    for (int i = 1; i < len; i++) {
        if (redactedWords[i] == '\n') {
            struct RedactedListItem *newItem = (struct RedactedListItem*) malloc(sizeof(struct RedactedListItem));
            newItem->charIndex = ++i;
            newItem->item = count++;
            thisItem->nextItem = newItem;
            thisItem = newItem;
        }
    }
}

int lengthToNextWord(char *text, int index) {
    int num = 0;
    while (text[index + num] != ' ') {
        num++;
    }
    return num + 1;
}

int countRedactedSpaces(char *redactWords) {
    int len = stringLength(redactWords);
    int spaceCount = 0;
    for (int i = 0; i < len; i++) {
        if (redactWords[i] == ' ') {
            spaceCount ++;
        }
    }
    return spaceCount;
}

void removeWords(char* text, char *redactWords, struct RedactedListItem* firstItem) {
    int len = stringLength(text);
    int count = 0;
    for (int i = 0; i < len; i = i + lengthToNextWord(text, i)) {
        int wordStart = i;
        struct RedactedListItem *currentItem;
        currentItem = firstItem;
        while (currentItem != NULL) {
            bool matched = false;
            int currentIndex = currentItem->charIndex;
            //printf("i is %d. text[i] %c. redactWords[currentIndex] %c.\n", i, text[i], redactWords[currentIndex]);
            while (text[i] == redactWords[currentIndex]) {
                //printf("i is %d. text[i] %c. redactWords[currentIndex] %c.\n", i, text[i], redactWords[currentIndex]);
                if (text[i] == ' ' && redactWords[currentIndex] == ' ') {
                    for (int j = wordStart; j < i; j++) {
                        text[j] = '*';
                    }
                    matched = true;
                    break;
                }
                i++;
                currentIndex++;
            }
            if (matched) {
                break;
            } else {
                i = wordStart;
            }
            
            currentItem = currentItem->nextItem;
            count++;
        }
    }
}

// takes a character and puts it into uppercase (or leave it as a punctuation mark)
char toUpper(char character) {
    if (character >= 97 && character <= 122) {
        character -= 32;
    }
    return character;
}

int main(void) {
    char c;
    FILE *file;
    // READ DEBATE.TXT
    file = fopen("Files/Q5/debate.txt", "r");
    // finds the length of the file
    fseek(file, 0L, SEEK_END);
    int fileLength = ftell(file);
    fseek(file, 0L, SEEK_SET);
    // resizes text to the size of the file
    char text[fileLength];
    // counts position in file and position in text
    int counter = 0;
    if (file) {
        // while not at end of file
        while (counter < fileLength) {
            // turn character read from file to upper case
            c = toUpper(getc(file));
            if (c >= 65 && c <= 90) {
                text[counter++] = c;
            } else {
                text[counter++] = ' ';
            }
        }
        // close file reader
        fclose(file);
    }
    // READ REDACT.TXT
    file = fopen("Files/Q5/redact.txt", "r");
    // finds the length of the file
    fseek(file, 0L, SEEK_END);
    fileLength = ftell(file);
    fseek(file, 0L, SEEK_SET);
    int currentSize = fileLength + 1;
    // resizes text to the size of the file + 1 (plus 1 as need to add a newline at the end of the char)
    char *redactWords = malloc (sizeof(char) * currentSize);
    //printf("length %d, Size 1 %lu, size 2 %lu, sizeOf(char) %lu\n", stringLength(redactWords), sizeof(redactWords) * sizeof(char), sizeof(char) * (fileLength + 1), sizeof(char));
    // counts position in file and position in text
    counter = 0;
    if (file) {
        // while not at end of file
        while (counter < fileLength) {
            // turn character read from file to upper case
            c = toUpper(getc(file));
            if (c == '\n') {
                redactWords = realloc(redactWords, sizeof(char) + currentSize);
                redactWords[counter++] = ' ';
            }
            redactWords[counter++] = c;
        }
        // close file reader
        fclose(file);
    }
    //redactWords[fileLength] = '\n';

    //char text[] = "the quick brown fox jumps over the lazy dog";
    //char redactWords[] = "TAKING NATIONAL ";
    struct RedactedListItem firstItem;
    setupRedactedList(&firstItem, redactWords);
    //printf("first redact index: %d, second index %d, third index %d\n", firstItem.charIndex, firstItem.nextItem->charIndex, firstItem.nextItem->nextItem->charIndex);
    removeWords(text, redactWords, &firstItem);
    printf("%s", text);
    return 0;
}
