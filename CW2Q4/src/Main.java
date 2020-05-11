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

    // insert the node after the 'after' value
    public static void insertAfter(String after, Node newObj, Node[] linkedList) {
        // checks if after is tail, if it is then don't run function
        if (!after.equals("TAIL")) {
            int address = 0;
            int prevNode = 0;
            int nextNode;
            // set the current node equal to the first node
            Node currentNode = linkedList[address];
            // loop through the list length
            for (int i = 0; i < linkedList.length; i++) {
                // if the current node is equal to after then ...
                if (currentNode.getName().equals(after)) {
                    // update pointer address for the new object
                    newObj.setPointer(address ^ (currentNode.getPointer() ^ prevNode));
                    // find free space in the list
                    int newIndex = findFreeSpace(linkedList);
                    // check if no space found
                    if (newIndex == -1) {
                        // error message
                        System.out.println("No space found for " + newObj.getName());
                        // if no space found then exit
                        break;
                    }
                    // add object to list
                    linkedList[newIndex] = newObj;
                    // updating the next item in the list's pointer to include the new item
                    nextNode = prevNode ^ currentNode.getPointer();
                    linkedList[nextNode].setPointer(newIndex ^ (address ^ linkedList[nextNode].getPointer()));
                    // updating the current pointer to include the new item
                    currentNode.setPointer(newIndex ^ prevNode);
                    // break the for loop
                    break;
                    // check if the current node is tail, if so then break
                } else if (currentNode.getName().equals("TAIL")) {
                    // tell user what happened
                    System.out.println("Node not found");
                    break;
                } else {
                    // traverse throught the list
                    // next node's address is current nodes pointer XOR with index of prev node
                    nextNode = currentNode.getPointer() ^ prevNode;
                    // update prevNodes position
                    prevNode = address;
                    // set address to next node
                    address = nextNode;
                    // set currentNode to the next node
                    currentNode = linkedList[address];
                }
            }
        }
    }

    public static void insertBefore(String before, Node newObj, Node[] linkedList) {
        // checks if after is head, if it is then don't run function
        if (!before.equals("HEAD")) {
            int address = 0;
            int prevNode = 0;
            // set the current node equal to the first node
            Node currentNode = linkedList[address];
            int nextNode = currentNode.getPointer() ^ prevNode;
            for (int i = 0; i < linkedList.length; i++) {
                // if next node is equal to before then
                if (linkedList[nextNode].getName().equals(before)) {
                    // update pointer address for the new object
                    newObj.setPointer(address ^ (currentNode.getPointer() ^ prevNode));
                    // find free space in the list
                    int newIndex = findFreeSpace(linkedList);
                    // check if no space found
                    if (newIndex == -1) {
                        // error message
                        System.out.println("No space found for " + newObj.getName());
                        // if no space found then exit
                        break;
                    }
                    // add object to list
                    linkedList[newIndex] = newObj;
                    // updating the next item in the list's pointer to include the new item
                    nextNode = prevNode ^ currentNode.getPointer();
                    linkedList[nextNode].setPointer(newIndex ^ (address ^ linkedList[nextNode].getPointer()));
                    // updating the current pointer to include the new item
                    currentNode.setPointer(newIndex ^ prevNode);
                    break;
                    // if current node is tail then before string not found so break
                } else if (currentNode.getName().equals("TAIL")) {
                    // tell user what happened
                    System.out.println("Node not found");
                    break;
                } else {
                    // update prevNodes position
                    prevNode = address;
                    // set address to next node
                    address = nextNode;
                    // set currentNode to the next node
                    currentNode = linkedList[address];
                    // next node's address is current nodes pointer XOR with index of prev node
                    nextNode = currentNode.getPointer() ^ prevNode;
                }
            }
        }
    }

    // find the next free index in the linkedList array
    public static int findFreeSpace(Node[] linkedList) {
        // loop through
        for (int i = 0; i < linkedList.length; i++) {
            // if index is null then return i
            if (linkedList[i] == null) {
                return i;
            }
        }
        // if no free space found output -1
        return -1;
    }

    public static void removeAfter(String after, Node[] linkedList) {
        // if after is TAIL then do not run function
        if (!after.equals("TAIL")) {
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
                    // set the item to be removed to null
                    linkedList[toRemoveNode] = null;
                    break;
                    // if at end of list then break
                } else if (currentNode.getName().equals("TAIL")) {
                    // tell user what happened
                    System.out.println("Item not found in list");
                    break;
                } else {
                    // List traversal - same code as insertAfter list traversal, see above for commenting
                    nextNode = currentNode.getPointer() ^ prevNode;
                    prevNode = address;
                    address = nextNode;
                    currentNode = linkedList[address];
                }
            }
        }
    }

    public static void removeBefore(String before, Node[] linkedList) {
        // if before is HEAD then don't run function
        if (!before.equals("HEAD")) {
            int address = 0;
            int prevNode = 0;
            Node currentNode = linkedList[address];
            int nextNode = currentNode.getPointer() ^ prevNode;
            for (int i = 0; i < linkedList.length; i++) {
                if (linkedList[nextNode].getName().equals(before)) {
                    int toRemoveNode = address;
                    // set the current node to the previous node
                    currentNode = linkedList[prevNode];
                    // update the current item's pointer to point to the node after the removed node
                    currentNode.setPointer(prevNode ^ nextNode);
                    // update the item after the node to be removed's pointer
                    linkedList[nextNode].setPointer(prevNode ^ (toRemoveNode ^ linkedList[nextNode].getPointer()));
                    // set the item to be removed to null
                    linkedList[toRemoveNode] = null;
                    break;
                } else if (currentNode.getName().equals("TAIL")) {
                    // tell user what happened
                    System.out.println("Item not found in list");
                    break;
                } else {
                    // list traversal, same as insertBefore traversal, see commenting there
                    prevNode = address;
                    address = nextNode;
                    currentNode = linkedList[address];
                    nextNode = currentNode.getPointer() ^ prevNode;
                }
            }
        }
    }

    // output the linkedList in the order it is traversed
    public static void outputList(Node[] linkedList) {
        int address = 0;
        int prevNode = 0;
        int nextNode;
        Node currentNode = linkedList[address];
        System.out.println("Data item " + currentNode.getName() + " @ index " + address + ". Current node's pointer: " + currentNode.getPointer() + ". Previous node index: " + prevNode);
        for (int i = 0; i < linkedList.length; i++) {
            // if currentNode is TAIl then we have finished so break
            if (currentNode.getName().equals("TAIL")) {
                break;
            }
            // traversal (same code as insertAfter traversal
            nextNode = currentNode.getPointer() ^ prevNode;
            prevNode = address;
            address = nextNode;
            currentNode = linkedList[address];
            System.out.println("Data item " + currentNode.getName() + " @ index " + address + ". Current node's pointer: " + currentNode.getPointer() + ". Previous node index: " + prevNode);
        }
    }

    // returns the length of a string
    public static int length(String text) {
        char[] textSplit = text.toCharArray();
        return textSplit.length;
    }

}
