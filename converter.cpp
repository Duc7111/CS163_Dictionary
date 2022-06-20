#include "converter.h"
void convert_txt (string dir)
{
    string tmp1,tmp2;
    bool isfist = false,iskey = false;
    ofstream fout;
    ifstream fin;
    fin.open (dir);
    fout.open ("output.txt");
    while (fin.eof() == false)
    {
        tmp2.clear();
        isfist = false;
        iskey = false;
        getline(fin,tmp1);
        if (!tmp1.empty())
        {
            for (int i = 0 ; i < tmp1.length() ; i++)
            {
                if (tmp1[i] == '(' && isfist == false)
                {
                    while (tmp1 [i] != ')')
                    {
                        i++;
                    }
                    i += 2;
                    isfist = true;
                }
                tmp2.push_back(tmp1[i]);
                if (tmp1[i+1] == ' ' && iskey == false)
                {
                    tmp2.push_back(':');
                    iskey = true;
                }
                
            }
            //cout << tmp2 <<endl;
            fout << tmp2 ;
        }
    }
    fout.close();
    fin.close();
}
