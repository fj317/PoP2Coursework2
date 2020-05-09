#include <stdio.h>

int stringLength(char* pointer) {
    int length = 0;
    while (pointer[length] != '\0') {
        length++;
    }
    return length;
}

char *swap(char *toSwapPointer, char indexA, char indexB) {
    char temp = toSwapPointer[indexB];
    toSwapPointer[indexB] = toSwapPointer[indexA];
    toSwapPointer[indexA] = temp;
    return toSwapPointer;
}

void bubbleSortText(char *key, char (*columns)[stringLength(key)], int rowNum) {
    char tempCharStore;
    // boolean - 0 is false, 1 is true
    int swapped;
    do {
        swapped = 0;
        for (int i = 0; i < stringLength(key) - 1; i++) {
            if (key[i] > key[i+1]) {
                key = swap(key, i, i + 1);
                    for (int j = 0; j < rowNum; j++) {
                        tempCharStore = columns[j][i];
                        columns[j][i] = columns[j][i + 1];
                        columns[j][i + 1] = tempCharStore;
                    }
                swapped = 1;
            }
        }
    } while (swapped == 1);
}

// https://stackoverflow.com/questions/2422712/rounding-integer-division-instead-of-truncating
// takes form of eg roundUP(12, 5) = 3
unsigned int roundUp(int dividend, int divisor)
{
    return (dividend + (divisor - 2)) / divisor;
}

void columnCreate(char key[], char text[], char (*columns)[stringLength(key)]) {
    int rowNum = roundUp(stringLength(text), stringLength(key));
    int columnNum = stringLength(key);
    int pointInText = 0;
    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < columnNum; j++) {
            columns[i][j] = text[pointInText];
            pointInText++;
        }
    }
}

void padMessage(char *text, char *padText, int paddedLength) {
    int textLength = stringLength(text);
    for (int i = 0; i < textLength; i++) {
        padText[i] = text[i];
        
    }
    int count = textLength;
    while (count != paddedLength) {
        padText[count] = 'X';
        count++;
    }
}

int main(void) {
    char text[] = "ATTACKATDA";
    char key[] = "KEYS";
    
    int paddedLength = stringLength(text) + (stringLength(text) % stringLength(key));
    char paddedText[paddedLength];
    padMessage(text, paddedText, paddedLength);
    printf("Pad message: %s\n", paddedText);

    int rowNum = roundUp(stringLength(paddedText), stringLength(key));
    int columnNum = stringLength(key);
    char columns[rowNum][columnNum];

    printf("Original text %s. Key: %s. ", text, key);
    columnCreate(key, paddedText, columns);
    bubbleSortText(key, columns, rowNum);
    int forLength = stringLength(paddedText) / stringLength(key);
    printf("Cipher text: ");
    for (int i = 0; i < stringLength(key); i++) {
        for (int j = 0; j <= forLength; j++) {
            printf("%c", columns[i][j]);
        }
    }
    return 0;
}