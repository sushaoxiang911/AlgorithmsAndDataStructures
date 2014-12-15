#include <iostream>
#include <vector>
#include <stdlib.h>
#include "headfile.h"
#include <time.h>

using namespace std;

void FASTTSP (vector<point> &data, int cakenumber, int** matrix, vector<int> &Minimum, vector<int> &SecondMinimum, clock_t start)
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
	int curCost = 0;
	int Promissing = 0;
	for(int i = 0; i < cakenumber; i++)
	{
		Promissing = Promissing + Minimum[i] + SecondMinimum[i];
	}
	
	int count = 0;
	FASTTSP_helper(q,s,curMin,curPath, matrix, Minimum, SecondMinimum, Promissing, start, count);
	
	
	cout << curMin << endl;
	cout << "0" << " ";
	for(int i = 0; i < curPath.size() - 1; i++)
	{
		cout << curPath[i] << " ";
	}
	cout << curPath[curPath.size()-1] << endl;
	
	
}


void FASTTSP_helper(deque<int> &q, deque<int> &s, int &curMin, deque<int> &curPath, int **matrix, vector<int> &Minimum, vector<int> &SecondMinimum, int Promissing, clock_t start, int &count)
{
	count++;
	if(count%10000000 == 0)
	{
		count = 0;
		clock_t end = clock();
		double interval = (end - start)/CLOCKS_PER_SEC;
		if(interval >= 25)
		{
			cout << curMin << endl;
			cout << "0" << " ";
			for(int i = 0; i < curPath.size() - 1; i++)
			{
				cout << curPath[i] << " ";
			}
			cout << curPath[curPath.size()-1] << endl;
			exit(0);
		}
	}
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

			
		
		FASTTSP_helper(q, s, curMin, curPath, matrix, Minimum, SecondMinimum, Promissing, start, count);
		
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



