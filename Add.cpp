<<<<<<< Updated upstream
﻿#include "AVL.h"
#include<iostream>
using namespace std;
int AVL::Add(AVL& tree, wstring key, wstring def, string def_dir)
{
	if (tree.search(key)) return -1;
	ofstream fout(def_dir, ios_base::binary | ios_base::app | ios_base::ate);
	if (!fout.is_open()) return -2;
	int d = fout.tellp(), l = def.length() + 1;
=======
#include "AVL.h"
#include<iostream>
using namespace std;

int AVL::Add(AVL& tree, wstring key, wstring def, string def_dir)
{
	/*if (tree.search(key)) return -1;
	ofstream fout(def_dir, ios_base::binary | ios_base::app | ios_base::ate);
	if (!fout.is_open()) return -2;
	int d = fout.tellp(),l = def.length()+1;
	int numb = 0;
	fout.write((char*)&numb, sizeof(int));
>>>>>>> Stashed changes
	fout.write((char*)&l, sizeof(int));
	fout.write((char*)&def[0], l * sizeof(wchar_t));
	fout.close();
	tree.insert(key, d);
	wcout << d << endl;
<<<<<<< Updated upstream
	wcout << key << endl;
	wcout << def << endl;
	return d;
=======
	wcout << l << endl;
	wcout << key << endl;
	wcout << def << endl;
	return d;*/
>>>>>>> Stashed changes
}