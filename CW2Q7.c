#include <stdio.h>

// finds the length of a string
int stringLength(char* pointer) {
    int length = 0;
    while (pointer[length] != '\0') {
        length++;
    }
    return length;
}

// swaps two elements in a char array with each other
char *swap(char *toSwapPointer, char indexA, char indexB) {
    char temp = toSwapPointer[indexB];
    toSwapPointer[indexB] = toSwapPointer[indexA];
    toSwapPointer[indexA] = temp;
    return toSwapPointer;
}

// bubble sort to sort the keyword columns into their alphabetical order
void bubbleSortText(char *key, char (*columns)[stringLength(key)], int rowNum) {
    char tempCharStore;
    // boolean - 0 is false, 1 is true
    int swapped;
    // loop until no swaps are made, therefore keyword and columns are sorted
    do {
        swapped = 0;
        // loop through each character of the key
        for (int i = 0; i < stringLength(key) - 1; i++) {
            // if the current key character is larger than the next, swap them
            if (key[i] > key[i+1]) {
                key = swap(key, i, i + 1);
                // swap all items in the columns around as well
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

// divides two numbers and returns the rounded up result
// https://stackoverflow.com/questions/2422712/rounding-integer-division-instead-of-truncating
// takes form of eg roundUP(12, 5) = 3
unsigned int roundUp(int dividend, int divisor)
{
    return (dividend + (divisor - 2)) / divisor;
}

// puts the text into column format
void columnCreate(char key[], char text[], char (*columns)[stringLength(key)]) {
    // gets the row and column numbers
    int rowNum = roundUp(stringLength(text), stringLength(key));
    int columnNum = stringLength(key);
    // stores current point in text
    int pointInText = 0;
    // loops through each row and column assigning the current location in the text to that index
    for (int i = 0; i < rowNum; i++) {
        for (int j = 0; j < columnNum; j++) {
            columns[i][j] = text[pointInText];
            pointInText++;
        }
    }
}

// pads the message
void padMessage(char *text, char *padText, int paddedLength) {
    // stores the text length
    int textLength = stringLength(text);
    // sets the pad text to the text already
    for (int i = 0; i < textLength; i++) {
        padText[i] = text[i];
    }
    int count = textLength;
    // adds extra 'X' character to the end if there is space allocated for it
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
    char c;
    FILE *file;
    file = fopen("Files/Q7/text.txt", "r");
    // finds the length of the file
    fseek(file, 0L, SEEK_END);
    int fileLength = ftell(file);
    fseek(file, 0L, SEEK_SET);
    // resizes text to the size of the file
    char text[fileLength];
    // counts position in file and position in text
    int fileCounter = 0;
    int textCounter = 0;
    if (file) {
        // while not at end of file
        while (fileCounter < fileLength) {
            // turn character read from file to upper case
            c = toUpper(getc(file));
            // if it is uppercase add it to the text, otherwise discard
            if (c >= 65 && c <= 90) {
                text[textCounter++] = c;
            }
            // add 1 to the file counter
            fileCounter++;
        }
        // close file reader
        fclose(file);
    }

    // KEY FOR ENCRYPTION OF THE TEXT
    char key[] = "LOVELACE";
    
    // stores what the length of the padded word should be
    int paddedLength = stringLength(key) * roundUp(stringLength(text), stringLength(key)) + 1;
    // allocates space for word
    char paddedText[paddedLength];
    // creates the padded text
    padMessage(text, paddedText, paddedLength);
    // output to console
    printf("Pad message: %s\n", paddedText);

    // works out the number of rows of table
    int rowNum = roundUp(stringLength(paddedText), stringLength(key));
    // works out number of columns of table
    int columnNum = stringLength(key);
    // stores the table data 
    char columns[rowNum][columnNum];

    printf("Key: %s.\n", key);
    // creates the columns the text are stored in
    columnCreate(key, paddedText, columns);
    // sort the columns by the key
    bubbleSortText(key, columns, rowNum);
    // output the columns in the sorted order
    // variable used to store the for loop max length
    int forLength = stringLength(paddedText) / stringLength(key);
    printf("Cipher text: ");
    for (int i = 0; i < stringLength(key); i++) {
        for (int j = 0; j <= forLength; j++) {
            printf("%c", columns[i][j]);
        }
    }
    return 0;
}