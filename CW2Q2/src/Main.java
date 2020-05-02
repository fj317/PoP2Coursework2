public class Main {
    public static void main(String[] args) {

    }

    public static String[] parition(String leftPointer, String rightPointer, String pivot) {

        return null;
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

    public static char getChar(String word, int index) {
        char[] wordSplit = word.toCharArray();
        return wordSplit[index];
    }
}
