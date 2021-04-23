#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <time.h>
using namespace std;
clock_t a_startTime, a_endTime;
struct Word
{
	string Eng;
	string Chi;
	Word(string eng, string chi)
	{
		Eng = eng;
		Chi = chi;
	}
};

class EnuSort
{
public:
	int len = 0;
	int total[10] = {2, 2, 2, 2, 3, 3, 3, 3, 3, 3};
	char c[10][10] = {"ab", "cd", "ef", "gh", "ijk", "lmn", "opq", "rst", "uvw", "xyz"};
	vector<Word> word;
	vector<int> number;
	vector<int> answer;
	int Chiflag = -1;

public:
	EnuSort()
	{
		read();
		input();
		Find();
	}
	bool find(string eng, vector<Word> temp);
	void read();
	void partition(string &sOriginal, char cDivider, vector<string> &satfile);
	void input();
	void Find();
};

bool EnuSort::find(string eng, vector<Word> temp)
{
	int num = temp.size();
	int count1 = 1;
	for (int i = 0; i < num; i++)
	{
		if (eng != temp[i].Eng)
		{
			count1++;
			continue;
		}
		else
		{
			Chiflag = i;
			return true;
		}
	}
	if (count1 == num + 1)
	{
		return false;
	}
}
void EnuSort::read()
{
	ifstream in("English.csv");
	string s;
	if (in.eof())
		cout << "Infile error!" << endl;
	else
		while (getline(in, s))
		{
			string eng;
			string chi;
			for (int i = 0; i < s.length(); i++)
			{
				if (s[i] != ',')
					eng += s[i];
				else
				{
					chi = s.substr(i + 1);
					break;
				}
			}
			Word temp(eng, chi);
			word.push_back(temp);
		}
	in.close();
}
void EnuSort::input()
{
	string str;
	cout << "Please input the numbers:" << endl;
	int a = 0;
	cin >> str;
	a_startTime = clock();
	len = str.length() - 1;
	for (int i = 0; i < len + 1; i++)
	{
		a = str[i] - '0';
		number.push_back(a);
		answer.push_back(0);
	}
}

void EnuSort::Find()
{
	while (true)
	{
		string temp1;
		for (int j = 0; j < len + 1; j++)
			temp1 += c[number[j]][answer[j]];
		cout << temp1 << endl;
		if (find(temp1, word))
		{
			cout << "The corresponding word is:" << '\t' << temp1 << '\t' << word[Chiflag].Chi << endl;
			a_endTime = clock();
			cout << "The run time is:" << (double)(a_endTime - a_startTime) / CLOCKS_PER_SEC << "s" << endl;
			return;

			temp1 = "";
		}
		int k = len;
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
		{
			break;
		}
	}
	cout << "No corresponding word." << endl;
	a_endTime = clock();
	cout << "The run time is:" << (double)(a_endTime - a_startTime) / CLOCKS_PER_SEC << "s" << endl;
}
