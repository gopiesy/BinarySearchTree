
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "bst.h"

/*Helper function*/
static bool check_bst(bstNode* root);

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

bstNode* getSmallestNode(bstNode *root)
{
	bstNode* current = root;

	/* Left most child in the BST is smallest */
	while (current->left != NULL){
		current = current->left;
	}

	return current;
} 

bstNode* getLargestNode(bstNode *root)
{
	bstNode* current = root;

	/* Right most child in the BST is largest */
	while (current->right != NULL){
		current = current->right;
	}

	return current;
} 

void inorderBst(bstNode *root)
{
	if (root != NULL) {
		inorderBst(root->left);
		printf("%d \n", root->key);
		inorderBst(root->right);
	}
}


bstNode* newNode(int item)
{
	bstNode *node =  (bstNode *)malloc(sizeof(bstNode));
	node->key = item;
	node->left = node->right = NULL;
	return node;
}


bstNode* insertIntoBst(bstNode* node, int key)
{
	/* If the tree is empty, return a new bstNode */
	if (node == NULL){
		return newNode(key);
	}

	/* Otherwise, go down the tree to insert later*/
	if (key < node->key) {
		node->left  = insertIntoBst(node->left, key);
	} else if (key > node->key) {
		node->right = insertIntoBst(node->right, key);   
	}

	/* return the (unchanged) node pointer */
	return node;
}

bstNode* deleteNodeFromBst(bstNode* root, int key)
{
	bstNode *temp;
	/* return if the node is null */
	if (root == NULL)
		return root;

	/*
	 *  key < root key; goto left	
	 *  key > root key; goto right
	 *  key == root key; (delete this node)
	 */

	if (key < root->key) { /* If the key to be deleted is smaller than the root's key, then it lies in left subtree */
		root->left = deleteNodeFromBst(root->left, key);
	} else if (key > root->key) { /* If the key to be deleted is greater than the root's key, then it lies in right subtree */
		root->right = deleteNodeFromBst(root->right, key);
	} else { /* Key is same as root's key, This is the node to be deleted */

		/*Here we may have to balance the tree by swapping the nodes*/

		/* If node has only one child or no children */
		if (root->left == NULL) {
			temp = root->right;
			free(root);
			return temp;
		} else if (root->right == NULL) {
			temp = root->left;
			free(root);
			return temp;
		}

		/* We Have both the children, so we have a choice to swap either
		 * smallest child on the right side (or)
		 * largest  child on the left  side*/

		/* Find the node to swap*/
		temp = getSmallestNode(root->right);

		/* Swap the node*/
		root->key = temp->key;

		/* Delete the node */
		root->right = deleteNodeFromBst(root->right, temp->key);
	}
	return root;
}

static bstNode *prev=NULL;
bool checkBST(bstNode* root) 
{
	prev=NULL;
	return check_bst(root);
}

static bool check_bst(bstNode* root)
{

	if(!root)
		return true;
	else {
		if(!check_bst(root->left))
			return false;

		if(prev!=NULL && prev->key >= root->key)
			return false;

		prev = root;
		return check_bst(root->right);
	}
	return true;
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
	root = insertIntoBst(root, 50);
	root = insertIntoBst(root, 30);
	root = insertIntoBst(root, 20);
	root = insertIntoBst(root, 40);
	root = insertIntoBst(root, 70);
	root = insertIntoBst(root, 60);
	root = insertIntoBst(root, 80);

	/* print inoder traversal of the BST */
	inorderBst(root);
	printf("\nIs BST : %s\n", checkBST(root)?"TRUE":"FALSE" );

	/* delete node from BST*/
	printf("\nDeleting: 50\n");
	root = deleteNodeFromBst(root, 50);

	/* print inoder traversal of the BST */
	inorderBst(root);

	printf("\nIs BST : %s\n", checkBST(root)?"TRUE":"FALSE" );
	return 0;
}
