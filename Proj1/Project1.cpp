#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include "function.h"
#include <getopt.h>

using namespace std;

bool queuescheme(queue<point>&,vector<point>&,int&,int,int);
bool stackscheme(stack<point>&,vector<point>&,int&,int,int);

char *l_opt_arg;
int do_stack,do_queue;
struct option longopts[]={
{"stack",no_argument,&do_stack,1},
{"queue",no_argument,&do_queue,1},
{"output",required_argument,NULL,'o'},
{"help",no_argument,NULL,'h'},
{0,0,0,0},
};
int main(int argc,char* argv[])
{
	
	bool path_found;
	int c;
	while((c=getopt_long(argc,argv,"sqo:h",longopts,NULL))!=-1)
	{
		switch(c){
		case 0:
		break;
		case 's':
		do_stack=1;
		break;
		case 'q':
		do_queue=1;
		break;
		case 'o':
		l_opt_arg=optarg;
		break;
		case 'h':
		cout<<"help information:"<<endl;
		cout<<"--stack, or -s: Use the stack-based routing scheme"<<endl;
		cout<<"--queue, or -q: Use the queue-based routing scheme"<<endl;
		cout<<"--output [M|C], or -o [M|C]: Indicate the output file format, where M means map format, C means coordinates format"<<endl;
		cout<<"--help, or -h: Print help manual"<<endl;
		exit(0);
		break;
		
		}
	}
	if ((do_stack==1&&do_queue==1)||(do_stack==0&&do_queue==0))
	{
		cerr<<"Illegal option"<<endl;
		exit(1);
	}
	char format=cin.get();
	cin.ignore();
	string length;
	getline(cin,length);
	string floor;
	getline(cin,floor);
	int len=atoi(length.c_str());
	int flo=atoi(floor.c_str());
	int size=sizeGet(len,flo);

	struct point ini;
	ini.sign='.';
	ini.origin=0;
	int start;
	int end;

	vector<point> building(size,ini);
	for(int i=0;i<size;i++)
	{
		building[i].location=i;
	}
	initbuilding(building,format,size,start,len,flo);	


	//stack
	if (do_stack==1)
	{
//		cout<<"stack"<<endl;
		stack<point> Mystack;
		path_found=stackscheme(Mystack,building,end,start,len);
	}	
	else
	{
//		cout<<"queue"<<endl;
		queue<point> Myqueue;
		path_found=queuescheme(Myqueue,building,end,start,len);
	}

	stack<point>path;
	if(path_found)
	{
	point temp=building[end];
	while(1)
	{
		if (temp.origin==7)
		{
			break;
		}
		else if (temp.origin==1)
		{
			building[temp.location+len].sign='n';
			temp=building[temp.location+len];
			path.push(temp);
		}
		else if (temp.origin==2)
		{
			building[temp.location-1].sign='e';
			temp=building[temp.location-1];
			path.push(temp);
		}
		else if (temp.origin==3)
		{
			building[temp.location-len].sign='s';
			temp=building[temp.location-len];
			path.push(temp);
		}
		else if (temp.origin==4)
		{
			building[temp.location+1].sign='w';
			temp=building[temp.location+1];
			path.push(temp);
		}
		else if (temp.origin==5)
		{
			building[temp.location+len*len].sign='u';
			temp=building[temp.location+len*len];
			path.push(temp);
		}
		else
		{
			building[temp.location-len*len].sign='d';
			temp=building[temp.location-len*len];
			path.push(temp);
		}
		
	}
	}
	cout<<len<<endl;
	cout<<flo<<endl;
	
	if ((l_opt_arg!=NULL)&&(!strcmp(l_opt_arg,"C")))
	{
	//coordinates solution
		cout<<"#path taken"<<endl;
		while(!path.empty())
		{
			point pt=path.top();
			cout<<"("<<pt.location%(len*len)/len<<","<<pt.location%len<<","<<flo-(pt.location/(len*len))-1<<","<<pt.sign<<")"<<endl;
			path.pop();
		}
	}


	else
	{
		for(int i=0;i<flo;i++)
		{
			cout<<"#floor "<<flo-1-i<<endl;
			for(int j=0;j<len*len;j++)
			{
				cout<<building[i*len*len+j].sign;
				if (j%len==len-1)
				{
					cout<<endl;
				}
			}
		}
	}

	
	return 0;
}


