#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int main()
{
    ifstream in;
    in.open("English.csv");
    string str;
    string s;
    int i = 0;
    while (getline(in, str))
    {
        for (i = 0;; i++)
            if (str[i] == ',')
                break;
                s+=str.substr(0,i-1);
    }
    int a=s.length();
    cout<<a<<endl;
    system("pause");
    return 0;
}