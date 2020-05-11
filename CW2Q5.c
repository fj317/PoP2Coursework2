#include <stdio.h>
#include <stdlib.h>

// own bool type
typedef int bool;
#define true 1
#define false 0

// struct to store the starting index of each of the redacted words
struct RedactedListItem {
    int charIndex;
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

// finds the starting index for each of the redacted words
void setupRedactedList(struct RedactedListItem* firstItem, char* redactedWords) {
    int len = stringLength(redactedWords);
    // intialise the first one to 0
    firstItem->charIndex = 0;
    struct RedactedListItem *thisItem = firstItem;
    for (int i = 1; i < len; i++) {
        // if the current item's character is a linebreak then we know this is the end of the redacted word
        if (redactedWords[i] == '\n') {
            // allocate memory for the next redacted word
            struct RedactedListItem *newItem = (struct RedactedListItem*) malloc(sizeof(struct RedactedListItem));
            // set the next redacted word's char index to the next character
            newItem->charIndex = ++i;
            // update the pointer to point to the next redacted word
            thisItem->nextItem = newItem;
            // set the current item to the next redacted word
            thisItem = newItem;
        }
    }
}

// finds the length to the next word in the text
int lengthToNextWord(char *text, int index) {
    int num = 0;
    // while the index and num is less than the length of the text
    while ((index + num) < stringLength(text)) {
        // checks if the location pointed by index + num is a space or linebreak
        if (text[index + num] == ' ' || text[index + num] == '\n') {
            // if it is break the while loop
            break;
        } else { 
            // otherwise add one to num and repeat
            num++; 
        }
    }
    // repeat num + 1 (plus 1 as otherwise it would return the space or linebreak character)
    return num + 1;
}

// replaces the redacted words in the text with *s
void removeWords(char* text, char *redactWords, struct RedactedListItem* firstItem) {
    int len = stringLength(text);
    // loop through the text in additions to the start of each word
    for (int i = 0; i < len; i = i + lengthToNextWord(text, i)) {
        // stores the start of the word
        int wordStart = i;
        // stores the current redacted word
        struct RedactedListItem *currentItem;
        currentItem = firstItem;
        // while not at the end of the redacted words
        while (currentItem != NULL) {
            // stores whether the entire word has matched or not
            bool matched = false;
            // stores whether the current character is punctuation
            bool punctuationEnd = false;
            // stores the current index of the redacted word
            int currentIndex = currentItem->charIndex;
            // while the two characters match OR the text has punctuation at the end
            while (text[i] == redactWords[currentIndex] || punctuationEnd == true) {
                // checks if the text is a punctuation mark or space AND the redactedWord character is a space
                if (text[i] < 'A' && redactWords[currentIndex] == ' ') {
                    // if so then loop through the word in the text and set each character to a star
                    for (int j = wordStart; j < i; j++) {
                        text[j] = '*';
                    }
                    // set match to true and break out the while loop
                    matched = true;
                    break;
                }
                // set punctuationEnd to false
                punctuationEnd = false;
                // move to next character of the text and redacted words to check if they match
                i++;
                currentIndex++;
                // if the text character is a punctuation then set punctuation end to true
                if (text[i] < 'A') {
                    punctuationEnd = true;
                }
            }
            // if matched is true then break out the while loop as there is no need to check for other redacted words
            if (matched) {
                break;
            } else {
                // otherwise move back to the start of the word
                i = wordStart;
            }
            // move to next redacted word
            currentItem = currentItem->nextItem;
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
            } else if (c == '\n') {
                text[counter++] = '\n';
            } else {
                text[counter++] = c;
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
                currentSize += sizeof(char);
                redactWords = realloc(redactWords, currentSize);
                redactWords[counter++] = ' ';
                fileLength++;
            }
            redactWords[counter++] = c;
        }
        // close file reader
        fclose(file);
    }
    redactWords[fileLength] = '\n';

    struct RedactedListItem firstItem;
    setupRedactedList(&firstItem, redactWords);
    //printf("first redact index: %d, second index %d, third index %d\n", firstItem.charIndex, firstItem.nextItem->charIndex, firstItem.nextItem->nextItem->charIndex);
    removeWords(text, redactWords, &firstItem);
    printf("%s", text);
    return 0;
}
