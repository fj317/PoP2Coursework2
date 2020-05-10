public class Main {

    public static void main(String[] args) {
        Node[] linkedList = new Node[60];
        setupList(linkedList);
        Node newObj = new Node("data1", 0);
        Node newObj2 = new Node("data2", 0);
        Node newObj3 = new Node("data3", 0);

        insertAfter("HEAD",newObj, linkedList);
        insertAfter("HEAD",newObj2, linkedList);
        //insertAfter("HEAD",newObj3, linkedList);
        insertBefore("data2", newObj3, linkedList);
        outputList(linkedList);
    }

    public static Node[] setupList(Node[] linkedList) {
        for (int i = 0; i < 60; i++) {
            linkedList[i] = new Node(null, 0);
        }
        setupHeadTail(linkedList);
        return linkedList;
    }

    public static Node[] setupHeadTail(Node[] linkedList) {
        linkedList[0].setName("HEAD");
        linkedList[0].setPointer(1);
        linkedList[1].setName("TAIL");
        linkedList[1].setPointer(0);
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

    public static int findFreeSpace(Node[] linkedList) {
        for (int i = 0; i < linkedList.length; i++) {
            if (linkedList[i].getName() == null) {
                return i;
            }
        }
        System.out.println("No free space");
        return -1;
    }

    public static void removeAfer(String after, Node[] linkedList) {
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
                linkedList[toRemoveNode].setName(null);
                linkedList[toRemoveNode].setPointer(0);
                break;
            } else if (currentNode.getName().equals("TAIL")) {
                break;
            }
            nextNode = currentNode.getPointer() ^ prevNode;
            prevNode = address;
            address = nextNode;
            currentNode = linkedList[address];
            System.out.println("Data item " + currentNode.getName() + ". CurrentPointer: " + currentNode.getPointer() + ". PrevNode: " + prevNode);
        }
    }

    public static void removeBefore(String before) {

    }

}
