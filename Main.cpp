#include<iostream>
#include<iomanip>

#include"Main.h"
#include"Const.h"

using namespace std;

int main()
{
    int i;
    //load data

    do
    {
        system("clear");
        //starting screen

        //options
        cout << "OPTIONS:" << endl;
        cout << setw(tap) << "[0]" << " Exist"  << endl;
        cout << setw(tap) << "[1]" << " Search" << endl;
        //input
        cout << "Enter your choice: ";
        cin >> i;

        //processing
        switch(i)
        {
            case 0://exist
            break;

            case 1://search
            S_screen();
            break;

            default://invalid input
            cout << "Unknow command, please try again";
        }
    } while (i != 0);
    return 0;
}

void S_screen() //sreen drawing add searching
{

}