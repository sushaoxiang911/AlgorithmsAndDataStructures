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
#include "duplicate.h"
#include <getopt.h>
#include <sstream>
#include <utility>
#include <sys/resource.h>
#include <sys/time.h>

using namespace std;

char *MODE;
char *ALGOR;
int report=0;
int t=0;
int mode;
struct option longopts[]={
{"algorithm",required_argument,NULL,'a'},
{"mode",required_argument,NULL,'m'},
{"report",no_argument,NULL,'r'},
{"help",no_argument,NULL,'h'},
{"timing",no_argument,NULL,'t'},
{0,0,0,0},
};

void submis_norm(string &str);
void timeprint();
void PrintManual();
pair<int,int> getindex(vector<vector<string> > &data,string &submissions);
int main(int argc,char *argv[])
{
/***************************************************************Get the option from the command line******************************************************/
	bool algor_choice;
	opterr=0;
	int c;
	while((c=getopt_long(argc,argv,":a:m:rht",longopts,NULL))!=-1)
	{
		switch(c){
		case 0:
		break;
		case 'a':
		ALGOR=optarg;
		if(strcmp(ALGOR,"SELF")&&strcmp(ALGOR,"STL"))
		{
			cerr<<"Unvalid algorithm mode"<<endl;
			exit(1);
		}
		break;
		case 'm':
		MODE=optarg;
		if(strcmp(MODE,"CODE")&&strcmp(MODE,"DOCUMENT"))
		{
			cerr<<"Unvalid file mode"<<endl;
			exit(1);
		}
		mode=1;
		break;
		case 'r':
		report=1;
		break;
		case 't':
		t=1;
		break;
		case 'h':
		PrintManual();
		exit(0);
		break;
		case ':':
		cerr<<"Undefine argument"<<endl;
		exit(1);
		case '?':
		cerr<<"Unrecognized option"<<endl;
		exit(1);
		
		}
	}
	if(mode==0)
	{
		cerr<<"No specific file mode"<<endl;
		exit(1);
	}
	

	string filename;
	if (argc-optind!=1)
         {
           cerr<<"Wrong input file name"<<endl;
           exit(1);
         }
	filename=argv[optind];


/*********************************************************Get the data and process data***************************************************/
//	string filename=argv[1];
	Timer totaltime;
	vector<vector<string> > data;

	if(!strcmp(MODE,"DOCUMENT"))
	{	
		input_document(data,filename);
	}
	else
	{
		input_code(data,filename);
	}
//	cout<<"a"<<endl;	
	
//	cout<<data[0].size()<<endl;
	// delete the empty lines.
/*	for(int i=0;i<data.size();i++)
	{
		vector<string> temp;
		for(int j=0;j<data[i].size();j++)
		{
//			cout<<"a"<<endl;
			if(data[i][j]!="")
			{
				temp.push_back(data[i][j]);
			}
		}
		data[i]=temp;	
	}
*/
//	cout<<data[0].size()<<endl;

	for(int i=0;i<data.size();i++)
	{
		for(int j=0;j<data[i].size();j++)
		{
			cout<<data[i][j]<<endl;
		}
	}

//	cout<<data[0].size()<<endl;
//	for(int i=0;i<data[0].size();i++)
//	{
//		if(data[0][i].length()>=295)
//		{
//			cout<<data[0][i][294]<<endl;
//		}
//	}
	if(ALGOR==NULL)
	{
		algor_choice=1;
	}
	else
	{
		if(!strcmp(ALGOR,"SELF"))
		{
			algor_choice=1;
		}
		else
		{
			algor_choice=0;
		}
	}
//	cout<<data.size()<<endl;
	
//	sort(data[0].begin()+1,data[0].end());
//	cout<<"a"<<endl;
/*

	for (int i=0;i<data.size();i++)	
	{
		if(algor_choice)
		{
			Timer timetemp;
			//my sort
			R_sort(data[i]);
			timetemp.recordTime();
			sort_time=sort_time+timetemp.getTime();
		}
		else
		{
			Timer timetemp;
			//stl sort
			sort(data[i].begin()+1,data[i].end());
			timetemp.recordTime();
			sort_time=sort_time+timetemp.getTime();

		}
//		cout<<"a"<<endl;
		if(algor_choice)
		{

			//my unique
			my_unique(data[i]);
	

		}
		else
		{
			//stl unique
			stl_unique(data[i]);

		}

	}
	
//	if(data.size()>0)
//	{
		vector<string> all_have=data[0];
		for(int i=1;i<data.size();i++)
		{
			if(algor_choice)
			{		
				all_have=my_intersection(all_have,data[i]);
			}
			else
			{
				all_have=stl_intersection(all_have,data[i]);
			}
		}
	

//		for(int i=0;i<all_have.size();i++)
//		{
//			cout<<all_have[i]<<endl;
//		}

		//delete the content that everyone have
		for(int i=0;i<data.size();i++)
		{
			professor_giving(all_have,data[i]);
		}

//	}
//	for(int i=0;i<data.size();i++)
//	{
//		for(int j=0;j<data[i].size();j++)
//		{
//			cout<<data[i][j]<<endl;
//		}
//	}
// kong wen dang zen me ban ??!
/*********************************************Instruction and Operation***************************************************************/
/*
	if(report==1)
	{	
		//s threshold operation
		vector<s_name> result_s;		
		if(algor_choice)
		{
			my_s_get(result_s,data,50);
		}
		else
		{
			stl_s_get(result_s,data,50);
		}		
		sort(result_s.begin(),result_s.end(),s_comp);
		for(int i=0;i<result_s.size();i++)
		{
			cout<<result_s[i].percent<<"% "<<result_s[i].name1<<", "<<result_s[i].name2<<endl;
		}

		//merge is for the g command
		vector<string> merge_result=data[0];
		for(int i=1;i<data.size();i++)
		{
			if(algor_choice)
			{
				merge_result=my_merge(merge_result,data[i]);
			}
			else
			{
				merge_result=stl_merge(merge_result,data[i]);
			}
		}

		//g THRESHOLD operation
		int num_submission=data.size();
		vector<g_line> result_g;
		g_get(result_g,merge_result,num_submission,50);
		sort(result_g.begin(),result_g.end(),g_comp);
		for(int i=0;i<result_g.size();i++)
		{
			cout<<result_g[i].percent<<"% "<<result_g[i].line<<endl;
		}
		totaltime.recordTime();
		total_time=totaltime.getTime();
		if(t==1)
		{
			timeprint();
		}
		exit(0);
		
	}

	string instruction;
	while(1)
	{
		cout<<"%";
		if(!getline(cin,instruction))
		{
			cerr<<"No q operation"<<endl;
			exit(1);
		}
		if(instruction=="")
		{
			continue;
		}
		istringstream stringstr;
		stringstr.str(instruction);
		char opcode;
		int num=-1;
		stringstr>>opcode;
		if(opcode=='s')
		{
			if(stringstr>>num)
			{	
//				cout<<"!"<<num<<endl;
				if(num>=0&&num<=100)
				{
					//s threshold operation
					vector<s_name> result_s;		
					if(algor_choice)
					{
						my_s_get(result_s,data,num);
					}
					else
					{
						stl_s_get(result_s,data,num);
					}		
					sort(result_s.begin(),result_s.end(),s_comp);
					for(int i=0;i<result_s.size();i++)
					{
						cout<<result_s[i].percent<<"% "<<result_s[i].name1<<", "<<result_s[i].name2<<endl;
					}
					continue;
				}
				else
				{
					cerr<<"Not illegal input! Input should be within [0,100]"<<endl;
					continue;
				}
			}
			else
			{
				cerr<<"Not illegal input!"<<endl;
				continue;
			}
		}
		else if(opcode=='g')
		{
			if(stringstr>>num)
			{
				if(num>=0&&num<=100)
				{
					Timer timetemp;
					//merge is for the g command
					vector<string> merge_result=data[0];
					for(int i=1;i<data.size();i++)
					{
						
						if(algor_choice)
						{
							merge_result=my_merge(merge_result,data[i]);
						}
						else
						{
							merge_result=stl_merge(merge_result,data[i]);
						}
					}
					timetemp.recordTime();
					merge_time=merge_time+timetemp.getTime();
//					for(int i=0;i<merge_result.size();i++)
//						cout<<merge_result[i]<<endl;
					//g THRESHOLD operation
					int num_submission=data.size();
					vector<g_line> result_g;
					g_get(result_g,merge_result,num_submission,num);
					sort(result_g.begin(),result_g.end(),g_comp);
					for(int i=0;i<result_g.size();i++)
					{
						cout<<result_g[i].percent<<"% "<<result_g[i].line<<endl;
					}
					continue;
				}
				else
				{
					cerr<<"Not illegal input! Input should be within [0,100]"<<endl;
					continue;
				}
			}
			else
			{
				cerr<<"Not illegal input!"<<endl;
				continue;
			}
		}
		else if(opcode=='i')
		{
			string submissions;
			pair<int,int> index;
			if(getline(stringstr,submissions))
			{
				submis_norm(submissions);
//				cout<<"!"<<submissions<<endl;
				index=getindex(data,submissions);
				if(index.first!=-1&&index.second!=-1)
				{
					
					if(algor_choice)
					{
						cout<<my_intersection(data[index.first],data[index.second]).size()-1<<endl;
					}
					else
					{
						cout<<stl_intersection(data[index.first],data[index.second]).size()-1<<endl;
					}
					continue;
				}
				else
				{
					cerr<<"Unvalid inputs"<<endl;
				}
			}
			else
			{
				cerr<<"No input"<<endl;
			}
			continue;
		}
		else if(opcode=='u')
		{
			string submissions;
			pair<int,int> index;
			if(getline(stringstr,submissions))
			{
				submis_norm(submissions);
				index=getindex(data,submissions);
				if(index.first!=-1&&index.second!=-1)
				{
					
					if(algor_choice)
					{
						cout<<my_union(data[index.first],data[index.second])<<endl;
					}
					else
					{
						cout<<stl_union(data[index.first],data[index.second])<<endl;
					}
					continue;
				}
				else
				{
					cerr<<"Unvalid inputs"<<endl;
				}
			}
			else
			{
				cerr<<"No input"<<endl;
			}
			continue;
		}
		else if(opcode=='d')
		{
			string submissions;
			pair<int,int> index;
			if(getline(stringstr,submissions))
			{
				submis_norm(submissions);
				index=getindex(data,submissions);
				if(index.first!=-1&&index.second!=-1)
				{
					
					if(algor_choice)
					{
						cout<<my_diff(data[index.first],data[index.second])<<endl;
					}
					else
					{
						cout<<stl_diff(data[index.first],data[index.second])<<endl;
					}
					continue;
				}
				else
				{
					cerr<<"Unvalid inputs"<<endl;
				}
			}
			else
			{
				cerr<<"No input"<<endl;
			}
			continue;
		}
		else if (opcode=='q')
		{
			totaltime.recordTime();
			total_time=totaltime.getTime();
//			cout<<total_time<<" "<<merge_time<<" "<<intersection_time<<" "<<unique_time<<" "<<union_time<<" "<<diff_time<<" "<<sort_time<<endl;
			if (t==1)
			{
				timeprint();
			}
			exit(0);
		}
		else
		{
			cerr<<"Unvalid instruction"<<endl;
		}

//	exit(1);
	}


//	cout<<my_union(data[0],data[2])<<endl;
//	cout<<stl_union(data[0],data[2])<<endl;


//	cout<<my_diff(data[1],data[2])<<endl;
//	cout<<stl_diff(data[1],data[2])<<endl;





/*
	//merge is for the g command
	vector<string> merge_result=data[0];
	for(int i=1;i<data.size();i++)
	{
//		merge_result=my_merge(merge_result,data[i]);
		merge_result=stl_merge(merge_result,data[i]);

	}
//	for(int i=0;i<merge_result.size();i++)
//	{
//		cout<<merge_result[i]<<endl;
//	}

	

	//g THRESHOLD operation
	int num_submission=data.size();
	vector<g_line> result=g_get(merge_result,num_submission,5);
	sort(result.begin(),result.end(),g_comp);
	for(int i=0;i<result.size();i++)
	{
		cout<<result[i].percent<<"% "<<result[i].line<<endl;
	}
//	g_out(result);
*/


	//s threshold operation
//	vector<s_name> result=my_s_get(data,0);
//	vector<s_name> result=stl_s_get(data,0);	
	
//	sort(result.begin(),result.end(),s_comp);
//	for(int i=0;i<result.size();i++)
//	{
//		cout<<result[i].percent<<"% "<<result[i].name1<<", "<<result[i].name2<<endl;
//	}



/*
	for(int i=0;i<result.size();i++)
	{
		cout<<result[i].line<<" "<<result[i].percent<<endl;
	}
*/




/*
	for(int i=0;i<data.size();i++)
	{
			cout<<data[i][0]<<endl;
	}


*/

/*   

	vector<string> myresult=stl_intersection(data[0],data[1]);
	vector<string> myresult=my_intersection(data[0],data[1]);

	for (int i=0;i<myresult.size();i++)
	{
		cout<<myresult[i]<<endl;
	}
	
*/	

}

pair<int,int> getindex(vector<vector<string> > &data,string &submissions)
{
	pair<int,int> result(-1,-1);
	string name1;
	string name2;
	int idx=submissions.find('|');
	if(idx!=-1)
	{
		name1=submissions.substr(0,idx);
		name2=submissions.substr(idx+1, submissions.length()-idx-1);
	}
	else
	{
		return result;
	}
	for(int i=0;i<data.size();i++)
	{
		if(data[i][0]==name1)
		{
			result.first=i;
		}
		if(data[i][0]==name2)
		{
			result.second=i;
		}
	}
	return result;
}

void timeprint()
{
	int sort_percent=(sort_time*100)/total_time;
	int unique_percent=(unique_time*100)/total_time;
	int intersection_percent=(intersection_time*100)/total_time;
	int union_percent=(union_time*100)/total_time;
	int diff_percent=(diff_time*100)/total_time;
	int merge_percent=(merge_time*100)/total_time;
	int other_percent=100-sort_percent-unique_percent-intersection_percent-union_percent-diff_percent;
	int total_percent=other_percent+sort_percent+unique_percent+intersection_percent+union_percent+diff_percent;
	cout<<"RUNTIME PRINTOUT:"<<endl;
	cout<<"SORT "<<sort_percent<<"% "<<sort_time<<endl;
	cout<<"MERGE "<<merge_percent<<"% "<<merge_time<<endl;
	cout<<"UNIQUE "<<unique_percent<<"% "<<unique_time<<endl;
	cout<<"INTERSECTION "<<intersection_percent<<"% "<<intersection_time<<endl;
	cout<<"UNION "<<union_percent<<"% "<<union_time<<endl;
	cout<<"SET_DIFFERENCE "<<diff_percent<<"% "<<diff_time<<endl;
	cout<<"OTHER "<<other_percent<<"% "<<(total_time-sort_time-unique_time-intersection_time-diff_time)<<endl;
	cout<<"TOTAL "<<total_percent<<"% "<<total_time<<endl;
}

void submis_norm(string &str)
{
	int i;
	for (i=0;i<str.length();i++)
	{
		if(str[i]!=' ')
		{
			break;
		}
		
	}
	str.erase(0,i);
	for(i=str.length()-1;i>=0;i--)
	{
		if(str[i]!=' ')
		{
			break;
		}
	}
	str.erase(i+1,str.length()-i-1);
}


void PrintManual()
{
	cout<<"NAME"<<endl;
	cout<<"    cheatcheck - detect duplicate content in submissions for potential cheating"<<endl;
	cout<<"SYNOPSIS"<<endl;
	cout<<"    cheatcheck --mode|-m MODE [OPTION]... [FILE]"<<endl;
	cout<<"DESCRIPTION"<<endl;
	cout<<"    Compute intersections of submission contents. Program will output certain"<<endl;
	cout<<"    statistics regarding the submission contents on user command. Mandatory"<<endl;
	cout<<"    arguments to long options are mandatory for short options too."<<endl;
	cout<<"OPTIONS"<<endl;
	cout<<"    -a, --algorithm ALGORITHM"<<endl;
	cout<<"        sort using specified ALGORITHM; must be one of STL, SELF, or FASTEST."<<endl;
	cout<<"        Value is SELF if the --algorithm option is not specified."<<endl;
	cout<<"    -m, --mode MODE"<<endl;
	cout<<"        parse file based on MODE; must be one of DOCUMENT or CODE."<<endl;
	cout<<"    -r, --report"<<endl;
	cout<<"        run s THRESHOLD and g THRESHOLD from STATISTICS RETRIEVAL ACTIONS and"<<endl;
	cout<<"        quit. Default values for both THRESHOLDs is 50%."<<endl;
	cout<<"    -t, --timing"<<endl;
	cout<<"        print out a timing report just before the program terminates."<<endl;
	cout<<"    -h, --help"<<endl;
	cout<<"        display this man page and exit"<<endl;
	cout<<"STATISTICS RETRIEVAL ACTIONS"<<endl;
	cout<<"    s THRESHOLD"<<endl;
	cout<<"        print submissions with similarity score greater or equal to THRESHOLD"<<endl;
	cout<<"    i SUBMISSION1|SUBMISSION2"<<endl;
	cout<<"        print number of CONTENT LINEs that appear in both SUBMISSION1 and"<<endl;
	cout<<"        SUBMISSION2"<<endl;
	cout<<"    u SUBMISSION1|SUBMISSION2"<<endl;
	cout<<"        print the number of CONTENT LINEs that appear in either SUBMISSION1 or"<<endl;
	cout<<"        SUBMISSION2 or both"<<endl;
	cout<<"    d SUBMISSION1|SUBMISSION2"<<endl;
	cout<<"        print number of CONTENT LINEs that appear in SUBMISSION1 but not in"<<endl;
	cout<<"        SUBMISSION2"<<endl;
	cout<<"    g THRESHOLD"<<endl;
	cout<<"        print all CONTENT LINEs that appear in THRESHOLD or more submissions"<<endl;
	cout<<"        across the entire set of submissions"<<endl;
	cout<<"    q quit"<<endl;

}

