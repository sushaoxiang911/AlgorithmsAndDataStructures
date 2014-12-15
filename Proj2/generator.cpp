#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "time.h"
#define CONTENTLENGTH 150
#define NAME 3

using namespace std;

int a=0;
void generate_name()
{
	string name="";
	static int a='A';
	name=a++;
	if(a=='~')
		a++;
	cout<<"~~~~~~~~~~~~~~~~~~~~";
	cout<<name;
	cout<<"~~~~~~~~~~~~~~~~~~~~"<<endl;
}

void generate_content()
{
	string content="";
	char temp;
	for(int i=0;i<CONTENTLENGTH;i++)
	{
		temp=(rand()%94)+32;
		if(rand()%40<10)
		{
			cout<<".";
		}
		else if (rand()%40<10)
		{
			cout<<"\t";
		}
		else if (rand()%80<10)
		{
			cout<<"\n";
			a++;
		}
		else if (rand()%30<15)
		{
			cout<<" ";
		}
		else if (rand()%10<4)
		{
			cout<<"~";
		}
		cout<<temp;
	}
	cout<<endl;
}

int main()
{
	srand(time(NULL));
	for (int i=0;i<NAME;i++)
	{
		generate_name();
		generate_content();
		if(a>40)
		{
			break;
		}
	}
}
