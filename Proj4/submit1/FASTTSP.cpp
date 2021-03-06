#include <iostream>
#include <vector>
#include <stdlib.h>
#include "headfile.h"

using namespace std;

void FASTTSP(vector<point> &data, int cakenumber)
{
	vector<int> result;
	int distancesum = 0;
	int currentvertex = 0;
	data[0].isinset = 1;
	result.push_back(0);
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
		result.push_back(nextvertex);
		currentvertex = nextvertex;
		data[currentvertex].isinset = 1;
		distancesum = distancesum + leastdistance;
//		cout << "The current distancesum is : " << distancesum << endl;
	}
	distancesum = distancesum + abs(data[currentvertex].x - data[0].x) + abs(data[currentvertex].y - data[0].y);
	cout << distancesum << endl;
	for(int i = 0; i< cakenumber-1; i++)
	{
		cout << result[i] << " ";
	}
	cout << result[cakenumber-1] << endl;

}
