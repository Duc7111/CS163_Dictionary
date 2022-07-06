#include "AVL.h"
int AVL::Add(AVL& tree, wstring key ,wstring def, wstring dir)
{
	if(tree.search(key)) return -1;
	ofstream fout(dir, ios_base::binary | ios_base::app);
	if(!fout.is_open()) return -2;
	int d = fout.tellp(), l = def.length() + 1;
	fout.write((char*)&l, sizeof(int));
	fout.write((char*)&def[0], l*sizeof(wchar_t));
	fout.close();
	tree.insert(key, d);
	return d;

	/* if (tree.insert(str, k))
	{
		bNode* root = tree.search(str);
		ofstream FileOut;
		FileOut.open(dir, ios_base::binary | ios_base::app);
		FileOut.write((char*)&k, sizeof(int));
		FileOut.write((char*)&def, sizeof(char)*(def.length() + 1));
		FileOut.close();
		return root;
	} */
}