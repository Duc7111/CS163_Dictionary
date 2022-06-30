#include "ViewRandomly.h"
#include "search.h"
int FindRandom(AVL tree,bNode*root)
{
	srand(time(NULL));
	int total;;
	tree.num_of_words(root, total);
	int number = rand()%total+1;
	return number;
}
string ViewRandom(bNode *root,int number,int count,AVL tree,string dir)
{
	if (root)
	{
		if (number == count)
		{
			string str;
			ifstream fin(dir, ios::binary);
			fin.seekg(root->d, ios::cur);
			fin.read((char*)&str, 500);
			return str;
		}
		if (root->left) return ViewRandom(root, number, count + 1, tree, dir);
		if (root->right) return ViewRandom(root, number, count + 1, tree, dir);
	}
}