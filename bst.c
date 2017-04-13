
#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

bstNode* searchBst(bstNode* root, int key)
{
	/* return if root is null or key is found*/
	if (root == NULL || root->key == key) {
		return root;
	}

	/* if key is greater goto right */
	if (root->key < key) {
		return searchBst(root->right, key);
	} else {
		return searchBst(root->left, key);
	}
}

void inorderBst(bstNode *root)
{
	if (root != NULL)
	{
		inorderBst(root->left);
		printf("%d \n", root->key);
		inorderBst(root->right);
	}
}


bstNode *newNode(int item)
{
	bstNode *node =  (bstNode *)malloc(sizeof(bstNode));
	node->key = item;
	node->left = node->right = NULL;
	return node;
}


bstNode* insertBst(bstNode* node, int key)
{
	/* If the tree is empty, return a new bstNode */
	if (node == NULL){
		return newNode(key);
	}

	/* Otherwise, go down the tree to insert later*/
	if (key < node->key) {
		node->left  = insertBst(node->left, key);
	} else if (key > node->key) {
		node->right = insertBst(node->right, key);   
	}

	/* return the (unchanged) node pointer */
	return node;
}

int main()
{
	/* Let us create following BST
	 *               50
	 *             /     \
	 *           30      70
	 *          /  \    /  \
	 *         20   40  60   80 
	 **/
	bstNode *root = NULL;
	root = insertBst(root, 50);
	insertBst(root, 30);
	insertBst(root, 20);
	insertBst(root, 40);
	insertBst(root, 70);
	insertBst(root, 60);
	insertBst(root, 80);

	// print inoder traversal of the BST
	inorderBst(root);

	return 0;
}
