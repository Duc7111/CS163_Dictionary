#include "search_history.h"

Node<wstring>* search_history::Load(string hist_dir)
{
	wifstream fin;
	fin.open(hist_dir);
	wstring word;
	fin >> word;
	while (!fin.eof()) {
		hist_head = new Node<wstring>(word, hist_head);
		fin >> word;
	}
	fin.close();
	return hist_head;
}

Node<wstring>* search_history::Add(wstring word, string hist_dir)
{
	hist_head = new Node<wstring>(word, hist_head);
	wofstream fout;
	fout.open(hist_dir, ios::app);
	fout << word << endl;
	fout.close();
	return hist_head;
}

void search_history::View()
{
	Node<wstring>* temp = hist_head;
	while (temp) {
		wcout << temp->data << endl;
		temp = temp->next;
	}
}

Node<wstring>* search_history::Delete() {
	hist_head->clear();
	hist_head = nullptr;
	return hist_head;
}