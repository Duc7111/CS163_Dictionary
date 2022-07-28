
#include "Main.h"

using namespace std;

int main()
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    string def_dir; // bin file that save the tree (based on mode of dictionary)
    string struct_dir; // bin file that save the tree (based on mode of dictionary)
    string hash_dir;
    c_hash key_hash;
    int i = 1, size;
    AVL tree;
    FL fl(0);
    do
    {
        system("cls");
        //choose language
        if (i == 1)
        {
            switch (size = Init_screen(tree, fl, key_hash, def_dir, struct_dir, hash_dir))
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

        wcout << setw(tap) << L"[3]" << L" View search history" << endl;
        wcout << setw(tap) << L"[4]" << L" Delete search history" << endl;

        wcout << setw(tap) << L"[5]" << L" View favorites" << endl;
        wcout << setw(tap) << L"[6]" << L" Quizzes" << endl;
        wcout << setw(tap) << L"[7]" << L" Add a new word" << endl;

        wcout << setw(tap) << L"[8]" << L" Edit a word's definition" << endl;
        wcout << setw(tap) << L"[9]" << L" Remove a word" << endl;

        wcout << setw(tap) << L"[10]" << L" View random word and its definition" << endl;
        wcout << setw(tap) << L"[11]" << L" Switch data set" << endl;
        wcout << setw(tap) << L"[12]" << L" Reset dictionary to its original state" << endl;
        //input
        wcout << L"Enter your choice: ";
        wcin >> i;
        wcin.ignore(1000, L'\n');
        search_history Search_History;

        //processing
        switch (i)
        {
        case 0://exist
            return 0;

        case 1://setting

        case 2://change
            S_screen(tree, fl, key_hash, Search_History, def_dir);
            break;

        case 3: //view search history
            ViewSearchHistory(Search_History);
            break;

        case 4: //delete search history
            DeleteSearchHistory(Search_History);
            break;

        case 5://favorite word
            F_screen(fl, def_dir);
            break;

        case 6:
            Quizz(tree, def_dir);
            break;
        case 7:
            Add(tree, def_dir);
            break;

        case 8: //edit a word definition

        case 9: //remove a word

        case 10:
            ViewRandomWord(tree, def_dir);
            break;

        case 11:
            Switch_data_set(struct_dir, def_dir);
            break;

        case 12:
            ResetToOriginal(tree, struct_dir, def_dir, hash_dir, key_hash);
            break;

        default://invalid input
            wcout << L"Unknow command, please try again";
            break;
        }
    } while (i != 0);
    return 0;
}

void DeleteSearchHistory(search_history& Search_History) {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    Search_History.Delete();
    wcout << setw(tap) << L"--------------------------------" << endl;
    wcout << setw(tap) << "History deleted!" << endl;
    wcout << setw(tap) << L"--------------------------------" << endl;
    system("pause");
}

void ViewSearchHistory(search_history& Search_History) {
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    Search_History.Load();
    wcout << setw(tap) << L"-------Your search history------" << endl;
    Search_History.View();
    wcout << setw(tap) << L"--------------------------------" << endl;
    system("pause");
}


int Init_screen(AVL& tree, FL& fl, c_hash& key_hash, string& def_dir, string& struct_dir, string& hash_dir)
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
        switch (i)
        {
        case 0:
            return -1;
            break;

        case 1://init e-v
        {
            def_dir = "database\\eng-vie\\def.bin";
            struct_dir = "database\\eng-vie\\struct.bin";
            ifstream fin(struct_dir, ios_base::binary);
            if (fin.good())
            {
                int size = tree.load(fin, fl);
                fin.open(hash_dir, ios_base::binary);
                key_hash.load(fin);
                fin.close();
                return size;
            }
            fin.close();
            return tree.maketree("database\\eng-vie\\2English-Vietnamese.txt", def_dir, struct_dir, hash_dir, key_hash);
        }
        break;

        case 2://int v-e
        {
            def_dir = "database\\vie-eng\\def.bin";
            struct_dir = "database\\vie-eng\\struct.bin";
            ifstream fin(struct_dir, ios_base::binary);
            if (fin.good())
            {
                int size = tree.load(fin, fl);
                fin.open(hash_dir, ios_base::binary);
                key_hash.load(fin);
                fin.close();
                return size;
            }
            fin.close();
            return tree.maketree("database\\vie-eng\\3Vietnamese-English.txt", def_dir, struct_dir, hash_dir, key_hash);
        }
        break;

        case 3://init e-e
        {
            def_dir = "database\\eng-eng\\def.bin";
            struct_dir = "database\\eng-eng\\struct.bin";
            ifstream fin(struct_dir, ios_base::binary);
            if (fin.good())
            {
                int size = tree.load(fin, fl);
                fin.open(hash_dir, ios_base::binary);
                key_hash.load(fin);
                fin.close();
                return size;
            }
            fin.close();
            return tree.maketree("database\\eng-eng\\1English definitions.txt", def_dir, struct_dir, hash_dir, key_hash);
        }
        break;

        case 4://init slang
        {
            def_dir = "database\\slang\\def.bin";
            struct_dir = "database\\slang\\struct.bin";
            hash_dir = "database\\slang\\hash.bin";
            ifstream fin(struct_dir, ios_base::binary);
            if (fin.good())
            {
                int size = tree.load(fin, fl);
                fin.open(hash_dir, ios_base::binary);
                key_hash.load(fin);
                fin.close();
                return size;
            }
            fin.close();
            return tree.maketree("database\\slang\\slang.txt", def_dir, struct_dir, hash_dir, key_hash);
        }
            break;

        case 5://init emotional
        {
            def_dir = "database\\emotional\\def.bin";
            struct_dir = "database\\emotional\\struct.bin";
            hash_dir = "database\\emotional\\hash.bin";
            ifstream fin(struct_dir, ios_base::binary);
            if (fin.good())
            {
                int size = tree.load(fin, fl);
                fin.open(hash_dir, ios_base::binary);
                key_hash.load(fin);
                fin.close();
                return size;
            }
            fin.close();
            return tree.maketree("database\\emotional\\emotional.txt", def_dir, struct_dir, hash_dir, key_hash);
        }
            break;

        default:
            wcout << L"Invaid input, please try again" << endl;
            system("pause");
            break;
        }
    } while (i > 5 || i < 0);
    return 0;
}

void S_screen(AVL& tree, FL& fl, c_hash& key_hash, search_history& search_history, string dir) //sreen drawing add searching
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
        if (k == L"0") return;
        search_history.Add(k);
        bNode* temp = tree.search(k);
        if (!temp)
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
            for (int j = 0; j < strs.size() - 1; j++)
            {
                wcout << setw(tap) << j + 1 << L". " << strs[j] << endl;
            }
            wcout << L"----------------------------------------------------" << endl;
            wcout << L"your options: " << endl;
            wcout << setw(tap) << L"[0]" << L" Back to searching" << endl;
            wcout << setw(tap) << L"[1]";
            if (temp->f) wcout << L" Unlike" << endl;
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
                int order;
                wstring t;
                wcout << L"order of def: " << endl;
                cin >> order;
                wcout << L"edited def: " << endl;
                getline(wcin, t);
                edit_definition(temp, order, t, strs, dir);
                break;

            default:
                wcout << L"Invalid input, please try again" << endl;
                system("pause");
                break;
            }
        } while (i != 0);
    } while (k != L"0");
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
        if (size == 0)
        {
            wcout << L"No word added to this list" << endl;
            system("pause");
            return;
        }
        for (int i = 0; i < size; ++i)
            wcout << setw(tap - 2) << L'[' << i + 1 << L']' << fl[i]->key << endl;
        wcout << L"Enter an index (0 to quit): ";
        wcin >> t;
        wcin.ignore(1000, L'\n');
        if (t < 0 || t > size)
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
            for (int i = 0; i < temp.size(); ++i)
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

void Quizz(AVL& tree, string dir)
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
        } while (option != 2 && option != 1 && option != 0);
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
                } while (option != 1 && option != 2);
            } while (option == 1);
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
                } while (option != 1 && option != 2);
            } while (option == 1);
            break;
        default:
            wcout << L"Invalid input, please try again" << endl;
            system("pause");
            break;
        }
    } while (1);
}

void Add(AVL& tree, string& def_dir)
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    bool again = true;
    wstring key, def;
    while (again)
    {
        wcout << L"Please input word  that you want to add to dictionary = ";
        getline(wcin, key);
        wcout << L"Please input definition of word that you want to add to dictionary = ";
        getline(wcin, def);
        int i = tree.Add(tree, key, def, def_dir);
        switch (i)
        {
        case -1:
            wcout << L"The word has already existed" << endl;
            system("pause");
            break;
        case -2:
            wcout << L"Can not open the distionary that you want to add to" << endl;
            system("pause");
            break;
        default:
            wcout << L"Add succesfully" << endl;
            system("pause");
            break;
        }
        wcout << L"Do you want to add new word once more time ? " << endl;
        wcout << L"[0] : No" << endl;
        wcout << L"[1] : Yes" << endl;
        int choice;
        wcout << L"Please input your choice = ";
        wcin >> choice;
        if (choice == 0)
        {
            again = false;
        }
    }
}
void ViewRandomWord(AVL& tree, string def_dir)
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    bNode* root = tree.get_root();
    int serial = FindRandom(tree, root);
    int count = 0;
    bNode* random = nullptr;
    ViewRandom(root, serial, count, tree, def_dir, random);
    vector <wstring> strs;
    strs = search_for_def(random, def_dir);
    system("cls");
    wcout << random->key << ':' << endl;
    for (int j = 0; j < strs.size() - 1; j++)
    {
        wcout << setw(tap) << j + 1 << L". " << strs[j] << endl;
    }
    system("pause");
}

void Switch_data_set(string& struct_dir, string& def_dir)
{
    _setmode(_fileno(stdout), _O_U16TEXT);
    _setmode(_fileno(stdin), _O_U16TEXT);
    wcout << L"CHANGE DATA SET" << endl;
    if (def_dir == "database\\eng-vie\\def.bin")
    {
        int choice;
        wcout << L"[1].Change to vie-eng mode" << endl;
        wcout << L"[2].Change to eng-eng mode" << endl;
        wcout << L"[3].Change to slang mode" << endl;
        wcout << L"[4].Change to emotional mode" << endl;
        wcout << L"Please input your choice = "; wcin >> choice;
        switch (choice)
        {
        case 1:
            def_dir = "database\\vie-eng\\def.bin";
            struct_dir = "database\\vie-eng\\struct.bin";
            wcout << L"Change succesfully" << endl;
            break;
        case 2:
            def_dir = "database\\eng-eng\\def.bin";
            struct_dir = "database\\eng-eng\\struct.bin";
            wcout << L"Change succesfully" << endl;
            break;
            //case 3:
            //    def_dir = "";
            //    struct_dir = "";
            //    break;
            //case 4:
            //    def_dir = "";
            //    struct_dir = "";
            //    break;
        default:
            wcout << L"Goodbye" << endl;
            break;
        }
        system("pause");
    }
    else if (def_dir == "database\\vie-eng\\def.bin")
    {
        int choice;
        wcout << L"[1].Change to eng-vie mode" << endl;
        wcout << L"[2].Change to eng-eng mode" << endl;
        wcout << L"[3].Change to slang mode" << endl;
        wcout << L"[4].Change to emotional mode" << endl;
        wcout << L"Please input your choice = "; wcin >> choice;
        switch (choice)
        {
        case 1:
            def_dir = "database\\eng-vie\\def.bin";
            struct_dir = "database\\eng-vie\\struct.bin";
            wcout << L"Change succesfully" << endl;
            break;
        case 2:
            def_dir = "database\\eng-eng\\def.bin";
            struct_dir = "database\\eng-eng\\struct.bin";
            wcout << L"Change succesfully" << endl;
            break;
        default:
            wcout << L"Goodbye" << endl;
            break;
        }
        system("pause");
    }
    else if (def_dir == "database\\eng-eng\\def.bin")
    {
        int choice;
        wcout << L"[1].Change to vie-eng mode" << endl;
        wcout << L"[2].Change to eng-vie mode" << endl;
        wcout << L"[3].Change to slang mode" << endl;
        wcout << L"[4].Change to emotional mode" << endl;
        wcout << L"Please input your choice = "; wcin >> choice;
        switch (choice)
        {
        case 1:
            def_dir = "database\\vie-eng\\def.bin";
            struct_dir = "database\\vie-eng\\struct.bin";
            wcout << L"Change succesfully" << endl;
            break;
        case 2:
            def_dir = "database\\eng-vie\\def.bin";
            struct_dir = "database\\eng-vie\\struct.bin";
            wcout << L"Change succesfully" << endl;
            break;
            //case 3:
            //    def_dir = "";
            //    struct_dir = "";
            //    break;
            //case 4:
            //    def_dir = "";
            //    struct_dir = "";
            //    break;
        default:
            wcout << L"Goodbye" << endl;
            break;
        }
        system("pause");
    }
    else if (def_dir == "database\\slang\\def.bin")
    {
        int choice;
        wcout << L"[1].Change to vie-eng mode" << endl;
        wcout << L"[2].Change to eng-vie mode" << endl;
        wcout << L"[3].Change to eng-eng mode" << endl;
        wcout << L"[4].Change to emotional mode" << endl;
        wcout << L"Please input your choice = "; wcin >> choice;
        switch (choice)
        {
        case 1:
            def_dir = "database\\vie-eng\\def.bin";
            struct_dir = "database\\vie-eng\\struct.bin";
            wcout << L"Change succesfully" << endl;
            break;
        case 2:
            def_dir = "database\\eng-vie\\def.bin";
            struct_dir = "database\\eng-vie\\struct.bin";
            wcout << L"Change succesfully" << endl;
            break;
        case 3:
            def_dir = "database\\eng-eng\\def.bin";
            struct_dir = "database\\eng-eng\\struct.bin";
            wcout << L"Change succesfully" << endl;
            break;
            //case 4:
            //    def_dir = "";
            //    struct_dir = "";
            //    break;
        default:
            wcout << L"Goodbye" << endl;
            break;
        }
        system("pause");
    }
    else
    {
        int choice;
        wcout << L"[1].Change to vie-eng mode" << endl;
        wcout << L"[2].Change to eng-vie mode" << endl;
        wcout << L"[3].Change to eng-eng mode" << endl;
        wcout << L"[4].Change to slang mode" << endl;
        wcout << L"Please input your choice = "; wcin >> choice;
        switch (choice)
        {
        case 1:
            def_dir = "database\\vie-eng\\def.bin";
            struct_dir = "database\\vie-eng\\struct.bin";
            wcout << L"Change succesfully" << endl;
            break;
        case 2:
            def_dir = "database\\eng-vie\\def.bin";
            struct_dir = "database\\eng-vie\\struct.bin";
            wcout << L"Change succesfully" << endl;
            break;
        case 3:
            def_dir = "database\\eng-eng\\def.bin";
            struct_dir = "database\\eng-eng\\struct.bin";
            wcout << L"Change succesfully" << endl;
            break;
            //case 4:
            //    def_dir = "";
            //    struct_dir = "";
            //    break;
        default:
            wcout << L"Goodbye" << endl;
            break;
        }
        system("pause");
    }
}
void ResetToOriginal(AVL& tree, string& struct_dir, string& def_dir, string& hash_dir, c_hash& key_hash)
{
    bool Check = DeleteFile(struct_dir);
    bool Check1 = DeleteFile(def_dir);
    int size = tree.maketree("database\\eng-eng\\1English definitions.txt", def_dir, struct_dir, hash_dir, key_hash);
    if (size == 1 && Check && Check1) wcout << L"Reset the dictionary to its original state successfully" << endl;
    else wcout << L"Not successfully" << endl;
    system("pause");

    //if (Check && Check1) wcout << L"Reset the dictionary to its original state successfully" << endl;
    //else wcout << L"Delete not successfully" << endl;
    //system("pause");
}
