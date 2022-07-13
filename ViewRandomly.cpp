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
void ViewRandom(bNode*& root, int number, int& count, AVL& tree, string dir, bNode*& random)
{
	if (root)
	{
		count++;
		if (count > number)
		{
			return;
		}
		if (number == count)
		{
			random = root;
			return;
		}
		if (root->left && !random) ViewRandom(root->left, number, count, tree, dir, random);
		if (root->right && !random) ViewRandom(root->right, number, count, tree, dir, random);
	}
}