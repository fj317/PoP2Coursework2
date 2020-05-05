#include <stdio.h>

typedef int bool;
#define true 1
#define false 0

struct RedactedListItem {
    int charIndex;
    int lastItem;
    struct RedactedListItem *nextItem;
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
    firstItem->charIndex = 0;
    struct RedactedListItem *thisItem = firstItem;
    for (int i = 1; i < len; i++) {
        if (redactedWords[i] == ' ') {
            struct RedactedListItem newItem;
            newItem.charIndex = i;
            newItem.lastItem = 0;
            thisItem->nextItem = &newItem;
            thisItem = &newItem;
        }
    }
    thisItem->lastItem = 1;
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
        printf("here\n");
        while (count < countRedactedSpaces(redactWords) + 1)  {
            bool matched = false;
            int currentIndex = currentItem->charIndex;
            printf("text[i]: %c, redactWords[currentindex]:%c, currentIndex: %d\n", text[i], redactWords[currentIndex], currentIndex);
            while (text[i] == redactWords[currentIndex]) {
                if (text[i] == ' ' && redactWords[currentIndex] == ' ') {
                    for (int j = wordStart; j < i; j++) {
                        text[j] = '*';
                    }
                    matched = true;
                    continue;
                }
                i++;
                currentIndex++;
            }
            if (matched) {
                continue;
            } else {
                i = wordStart;
            }
            printf("Next redactedWord\n\n");
            currentItem = currentItem->nextItem;
            count ++;
        }
    }
}

int main(void) {
    char text[] = "The quick brown fox jumps over the lazy dog";
    char redactWords[] = "the jumps lazy";
    struct RedactedListItem firstItem;
    setupRedactedList(&firstItem, redactWords);
    removeWords(text, redactWords, &firstItem);
    printf("%s", text);
    return 0;
}
