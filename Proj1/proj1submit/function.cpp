#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include "function.h"
using namespace std;




int sizeGet(int len,int flo)
{
	return len*len*flo;
}

void initbuilding(vector<point> &building,char format,int size,int& start,int len,int flo)
{
	if (format=='M')
	{
		string temp;
		int j=len;
/*		for(int i=0;i<size;i++)
		{
			
			if(cin.peek()=='\n')
			{
				if(j!=len)
				{
					cout<<"Not valid input"<<endl;
					exit(1);
				}

				
			}
			
			if(!cin.eof())
			{
				if(j==len)
				{
					while(cin.peek()!='\n')
					{
						cin.ignore();
					}
					cin.ignore();
					j=0;
				}
				ignorecomm();
				building[i].sign=cin.get();
			}
			else
			{
				cout<<"Not completed map"<<endl;
				exit(1);
			}
			if(building[i].sign=='S')
				start=i;
			j++;
			cout<<building[i].sign<<endl;
		}*/
		for(int i=0;i<size;i++)
		{
			if(j==len)
			{
				if(!getline(cin,temp))
				{
					cout<<"invalid size"<<endl;
					exit(1);
				}
				else
				{
					while(temp[0]=='#')
					{
						if(!getline(cin,temp))
						{
							cout<<"invalid size"<<endl;
							exit(1);
						}
					}
					if(temp.size()<len)
					{
						cout<<"invalid length"<<endl;
						exit(1);
					}

				}
				j=0;
			}
			if(temp[j]!='W'&&temp[j]!='.'&&temp[j]!='S'&&temp[j]!='H'&&temp[j]!='P'&&temp[j]!='^'&&temp[j]!='v')
			{
				cout<<"ilegal sign"<<endl;
				exit(1);
			}
			building[i].sign=temp[j];
			if(building[i].sign=='S')
				start=i;
			j++;
		}
/*		for(int i=0;i<size;i++)
		{
			cout<<building[i].sign<<endl;
		}*/
	}
	else if (format=='C')
	{
		int row;
		int col;
		int f;
		char sig;
		while(cin.peek()!=-1)
		{
			ignorecomm();
			if(cin.get()!='(')
			{
				cerr<<"Invalid inputs"<<endl;
				exit(1);
			}
			else
			{
				cin>>row;
				if(cin.peek()!=',')
				{
					cout<<"invalid separator"<<endl;
					exit(1);
				}
				cin.ignore();
				cin>>col;
				if(cin.peek()!=',')
				{
					cout<<"invalid separator"<<endl;
					exit(1);
				}
				cin.ignore();
				cin>>f;
				if(cin.peek()!=',')
				{
					cout<<"invalid separator"<<endl;
					exit(1);
				}
				cin.ignore();
				cin>>sig;
				if(cin.get()!=')')
				{
					cout<<"Invalid input"<<endl;
					exit(1);
				}
			}
			while(cin.peek()!='\n')
			{
				cin.ignore();
			}
			cin.ignore();
//			cout<<x<<y<<f<<sig<<endl;

			if(row<0||row>=len||col<0||col>=len||f<0||f>=flo||(sig!='W'&&sig!='.'&&sig!='S'&&sig!='H'&&sig!='P'&&sig!='^'&&sig!='v'))
			{
				cout<<"Invalid sign&number"<<endl;
				exit(1);
			}
			building[convtovec(row,col,f,len,flo)].sign=sig;
			if(sig=='S')
			{
				start=convtovec(row,col,f,len,flo);
			}
		}
	}
//	cout<<building[convtovec(1,7,2,len,flo)].sign<<endl;
}

int convtovec(int row,int col,int floorNum,int len,int flo)
{
	return len*len*(flo-1-floorNum)+row*len+col; 
}

void ignorecomm()
{
	while(cin.peek()=='#')
	{
		while(cin.peek()!='\n')
		{
			cin.ignore();
		}
		cin.ignore();
	}
}
