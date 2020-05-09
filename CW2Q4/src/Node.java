public class Node {
    String name;
    int pointer;

    public Node(String name, int pointer) {
        this.name = name;
        this.pointer = pointer;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setPointer(int pointer) {
        this.pointer = pointer;
    }

    public String getName() {
        return name;
    }

    public int getPointer() {
        return pointer;
    }
}
