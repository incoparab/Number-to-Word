#include <iostream>
#include <fstream>
#include <string>
#include <time.h>
#define CLOCKS_PER_SEC 1000
using namespace std;
clock_t b_startTime, b_endTime;
struct W_Tree_Node
{                //结点
    char Eng;    //字母
    string Ches; //汉语，初值为@
    W_Tree_Node *next[26];
    W_Tree_Node()
    {
        Ches = "@";
        for (int i = 0; i < 26; i++)
            next[i] = NULL;
    }
    W_Tree_Node(char ch)
    {
        Eng = ch;
        Ches = "@";
        for (int i = 0; i < 26; i++)
            next[i] = NULL;
    }
};
class E_Tree
{
private:
    int total[10] = {2, 2, 2, 2, 3, 3, 3, 3, 3, 3};
    char c[10][10] = {"ab", "cd", "ef", "gh", "ijk", "lmn", "opq", "rst", "uvw", "xyz"};

private:
    W_Tree_Node *root;

public:
    E_Tree()
    {
        root = new W_Tree_Node;
        Infile();
        Find();
    }
    void Infile(); //读取文件+建树
    void Find();   //检索
};
void E_Tree::Infile()
{
    ifstream infile;
    infile.open("English.csv", ios::in);
    if (!infile)
    {
        cout << "Infile error!" << endl;
        system("pause");
    }
    string str;
    while (getline(infile, str))
    {
        W_Tree_Node *p = root;
        for (int i = 0; i < str.length(); i++)
            if (str[i] != ',')
            {
                int n;
                if (str[i] >= 'a' && str[i] <= 'z')
                    n = str[i] - 'a';
                else
                    break;
                if (p->next[n])
                {
                    p = p->next[n];
                    continue;
                }
                W_Tree_Node *newNode = new W_Tree_Node(str[i]);
                p->next[n] = newNode;
                p = p->next[n];
            }
            else
            {
                p->Ches = str.substr(i + 1);
                break;
            }
    }
    infile.close();
}
void E_Tree::Find()
{
    string str;
    cout << "Please input the numbers:" << endl;
    cin >> str;
    b_startTime = clock();
    int i = 0;
    int k = str.length();
    W_Tree_Node *p = root;
    string re;
    int *number = new int[k];
    int *answer = new int[k];
    for (i = 0; i <= k; i++)
    {
        number[i] = str[i] - '0';
        answer[i] = 0;
    }
    while (true)
    {
        k = str.length() - 1;
        for (i = 0; i < k + 1; i++)
        {
            re += c[number[i]][answer[i]];
            if (p->next[re[i] - 'a'])
                p = p->next[re[i] - 'a'];
            else
                break;
        }
        if (i == k + 1 && p->Ches != "@")
        {
            cout << "The corresponding word is:" << '\t' << re << '\t' << p->Ches << endl;
            b_endTime=clock();
            cout << "The run time is:" << (double)(b_endTime - b_startTime) / CLOCKS_PER_SEC << "s" << endl;
            return;
        }

        re = "";
        p = root;
        while (k >= 0)
        {
            if (answer[k] < total[number[k]] - 1)
            {
                answer[k]++;
                break;
            }
            else
            {
                answer[k] = 0;
                k--;
            }
        }
        if (k < 0)
            break;
    }
    cout << "No corresponding word." << endl;
    b_endTime = clock();
    cout << "The run time is:" << (double)(b_endTime - b_startTime) / CLOCKS_PER_SEC << "s" << endl;
}