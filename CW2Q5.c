#include <stdio.h>

int stringLength(char* ptr) {
    int length = 0;
    while (ptr[length] != '\0') {
        length++;
    }
    return length;
}

char * removeWords(char *text, char *redactWords) {
    char currentWord[stringLength(text)];
    int currentWordIndex = 0;
    int currentTextIndex = 0;
    int len = stringLength(text);
    for (int i = 0; i < len; i ++) {
        //printf("Text %c\n", text[i]);
        if (text[i] != ' ') {
            currentWord[currentWordIndex] = text[i];
            currentWordIndex += 1;
        }
        else {
            // compare redacted words against words in text


            currentTextIndex += currentWordIndex + 1;
            currentWordIndex = 0;


        }
        printf("%s\n", currentWord);

    }


    return 0;
}

int main() {
    char *text = "The quick brown fox jumps over the lazy dog";
    char *redactWords = "the jumps lazy";
    char *textPtr = removeWords(text, redactWords);
    return 0;
}