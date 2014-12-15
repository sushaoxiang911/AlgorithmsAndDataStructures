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
	}
	curMin = distancesum + abs(data[currentvertex].x - data[0].x) + abs(data[currentvertex].y - data[0].y);
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
		return;
	}
	if(q.empty())
	{
		Promissing = Promissing - Minimum[s[s.size()-1]] - SecondMinimum[0] +  2 * matrix[s[s.size()-1]][0];		
		
		if(Promissing/2 < curMin)
		{
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
		int c = s.size();	
		if(c >= 3)
		{
			int path1 = matrix[s[c-3]][s[c-2]] + matrix[s[c-1]][q[0]];
			int path2 = matrix[s[c-3]][s[c-1]] + matrix[q[0]][s[c-2]];
			if(path1 > path2)
			{
				q.push_back(q.front());
				q.pop_front();
				continue;
			}
		}
		s.push_back(q[0]);
		q.pop_front();
		
		
		if(s.size() == 1)
		{
			Promissing = Promissing - Minimum[0] - SecondMinimum[s[s.size()-1]] + 2 * matrix[s[s.size()-1]][0];
		}
		else
		{
			Promissing = Promissing - Minimum[s[s.size()-2]] - SecondMinimum[s[s.size()-1]] + 2 * matrix[s[s.size()-1]][s[s.size()-2]];
		}

		
		OPTTSP_helper(q, s, curMin, curPath, matrix, Minimum, SecondMinimum, Promissing);
		
		if(s.size() == 1)
		{
			Promissing = Promissing + Minimum[0] + SecondMinimum[s[0]] - 2 * matrix[s[0]][0];
		}
		else
		{
			Promissing = Promissing + Minimum[s[s.size()-2]] + SecondMinimum[s[s.size()-1]] - 2 * matrix[s[s.size()-1]][s[s.size()-2]];
		}
		q.push_back(s[s.size()-1]);
		s.pop_back();
	}
}







