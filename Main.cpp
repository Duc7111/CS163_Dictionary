#include<iostream>
#include<iomanip>
#include<io.h>
#include<fcntl.h>
#include<string>
#include<codecvt>

#include"Main.h"
#include"AVL.h"
#include"Const.h"
#include"search.h"

using namespace std;

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    string def_dir; // bin file that save the tree (based on mode of dictionary)
    string struct_dir; // bin file that save the tree (based on mode of dictionary)
    int i = 1, size;
    AVL tree;
    FL fl(0);
    do
    {
        system("cls");
        //choose language
        if(i == 1) 
        {
            switch(size = Init_screen(tree, fl, def_dir, struct_dir))
            {
            case -1:
                return 0;

            case 0:
                wcout << L"Error! the program will auto quit, please try again" << endl;
                system("pause");
                return -1;
            default:
                wcout << L"File load succesfully" << endl;
                system("pause");
                break;
            }
        }

        //starting screen
        system("cls");

        //options
        wcout << L"OPTIONS:" << endl;
        wcout << setw(tap) << L"[0]" << L" Exist" << endl;
        wcout << setw(tap) << L"[1]" << L" Change language" << endl;
        wcout << setw(tap) << L"[2]" << L" Search" << endl;
        wcout << setw(tap) << L"[3]" << L" View favorites" << endl;
        wcout << setw(tap) << L"[4]" << L" Quizzes" << endl;
        //input
        wcout << L"Enter your choice: ";
        wcin >> i;
        wcin.ignore(1000, L'\n');

        //processing
        switch(i)
        {
        case 0://exist
            return 0;

        case 1://setting

        case 2://change
            S_screen(tree, fl, def_dir);
            break;

        case 3://favorite word
            F_screen(fl, def_dir);
            break;
        
        case 4:
            Quizz(tree, def_dir);
            break;
        default://invalid input
            wcout << L"Unknow command, please try again";
            break;
        }
    } while (i != 0);
    return 0;
}

int Init_screen(AVL& tree, FL& fl, string& def_dir, string& struct_dir)
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    int i;
    do
    {
        system("cls");
        wcout << L"Choose language:" << endl;
        wcout << setw(tap) << L"[0]" << L" Exist" << endl; 
        wcout << setw(tap) << L"[1]" << L" ENG - VI" << endl; 
        wcout << setw(tap) << L"[2]" << L" VI - ENG" << endl; 
        wcout << setw(tap) << L"[3]" << L" ENG - ENG" << endl;
        wcout << setw(tap) << L"[4]" << L" slang" << endl;
        wcout << setw(tap) << L"[5]" << L" emotional" << endl;
        wcout << L"Enter your choice: ";
        wcin >> i;
        wcin.ignore(1000, L'\n');
        switch(i)
        {
        case 0:
            return -1;
            break;

        case 1://init e-v
        {
            def_dir = "database\\eng-vie\\def.bin";
            struct_dir = "database\\eng-vie\\struct.bin";
            ifstream fin(struct_dir, ios_base::binary);
            if(fin.good()) return tree.load(fin, fl);
            fin.close();
            return tree.maketree("database\\eng-vie\\2English-Vietnamese.txt", def_dir, struct_dir);
        }        
            break;

        case 2://int v-e
        {
            def_dir = "database\\vie-eng\\def.bin";
            struct_dir = "database\\vie-eng\\struct.bin";
            ifstream fin(struct_dir, ios_base::binary);
            if(fin.good()) return tree.load(fin, fl);
            fin.close();
            return tree.maketree("database\\vie-eng\\3Vietnamese-English.txt", def_dir, struct_dir);
        }        
            break;

        case 3://init e-e
        {
            def_dir = "database\\eng-eng\\def.bin";
            struct_dir = "database\\eng-eng\\struct.bin";
            ifstream fin(struct_dir, ios_base::binary);
            if(fin.good()) return tree.load(fin, fl);
            fin.close();
            return tree.maketree("database\\eng-eng\\1English definitions.txt", def_dir, struct_dir);
        }
            break;

        case 4://init slang

            break;

        case 5://init emotional

            break;

        default:
            wcout << L"Invaid input, please try again" << endl;
            system("pause");
            break;
        }
    } while (i > 5 || i < 0);
    return 0;
}

void S_screen(AVL& tree, FL& fl, string dir) //sreen drawing add searching
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    vector <wstring> strs;
    wstring k;
    int i = 1;
    do
    {
        system("cls");
        //searching
        wcout << L"Enter a word (0 to quit): ";
        getline(wcin, k);
        if(k == L"0") return;
        bNode* temp = tree.search(k);
        if(!temp)
        {
            wcout << L"No result" << endl;
            system("pause");
            continue;
        }
        //search definition (done)
        strs = search_for_def(temp, dir);

        //options
        do
        {
            system("cls");
            wcout << k << ':' << endl;
            for (int j = 0 ; j<strs.size() - 1 ; j++)
            {
                wcout << setw(tap) << j+1 << L". " << strs[j] << endl;
            }
            wcout << L"----------------------------------------------------" << endl;
            wcout << L"your options: " << endl;
            wcout << setw(tap) << L"[0]" << L" Back to searching" << endl;
            wcout << setw(tap) << L"[1]";
            if(temp->f) wcout << L" Unlike" << endl;
            else wcout << L" Like" << endl;
            wcout << setw(tap) << L"[2]" << L" Modify" << endl;
            wcout << L"Enter your choice: ";
            wcin >> i;
            wcin.ignore(1000, '\n');
            wcout << L"----------------------------------------------------" << endl;
            switch (i)
            {
            case 0:
                break;

            case 1:
                temp->f = !temp->f;
                fl.AoR(temp);
                break;

            case 2://modifying functions

                break;
                
            default:
                wcout << L"Invalid input, please try again" << endl;
                system("pause");
                break;
            }
        } while (i != 0);
    }while(k != L"0");
}


void F_screen(FL& fl, string def_dir)
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    int t;
    do
    {
        system("cls");
        wcout << L"Favorite words: " << endl;
        int size = fl.size();
        if(size == 0)
        {
            wcout << L"No word added to this list" << endl;
            system("pause");
            return;
        }
        for(int i = 0; i < size; ++i)
            wcout << setw(tap - 2) << L'[' << i + 1 << L']' << fl[i]->key << endl;
        wcout << L"Enter an index (0 to quit): ";
        wcin >> t;
        wcin.ignore(1000, L'\n');
        if(t < 0 || t > size)
        {
            wcout << L"Invalid input, please try again!" << endl;
            system("pause");
        }
        //show def and modifying stuff
        int i;
        do
        {
            system("cls");
            wcout << fl[t]->key << L':' << endl;
            vector<wstring> temp = search_for_def(fl[t], def_dir);
            for(int i = 0; i < temp.size(); ++i)
            {
                wcout << setw(tap) << i + 1 << L". " << temp[i] << endl;
            }
            wcout << setw(tap) << L"[0]" << L" Back to favorite list" << endl;
            wcout << setw(tap) << L"[1]" << L" Remove this from favorite list" << endl;
            wcout << L"Enter your choise: ";
            wcin >> i;
            wcin.ignore(1000, L'\n');
            switch (i)
            {
            case 0:
                break;

            case 1:
                fl.remove(t);
                break;
            
            default:
                wcout << L"Invalid input, please try again" << endl;
                system("pause");
                break;
            }
        } while (i != 0);
    } while (t != 0);   
}

void Quizz (AVL& tree, string dir)
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    vector<vector<wstring>> random_words;
    int num = 0;
    tree.num_of_words(tree.get_root(), num);
    int option;
    wcout << L"Game options: " << endl;
    do
    {
        wcout << setw(tap) << L"[0]" << L" Exit quizz mode." << endl;
        wcout << setw(tap) << L"[1]" << L" Guess the definition of a given keyword." << endl;
        wcout << setw(tap) << L"[2]" << L" Guess the keyword of a given definition." << endl;
        do
        {
            wcout << L"your choice: ";
            wcin >> option;
            wcin.ignore(1000, '\n');
        }while (option != 2 && option != 1 && option != 0);
        if (option == 0)
            return;
        switch (option)
        {
            case 1:
                do
                {
                    random_words.clear();
                    random_words = random_word(tree, dir, num);
                    random_game(random_words);
                    wcout << L"Try again?" << endl;
                    wcout << setw(tap) << L"[1]" << L" Yes." << endl;
                    wcout << setw(tap) << L"[2]" << L" Back to game's menu." << endl;
                    do
                    {
                        wcout << "your choice: ";
                        wcin >> option;
                        wcin.ignore(1000, L'\n');
                    }while (option != 1 && option != 2);
                }while (option == 1);
                break;
            case 2:
                do
                {
                    random_words.clear();
                    random_words = random_word(tree, dir, num);
                    random_def_game(random_words);
                    wcout << L"Try again?" << endl;
                    wcout << setw(tap) << L"[1]" << L" Yes." << endl;
                    wcout << setw(tap) << L"[2]" << L" Back to game's menu." << endl;
                    do
                    {
                        wcout << L"your choice: ";
                        wcin >> option;
                        wcin.ignore(1000, L'\n');
                    }while (option != 1 && option != 2);
                }while (option == 1);
                break;
            default:
                wcout << L"Invalid input, please try again" << endl;
                system("pause");
                break;
        }
    }while (1);
}
void Add(AVL& tree, wstring dir)
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    wstring key, def;
    wcout << L"Please input word  that you want to add to dictionary = ";
    getline(wcin, key);
    wcout << L"Please input definition of word that you want to add to dictionary = ";
    getline(wcin, def);
    int i = tree.Add(tree, key, def, dir);
    switch (i)
    {
    case -1:
        wcout << L"The word has already existed" << endl;
        break;
    case -2:
        wcout << L"Can not open the distionary that you want to add to" << endl;
        break;
    default:
        wcout << L"Add succesfully" << endl;
        break;
    }
}