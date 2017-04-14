
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


int heightOfBst(bstNode* root)
{
	if(root==NULL)
		return 0;

	int left=heightOfBst(root->left);
	int right=heightOfBst(root->right);

	return left>right?left+1:right+1;
}

/*BST Depth First Search Traversal*/
/*Pre Order*/
void preOrderBst(bstNode *root) 
{
	if(root != NULL) {
		printf("%d ", root->key);
		preOrderBst(root->left);
		preOrderBst(root->right);
	}

	return;
}

/*Post Order*/
void postOrderBst(bstNode *root) 
{
	if(root != NULL){
		postOrderBst(root->left);
		postOrderBst(root->right);
		printf("%d ", root->key);
	}

	return;
}

/*In Order*/
void inOrderBst(bstNode *root)
{
	if (root != NULL) {
		inOrderBst(root->left);
		printf("%d ", root->key);
		inOrderBst(root->right);
	}

	return;
}


/*BST Breath First Search Traversal (Level Order Traversal)*/
static void print_level(bstNode *root, int level, int id)
{
	if(!root)
		return;

	if(level == id)
		printf("%d ", root->key);

	print_level(root->left, level, id+1);
	print_level(root->right, level, id+1);
}


void levelOrderBst(bstNode * root)
{
	int level=0;
	if(!root)
		return;

	/* get the height of the tree first */
	int h = heightOfBst(root);
	for(level=1; level<=h; level++) {
		print_level(root, level, 1);
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
static bool check_bst(bstNode* root)
{
	if(root) {
		if(!check_bst(root->left))
			return false;

		if(prev!=NULL && prev->key >= root->key)
			return false;

		prev = root;
		return check_bst(root->right);
	}
	return true;
}

bool checkBST(bstNode* root) 
{
	prev=NULL;
	return check_bst(root);
}

bstNode* lowestCommonAncestorOfBstNode(bstNode * root, int v1,int v2)
{
	if (!root)
		return NULL;

	if (root->key == v1 || root->key == v2)
		return root;

	bstNode *left_lca  = lowestCommonAncestorOfBstNode(root->left, v1, v2);
	bstNode *right_lca = lowestCommonAncestorOfBstNode(root->right, v1, v2);

	if (left_lca && right_lca)
		return root;

	return (left_lca != NULL)? left_lca: right_lca;
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

	printf("\n\nSample BST:\n");
	printf("\n     %d", 50);
	printf("\n    %c  %c", '/', '|');
	printf("\n  %d     %d", 30, 70);
	printf("\n %c  %c   %c  %c", '/', '|', '/', '|');
	printf("\n%d  %d %d   %d", 20, 40, 60, 80);

	printf("\n\nIs BST : %s", checkBST(root)?"TRUE":"FALSE" );
	printf("\nHeight of BST is: %d", heightOfBst(root));

	printf("\n\nDepth First Traversal:");
	/* print BST */
	printf("\n1: Pre-Order:\n");
	preOrderBst(root);

	printf("\n\n2: Post-Order:\n");
	postOrderBst(root);

	printf("\n\n3: In-Order:\n");
	inOrderBst(root);

	printf("\n\nBreath First Traversal:\n");
	levelOrderBst(root);

	/* delete node from BST*/
	printf("\n\nDeleting: 50\n");
	root = deleteNodeFromBst(root, 50);

	/* print inoder traversal of the BST */
	inOrderBst(root);

	printf("\n\nIs BST : %s\n", checkBST(root)?"TRUE":"FALSE" );

	bstNode* tmp = lowestCommonAncestorOfBstNode(root, 30, 80);
	if(tmp)
		printf("\nLowest Comomn Ancestor of 30 and 80 in BST is: %d\n", tmp->key );
	
	return 0;
}
