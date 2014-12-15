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

bool identify(string &str);
int datain_code(vector<string> &data, int check,string & _str);
void norm(string &_str);

void input_code(vector<vector<string> >&data, const string filename)
{
	ifstream infile;
	infile.open(filename.c_str());
	if(!infile.is_open())
	{
		cerr<<"open error!"<<endl;
		exit(1);
	}
	string templine;
	int check=0;
	while(getline(infile,templine))
	{
		if (identify(templine))
		{
			check=0;
			vector<string> currentdata;
			string name;
			name=templine.substr(20,templine.length()-40);
			currentdata.push_back(name);
			data.push_back(currentdata);
			continue;
		}
		norm(templine);
		if(templine!="")
		{
			int lastcheck=check;
			check=datain_code(data.back(),lastcheck,templine);
		}
		else
		{
			check=0;
		}
		
		
	}
	infile.close();
//	for (int i=0;i<data.size();i++)	
//	{
//		for(int j=1;j<data[i].size();j++)
//		{
//			norm(data[i][j]);
//			cout<<data[i][j]<<endl;
//		}
//	}
	
}


//b records if the line of the former element is ended
//return 1 if there is no termination
//return 0 if there is a termination
int datain_code(vector<string> &data, int check,string & _str)
{
//	cout<<_str<<endl;
	int start=0;
	int i=-1;
//	cout<<i<<endl;
//	cout<<_str.length()<<endl;
//	cout<<(i>_str.length())<<endl;
	while(start<_str.length())
	{
//		cout<<"aa"<<endl;
		
		for (i=start;i<_str.length();i++)
		{
			if(_str[i]==';'||_str[i]=='{'||_str[i]=='}')
			{
				break;
			}
		}
		string temp;
//		cout<<start<<endl;
		if(i-start!=0)
		{
			if(_str[i-1]==' ')
			{
				temp=_str.substr(start,i-start-1);
			}
			else
			{
				temp=_str.substr(start,i-start);
			}
//			cout<<temp;
			if (check==1&&start==0)
			{
//				cout<<"1"<<endl;	
				data.back()=data.back()+" "+temp;
			}
			else
			{
//				cout<<"2"<<endl;
				data.push_back(temp);
			}
		}
		if(_str[i+1]==' ')
		{
			start=i+2;
		}
		else
		{
			start=i+1;
		}
	}
//	cout<<data.size()<<endl;
	if(_str[_str.length()-1]==';'||_str[_str.length()-1]=='{'||_str[_str.length()-1]=='}')
	{
		return 0;
	}
	else
	{
		return 1;
	}
//	cout<<data.size()<<endl;
}


