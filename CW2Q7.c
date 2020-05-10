#include <stdio.h>
#include <stdlib.h> 

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

// takes a character and puts it into uppercase (or leave it as a punctuation mark)
char toUpper(char character) {
    if (character >= 97 && character <= 122) {
        character -= 32;
    }
    return character;
}

int main(void) {
    // file reading
    int c;
    FILE *file;
    file = fopen("Files/Q7/text.txt", "r");
    // finds the length of the file
    fseek(file, 0L, SEEK_END);
    int fileLength = ftell(file);
    fseek(file, 0L, SEEK_SET);
    // resizes text to the size of the file
    char text[fileLength];
    //char *text = (char*) malloc ((fileLength + 1) * sizeof(char));
    int fileCounter = 0;
    int textCounter = 0;
    if (file) {
        while (fileCounter < fileLength) {
            c = toUpper(getc(file));
            if (c >= 65 && c <= 90) {
                text[textCounter++] = c;
            }
            fileCounter++;
            //printf("char %c\n", c);
        }
        fclose(file);
    }

    //char text[] = "It will now be inquired how the machine can of itself, and without having recourse to the hand of man, assume the successive dispositions suited to the operations. The solution of this problem has been taken from Jacquard's apparatus, used for the manufacture of brocaded stuffs, in the following manner.";
    char key[] = "LOVELACE";
    
    int paddedLength = stringLength(key) * roundUp(stringLength(text), stringLength(key)) + 1;
    char *paddedText = (char*) malloc (paddedLength * sizeof(char));
    padMessage(text, paddedText, paddedLength);
    printf("Pad message: %s\n", paddedText);

    int rowNum = roundUp(stringLength(paddedText), stringLength(key));
    int columnNum = stringLength(key);
    char columns[rowNum][columnNum];

    printf("Key: %s.\n", key);
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