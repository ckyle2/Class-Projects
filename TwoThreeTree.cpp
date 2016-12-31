#include <iostream> 
using namespace std;

//Chase Kyle
//CPSC 250 11:00-11:50AM
//HANDS ON 5
//Implementation of a binary search tree, and a two-three tree
struct TreeNode
{
	int info;
	TreeNode *left;
	TreeNode *right;
};

struct TwoThreeNode
{
	int small;
	int large;
	TwoThreeNode * left;
	TwoThreeNode * middle;
	TwoThreeNode * right;
};

void insert(TreeNode *&tree, int item);
void inOrder(TreeNode *tree);
TreeNode *TreeSearch(TreeNode *node, int key);

void in_order_two_three(TwoThreeNode*);
TwoThreeNode *TreeSearch_two_three(TwoThreeNode*, int);


int main()
{
	//creates a bst of type treenode
	TreeNode *tree = NULL;
	insert(tree, 10);
	insert(tree, 18);
	insert(tree, 7);
	insert(tree, 2);
	insert(tree, 20);
	insert(tree, 15);
	cout << "The inserted numbers are: ";
	inOrder(tree);
	cout << endl << endl;
	if (TreeSearch(tree, 7))
		cout << "7 is in the tree" << endl;
	else
		cout << "7 is not in the tree" << endl;
	if (TreeSearch(tree, 13))
		cout << "13 is in the tree" << endl;
	else
		cout << "13 is not in the tree" << endl << endl;
	//creates two-three nodes with initialized values
	TwoThreeNode one, two, three, four, five, six, seven, eight, nine, ten, eleven;
	one.small = 50;
	one.large = 90;
	one.left = &two;
	one.middle = &three;
	one.right = &four;

	two.small = 20;
	two.large = NULL;
	two.left = &five;
	two.middle = NULL;
	two.right = &six;

	three.small = 70;
	three.large = NULL;
	three.left = &seven;
	three.middle = NULL;
	three.right = &eight;

	four.small = 120;
	four.large = 150;
	four.left = &nine;
	four.middle = &ten;
	four.right = &eleven;

	five.small = 10;
	five.large = NULL;
	five.left = NULL;
	five.middle = NULL;
	five.right = NULL;

	six.small = 30;
	six.large = 40;
	six.left = NULL;
	six.middle = NULL;
	six.right = NULL;

	seven.small = 60;
	seven.large = NULL;
	seven.left = NULL;
	seven.middle = NULL;
	seven.right = NULL;

	eight.small = 80;
	eight.large = NULL;
	eight.left = NULL;
	eight.middle = NULL;
	eight.right = NULL;

	nine.small = 100;
	nine.large = 110;
	nine.left = NULL;
	nine.middle = NULL;
	nine.right = NULL;

	ten.small = 130;
	ten.large = 140;
	ten.left = NULL;
	ten.middle = NULL;
	ten.right = NULL;

	eleven.small = 160;
	eleven.large = NULL;
	eleven.left = NULL;
	eleven.middle = NULL;
	eleven.right = NULL;
	
	//make the first two-three node the root
	TwoThreeNode *root = &one;
	//print two-three tree in order
	in_order_two_three(root);

	cout << endl << endl;

	if (TreeSearch_two_three(root, 70))
		cout << "70 is in the tree" << endl << endl;
	else
		cout << "70 is not in the tree" << endl << endl;

	if (TreeSearch_two_three(root, 200))
		cout << "200 is in the tree" << endl << endl;
	else
		cout << "200 is not in the tree" << endl << endl;

	system("pause");
	return 0;
}
//function for inserting an item into the bst
void insert(TreeNode*& tree, int item)
{
	//if the tree does not exist, create it using first item as head
	if (tree == NULL)
	{
		tree = new TreeNode;
		tree->right = NULL;
		tree->left = NULL;
		tree->info = item;
	}
	//insert item left or right of current node based on value
	else if (item < tree->info)
		insert(tree->left, item);
	else
		insert(tree->right, item);
}
//prints each node of bst in order
void inOrder(TreeNode*tree)
{
	if (tree != NULL)
	{
		inOrder(tree->left);
		cout << tree->info << " ";
		inOrder(tree->right);
	
	}
}
//function for searching bst to see if an item exists
TreeNode *TreeSearch(TreeNode *node, int key)
{
	if (node == NULL || key == node->info)
		return node;
	if (key < node->info)
		return TreeSearch(node->left, key);
	else
		TreeSearch(node->right, key);
}
//function for printing the two-three nodes in the tree in order
void in_order_two_three(TwoThreeNode *node)
{
	if (node->left != NULL)
		in_order_two_three(node->left);
	if (node->small != NULL)
		cout << node->small << " ";
	if (node->middle != NULL)
		in_order_two_three(node->middle);
	if (node->large != NULL)
		cout << node->large << " ";
	if (node->right != NULL)
		in_order_two_three(node->right);
}
//function for searching the two-three tree to see if an item exists
TwoThreeNode *TreeSearch_two_three(TwoThreeNode *node, int key)
{
	if (node == NULL || key == node->small || key == node->large)
		return node;
	if (key < node->small)
		return TreeSearch_two_three(node->left, key);
	if (key > node->small && key < node->large)
		return TreeSearch_two_three(node->middle, key);
	else
		TreeSearch_two_three(node->right, key);
}