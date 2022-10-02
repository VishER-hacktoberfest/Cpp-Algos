// A O(n) C++ program to construct cartesian tree
// from a given array
#include<bits/stdc++.h>

/* A binary tree node has data, pointer to left
child and a pointer to right child */
struct Node
{
	int data;
	Node *left, *right;
};

/* This function is here just to test buildTree() */
void printInorder (Node* node)
{
	if (node == NULL)
		return;
	printInorder (node->left);
	cout << node->data << " ";
	printInorder (node->right);
}

// Recursively construct subtree under given root using
// leftChild[] and rightchild
Node * buildCartesianTreeUtil (int root, int arr[],
		int parent[], int leftchild[], int rightchild[])
{
	if (root == -1)
		return NULL;

	// Create a new node with root's data
	Node *temp = new Node;
	temp->data = arr[root] ;

	// Recursively construct left and right subtrees
	temp->left = buildCartesianTreeUtil( leftchild[root],
					arr, parent, leftchild, rightchild );
	temp->right = buildCartesianTreeUtil( rightchild[root],
					arr, parent, leftchild, rightchild );

	return temp ;
}

// A function to create the Cartesian Tree in O(N) time
Node * buildCartesianTree (int arr[], int n)
{
	// Arrays to hold the index of parent, left-child,
	// right-child of each number in the input array
	int parent[n],leftchild[n],rightchild[n];

	// Initialize all array values as -1
	memset(parent, -1, sizeof(parent));
	memset(leftchild, -1, sizeof(leftchild));
	memset(rightchild, -1, sizeof(rightchild));

	// 'root' and 'last' stores the index of the root and the
	// last processed of the Cartesian Tree.
	// Initially we take root of the Cartesian Tree as the
	// first element of the input array. This can change
	// according to the algorithm
	int root = 0, last;

	// Starting from the second element of the input array
	// to the last on scan across the elements, adding them
	// one at a time.
	for (int i=1; i<=n-1; i++)
	{
		last = i-1;
		rightchild[i] = -1;

		// Scan upward from the node's parent up to
		// the root of the tree until a node is found
		// whose value is greater than the current one
		// This is the same as Step 2 mentioned in the
		// algorithm
		while (arr[last] <= arr[i] && last != root)
			last = parent[last];

		// arr[i] is the largest element yet; make it
		// new root
		if (arr[last] <= arr[i])
		{
			parent[root] = i;
			leftchild[i] = root;
			root = i;
		}

		// Just insert it
		else if (rightchild[last] == -1)
		{
			rightchild[last] = i;
			parent[i] = last;
			leftchild[i] = -1;
		}

		// Reconfigure links
		else
		{
			parent[rightchild[last]] = i;
			leftchild[i] = rightchild[last];
			rightchild[last] = i;
			parent[i] = last;
		}

	}

	// Since the root of the Cartesian Tree has no
	// parent, so we assign it -1
	parent[root] = -1;

	return (buildCartesianTreeUtil (root, arr, parent,
									leftchild, rightchild));
}

/* Driver program to test above functions */
int main()
{
	/* Assume that inorder traversal of following tree
	is given
		40
	/ \
	10	 30
	/		 \
	5		 28 */

	int arr[] = {5, 10, 40, 30, 28};
	int n = sizeof(arr)/sizeof(arr[0]);

	Node *root = buildCartesianTree(arr, n);

	/* Let us test the built tree by printing Inorder
	traversal */
	printf("Inorder traversal of the constructed tree : \n");
	printInorder(root);

	return(0);
}
