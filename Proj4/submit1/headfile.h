#include <iostream>
#include <vector>

using namespace std;

struct point
{
	int x;
	int y;
	int leastdistance;
	bool isinset;
	int target;
};

void getMST(vector<point> &data, int cakenumber);

void FASTTSP(vector<point> &data, int cakenumber);
