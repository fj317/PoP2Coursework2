#include <stdio.h>

int stringLength(char* ptr) {
    int length = 0;
    while (ptr[length] != '\0') {
        length++;
    }
    return length;
}

// int intLength(int num) {
//     return num % 10;
// }

//https://www.udemy.com/blog/c-string-to-int/
int stringToInt(char* ptr) {
    int len = stringLength(ptr);
    int result = 0;
    for (int i = 0; i < len - 1; i++) {
        result = result * 10 + (ptr[i] - '0');
        //printf("Result %d\n", result);
    }
    return result;
}

int intPow(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

void intToString(char* result, int num, int len) {
    for (int i = 0; i < len; i++) {
        int digit = len - i - 1;
        int rem = num % 10;
        result[digit] = '0' + rem;
        num = (num - rem) / 10;
    }
}

// assume seed is always 4 digit value
int createRand(int seed) {
    int nextRand = seed * seed;
    // 8 digits long as 9999^2 is 8 digits total
    int len = 8;
    char nextString[len];
    intToString(nextString, nextRand, len);

    // pad to 8 long using 0s
    char ret[4] = {
        nextString[2],
        nextString[3],
        nextString[4],
        nextString[5]
    };
    int returnNum = stringToInt(ret);
    return returnNum;
}

int * generate100Rand() {
    static int numbers[99];
    int seed = 1111;
    for (int i = 0; i < 99; i++) {
        numbers[i] = createRand(seed);
        seed = numbers[i];
    }
    return numbers;
}

int * swap(int *toSwapPointer, int indexA, int indexB) {
    int temp = toSwapPointer[indexB];
    toSwapPointer[indexB] = toSwapPointer[indexA];
    toSwapPointer[indexA] = temp;
    return toSwapPointer;
}

int * cocktailSort(int *ptr) {

    // boolean - 0 is false, 1 is true
    int swapped;
    do {
        swapped = 0;
        for (int i = 0; i < 99; i++) {
            if (ptr[i] > ptr[i+1]) {
                ptr = swap(ptr, i, i + 1);
                swapped = 1;
            }
        }
        if (swapped == 0) {
            break;
        }
        swapped = 0;
        for (int i = 98; i >= 0; i--) {
            if (ptr[i] > ptr[i+1]) {
                ptr = swap(ptr, i, i + 1);
                swapped = 1;
            }
        }
    } while (swapped == 1);
    return ptr;
}


int main() {
    //char test = createRand(2343);
    //printf("\n%d\n", test);

    int *ptr;
    ptr = generate100Rand();
    printf("Unsorted List: ");
    for (int i = 0; i < 100; i++ ) {
      printf( "Number: %d : %d\n", i+1, *(ptr + i));
    }
    ptr = cocktailSort(ptr);

    for (int i = 0; i < 100; i++ ) {
      printf( "Number: %d : %d\n", i+1, *(ptr + i));
    }

    //char ret[4] = "4896";
    //printf("%d", stringToInt(ret));
    return 0;
}