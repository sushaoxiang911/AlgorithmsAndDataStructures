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

bool stackscheme(stack<point> &Mystack,vector<point> &building,int &end,int start,int len)
{
	building[start].origin=7;
	Mystack.push(building[start]);
	while(!Mystack.empty())
	{
		point Ptemp;
		Ptemp=Mystack.top();
		
//		cout<<Mystack.top().location<<endl;
		Mystack.pop();

		if (Ptemp.sign=='.'||Ptemp.sign=='S')//!!!!
		{
		//north
		if (Ptemp.location%(len*len)/len!=0)
		{
			if (building[Ptemp.location-len].sign=='P'||building[Ptemp.location-len].sign=='H')
			{
				end=Ptemp.location-len;
				building[Ptemp.location-len].origin=1;
				return 1;
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
				return 1;
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
				return 1;
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
				return 1;
			}
			if ((building[Ptemp.location-1].sign=='.'||building[Ptemp.location-1].sign=='^'||building[Ptemp.location-1].sign=='v')&&building[Ptemp.location-1].origin==0)
			{
				Mystack.push(building[Ptemp.location-1]);
				building[Ptemp.location-1].origin=4;
			}
			
		}	
		
		}	
		//upstairs
		else if(Ptemp.sign=='^')
		{
			if(Ptemp.location-len*len>=0)//!!!!!!!
			{
			if (building[Ptemp.location-len*len].sign=='P'||building[Ptemp.location-len*len].sign=='H')
			{
				end=Ptemp.location-len*len;
				building[Ptemp.location-len*len].origin=5;
				return 1;
			}
			if ((building[Ptemp.location-len*len].sign=='.'||building[Ptemp.location-len*len].sign=='^'||building[Ptemp.location-len*len].sign=='v')&&building[Ptemp.location-len*len].origin==0)
			{
				Mystack.push(building[Ptemp.location-len*len]);
				building[Ptemp.location-len*len].origin=5;
			}
			}
		
		}
		

		//downstairs
		else
		{
			if(Ptemp.location+len*len<building.size())//!!!!!!!
			{
			if (building[Ptemp.location+len*len].sign=='P'||building[Ptemp.location+len*len].sign=='H')
			{
				end=Ptemp.location+len*len;
				building[Ptemp.location+len*len].origin=6;
				return 1;
			}
			if ((building[Ptemp.location+len*len].sign=='.'||building[Ptemp.location+len*len].sign=='^'||building[Ptemp.location+len*len].sign=='v')&&building[Ptemp.location+len*len].origin==0)
			{
				Mystack.push(building[Ptemp.location+len*len]);
				building[Ptemp.location+len*len].origin=6;
			}
			}
			
		}
		
	}
	return 0;
}
