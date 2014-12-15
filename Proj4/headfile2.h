#include <iostream>

using namespace std;

class node
{
	public:
		int cc;
		vector<int> path;
		int lcost;
		int s;
		node(int cakenumber, int a, int b, int c)
		{
			cc = a;
			for (int i = 0; i < cakenumber; i++)
			{
				path.push_back(i);
			}
			lcost = b;
			s = c;
		}
};

class comp
{
	public:
		bool operator()(node &node1, node &node2)
		{
			return node1.cc < node2.cc;
		}
};

void OPTTSP2 (int cakenumber, int **matrix, vector<int> &Minimum);

struct temppoint
{
	int value;
	int vertex;
};

class cmp
{
	public:
		bool operator()(temppoint &point1,temppoint &point2)
		{
			return point1.value < point2.value;
		}
		
};



