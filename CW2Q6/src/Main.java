
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
        for (int i = 1; i < text.length(); i++) {
            // if text is a capital, and previous character was a space, and the character before that was not a fullstop
            if (getChar(text, i) >= 65 && getChar(text, i) <= 90 && getChar(text, i - 1) == 32 && getChar(text, i - 2) != 46) {
                text = removeWords(text, i);
            }
        }
        System.out.println(text);
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
        return text.substring(0, index) + replaceWith + text.substring(index + 1, text.length() - 1);
    }


    // gets the char from word at the specified index and returns it
    public static char getChar(String word, int index) {
        char[] wordSplit = word.toCharArray();
        return wordSplit[index];
    }
}
