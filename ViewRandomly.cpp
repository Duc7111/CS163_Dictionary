#include "ViewRandomly.h"
#include "search.h"
int FindRandom(AVL& tree, bNode*& root)
{
	srand(time(NULL));
	int total;;
	tree.num_of_words(root, total);
	int number = rand() % total + 1;
	return number;
}
bNode* ViewRandom(bNode*& root, int number, int count, AVL& tree, string dir)
{
	if (root)
	{
		if (number == count)
		{
			return root;
		}
		if (root->left) ViewRandom(root->left, number, count + 1, tree, dir);
		if (root->right) ViewRandom(root->right, number, count + 1, tree, dir);
	}
}