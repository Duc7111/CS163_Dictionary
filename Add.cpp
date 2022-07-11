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
}