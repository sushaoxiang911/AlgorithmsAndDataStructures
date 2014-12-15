#include <iostream>
#include <queue>
#include <algorithm> 
#include "headfile2.h"

using namespace std;


void OPTTSP2 (int cakenumber, int **matrix, vector<int> &Minimum)
{
	priority_queue<node, vector<node>, comp> nodequeue;
	int MinSum = 0;
	for(int i = 0; i < cakenumber; i++)
	{
		MinSum = MinSum + Minimum[i];
	}
	int bestc = -1;
	node root(cakenumber, 0, MinSum, 0);
	nodequeue.push(root);
	while(nodequeue.top().s != cakenumber-1)
	{	
//		cout << bestc << endl;
//		cout << nodequeue.top().s << endl;
		if(nodequeue.top().s == cakenumber-2)
		{
			cout << "a" << endl;
			node tempnode = nodequeue.top();
			int c = tempnode.cc + matrix[tempnode.path[cakenumber-1]][tempnode.path[cakenumber-2]] + matrix[0][tempnode.path[cakenumber-1]];
			if(bestc ==-1 || c < bestc)
			{
				bestc = c;
				tempnode.s++;
				tempnode.cc = c;
				nodequeue.push(tempnode);
			}
			nodequeue.pop();
		}
		else 
		{
			node tempnode = nodequeue.top();
			cout << tempnode.cc << endl;
			for(int i = tempnode.s+1; i < cakenumber; i++)
			{
				tempnode.cc = tempnode.cc + matrix[tempnode.path[tempnode.s]][tempnode.path[i]];
				tempnode.lcost = tempnode.lcost - Minimum[tempnode.path[tempnode.s]];
				if(tempnode.cc + tempnode.lcost < bestc || bestc == -1)
				{
					tempnode.s++;
					int temp = tempnode.path[tempnode.s];
					tempnode.path[tempnode.s] = tempnode.path[i];
					tempnode.path[i] = temp;
					nodequeue.push(tempnode);
				}
			}
			nodequeue.pop();
		}
	}
	cout << bestc << endl;
	for (int i = 0; i < cakenumber; i++)
	{
		cout << nodequeue.top().path[i] << endl;
	}
}








