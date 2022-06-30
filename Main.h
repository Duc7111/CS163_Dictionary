#pragma once
#include "FL.h"
#include "AVL.h"

bool load(AVL tree); // load data from file

int Init_screen(AVL&, FL&, string&);

void S_screen(AVL&, FL&);

void F_screen(FL&);