
import java.util.*;

class Node <T extends Comparable <T>> {
	Node <T> left, right, parent;
	T data;
	int count;

	public Node (T d, Node <T> p) {
		data = d;
		left = right = null;
		parent = p;
		count = 0; // Instruccion de mas
	}

	public void insert (T value, Node <T> father) {
		if (value.compareTo (data) < 0) {
			if (left == null) {
				left = new Node <T> (value, father);
			}
			else 
				left.insert (value, left);
		} 
		if (value.compareTo (data) > 0) {
			if (right == null) { 
				right = new Node <T> (value, father);
			}
			else 
				right.insert (value, right);
		} 
	}

	public boolean isLeaf () {
		return left == null && right == null && data != null;
	}

	public Node <T> get (T value) {
		if (data != null) {
			if (value.compareTo (data) == 0)
				return this;
			if (value.compareTo (data) < 0 && left != null)
				return left.get (value);
			if (value.compareTo (data) > 0 && right != null)
				return right.get (value);
		} 
		return null;
	}

	public Node <T> minimum () {
		if (left == null)
			return this;
		return left.minimum ();
	}

	public Node <T> maximum () {
		if (right == null)
			return this;
		return right.maximum ();
	}

	private void transplant(Node <T> old, Node <T> replace){
		if (old.parent == null)  
			old = replace;
		else if (old.parent.left == old) 
			old.parent.left = replace;
		else
			old.parent.right = replace;
		if (replace != null) 
			replace.parent = old.parent;
		old = null;  
	}

	public boolean delete (T value) {
		Node <T> remove = this.get (value);
		if (remove == null) 
			return false;
		if (remove.left == null)
			transplant(remove, remove.right);
		else if (remove.right == null) 
			transplant (remove, remove.left);
		else {
			Node <T> min = remove.right.minimum();
			T temp = min.data;
			min.delete(min.data);
			remove.data = temp;
		}
		return true;
	}

}

public class Bst <T extends Comparable <T>> {
	private Node <T> root;

	public Bst () { root = null; }

	public void delete (T data) { 
		root.delete (data);
		root.count--;
		if (root.count == 0) // Parche
			root = null;
	}

	public int size () { return root.count; }

	public void insert (T data) {
		if (root == null)
			root = new Node <T> (data, null);
		else 
			root.insert (data, root);
		root.count++;
	}

	public void inorder () {
		inorderHelper (root);
		System.out.println ();
	}

	private void inorderHelper (Node <T> node) {
		if (node == null) {
			System.out.print("-");
			return;
		}
		System.out.print("(");
		inorderHelper (node.left);
		System.out.print (node.data);
		inorderHelper (node.right);
		System.out.print(")");
	}

	public T search (T value) {
		Node <T> current = root.get (value);
		if (current == null)
			return null;
		return current.data;
	}

	public T maximum() { return root.maximum().data; }

	public T minimum() { return root.minimum().data; }

	public T successor (T value) {
		Node <T> current = root.get (value);
		if (current == null)
			return null;
		if (current.right != null) 
			return current.right.minimum().data;
		while (current != null && value.compareTo (current.data) < 0)
			current = current.parent;
		if (current == null)
			return null;
		return current.data;
	}	

} 
