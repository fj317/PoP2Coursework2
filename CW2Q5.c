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

char *clearArray(char* array) {
    for (int i = 0; i < stringLength(array); i++) {
        array[i] = '\0';
    }
    return array;
}

void setupRedactedList(struct RedactedListItem* firstItem, char* redactedWords) {
    int len = stringLength(redactedWords);
    int count = 0;
    firstItem->charIndex = 0;
    firstItem->item = count++;
    struct RedactedListItem *thisItem = firstItem;
    for (int i = 1; i < len; i++) {
        if (redactedWords[i] == ' ') {
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
            while (text[i] == redactWords[currentIndex]) {
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

int main(void) {
    char text[] = "the quick brown fox jumps over the lazy dog";
    char redactWords[] = "the jumps lazy ";
    struct RedactedListItem firstItem;
    setupRedactedList(&firstItem, redactWords);
    // printf("first redact index: %d, second index %d, third index %d\n", firstItem.charIndex, firstItem.nextItem->charIndex, firstItem.nextItem->nextItem->charIndex);
    removeWords(text, redactWords, &firstItem);
    printf("%s", text);
    return 0;
}
