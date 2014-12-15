#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "time.h"
#define CONTENTLENGTH 2000
#define LINENUM 100000

using namespace std;
	

int main()
{
	srand(time(NULL));
	for (int i=0;i<LINENUM;i++)
	{
		cout<<(rand()%9)<<(rand()%9)<<":"<<((rand()+6387)%9)<<((rand()+6387)%9)<<":"<<((rand()+6387)%9)<<((rand()+6387)%9)<<":"<<((rand()+6387)%9)<<((rand()+6387)%9)<<":"<<((rand()+6387)%9)<<((rand()+6387)%9)<<"|";
		for(int j=0;j<10;j++)
		{
			char k=rand()%95+32;
			if(k!='|'&&k!='\t'&&k!='%')
			{
				cout<<k;
			}
		}
		cout<<"|";
		for(int j=0;j<CONTENTLENGTH;j++)
		{
			char k=rand()%95+32;
			if(k!='|'&&k!='\t'&&k!='%')
			{
				cout<<k;
			}
		}
		cout<<endl;
	}
}
