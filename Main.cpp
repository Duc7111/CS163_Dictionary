#include<iostream>
#include<iomanip>

#include"Main.h"
#include"Const.h"

using namespace std;

int main()
{
    int i = 1;
    AVL tree;
    FL fl(0);
    do
    {
        system("clear");
        //choose language
        if(i == 1) 
        {
            switch(Init_screen(tree, fl))
            {
            case 'E':
                return 0;

            case '0':
                cout << "File load succesfully" << endl;
                system("pause");
                break;
            default:
                cout << "Error! the program will auto quit, please try again" << endl;
                system("pause");
                return -1;
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
            S_screen();
            break;

        case 3://favorite word
            F_screen(fl);

        default://invalid input
            cout << "Unknow command, please try again";
        }
    } while (i != 0);
    return 0;
}

char Init_screen(AVL& tree, FL& fl)
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
        cout << "Enter your choise: ";
        cin >> i;
        switch (i)
        {
        case 0:
            return 'E';
            break;

        case 1://init e-v
            break;

        case 2:
            break;

        case 3:
            break;

        default:
            cout << "Invaid input, please try again << endl";
            system("pause");
            break;
        }
    } while (i > 3 || i < 0);
    return '0';
}

void S_screen() //sreen drawing add searching
{

}


void F_screen(FL& fl)
{
    int t;
    do
    {
        system("clear");
        cout << "Favorite words: " << endl;
        int i = -1;
        while(fl[++i]->d > -1)
        cout << setw(tap) << '[' << i + 1 << ']' << fl[i]->key << endl;
        if(i == 0)
        {
            cout << "No word added to this list" << endl;
            system("pause");
            return;
        }
        cout << "Enter an index (0 to quit): ";
        cin >> t;
        if(t > i) 
        {
            cout << "Invalid input, please try again!" << endl;
            system("pause");
        }
        //show def and modifing stuff
    } while (t != 0);
    
}