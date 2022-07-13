#pragma once
#include "FL.h"
#include "AVL.h"

bool load(AVL tree); // load data from file

int Init_screen(AVL&, FL&, string&, string&);

void S_screen(AVL&, FL&, string);

void F_screen(FL&, string def_dir);

void Quizz(AVL&, string);

void ViewRandomWord(AVL& tree, string def_dir);
