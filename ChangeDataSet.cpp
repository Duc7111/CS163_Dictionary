#include "ChangeDataSet.h"

void ChangeDataSet(string& dir)
{
	int choice;
	cout << "Choose the translatation mode" << endl;
	cout << "1.English - Vietnamese" << endl;
	cout << "2.Vietnamese - English" << endl;
	cout << "Please input your choice = "; cin >> choice;
	if (choice == 1)
	{
		dir = "database/eng_viet/";// + Cong duong dan toi file txt ;
	}
	else if (choice == 2)
	{
		dir = "database/viet_eng/";//; + Cong duong dan toi file txt ;
	}
	else return;
}