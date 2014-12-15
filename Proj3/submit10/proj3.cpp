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
#include <algorithm>
#include <utility>
#include <deque>
#include "headfile.h"
#include "comparator.h"

#define HASH_SIZE 200000

using namespace std;



struct option longopts[]={
{"help",no_argument,NULL,'h'},
{0,0,0,0},
};


void PrintManual();

int main(int argc,char *argv[])
{
/***************************get option************************************/
	int c;
	while((c=getopt_long(argc,argv,":a:m:rht",longopts,NULL))!=-1)
	{
		switch(c)
		{
			case 0:
			break;
			case 'h':
			PrintManual();
			exit(0);
			break;	
			case '?':
			cerr<<"Unrecognized option"<<endl;
			exit(1);
		}
	}
	string filename;
	if (argc-optind!=1)
         {
           cerr<<"Wrong input file name"<<endl;
           exit(1);
         }
	filename=argv[optind];
	
/****************************data container**************************************/	
	ios::sync_with_stdio(false);
        
	vector<entry*> timestampdata;
	vector<entry*> categorydata;
	
	//original data
	vector<entry*> data;
	
        //the recent data
        vector<entry*> recent;
        
        //excerpt list
        deque<entry*> excerpt;
        
        //my hash table
        vector<keywordarray*> hashtable[HASH_SIZE];
        
/**************************Input the data********************************************/
        input(timestampdata,categorydata,data,filename);
        int datasize=timestampdata.size();
        cout<<datasize<<" entries loaded"<<endl;

/***************************put in hash table*******************************************/

        for(int i=0;i<data.size();i++)
        {
        	parse(data[i],hashtable,HASH_SIZE);
        }

/*********************Sort timestampdata vector by timestamp**************************/
	sort(timestampdata.begin(),timestampdata.end(),comp_time);

/*********************Sort category vector by category*******************************/
	sort(categorydata.begin(),categorydata.end(),comp_category);

/***************************************Operation*********************************************/



	string instruction;
	while(1)
	{
		cout<<"%";
		if(!getline(cin,instruction))
		{
			cerr<<"No q operation"<<endl;
			for(int i=0;i<data.size();i++)
			{
				delete data[i];
			}
			for(int i=0;i<HASH_SIZE;i++)
			{
				for(int j=0;j<hashtable[i].size();j++)
				{
					delete hashtable[i][j];
				}
			}
			exit(1);
		}
		if(instruction=="")
		{
			continue;
		}
		istringstream stringstr;
		stringstr.str(instruction);
		char opcode;
		int num_input=-1;
		string str_input;
		stringstr>>opcode;
		if(opcode=='t')
		{
			if(stringstr>>str_input)
			{
				pair<string,string> temp;
				if(getTpair(temp,str_input))
				{
					t_search(timestampdata,temp.first,temp.second,recent);
				}
				else
				{
					cerr<<"Not valid argument"<<endl;
					continue;
				}
			}
			else
			{
				cerr<<"Require one argument for t opcode"<<endl;
				continue;
			}
		}
		else if(opcode=='c')
		{
			if(getline(stringstr,str_input))
			{
				pair<string,string> temp;
				if(getCpair(temp,str_input.substr(1)))
				{
					c_search(categorydata,temp.first,temp.second,recent);
				}
				else
				{
					cerr<<"Not valid argument"<<endl;
					continue;
				}
			}
			else
			{
				cerr<<"Require one argument for c opcode"<<endl;
				continue;
			}
		}
		else if(opcode=='k')
		{
			if(getline(stringstr,str_input))
			{
				recent.clear();
				string keyinput=str_input.substr(1);
				vector<string> keywordset;
				parsekeyword(keyinput,keywordset);
				if(keywordset.empty())
				{
					cerr<<"No keyword find"<<endl;
					continue;
				}
				int hashindex=hashstring(keywordset[0],HASH_SIZE);
				for(int i=0;i<hashtable[hashindex].size();i++)
				{
					if(hashtable[hashindex][i]->keyword==keywordset[0])
					{
						if(hashtable[hashindex][i]->issort==0)
						{
							(hashtable[hashindex][i]->indexarray).erase(unique((hashtable[hashindex][i]->indexarray).begin(),(hashtable[hashindex][i]->indexarray).end()),(hashtable[hashindex][i]->indexarray).end());
							hashtable[hashindex][i]->issort=1;
						}
						recent=hashtable[hashindex][i]->indexarray;
					}
				}
				for(int i=1;i<keywordset.size();i++)
				{
					hashindex=hashstring(keywordset[i],HASH_SIZE);
					vector<entry*> temp;
					for(int j=0;j<hashtable[hashindex].size();j++)
					{
						if(hashtable[hashindex][j]->keyword==keywordset[i])
						{
							if(hashtable[hashindex][j]->issort==0)
							{
								(hashtable[hashindex][j]->indexarray).erase(unique((hashtable[hashindex][j]->indexarray).begin(),(hashtable[hashindex][j]->indexarray).end(),entryptrunique),(hashtable[hashindex][j]->indexarray).end());
								hashtable[hashindex][j]->issort=1;	
							}
							temp=hashtable[hashindex][j]->indexarray;

							
						}
					}
					recent=stl_intersection(recent,temp);
				}
				sort(recent.begin(),recent.end(),comp_time);
				ostringstream tempstream;
				for(int i=0;i<recent.size();i++)
				{
					tempstream<<recent[i]->id<<"|"<<recent[i]->timestamp<<"|"<<recent[i]->category<<"|"<<recent[i]->message<<'\n';
				}
				cout<<tempstream.str();
			}
			else
			{
				cerr<<"No input for k operation"<<endl;
				continue;
			}	
		}
		
		else if(opcode=='i')
		{
			if(stringstr>>num_input)
			{
				if(num_input<0||num_input>datasize-1)
				{
					cerr<<"Not proper master entry id"<<endl;
					continue;
				}
				else
				{
					excerpt.push_back(data[num_input]);
				}
			}
			else
			{
				cerr<<"Require one argument for i operation"<<endl;
				continue;
			}
		}
		else if (opcode=='r')
		{
			for(int i=0;i<recent.size();i++)
			{
				excerpt.push_back(recent[i]);
			}
		}
		else if(opcode=='d')
		{
			if(stringstr>>num_input)
			{
				if(num_input<0||num_input>(int)(excerpt.size()-1))
				{
					cerr<<"Not proper excerpt entry id"<<endl;
					continue;
				}
				else
				{
					excerpt.erase(excerpt.begin()+num_input);
				}
			}
			else
			{
				cerr<<"Require one argument for d operation"<<endl;
				continue;
			}
		}
		
		else if(opcode=='b')
		{
			if(stringstr>>num_input)
			{
				if(num_input<0||num_input>(int)(excerpt.size()-1))
				{
					cerr<<"Not proper excerpt entry id"<<endl;
					continue;
				}
				else
				{
					entry* temp=*(excerpt.begin()+num_input);
					excerpt.erase(excerpt.begin()+num_input);
					excerpt.push_front(temp);
					
				}
			}
			else
			{
				cerr<<"Require one argument for b operation"<<endl;
				continue;
			}
		}
		else if(opcode=='e')
		{
			if(stringstr>>num_input)
			{
				if(num_input<0||num_input>(int)(excerpt.size()-1))
				{
					cerr<<"Not proper excerpt entry id"<<endl;
					continue;
				}
				else
				{
					entry* temp=*(excerpt.begin()+num_input);
					excerpt.erase(excerpt.begin()+num_input);
					excerpt.push_back(temp);
				}
			}
			else
			{
				cerr<<"Require one argument for b operation"<<endl;
				continue;
			}
		}
		else if(opcode=='s')
		{
			sort(excerpt.begin(),excerpt.end(),comp_time);
		}
		else if(opcode=='p')
		{
			ostringstream tempstream;
			for(int i=0;i<excerpt.size();i++)
			{
				tempstream<<i<<'|'<<(*(excerpt.begin()+i))->id<<"|"<<(*(excerpt.begin()+i))->timestamp<<'|'
				<<(*(excerpt.begin()+i))->category<<'|'<<(*(excerpt.begin()+i))->message<<'\n';
			}
			cout<<tempstream.str();
		}
		
		else if (opcode=='q')
		{
			for(int i=0;i<data.size();i++)
			{
				delete data[i];
			}
			for(int i=0;i<HASH_SIZE;i++)
			{
				for(int j=0;j<hashtable[i].size();j++)
				{
					delete hashtable[i][j];
				}
			}
			exit(0);
		}
		else
		{
			cerr<<"Not valid operation"<<endl;
			continue;
		}	
	}
	return 0;
}

void PrintManual()
{
	cout<<"NAME"<<endl;
	cout<<"      logman - a command line log manager program."<<endl;
	cout<<"SYNOPSIS"<<endl;
	cout<<"      logman [OPTION|LOGFILE]"<<endl;
	cout<<"DESCRIPTION"<<endl;
	cout<<"      logman is a command line log manager which supports excerpt list creation and"<<endl;
	cout<<"      editing. Upon startup, logman reads the master log entry file, LOGFILE. Normally, "<<endl;
	cout<<"      logman reads to standard output. It also supports reading excerpt list editing commands "<<endl;
	cout<<"      from a script file."<<endl;
	cout<<"OPTIONS"<<endl;
	cout<<"      -h, --help"<<endl;
	cout<<"            Print this help screen and exit."<<endl;
}
