#include "AVL.h"
bNode* AVL::Add(AVL tree,string str, int k,string dir,string def)
{
	bNode* searchh = tree.search(str);
	if (!search)
	{
		bNode* root = tree.insert(str, k);
		ofstream FileOut;
		FileOut.open(dir, ios_base::binary | ios_base::app);
		FileOut.write((char*)&k, sizeof(int));
		FileOut.write((char*)&def, sizeof(char) * def.length());
		FileOut.close();
		return root;
	}
}