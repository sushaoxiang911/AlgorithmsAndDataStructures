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

void queuescheme(queue<point>&,vector<point>&,int&,int,int);
void stackscheme(stack<point>&,vector<point>&,int&,int,int);


int main(int argc,char* argv[])
{

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
		cout<<"Illegal option"<<endl;
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
		building[i].location=i;
	initbuilding(building,format,size,start,len,flo);	


	//stack
	if (do_stack==1)
	{
		stack<point> Mystack;
		stackscheme(Mystack,building,end,start,len);
	}	
	else
	{
		queue<point> Myqueue;
		queuescheme(Myqueue,building,end,start,len);
	}
	stack<point>path;
	point temp=building[end];
	while(1)
	{
		if (temp.origin==0)
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
	cout<<len<<endl;
	cout<<flo<<endl;
	if (!strcmp(l_opt_arg,"C"))
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
				if (j%8==7)
				{
					cout<<endl;
				}
			}
		}
	}

	
	
	return 0;
}


