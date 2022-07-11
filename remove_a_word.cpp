
#include "remove_a_word.h"

//bool remove_def_from_file(int d, wstring word_dir) {
//	
//}

bool remove_a_word(wstring word, AVL& tree, string def_dir) {
	int d = tree.search(word)->d;
	wstring word_dir =	wstring(def_dir.begin(), def_dir.end()) + (wchar_t)towupper(word[0]) + L".bin";

	return tree.remove(word);
}