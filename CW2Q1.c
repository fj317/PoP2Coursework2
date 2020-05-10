#include <stdio.h>

// calculates the length of a char pointer
int stringLength(char* ptr) {
    int length = 0;
    while (ptr[length] != '\0') {
        length++;
    }
    return length;
}

// converts string to an interger, based upon https://www.udemy.com/blog/c-string-to-int/
int stringToInt(char* ptr) {
    int len = stringLength(ptr);
    int result = 0;
    for (int i = 0; i < len - 1; i++) {
        result = result * 10 + (ptr[i] - '0');
    }
    return result;
}

// finds the power of two values
int intPow(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

// converts integer to string
void intToString(char* result, int num, int len) {
    // converts each character to the string version of itself, starting at the end and moving to the start
    for (int i = 0; i < len; i++) {
        int digit = len - i - 1;
        // rem stores the last digit of the number
        int rem = num % 10;
        // this is then added to the string at the end position
        result[digit] = '0' + rem;
        // the number is then updated to remove this digit
        num = (num - rem) / 10;
    }
}

// creates a random number
// assume seed is always 4 digit value
int createRand(int seed) {
    int nextRand = seed * seed;
    // 8 digits long as 9999^2 is 8 digits total
    int len = 8;
    char nextString[len];
    // convert to string so can take each number character
    intToString(nextString, nextRand, len);

    // takes the digits 3-7 as the next random number seed
    char ret[4] = {
        nextString[2],
        nextString[3],
        nextString[4],
        nextString[5]
    };
    // convert back to integer
    int returnNum = stringToInt(ret);
    // return the random number
    return returnNum;
}

// generates 100 random numbers
int *generate100Rand() {
    static int numbers[99];
    // starting seed of 1111
    int seed = 1111;
    // loop 100 times to produce 100 numbers
    for (int i = 0; i < 99; i++) {
        numbers[i] = createRand(seed);
        seed = numbers[i];
    }
    return numbers;
}

// swap two integer values around
int *swap(int *toSwapPointer, int indexA, int indexB) {
    int temp = toSwapPointer[indexB];
    toSwapPointer[indexB] = toSwapPointer[indexA];
    toSwapPointer[indexA] = temp;
    return toSwapPointer;
}

int *cocktailSort(int *ptr) {

    // boolean - 0 is false, 1 is true
    int swapped;
    do {
        swapped = 0;
        // loop through the random numbers start -> end
        for (int i = 0; i < 99; i++) {
            // checks if a swap can happen, if it can it swaps and sets swapped to 1
            if (ptr[i] > ptr[i+1]) {
                ptr = swap(ptr, i, i + 1);
                swapped = 1;
            }
        }
        // if no swaps have been made then list is sorted, exit do loop
        if (swapped == 0) {
            break;
        }
        // reset swapped to 0
        swapped = 0;
        // loop through random numbers end -> start
        for (int i = 98; i >= 0; i--) {
            // checks if a swap can happen, if it can it swaps and sets swapped to 1
            if (ptr[i] > ptr[i+1]) {
                ptr = swap(ptr, i, i + 1);
                swapped = 1;
            }
        }
        // loops while swapped is set to 1
    } while (swapped == 1);
    // return the pointer
    return ptr;
}


int main(void) {
    // generate 100 random numbers
    int *ptr;
    ptr = generate100Rand();
    // prints unsorted list
    printf("Unsorted List: ");
    for (int i = 0; i < 100; i++ ) {
      printf( "Number: %d : %d\n", i+1, *(ptr + i));
    }
    // sorts
    ptr = cocktailSort(ptr);

    // output sorted list
    for (int i = 0; i < 100; i++ ) {
      printf( "Number: %d : %d\n", i+1, *(ptr + i));
    }

    return 0;
}