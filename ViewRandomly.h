#pragma once
#include <cstdlib>
#include <ctime>
#include "AVL.h"

int FindRandom(AVL& tree, bNode*& root);

bNode* ViewRandom(bNode*& root, int number, int count, AVL& tree, string dir);
