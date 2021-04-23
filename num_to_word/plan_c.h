#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <time.h>
#define size 10
using namespace std;
clock_t c_startTime, c_endTime;
struct Node
{
	Node *next[size];
	string Chinese;
	int n;
	bool tag;
	Node()
	{
		Chinese = "@";
		for (int i = 0; i < size; i++)
			next[i] = NULL;
	}
	Node(int m)
	{
		n = m;
		Chinese = "@";
		for (int i = 0; i < size; i++)
			next[i] = NULL;
	}
};

class N_tree
{
private:
	Node *root;

public:
	N_tree()
	{
		root = new Node;
		Read();
		Find();
	}
	void Read();
	void Find();
};

int Translate(char a)
{
	if (a == 'a' || a == 'b')
	{
		return 0;
	}

	if (a == 'c' || a == 'd')
	{
		return 1;
	}

	if (a == 'e' || a == 'f')
	{
		return 2;
	}

	if (a == 'g' || a == 'h')
	{
		return 3;
	}

	if (a == 'i' || a == 'j' || a == 'k')
	{
		return 4;
	}

	if (a == 'l' || a == 'm' || a == 'n')
	{
		return 5;
	}

	if (a == 'o' || a == 'p' || a == 'q')
	{
		return 6;
	}

	if (a == 'r' || a == 's' || a == 't')
	{
		return 7;
	}

	if (a == 'u' || a == 'v' || a == 'w')
	{
		return 8;
	}

	if (a == 'x' || a == 'y' || a == 'z')
	{
		return 9;
	}
}
void N_tree::Read()
{
	string temp;
	int strline;
	ifstream input;
	input.open("English.csv");
	while (getline(input, temp))
	{
		Node *p = root;
		for (int i = 0; i < temp.length(); i++)
		{
			if (temp[i] != ',')
			{
				if (temp[i] >= 'a' && temp[i] <= 'z')
					strline = Translate(temp[i]);
				else
					continue;
				if (p->next[strline] == NULL)
				{
					Node *newnode = new Node(strline);
					newnode->tag = false;
					p->next[strline] = newnode;
					p = p->next[strline];
					continue;
				}
				p = p->next[strline];
			}
			else
			{
				p->tag = true;
				p->Chinese = temp.substr(i + 1);
				break;
			}
		}
	}

	input.close();
}
void N_tree::Find()
{
	cout << "Please input the numbers:" << endl;
	string str;
	cin >> str;
	c_startTime = clock();
	int k = str.length();
	Node *p = root;
	for (int i = 0; i < k; i++)
	{
		int n;
		n = str[i] - '0';
		if (p->next[n])
			p = p->next[n];
		else
		{
			cout << "No corresponding word." << endl;
			c_endTime = clock();
			cout << "The run time is:" << (double)(c_endTime - c_startTime) / CLOCKS_PER_SEC << "s" << endl;
			return;
		}
	}
	if (!p->tag)
	{
		cout << "No corresponding word." << endl;
		c_endTime = clock();
		cout << "The run time is:" << (double)(c_endTime - c_startTime) / CLOCKS_PER_SEC << "s" << endl;
	}
	else
	{
		cout << p->Chinese << endl;
		c_endTime = clock();
		cout << "The run time is:" << (double)(c_endTime - c_startTime) / CLOCKS_PER_SEC << "s" << endl;
	}
}