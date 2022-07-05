#include<iostream>
#include<iomanip>

#include"Main.h"
#include"AVL.h"
#include"Const.h"
#include"search.h"

using namespace std;

int main()
{
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
                cout << "Error! the program will auto quit, please try again" << endl;
                system("pause");
                return -1;
            default:
                cout << "File load succesfully" << endl;
                system("pause");
                break;
            }
        }

        //starting screen
        system("cls");

        //options
        cout << "OPTIONS:" << endl;
        cout << setw(tap) << "[0]" << " Exist" << endl;
        cout << setw(tap) << "[1]" << " Change language" << endl;
        cout << setw(tap) << "[2]" << " Search" << endl;
        cout << setw(tap) << "[3]" << " View favorites" << endl;
        cout << setw(tap) << "[4]" << " Quizzes" << endl;
        //input
        cout << "Enter your choice: ";
        cin >> i;

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
            F_screen(fl);
            break;
        
        case 4:
            Quizz(tree, def_dir);
            break;
        default://invalid input
            cout << "Unknow command, please try again";
            break;
        }
    } while (i != 0);
    return 0;
}

int Init_screen(AVL& tree, FL& fl, string& def_dir, string& struct_dir)
{
    int i;
    do
    {
        system("cls");
        cout << "Choose language:" << endl;
        cout << setw(tap) << "[0]" << " Exist" << endl; 
        cout << setw(tap) << "[1]" << " ENG - VI" << endl; 
        cout << setw(tap) << "[2]" << " VI - ENG" << endl; 
        cout << setw(tap) << "[3]" << " ENG - ENG" << endl;
        cout << setw(tap) << "[4]" << " slang" << endl;
        cout << setw(tap) << "[5]" << " emotional" << endl;
        cout << "Enter your choice: ";
        cin >> i;
        switch(i)
        {
        case 0:
            return -1;
            break;

        case 1://init e-v

            break;

        case 2://int v-e

            break;

        case 3://init e-e
        {
            def_dir = "database\\eng-eng\\def.bin";
            struct_dir = "database\\eng-eng\\struct.bin";
            ifstream fin(def_dir);
            if(fin.good()) 
            {
                fin.close();
                fin.open(struct_dir, ios_base::binary);
                return tree.load(fin, fl);
            }
            fin.close();
            return tree.maketree("database\\eng-eng\\1English definitions.txt", def_dir, struct_dir);
        }
            break;

        case 4://init slang

            break;

        case 5://init emotional

            break;

        default:
            cout << "Invaid input, please try again" << endl;
            system("pause");
            break;
        }
    } while (i > 3 || i < 0);
    return '0';
}

void S_screen(AVL& tree, FL& fl,string dir) //sreen drawing add searching
{
    vector <string> strs;
    string k;
    int i = 1;
    do
    {
        //searching
        cout << "Enter a word (0 to quit): ";
        cin.clear();
        cin.ignore();
        getline(cin, k);
        if(k == "0") return;
        bNode* temp = tree.search(k);
        cout << k << endl;
        if(!temp)
        {
            cout << "No result" << endl;
            system("pause");
            continue;
        }
        //cout definition (done)
        strs = search_for_def(temp,dir);
        cout << k << ':' << endl;
        for (int j = 0 ; j<strs.size() - 1 ; j++)
        {
            cout << setw(tap) << j+1 << ". " << strs[j] << endl;
        }
        //def

        //options
        cout << "----------------------------------------------------" << endl;
        cout << "your options: " << endl;
        do
        {
            cout << setw(tap) << "[0]" << " Back to searching" << endl;
            cout << setw(tap) << "[1]";
            if(temp->f) cout << " Unlike" << endl;
            else cout << " Like" << endl;
            cout << setw(tap) << "[2]" << " Modify" << endl;
            cout << "Enter your choice: ";
            cin >> i;
            cout << "----------------------------------------------------" << endl;
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
                cout << "Invalid input, please try again" << endl;
                system("pause");
                break;
            }
        } while (i != 0);
    }while(k != "0");
}


void F_screen(FL& fl)
{
    int t;
    do
    {
        system("cls");
        cout << "Favorite words: " << endl;
        int size = fl.size();
        if(size == 0)
        {
            cout << "No word added to this list" << endl;
            system("pause");
            return;
        }
        for(int i = 0; i < size; ++i)
            cout << setw(tap - 2) << '[' << i + 1 << ']' << fl[i]->key << endl;
        cout << "Enter an index (0 to quit): ";
        cin >> t;
        if(t < 0 || t > size)
        {
            cout << "Invalid input, please try again!" << endl;
            system("pause");
        }
        //show def and modifying stuff
        //def
        system("cls");
        cout << fl[t] << ':' << endl;

        //modifying
        int i;
        do
        {
            cout << setw(tap) << "[0]" << " Back to favorite list" << endl;
            cout << setw(tap) << "[1]" << " Remove this from favorite list" << endl;
            cout << "Enter your choise: ";
            cin >> i;
            switch (i)
            {
            case 0:
                break;

            case 1:
                fl.remove(t);
                break;
            
            default:
                cout << "Invalid input, please try again" << endl;
                system("pause");
                break;
            }
        } while (i != 0);
    } while (t != 0);   
}

void Quizz (AVL& tree, string dir)
{
    vector<vector<string>> random_words;
    int num = 0;
    tree.num_of_words(tree.get_root(), num);
    int option;
    cout << "Game options: " << endl;
    do
    {
        cout << setw(tap) << "[0]" << " Exit quizz mode." << endl;
        cout << setw(tap) << "[1]" << " Guess the definition of a given keyword." << endl;
        cout << setw(tap) << "[2]" << " Guess the keyword of a given definition." << endl;
        do
        {
            cout << "your choice: ";
            cin >> option;
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
                    cout << "Try again?" << endl;
                    cout << setw(tap) << "[1]" << " Yes." << endl;
                    cout << setw(tap) << "[2]" << " Back to game's menu." << endl;
                    do
                    {
                        cout << "your choice: ";
                        cin >> option;
                    }while (option != 1 && option != 2);
                }while (option == 1);
                break;
            case 2:
                do
                {
                    random_words.clear();
                    random_words = random_word(tree, dir, num);
                    random_def_game(random_words);
                    cout << "Try again?" << endl;
                    cout << setw(tap) << "[1]" << " Yes." << endl;
                    cout << setw(tap) << "[2]" << " Back to game's menu." << endl;
                    do
                    {
                        cout << "your choice: ";
                        cin >> option;
                    }while (option != 1 && option != 2);
                }while (option == 1);
                break;
            default:
                cout << "Invalid input, please try again" << endl;
                system("pause");
                break;
        }
    }while (1);
}
