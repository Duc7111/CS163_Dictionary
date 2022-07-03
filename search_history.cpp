#include "search_history.h"

void load_search_history(Node<string>*& search_history, string dir) 
{
	ifstream fin;
	fin.open(dir);
	string word;
	fin >> word;
	while (!fin.eof()) {
		search_history = new Node<string>(word, search_history);
		fin >> word;
	}
	fin.close();
}

Node<string>* add_search_history(Node<string>*& search_history, string word, string dir)
{
	search_history = new Node<string>(word, search_history);
	ofstream fout;
	fout.open(dir, ios::app);
	fout << word << endl;
	fout.close();
	return search_history;
}

void view_search_history(Node<string>* search_history) 
{
	while (search_history) {
		cout << search_history->data << endl;
		search_history = search_history->next;
	}
}

Node<string>* delete_search_history(Node<string>* search_history) {
	search_history->clear();
	search_history = nullptr;
	return search_history;
}