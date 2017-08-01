
import java.util.*;

public class BstTest{
	public static void main(String[] args) {
		Bst <Integer> tree = new Bst <Integer>();
		int[] array = { 2, 4, 5, 3, 1 };

		for (int i = 0; i < array.length; i++)
			tree.insert (array[i]);
		tree.inorder();
		tree.delete (2);
		tree.inorder();
		tree.delete (1);
		tree.inorder();
		tree.delete (4);
		tree.inorder();
		tree.delete (3);
		tree.inorder();
		tree.delete (5);
		tree.inorder();
	}
} 
