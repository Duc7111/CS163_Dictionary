#include "ViewRandomly.h"
#include "search.h"
int FindRandom(AVL &tree, bNode* &root)
{
	srand((int)time(0));
	int total = 0;
	tree.num_of_words(root, total);
<<<<<<< Updated upstream
	int number = 1 + rand() % (total + 1 - 1);
	wcout << number << endl;
=======
	int number = rand() % (total + 1);
>>>>>>> Stashed changes
	return 1 + (1 + (number * rand()) % (total + 1 - 1)) % (total + 1 - 1);
}
void ViewRandom(bNode* &root, int number, int &count, AVL &tree, string dir,bNode*&random)
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
		if (root->left && !random) ViewRandom(root->left, number, count, tree, dir,random);
		if (root->right && !random) ViewRandom(root->right, number, count, tree, dir,random);
	}
}