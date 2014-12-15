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
#include "headfile.h"

#define HASH_SIZE 555555

using namespace std;





int main(int argc,char *argv[])
{
        string filename=argv[1];
        
//        //original data
//        vector<entry> data;
	
	//two copy for original data, one for timestamp sort
	//one for categrorysort
	vector<entry*> timestampdata;
	vector<entry*> categorydata;
	
	//original data
	vector<entry*> data;
	
        //the recent data
        vector<int> recent;
        
        //excerpt list
        vector<entry*> excerpt;
//       cout<<excerpt.size()<<endl;
        
        //my hash table
        vector<keywordarray*> hashtable[HASH_SIZE];
        
/**************************Input the data********************************************/
        input(timestampdata,categorydata,data,filename);
        int datasize=timestampdata.size();
        cout<<datasize<<" entries loaded"<<endl;
//      cout<<hashstring("packet",HASH_SIZE)<<endl;

	
      	


/***************************put in hash table*******************************************/

//!!!!!!!!!!!!!!!!!!!!!!!!
//Notice that this one consume time and could be put into inputfile part!!!!


        for(int i=0;i<data.size();i++)
        {
        	parse(data[i],hashtable,HASH_SIZE,i);
        }
/*
        for(int i=0;i<HASH_SIZE;i++)
        {
        	cout<<"!"<<endl;
        	for(int j=0;j<hashtable[i].size();j++)
        	{
        		cout<<"keyword:"<<hashtable[i][j]->keyword<<" ";
        		for(int k=0;k<(hashtable[i][j]->indexarray).size();k++)
        		{
        			cout<<(hashtable[i][j]->indexarray)[k]<<" ";
        		}
        		cout<<"issort:"<<hashtable[i][j]->issort<<endl;
        	}
        }
        
        
/*
        for(int i=0;i<data.size();i++)
        {
        	cout<<data[i].id<<endl;
        }
*/
/*
	for(int i=0;i<HASH_SIZE;i++)
	{
		sort(hashtable[i].begin(),hashtable[i].end(),comp_key_keyword);
		hashtable[i].erase(unique(hashtable[i].begin(),hashtable[i].end(),beq_key_keyword),hashtable[i].end());
	}
*/
	
/*	
        for(int i=0;i<HASH_SIZE;i++)
        {
        	cout<<hashtable[i].size()<<endl;
        	for(int j=0;j<hashtable[i].size();j++)
        	{
        		cout<<hashtable[i][j].id<<" "<<hashtable[i][j].keyword<<" || ";
        	}
        	cout<<endl;
        	
        }

*/


/*********************Sort timestampdata vector by timestamp**************************/
	sort(timestampdata.begin(),timestampdata.end(),comp_time);
//	t_search(timestampdata,"01:23:10:03:00","04:25:21:55:37",recent);
//	for(int i=0;i<timestampdata.size();i++)
//	{
//		cout<<timestampdata[i]->id<<"|"<<timestampdata[i]->timestamp<<"|"<<timestampdata[i]->category<<endl;
//	}
/*********************Sort category vector by category*******************************/
	sort(categorydata.begin(),categorydata.end(),comp_category);
//	c_search(categorydata,"rzzz","ti",recent);
//	for(int i=0;i<categorydata.size();i++)
//	{
//		cout<<categorydata[i]->id<<"|"<<categorydata[i]->timestamp<<"|"<<categorydata[i]->category<<endl;
//	}

	


/*
	pair<string,string> temp;
	cout<<getTpair(temp, "::::|01:00:09:12:00")<<endl;
	cout<<temp.first<<" "<<temp.second<<endl;

*/


/*
	vector<string>result;
	string temp="fda;fj;a";
	parsekeyword(temp, result);
	for(int i=0;i<result.size();i++)
	{
		cout<<result[i]<<endl;
	}
*/
	
/*	
	vector<string> keywordsettest;
//	cout<<keyinput<<endl;
	string test="***sa***** ";
	parsekeyword(test,keywordsettest);
	cout<<keywordsettest.size()<<endl;
*/
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
			//	cout<<keyinput<<endl;
				parsekeyword(keyinput,keywordset);
				if(keywordset.empty())
				{
					cerr<<"No keyword find"<<endl;
					continue;
				}
//				for(int i=0;i<keywordset.size();i++)
//				{
//					cout<<keywordset[i]<<endl;
//				}
				
//				cout<<hashstring("a",HASH_SIZE)<<endl;
				int hashindex=hashstring(keywordset[0],HASH_SIZE);
//				cout<<hashindex<<" "<<hashtable[hashindex].size()<<endl;
				for(int i=0;i<hashtable[hashindex].size();i++)
				{
//					cout<<hashtable[hashindex][i].keyword<<endl;
					if(hashtable[hashindex][i]->keyword==keywordset[0])
					{
						if(hashtable[hashindex][i]->issort==0)
						{
							(hashtable[hashindex][i]->indexarray).erase(unique((hashtable[hashindex][i]->indexarray).begin(),(hashtable[hashindex][i]->indexarray).end()),(hashtable[hashindex][i]->indexarray).end());
							hashtable[hashindex][i]->issort=1;
		//					for(int j=0;j<(hashtable[hashindex][i]->indexarray).size();j++)
		//					{
		//						cout<<(hashtable[hashindex][i]->indexarray)[j]<<endl;
		//					}
						}
						recent=hashtable[hashindex][i]->indexarray;
//						for(int j=0;j<recent.size();j++)
//						{
//							cout<<recent[j]<<endl;
//						}
					}
				}
//				for(int i=0;i<recent.size();i++)
//				{
//					cout<<recent[i]<<endl;
//				}
				for(int i=1;i<keywordset.size();i++)
				{
//					cout<<keywordset[i]<<endl;
					hashindex=hashstring(keywordset[i],HASH_SIZE);
//					cout<<hashindex<<endl;
//					cout<<hashtable[hashindex].size()<<endl;
					vector<int> temp;
					for(int j=0;j<hashtable[hashindex].size();j++)
					{
						if(hashtable[hashindex][j]->keyword==keywordset[i])
						{
//							for(int k=0;k<(hashtable[hashindex][j]->indexarray).size();k++)
//							{
//								cout<<(hashtable[hashindex][j]->indexarray)[k]<<endl;
//							}
							if(hashtable[hashindex][j]->issort==0)
							{
								(hashtable[hashindex][j]->indexarray).erase(unique((hashtable[hashindex][j]->indexarray).begin(),(hashtable[hashindex][j]->indexarray).end()),(hashtable[hashindex][j]->indexarray).end());
								hashtable[hashindex][j]->issort=1;
//								for(int k=0;k<(hashtable[hashindex][j]->indexarray).size();k++)
//								{
//									cout<<(hashtable[hashindex][j]->indexarray)[k]<<endl;
//								}	
							}
							temp=hashtable[hashindex][j]->indexarray;
//							for(int k=0;k<temp.size();k++)
							
						}
					}
//					cout<<temp.size()<<endl;
//					for(int k=0;k<temp.size();k++)
//					{
//						cout<<temp[k]<<endl;
//					}
					recent=stl_intersection(recent,temp);
				}
				//!!!!!!!!!!!!!!!recent should be integer type or ...?
				vector<entry*> tempdata;
				for(int i=0;i<recent.size();i++)
				{
					tempdata.push_back(data[recent[i]]);
				}
				sort(tempdata.begin(),tempdata.end(),comp_time);
				recent.clear();
				for(int i=0;i<tempdata.size();i++)
				{
//					cout<<tempdata[i].id<<endl;
					recent.push_back(tempdata[i]->id);
				}
				
				for(int i=0;i<recent.size();i++)
				{
					cout<<tempdata[i]->id<<"|"<<tempdata[i]->timestamp<<"|"<<tempdata[i]->category<<"|"<<tempdata[i]->message<<endl;
				}
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
				excerpt.push_back(data[recent[i]]);
			}
		}
		else if(opcode=='d')
		{
			if(stringstr>>num_input)
			{
//				cout<<datasize-1<<endl;
				if(num_input<0||num_input>(int)(excerpt.size()-1))
				{
					cerr<<"Not proper excerpt entry id"<<endl;
					continue;
				}
				else
				{
					for(int i=num_input;i<excerpt.size()-1;i++)
					{
						excerpt[i]=excerpt[i+1];
					}
					excerpt.pop_back();
				}
			}
			else
			{
				cerr<<"Require one argument for d operation"<<endl;
				continue;
			}
		}
		
		//ru guo shi kong ?? -1 shenme de = =
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
					entry* temp=excerpt[num_input];
					for(int i=1;i<=num_input;i++)
					{
						excerpt[i]=excerpt[i-1];
					}
					excerpt[0]=temp;
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
					entry* temp=excerpt[num_input];
					for(int i=num_input;i<excerpt.size()-1;i++)
					{
						excerpt[i]=excerpt[i+1];
					}
					excerpt[excerpt.size()-1]=temp;
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
			for(int i=0;i<excerpt.size();i++)
			{
				cout<<i<<"|"<<excerpt[i]->id<<"|"<<excerpt[i]->timestamp<<"|"
				<<excerpt[i]->category<<"|"<<excerpt[i]->message<<endl;
			}
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



	


//	t_search(timestampdata,"01:12:11:12:12","12:12:12:12:12",recent);
	
//	for(int i=0;i<recent.size();i++)
//	{
//		cout<<recent[i].category<<endl;
//	}
//	t_search(data,"12:11:20:12:12","12:15:20:56:23",recent);
//	for(int i=0;i<recent.size();i++)
//	{
//		cout<<recent[i].category<<endl;
//	}


/*
	for(int i=0;i<categorydata.size();i++)
	{
		cout<<categorydata[i].id<<endl;
	}
	
	c_search(categorydata,"rzzz","ti",recent);
*/	
//      for(int i=0;i<recent.size();i++)
//	{
//		cout<<recent[i].category<<endl;
//	}
/*
        for(int i=0;i<data.size();i++)
        {
        	for(int j=0;j<data[i].keyword.size();j++)
        	{
        		cout<<data[i].keyword[j]<<" ";
		}
		cout<<endl;
        	
        }
*/  
/*
	string test1="";
	string test2="aaa";
	cout<<(test1<test2)<<endl;
*/	     
	

        return 0;

}
