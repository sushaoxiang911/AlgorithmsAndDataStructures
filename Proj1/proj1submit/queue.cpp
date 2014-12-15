#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include <vector>
#include <queue>
#include "function.h"

using namespace std;

void queuescheme(queue<point> &Myqueue,vector<point> &building,int &end,int start,int len)
{
	Myqueue.push(building[start]);
	while(1)
	{
		point Ptemp;
		Ptemp=Myqueue.front();
		Myqueue.pop();

		//north
		if (Ptemp.location%(len*len)/len!=0)
		{
			if (building[Ptemp.location-len].sign=='P'||building[Ptemp.location-len].sign=='H')
			{
				end=Ptemp.location-len;
				building[Ptemp.location-len].origin=1;
				break;
			}
			if ((building[Ptemp.location-len].sign=='.'||building[Ptemp.location-len].sign=='^'||building[Ptemp.location-len].sign=='v')&&building[Ptemp.location-len].origin==0)
			{
				Myqueue.push(building[Ptemp.location-len]);
				building[Ptemp.location-len].origin=1;
//				cout<<"1"<<endl;
			}
			
		}
		
		
		//east
		if(Ptemp.location%len!=(len-1))
		{
			if (building[Ptemp.location+1].sign=='P'||building[Ptemp.location+1].sign=='H')
			{
				end=Ptemp.location+1;
				building[Ptemp.location+1].origin=2;
				break;
			}
			if ((building[Ptemp.location+1].sign=='.'||building[Ptemp.location+1].sign=='^'||building[Ptemp.location+1].sign=='v')&&building[Ptemp.location+1].origin==0)
			{
				Myqueue.push(building[Ptemp.location+1]);
				building[Ptemp.location+1].origin=2;
//				cout<<"2"<<endl;
			}
			
		}
		

		//south
		if(Ptemp.location%(len*len)/len!=(len-1))
		{
			if (building[Ptemp.location+len].sign=='P'||building[Ptemp.location+len].sign=='H')
			{
				end=Ptemp.location+len;
				building[Ptemp.location+len].origin=3;
				break;
			}
			if ((building[Ptemp.location+len].sign=='.'||building[Ptemp.location+len].sign=='^'||building[Ptemp.location+len].sign=='v')&&building[Ptemp.location+len].origin==0)
			{
				Myqueue.push(building[Ptemp.location+len]);
				building[Ptemp.location+len].origin=3;
//				cout<<"3"<<endl;
			}
			
		}
				

		//west
		if(Ptemp.location%len!=0)
		{
			if (building[Ptemp.location-1].sign=='P'||building[Ptemp.location-1].sign=='H')
			{
				end=Ptemp.location-1;
				building[Ptemp.location-1].origin=4;
				break;
			}
			if ((building[Ptemp.location-1].sign=='.'||building[Ptemp.location-1].sign=='^'||building[Ptemp.location-1].sign=='v')&&building[Ptemp.location-1].origin==0)
			{
				Myqueue.push(building[Ptemp.location-1]);
				building[Ptemp.location-1].origin=4;
//				cout<<"4"<<endl;
			}
			
		}	
		
			
		//upstairs
		if(Ptemp.sign=='^')
		{
			if (building[Ptemp.location-len*len].sign=='P'||building[Ptemp.location-len*len].sign=='H')
			{
				end=Ptemp.location-len*len;
				building[Ptemp.location-len*len].origin=5;
				break;
			}
			if ((building[Ptemp.location-len*len].sign=='.'||building[Ptemp.location-len*len].sign=='^'||building[Ptemp.location-len*len].sign=='v')&&building[Ptemp.location-len*len].origin==0)
			{
				Myqueue.push(building[Ptemp.location-len*len]);
				building[Ptemp.location-len*len].origin=5;
//				cout<<"5"<<endl;
			}
		
		}
		

		//downstairs
		if(Ptemp.sign=='v')
		{
			if (building[Ptemp.location+len*len].sign=='P'||building[Ptemp.location+len*len].sign=='H')
			{
				end=Ptemp.location+len*len;
				building[Ptemp.location+len*len].origin=6;
				break;
			}
			if ((building[Ptemp.location+len*len].sign=='.'||building[Ptemp.location+len*len].sign=='^'||building[Ptemp.location+len*len].sign=='v')&&building[Ptemp.location+len*len].origin==0)
			{
				Myqueue.push(building[Ptemp.location+len*len]);
				building[Ptemp.location+len*len].origin=6;
//				cout<<"6"<<endl;
			}
			
		}
		
	}
}

