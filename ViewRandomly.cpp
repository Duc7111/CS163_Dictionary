#include "ViewRandomly.h"
#include "search.h"
int FindRandom(AVL tree,bNode*root)
{
	srand(time(NULL));
	int total;;
	tree.total_word1(root, total);
	int number = rand()%total+1;
	return number;
}
string ViewRandom(bNode *root,int number,int count,AVL tree,string dir)
{
	if (root)
	{
		if (number == count)
		{
			 return search_for_def(tree, root->key, dir);
		}
		if (root->left) return ViewRandom(root, number, count + 1, tree, dir);
		if (root->right) return ViewRandom(root, number, count + 1, tree, dir);
	}
}