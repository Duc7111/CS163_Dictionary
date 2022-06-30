#include<iostream>
#include<iomanip>

#include"Main.h"
#include"AVL.h"
#include"Const.h"

using namespace std;

int main()
{
    int i = 1, size;
    AVL tree;
    FL fl(0);
    string dir;
    do
    {
        system("clear");
        //choose language
        if(i == 1) 
        {
            switch(Init_screen(tree, fl, dir))
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
        system("clear");

        //options
        cout << "OPTIONS:" << endl;
        cout << setw(tap) << "[0]" << " Exist" << endl;
        cout << setw(tap) << "[1]" << " Change language" << endl;
        cout << setw(tap) << "[2]" << " Search" << endl;
        cout << setw(tap) << "[3]" << " View favorites" << endl;
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
            S_screen(tree, fl);
            break;

        case 3://favorite word
            F_screen(fl);

        default://invalid input
            cout << "Unknow command, please try again";
        }
    } while (i != 0);



    return 0;
}

int Init_screen(AVL& tree, FL& fl, string& dir)
{
    int i;
    do
    {
        system("clear");
        cout << "Choose language:" << endl;
        cout << setw(tap) << "[0]" << " Exist" << endl; 
        cout << setw(tap) << "[1]" << " ENG - VI" << endl; 
        cout << setw(tap) << "[2]" << " VI - ENG" << endl; 
        cout << setw(tap) << "[3]" << " ENG - ENG" << endl;
        cout << setw(tap) << "[4]" << " slang" << endl;
        cout << setw(tap) << "[5]" << " emotional" << endl;
        cout << "Enter your choise: ";
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
            dir = "database\\eng-eng\\def.bin";
            ifstream fin("dir");
            if(fin.good()) 
                return tree.load(fin, fl);
            return tree.maketree("database\\eng-eng\\1English definition.txt", dir);
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

void S_screen(AVL& tree, FL& fl) //sreen drawing add searching
{
    string k;
    int i = 1;
    do
    {
        //searching
        system("clear");
        cout << "Enter a word (0 to quit): ";
        cin.ignore(1000);
        getline(cin, k);
        bNode* temp = tree.search(k);
        if(temp)
        {
            cout << "No result" << endl;
            system("pause");
            continue;
        }
        //cout definition (undone)
        system("clear");
        cout << k << ':' << endl;
        //def

        //options
        do
        {
            cout << setw(tap) << "[0]" << " Back to searching" << endl;
            cout << setw(tap) << "[1]";
            if(temp->f) cout << " Like" << endl;
            else cout << " Unlike" << endl;
            cout << setw(tap) << "[2]" << " Modify" << endl;
            cout << "Enter your choise";
            cin >> i;
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
        system("clear");
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
        system("clear");
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