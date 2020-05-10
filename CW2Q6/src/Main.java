import java.io.*;

public class Main {
    public static void main(String[] args) throws IOException {
        // CHANGE THIS LINE TO CHANGE WHAT FILE IS READ
        String fileToRedact = "../Files/Q6/warandpeaceChapter1.txt";
        // REDACT TEXT READING
        // reads from local file redact.txt
        File file = new File("../Files/Q6/redact.txt");
        BufferedReader br = new BufferedReader(new FileReader(file));
        // stores the names that are read from txt file
        String line;
        String redact = "";
        // reads the redacted text from redact.txt
        while ((line = br.readLine()) != null) {
            redact = redact + line + " ";
        }
        // WAR&PEACE TEXT READING
        file = new File(fileToRedact);
        br = new BufferedReader(new FileReader(file));
        String text = "";
        // reads the chapter text from warandpeace.txt
        while ((line = br.readLine()) != null) {
            text = text + line + " ";
        }

        for (int i = 1; i < length(text); i++) {
            char currentChar = getChar(text, i);
            // if text is a capital, and previous character was a space, and the character before that was not a fullstop
            // Also checks for the letter I by checking if the character after it is a space or not
            // i.e. proper pronoun in middle of a sentence
            if (currentChar >= 65 && currentChar <= 90 && getChar(text, i - 1) == 32 && getChar(text, i - 2) != 46 && (currentChar != 'I' && getChar(text, i + 1) != ' ')) {
                //if (currentChar != 'I' && getChar(text, i + 1) != ' ')
                text = removeWords(text, i);
            } else if ((currentChar == 46 || currentChar == 10) && i < length(text) - 1) { // need to check if word is proper noun if at start of sentence or paragraph
                String[] redactedList = getRedactedArray(redact);
                String currentWord = getWordAtIndex(text, i + 2);
                for (int j = 1; j < redactedList.length; j++) {
                    if (currentWord.equals(redactedList[j])) {
                        text = removeWords(text, i + 2);
                    }
                }
            }
        }
        File fileOutput = new File("../Files/Q6/redactedOutput.txt");
        fileOutput.createNewFile();
        FileWriter fileWriter = new FileWriter(fileOutput);
        fileWriter.write(text);
        fileWriter.close();
        System.out.println("Redacted text has been outputted to file.");
    }

    public static String[] getRedactedArray(String redactedWordsList) {
        String[] redactedWordsArray = new String[1];
        String redactedWord;
        int startIndex = 0;
        while (startIndex < length(redactedWordsList)) {
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
        for (int i = startIndex; i < length(text); i++) {
            char character = getChar(text, i);
            // if the next char is a space return i
            if (character == 32 || character == 10) {
                return i;
            }
        }
        return length(text);
    }

    public static String removeWords(String text, int startIndex) {
        for (int i = startIndex; i < length(text); i++) {
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
        return text.substring(0, index) + replaceWith + text.substring(index + 1, length(text));
    }


    // gets the char from word at the specified index and returns it
    public static char getChar(String word, int index) {
        char[] wordSplit = word.toCharArray();
        return wordSplit[index];
    }

    public static int length(String text) {
        char[] textSplit = text.toCharArray();
        return textSplit.length;
    }

    // removes a char from a string and replaces it with no character
    public static String removeChar(String words, char toReplace) {
        String result = "";
        // loops through the string
        for (int i = 0; i < length(words); i++) {
            // if the character the current index is located at is NOT the word to replace then it adds it to the string
            // otherwise it does not add it, therefore the character is removed
            char character = getChar(words,i);
            if (character != toReplace) {
                result += character;
            }
        }
        return result;
    }
}
