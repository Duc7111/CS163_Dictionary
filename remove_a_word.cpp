
#include "remove_a_word.h"

bool remove_a_word(wstring word, AVL& tree) {
	return tree.remove(word);
}