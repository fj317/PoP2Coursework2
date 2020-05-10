import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException {
        // reads from local file names.txt
        File file = new File("../Files/Names/names.txt");
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
        int nameLength = names.length;
        Node[] linkedList = new Node[nameLength + 2];
        setupHeadTail(linkedList);
        Node tempObj;
        for (int i = 0; i < nameLength; i++) {
            tempObj = new Node(names[i], 0);
            insertBefore("TAIL", tempObj, linkedList);
        }

        // TESTING
        Node newObj = new Node("Data1", 0);
        removeBefore("PATRICIA", linkedList);
        insertAfter("LINDA", newObj, linkedList);
        newObj = new Node("Data2", 0);
        removeAfter("BARBARA", linkedList);
        insertBefore("MARIA", newObj, linkedList);
        
        outputList(linkedList);
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

    // gets the char from word at the specified index and returns it
    public static char getChar(String word, int index) {
        char[] wordSplit = word.toCharArray();
        return wordSplit[index];
    }

    public static Node[] setupHeadTail(Node[] linkedList) {
        linkedList[0] = new Node("HEAD", 1);
        linkedList[1] = new Node("TAIL", 0);
        return linkedList;
    }

    public static void insertAfter(String after, Node newObj, Node[] linkedList) {
        int address = 0;
        int prevNode = 0;
        int nextNode;
        Node currentNode = linkedList[address];
        for (int i = 0; i < linkedList.length; i++) {
            if (currentNode.getName().equals(after)) {
                // update pointer address for the new object
                newObj.setPointer(address ^ (currentNode.getPointer() ^ prevNode));
                // find free space in the list
                int newIndex = findFreeSpace(linkedList);
                // add object to list
                linkedList[newIndex] = newObj;
                // updating the next item in the list's pointer to include the new item
                nextNode = prevNode ^ currentNode.getPointer();
                linkedList[nextNode].setPointer(newIndex ^ (address ^ linkedList[nextNode].getPointer()));
                // updating the current pointer to include the new item
                currentNode.setPointer(newIndex ^ prevNode);
                break;
            } else if (currentNode.getName().equals("TAIL")) {
                break;
            } else {
                nextNode = currentNode.getPointer() ^ prevNode;
                prevNode = address;
                address = nextNode;
                currentNode = linkedList[address];
            }
        }
    }

    public static void insertBefore(String before, Node newObj, Node[] linkedList) {
        int address = 0;
        int prevNode = 0;
        Node currentNode = linkedList[address];
        int nextNode = currentNode.getPointer() ^ prevNode;
        for (int i = 0; i < linkedList.length; i++) {
            if (linkedList[nextNode].getName().equals(before)) {
                // update pointer address for the new object
                newObj.setPointer(address ^ (currentNode.getPointer() ^ prevNode));
                // find free space in the list
                int newIndex = findFreeSpace(linkedList);
                // add object to list
                linkedList[newIndex] = newObj;
                // updating the next item in the list's pointer to include the new item
                nextNode = prevNode ^ currentNode.getPointer();
                linkedList[nextNode].setPointer(newIndex ^ (address ^ linkedList[nextNode].getPointer()));
                // updating the current pointer to include the new item
                currentNode.setPointer(newIndex ^ prevNode);
                break;
            } else {
                prevNode = address;
                address = nextNode;
                currentNode = linkedList[address];
                nextNode = currentNode.getPointer() ^ prevNode;
            }
        }
    }

    public static int findFreeSpace(Node[] linkedList) {
        for (int i = 0; i < linkedList.length; i++) {
            if (linkedList[i] == null) {
                return i;
            }
        }
        System.out.println("No free space");
        return -1;
    }

    public static void removeAfter(String after, Node[] linkedList) {
        int address = 0;
        int prevNode = 0;
        int nextNode;
        Node currentNode = linkedList[address];
        for (int i = 0; i < linkedList.length; i++) {
            if (currentNode.getName().equals(after)) {
                int toRemoveNode = currentNode.getPointer() ^ prevNode;
                nextNode = linkedList[toRemoveNode].getPointer() ^ address;
                // update the current item's pointer to point to the node after the removed node
                currentNode.setPointer(prevNode ^ nextNode);
                // update the item after the node to be removed's pointer
                linkedList[nextNode].setPointer(address ^ (toRemoveNode ^ linkedList[nextNode].getPointer()));
                linkedList[toRemoveNode] = null;
                break;
            } else if (currentNode.getName().equals("TAIL")) {
                break;
            } else {
            nextNode = currentNode.getPointer() ^ prevNode;
            prevNode = address;
            address = nextNode;
            currentNode = linkedList[address];
            }
        }
    }

    public static void removeBefore(String before, Node[] linkedList) {
        int address = 0;
        int prevNode = 0;
        Node currentNode = linkedList[address];
        int nextNode = currentNode.getPointer() ^ prevNode;
        for (int i = 0; i < linkedList.length; i++) {
            if (linkedList[nextNode].getName().equals(before)) {
                int toRemoveNode = address;
                currentNode = linkedList[prevNode];
                // update the current item's pointer to point to the node after the removed node
                currentNode.setPointer(prevNode ^ nextNode);
                // update the item after the node to be removed's pointer
                linkedList[nextNode].setPointer(prevNode ^ (toRemoveNode ^ linkedList[nextNode].getPointer()));
                linkedList[toRemoveNode] = null;
                break;
            } else {
                prevNode = address;
                address = nextNode;
                currentNode = linkedList[address];
                nextNode = currentNode.getPointer() ^ prevNode;
                //System.out.println("Data item " + currentNode.getName() + ". CurrentPointer: " + currentNode.getPointer() + ". PrevNode: " + prevNode);
            }
        }
    }

    public static void outputList(Node[] linkedList) {
        int address = 0;
        int prevNode = 0;
        int nextNode;
        Node currentNode = linkedList[address];
        for (int i = 0; i < linkedList.length; i++) {
            if (currentNode.getName().equals("TAIL")) {
                break;
            }
            nextNode = currentNode.getPointer() ^ prevNode;
            prevNode = address;
            address = nextNode;
            currentNode = linkedList[address];
            System.out.println("Data item " + currentNode.getName() + ". CurrentPointer: " + currentNode.getPointer() + ". PrevNode: " + prevNode);
        }
    }

}
