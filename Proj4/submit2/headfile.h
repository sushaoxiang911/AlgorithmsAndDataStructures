#include <iostream>
#include <vector>
#include <deque>

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

void OPTTSP_firstMin(vector<point> &data, int cakenumber, int &curMin, deque<int> &curPath);

void OPTTSP_helper(deque<int> &q, deque<int> &s, int &curMin, deque<int> &curPath, int **matrix, vector<int> &Minimum, vector<int> &SecondMinimum, int Promissing);

void OPTTSP (vector<point> &data, int cakenumber, int **matrix, vector<int> &Minimum, vector<int> &SecondMinimum);
