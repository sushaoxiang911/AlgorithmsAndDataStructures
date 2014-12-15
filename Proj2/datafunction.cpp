#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <vector>
#include <fstream>
#include <getopt.h>

using namespace std;

void norm(string &_str)
{
	for(int i=0;i<_str.length();i++)
	{
		if(_str[i]=='\t'||_str[i]=='\n')
		{
			_str[i]=' ';
		}
	}
	int len;
	int start=0;
	int i;
	while(start<_str.length())
	{
//		cout<<start<<" "<<i<<endl;
		len=0;
		for(i=start;i<_str.length();i++)
		{
			if(_str[i]==' ')
			{
				break;
			}
		}
		start=i;
		for(i=start;i<_str.length();i++)
		{
			if(_str[i]!=' ')
			{
				break;
			}
		}
//		cout<<i<<endl;
//		cout<<endl;
		if(start==0||i==_str.length())//pan duan you wu ....ke yi xiu gai 
		{
			len=i-start;
			_str.erase(start,i-start);
		}
		
		else
		{
			if(i-start>1)
			{
				len=i-start-1;
				_str.erase(start+1,i-start-1);
			}
		}
		start=i-len;
	}

} 

bool identify(string &str)
{
	if(str.length()<=40)
	return false;
	for(int i=0;i<20;i++)
	{
		if(str[i]!='~')
			return false;
	}
	for(int i=str.length()-20;i<str.length();i++)
	{
		if (str[i]!='~')
			return false;
	}
	return true;
}
