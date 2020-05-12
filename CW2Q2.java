import java.io.*;

public class CW2Q2 {
    public static void main(String[] args) throws IOException {
        // reads from local file names.txt
        File file = new File("Files/Names/names.txt");
        BufferedReader br = new BufferedReader(new FileReader(file));
        // stores the names that are read from txt file
        String line;
        // stores the list of names as an array
        String[] names = new String[0];
        // reads the names from names.txt
        while ((line = br.readLine()) != null) {
            // removes " from around each name
            line = removeChar(line, '"');
            // splits the text into a string array every time a , occurs
            names = line.split(",");
        }
        // sorts the names
        quickSort(names, 0, names.length - 1);
        // outputs the names on a new line for each name
        for (int i = 0; i < names.length; i ++) {
            System.out.println(names[i]);
        }
        br.close();
    }

    // removes a char from a string and replaces it with no character
    public static String removeChar(String words, char toReplace) {
        String result = "";
        // loops through the string
        for (int i = 0; i < words.length(); i++) {
            // if the character the current index is located at is NOT the word to replace then it adds it to the string
            // otherwise it does not add it, therefore the character is removed
            char character = getChar(words,i);
            if (character != toReplace) {
                result += character;
            }
        }
        return result;
    }

    public static String[] quickSort(String[] arrayToSort, int low, int high) {
        if (low < high) {
            // picks a pivot element
            int pivot = parition(arrayToSort, low, high);
            // recursively apply partitioning to sort sub-arrays, therefore sorting the entire array
            quickSort(arrayToSort, low, pivot - 1);
            quickSort(arrayToSort, pivot + 1, high);
        }
        return arrayToSort;
    }

    public static int parition(String[] arrayToSort, int low, int high) {
        // get pivot
        String pivot = arrayToSort[high];
        int i = low;
        // loop through the array
        for (int j = low; j < high; j++) {
            // if any values are higher than the pivot then swap with the pivot
            if (compareTo(arrayToSort[j], pivot) > 0) {
                // swaps the two items located at i and j
                swap(arrayToSort, i, j);
                // increments i by 1
                i++;
            }
        }
        // swap two items at i and high
        swap(arrayToSort, i, high);
        return i;
    }

    // swaps two elements in an array at the two specified indexes
    public static String[] swap(String[] array, int indexOne, int indexTwo) {
        // temporarily stores the value at indexOne
        String tempValue = array[indexOne];
        // swaps the value at indexOne with the value at indexTwo
        array[indexOne] = array[indexTwo];
        // swaps the value at indexTwo with the value that was previously at IndexOne (before the initial swap)
        array[indexTwo] = tempValue;
        return array;
    }

    // compare two strings, returns negative if a is 'larger', 0 is equal and positive is b is 'larger'
    public static int compareTo(String a, String b) {
        // make char arrays length of the strings
        char[] aLetters = new char[a.length()];
        char[] bLetters = new char[b.length()];
        // put the strings into the char arrays so the chars can be compared against one another
        for (int i = 0; i < a.length(); i++) {
            aLetters[i] = getChar(a,i);
        }
        for (int i = 0; i < b.length(); i++) {
            bLetters[i] = getChar(b,i);
        }
        // stores a counter as each letter is compared
        int letterCount = 0;
        // compares each letter of each word to find the 'larger one'
        do {
            // checks the length, if the current letterCount is larger than the length, then it picks the shorter word (as the words would be  identical at this point)
            if (letterCount >= a.length()) {
                return -1;
            } else if (letterCount >= b.length()) {
                return 1;
            }
            // compares the two letters and returns -1 or 1 depending on which word is 'larger'
            if (aLetters[letterCount] > bLetters[letterCount]) {
                return -1;
            } else if (bLetters[letterCount] > aLetters[letterCount]) {
                return 1;
            }
            // if the letters are the same then increments the letterCount and moves to next letter
            letterCount ++;
        } while (true);
    }

    // gets the char from word at the specified index and returns it
    public static char getChar(String word, int index) {
        char[] wordSplit = word.toCharArray();
        return wordSplit[index];
    }
}
