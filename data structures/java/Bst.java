
import java.util.*;

class TreeNode <T extends Comparable <T>> {
	TreeNode <T> left, right, parent;
	T data;

	public TreeNode (T d, TreeNode <T> p) {
		data = d;
		left = right = null;
		parent = p;
	}

	public void insert (T value, TreeNode <T> father) {
		if (value.compareTo (data) < 0) {
			if (left == null) 
				left = new TreeNode <T> (value, father);
			else 
				left.insert (value, left);
		} 
		if (value.compareTo (data) > 0) {
			if (right == null) 
				right = new TreeNode <T> (value, father);
			else 
				right.insert (value, right);
		} 
	}

	public boolean isLeaf () {
		return left == null && right == null && data != null;
	}

	public TreeNode <T> get (T value) {
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

	public TreeNode <T> minimum () {
		if (left == null)
			return this;
		return left.minimum ();
	}

	public TreeNode <T> maximum () {
		if (right == null)
			return this;
		return right.maximum ();
	}

	private void transplant(TreeNode <T> old, TreeNode <T> replace){
		if (old.parent == null)  
			old = replace;
		else if (old.parent.left == old) 
			old.parent.left = replace;
		else
			old.parent.right = replace;
		if (replace != null) 
			old.parent = replace.parent;
	}

	public void delete(T value) {
		TreeNode <T>remove = this.get (value);
		if (remove == null) {
			System.out.println("No exists the value " + value);
			return;
		}
		if (remove.left == null)
			transplant(remove, remove.right);
		else if (remove.right == null) 
			transplant(remove, remove.left);
		else {
			TreeNode <T> min = remove.right.minimum();
			T temp = min.data;
			min.delete(min.data);
			remove.data = temp;
		}
	}
}

public class Bst <T extends Comparable <T>> {
	private TreeNode <T> root;

	public Bst () {
		root = null;
	}

	public void delete (T data) {
		root.delete (data);
	}

	public void insert (T data) {
		if (root == null)
			root = new TreeNode <T> (data, null);
		else 
			root.insert (data, root);
	}

	public void inorder () {
		inorderHelper (root);
		System.out.println();
	}

	private void inorderHelper (TreeNode <T> node) {
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
		TreeNode <T> current = root.get (value);
		if (current == null)
			return null;
		return current.data;
	}

	public T maximum() {
		return root.maximum().data;
	}

	public T minimum() {
		return root.minimum().data;
	}

	public T successor (T value) {
		TreeNode <T> current = root.get (value);
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
