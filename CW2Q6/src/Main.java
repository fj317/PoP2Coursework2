
public class Main {
    public static void main(String[] args) {
        String text = "It was in July, 1805, and the speaker was the well-known Anna Pavlovna Scherer, maid of honor and favorite of the Empress Marya Fedorovna. With these words she greeted Prince Vasili Kuragin, a man of high rank and importance, who was the first to arrive at her reception. Anna Pavlovna had had a cough for some days. She was, as she said, suffering from la grippe; grippe being then a new word in St. Petersburg, used only by the elite.";
        String redact = "Ilya Rostov\n" +
                "St. Petersburg \n" +
                "Marya Fedorovna\n" +
                "Moscow\n" +
                "Anna Pavlovna Scherer\n" +
                "Countess Bezukhova\n" +
                "Andrew Bolkonski\n" +
                "Boris Drubetskoy\n" +
                "Vasili Kuragin\n" +
                "Nicholas Rostov\n";
        System.out.println(text);
        for (int i = 1; i < text.length(); i++) {
            char currentChar = getChar(text, i);
            // if text is a capital, and previous character was a space, and the character before that was not a fullstop
            // i.e. proper pronoun in middle of a sentence
            if (currentChar >= 65 && currentChar <= 90 && getChar(text, i - 1) == 32 && getChar(text, i - 2) != 46) {
                text = removeWords(text, i);
            } else if ((currentChar == 46 || currentChar == 10) && i < text.length() - 1) { // need to check if word is proper noun if at start of sentence or paragraph
                String[] redactedList = getRedactedArray(redact);
                String currentWord = getWordAtIndex(text, i + 2);
                for (int j = 1; j < redactedList.length; j++) {
                    if (currentWord.equals(redactedList[j])) {
                        text = removeWords(text, i + 2);
                    }
                }
            }
        }
        System.out.println(text);
    }

    public static String[] getRedactedArray(String redactedWordsList) {
        String[] redactedWordsArray = new String[1];
        String redactedWord;
        int startIndex = 0;
        while (startIndex < redactedWordsList.length()) {
            redactedWord = getWordAtIndex(redactedWordsList, startIndex);
            redactedWordsArray = addElement(redactedWordsArray, redactedWord);
            startIndex = getWordEndIndex(redactedWordsList,startIndex) + 1;
        }
        return redactedWordsArray;
    }

    public static String[] addElement(String[] array, String element) {
        // temp array to store the array's data
        String[] tempArray = new String[array.length];
        // fill it with the array's data
        for(int i = 0; i < array.length; i++){
            tempArray[i] = array[i];
        }
        // increase array's size
        array = new String[array.length+1];
        // fill the array with the original data
        for(int i = 0; i < tempArray.length; i++){
            array[i] = tempArray[i];
        }
        // add the new element in
        array[array.length-1] = element;
        return array;
    }

    public static String getWordAtIndex(String text, int startIndex) {
        int endIndex = getWordEndIndex(text, startIndex);
        String word = text.substring(startIndex, endIndex);
        return word;
    }

    // gets the index of where the word ends
    public static int getWordEndIndex(String text, int startIndex) {
        for (int i = startIndex; i < text.length(); i++) {
            char character = getChar(text, i);
            // if the next char is a space return i
            if (character == 32 || character == 10) {
                return i;
            }
        }
        return text.length();
    }

    public static String removeWords(String text, int startIndex) {
        for (int i = startIndex; i < text.length(); i++) {
            if (getChar(text, i) >= 32 && getChar(text, i) <= 45) {
                for (int j = startIndex; j < i; j++) {
                    text = replaceCharAt(text, j, '*');
                }
                break;
            }
        }
        return text;
    }

    public static String replaceCharAt(String text, int index, char replaceWith) {
        return text.substring(0, index) + replaceWith + text.substring(index + 1, text.length());
    }


    // gets the char from word at the specified index and returns it
    public static char getChar(String word, int index) {
        char[] wordSplit = word.toCharArray();
        return wordSplit[index];
    }
}
