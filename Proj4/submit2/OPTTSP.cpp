#include <iostream>
#include <vector>
#include <stdlib.h>
#include "headfile.h"
#include <deque>

using namespace std;


void OPTTSP_firstMin(vector<point> &data, int cakenumber, int &curMin, deque<int> &curPath)
{
	int distancesum = 0;
	int currentvertex = 0;
	data[0].isinset = 1;
	for(int i = 0; i < cakenumber - 1; i++)
	{	
		int leastdistance = -1;
		int nextvertex = 0;
		for(int j = 0; j < cakenumber; j++)
		{
			if(data[j].isinset == 0)
			{
				int distance = abs(data[currentvertex].x - data[j].x) + abs(data[currentvertex].y - data[j].y);
				if(leastdistance == -1)
				{
					leastdistance = distance;
					nextvertex = j;
				}
				if(distance < leastdistance)
				{
					leastdistance = distance;
					nextvertex = j;
				}
			}
			
		}
		curPath.push_back(nextvertex);
		currentvertex = nextvertex;
		data[currentvertex].isinset = 1;
		distancesum = distancesum + leastdistance;
//		cout << "The current distancesum is : " << distancesum << endl;
	}
	curMin = distancesum + abs(data[currentvertex].x - data[0].x) + abs(data[currentvertex].y - data[0].y);
//	cout << distancesum << endl;
}

void OPTTSP (vector<point> &data, int cakenumber, int** matrix, vector<int> &Minimum, vector<int> &SecondMinimum)
{
	int curMin;
	deque<int> curPath;
	OPTTSP_firstMin(data, cakenumber, curMin, curPath);	
	
	deque<int> s;
	deque<int> q;
	for(int i = 1; i < cakenumber; i++)
	{
		q.push_back(i);
	}
//	int curVertex = 0;
	int curCost = 0;
	
//	cout << curMin << endl;
//	for (int i = 0; i < curPath.size(); i++)
//	{
//		cout << curPath[i] << endl;
//	}
//	for (int i = 0; i < q.size(); i++)
//	{
//		cout << q[i] << endl;
//	}
	
	int Promissing = 0;
	for(int i = 0; i < cakenumber; i++)
	{
		Promissing = Promissing + Minimum[i] + SecondMinimum[i];
	}
	
	OPTTSP_helper(q,s,curMin,curPath, matrix, Minimum, SecondMinimum, Promissing);
	
	
	cout << curMin << endl;
	cout << "0" << " ";
	for(int i = 0; i < curPath.size() - 1; i++)
	{
		cout << curPath[i] << " ";
	}
	cout << curPath[curPath.size()-1] << endl;
	
	
}

void OPTTSP_helper(deque<int> &q, deque<int> &s, int &curMin, deque<int> &curPath, int **matrix, vector<int> &Minimum, vector<int> &SecondMinimum, int Promissing)
{
	unsigned k, size = q.size();
	if(Promissing/2 >= curMin)
	{
//		cout << "Current Min is: " << curMin << endl;
		return;
	}
	if(q.empty())
	{
		for(int i = 0;i < s.size();i++)
		{
//			cout << s[i];
		}
//		cout << endl;
//		cout << "a" << endl;
//		curCost = curCost + abs(data[s[s.size()-1]].x - data[0].x) + 
//		abs(data[s[s.size()-1]].y - data[0].y);
		Promissing = Promissing - Minimum[s[s.size()-1]] - SecondMinimum[0] +  2 * matrix[s[s.size()-1]][0];		
		
		if(Promissing/2 < curMin)
		{
//			cout << "a" << endl;
			curMin = Promissing/2;
			for(int i=0;i < s.size();i++)
			{
				curPath[i] = s[i];
			}
		}
		return;
	}
	for(k = 0; k != size; k++)
	{
//		cout << "a" << endl;
		s.push_back(q[0]);
		q.pop_front();
		
//		cout << curVertex << endl;
		
		if(s.size() == 1)
		{
//			curCost = curCost + abs(data[s[s.size()-1]].x-data[0].x)
//				+ abs(data[s[s.size()-1]].y-data[0].y);
			Promissing = Promissing - Minimum[0] - SecondMinimum[s[s.size()-1]] + 2 * matrix[s[s.size()-1]][0];
		}
		else
		{
//			curCost = curCost + abs(data[s[s.size()-1]].x-data[s[s.size()-2]].x)
//				+ abs(data[s[s.size()-1]].y-data[s[s.size()-2]].y);
			Promissing = Promissing - Minimum[s[s.size()-2]] - SecondMinimum[s[s.size()-1]] + 2 * matrix[s[s.size()-1]][s[s.size()-2]];
		}

//		cout << curCost << endl;
			
//		curVertex = s[s.size()-1];
//		cout << "current path size: " << s.size() << "  The last vertex:  " << curVertex << endl;
		
		OPTTSP_helper(q, s, curMin, curPath, matrix, Minimum, SecondMinimum, Promissing);
		
		if(s.size() == 1)
		{
			Promissing = Promissing + Minimum[0] + SecondMinimum[s[0]] - 2 * matrix[s[0]][0];
		}
		else
		{
//			curCost = curCost - (abs(data[s[s.size()-1]].x-data[s[s.size()-2]].x)
//				+ abs(data[s[s.size()-1]].y-data[s[s.size()-2]].y));
			Promissing = Promissing + Minimum[s[s.size()-2]] + SecondMinimum[s[s.size()-1]] - 2 * matrix[s[s.size()-1]][s[s.size()-2]];
		}
		q.push_back(s[s.size()-1]);
		s.pop_back();
	}
}








