#pragma once
#include "FL.h"
#include "search.h"

bool load(AVL tree); // load data from file

char Init_screen(AVL& tree, FL& fl, int& size);

void S_screen(AVL&, FL&,string);

void F_screen(FL&);
