#pragma once

#include<iostream>
#include<iomanip>
#include<io.h>
#include<fcntl.h>
#include<string>
#include<codecvt>

#include"AVL.h"
#include "FL.h"
#include"Const.h"
#include"search.h"
#include"ViewRandomly.h"
#include "RemoveFile.h"
#include "remove_a_word.h"

bool load(AVL tree); // load data from file

int Init_screen(AVL&, FL&, string&, string&);

void S_screen(AVL&, FL&, string);

void F_screen(FL&, string def_dir);

void Quizz(AVL&, string);

void Add(AVL& tree, string& def_dir);

void ViewRandomWord(AVL& tree, string def_dir);

void Switch_data_set(string& struct_dir, string& def_dir);

void ResetToOriginal(AVL& tree, string& struct_dir, string& def_dir);