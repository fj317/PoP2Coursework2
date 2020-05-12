public class Node {
    String name;
    int pointer;

    // constructor to setup the node
    public Node(String name, int pointer) {
        this.name = name;
        this.pointer = pointer;
    }

    // setter for the name
    public void setName(String name) {
        this.name = name;
    }

    // setter for the pointer
    public void setPointer(int pointer) {
        this.pointer = pointer;
    }


    // getter for the name
    public String getName() {
        return name;
    }

    // getter for the pointer
    public int getPointer() {
        return pointer;
    }
}
