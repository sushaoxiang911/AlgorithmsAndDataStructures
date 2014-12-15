#include <iostream>
#include <vector>
#include <stdlib.h>
#include "headfile.h"

using namespace std;

void getMST(vector<point> &data, int cakenumber)
{
	data[0].isinset = 1;
	data[0].leastdistance = 0;
	int distancesum = 0;
	int distancetemp = -1;
	int newvertice;
	int newverticetemp;
//	pair <int, int> temp;
//	vector<pair<int, int>> result;
	
	for (int i=1;i<cakenumber;i++)
	{
		data[i].target = 0;
		data[i].leastdistance = abs(data[i].x - data[0].x) + abs(data[i].y - data[0].y);
		if(distancetemp == -1)
		{
			distancetemp = data[i].leastdistance;
			newverticetemp = i;
//			temp.first = 0;
//			temp.second = i;
		}
		if(data[i].leastdistance < distancetemp)
		{
			distancetemp = data[i].leastdistance;
			newverticetemp = i;
//			temp.first = 0;
//			temp.second = i;
		}
	}
	newvertice = newverticetemp;
//	cout << "The new vertice for " << "1" << " is: " << newvertice << endl;
	data[newvertice].isinset = 1;
	distancesum = distancesum + distancetemp;
	
	for(int i=2;i<cakenumber;i++)
	{
		distancetemp = -1;
		for(int j=0;j<cakenumber;j++)
		{
			if(data[j].isinset == 0)
			{
//				cout << "The new vertice is " << newvertice << endl;
//				cout << "The vertice to be changed: " << j << endl;
				int newdistance = abs(data[j].x - data[newvertice].x) + abs(data[j].y - data[newvertice].y);
				if(newdistance < data[j].leastdistance)
				{
					data[j].leastdistance = newdistance;
					data[j].target = newvertice;
//					cout << "The leastdistance for " << j << " change to " << newdistance << endl;
				}
				if(distancetemp == -1)
				{
					distancetemp = data[j].leastdistance;
					newverticetemp = j;
				}
				if(data[j].leastdistance < distancetemp)
				{
					distancetemp = data[j].leastdistance;
					newverticetemp = j;
				}
				
			}
			
		}
		newvertice = newverticetemp;
//		cout << "The new vertice for " << i << " is: " << newvertice << endl;
		data[newvertice].isinset = 1;
		distancesum = distancesum + distancetemp;
	}
	cout << distancesum << endl;
	for(int i = 1;i < data.size();i++)
	{
		if(data[i].target < i)
		{
			cout << data[i].target << " " << i <<endl;
		}
		else
		{
			cout << i << " " << data[i].target << endl;
		}
	}
}
