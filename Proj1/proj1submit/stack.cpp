#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include <vector>
#include <stack>
#include "function.h"

using namespace std;

void stackscheme(stack<point> &Mystack,vector<point> &building,int &end,int start,int len)
{
	Mystack.push(building[start]);
	while(1)
	{
		point Ptemp;
		Ptemp=Mystack.top();
		
//		cout<<Mystack.top().sign<<endl;
		Mystack.pop();
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
				Mystack.push(building[Ptemp.location-len]);
				building[Ptemp.location-len].origin=1;
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
				Mystack.push(building[Ptemp.location+1]);
				building[Ptemp.location+1].origin=2;
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
				Mystack.push(building[Ptemp.location+len]);
				building[Ptemp.location+len].origin=3;
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
				Mystack.push(building[Ptemp.location-1]);
				building[Ptemp.location-1].origin=4;
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
				Mystack.push(building[Ptemp.location-len*len]);
				building[Ptemp.location-len*len].origin=5;
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
				Mystack.push(building[Ptemp.location+len*len]);
				building[Ptemp.location+len*len].origin=6;
			}
			
		}
		
	}
}
