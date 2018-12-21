//linked list with dummy node cycle mode
import java.util.Iterator;

public class LinkedLinearList<T> implements Iterable<LinkedLinearList<T>> {
    private Node<T> headerNode;
    private int mSize;

    public LinkedLinearList() {
        mSize = 0;
        headerNode = new Node<T>();
        headerNode.next = headerNode;
        headerNode.prev = headerNode;
    }

    @Override
    public Iterator<LinkedLinearList<T>> iterator() {
        return new LinkedListForwardIterator<>();
    }

    public Iterator<T> ForwardIterator() {
        return new LinkedListForwardIterator(headerNode);
    }

    public Iterator<T> BackwardIterator() {
        return new LinkedListBackwardIterator(headerNode);
    }

    // The returned iterator would point to the inserted element.
    public void insert(int position, T data) throws IndexOutOfBoundsException {
        if (position > size()) {
            throw new IndexOutOfBoundsException();
        }
        Node<T> newnode = new Node<>();
        newnode.data = data;

        Node<T> lastnode = headerNode;
        for (int i = 0; i < position; i++) {
            lastnode = lastnode.next;
        }
        newnode.prev = lastnode;
        newnode.next = lastnode.next;
        lastnode.next.prev = newnode;
        lastnode.next = newnode;
        mSize++;
    }

    // The returned iterator would point to the element after the removed one.
    public void remove(int position) throws IndexOutOfBoundsException {
        if (position > size()) {
            throw new IndexOutOfBoundsException();
        }
        Node<T> lastnode = headerNode;
        for (int i = 0; i < position; i++) {
            lastnode = lastnode.next;
        }
        lastnode.next.next.prev = lastnode;
        lastnode.next = lastnode.next.next;
        mSize--;
    }

    public int size() {
        return mSize;
    }

    @Override
    public String toString() {
        String str = "";
        Node currNode = headerNode;
        for (int i = 0; i < mSize; i++) {
            currNode = currNode.next;
            str += (" " + currNode.data);
        }
        return str;
    }

    private class Node<T> {
        public T data;
        public Node prev;
        public Node next;
    }

    public class LinkedListForwardIterator<T> implements Iterator<T> {
        private Node<T> currNode;

        public LinkedListForwardIterator() {
            this.currNode = null;
        }

        public LinkedListForwardIterator(Node<T> node) {
            this.currNode = node;
        }

        public T retrieve() {//it's get equivalent
            return this.currNode.data;
        }

        @Override
        public T next() { // preincrement
            currNode = currNode.next;
            return currNode.data;
        }

        @Override
        public boolean hasNext() {
            return currNode.next != headerNode;
        }
    }

    public class LinkedListBackwardIterator<T> implements Iterator<T> {
        Node<T> currNode;

        public LinkedListBackwardIterator() {
            this.currNode = null;
        }

        public LinkedListBackwardIterator(Node<T> node) {
            this.currNode = node;
        }

        public T retrieve() {//it's get equivalent
            return this.currNode.data;
        }

        @Override
        public T next() { // preincrement
            currNode = currNode.prev;
            return currNode.data;
        }

        @Override
        public boolean hasNext() {
            return currNode.prev != headerNode;
        }
    }
}
