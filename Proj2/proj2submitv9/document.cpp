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
//EFFECT:	CHECK IF THE CURRENT SENTENCE IS A IDENTIFIER SENTENCE
//		RETURN 1 IF IT IS AN IDENTIFIER
//		RETURN 0 IF IT IS NOT AN IDENTIFIER
//REQUIRED:	THE CURRENT STRING
//MODIFY:	NONE
int datain_document(vector<string> &data, int check,string & _str);
//EFFECT:	PARCED THE CURRENT LINE BASED ON THE DILIMITER 
//		PUT THEM INTO THE THE LINE DATABASE
//		CHECK IF THERE IS A DILIMITER AT THE END OF THE LINE
//		RETURN 0 IF THERE IS A DILIMITER AT THE END OF THE LINE
//		RETURN 1 IF THERE IS NO DILIMITER AT THE END OF THE LINE
//REQUIRED:	VECTOR<STRING> TYPE DATA, THE CURRENT STRING AND
//		AN INT VARIABLE TO CHECK IF THE SENTENCE SHOULD BE APPEND
//MODIFY:	THE DATABASE OF THE PERSON

void norm(string &_str);
//EFFECT:	NORMALIZE THE CURRENT LINE.
//		CONVERT ALL THE \T INTO SPACE AND NOMALIZE
//REQUIRED:	THE CURRENT INPUT STRING
//MODIFY:	THE CURRENT INPUT STRING

void input_document(vector<vector<string> >&data, const string filename)
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
			check=datain_document(data.back(),lastcheck,templine);
		}
		else
		{
			check=0;
		}
		
		
	}
	infile.close();
}

int datain_document(vector<string> &data, int check,string & _str)
{
	int start=0;
	int i=-1;
	while(start<_str.length())
	{	
		for (i=start;i<_str.length();i++)
		{
			if(_str[i]=='.'||_str[i]=='!'||_str[i]=='?')
			{
				break;
			}
		}
		string temp;
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
			if (check==1&&start==0)
			{	
				data.back()=data.back()+" "+temp;
			}
			else
			{
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
	if(_str[_str.length()-1]=='.'||_str[_str.length()-1]=='!'||_str[_str.length()-1]=='?')
	{
		return 0;
	}
	else
	{
		return 1;
	}
}


