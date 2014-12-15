#include <iostream>
#include <fstream>
#include "stdlib.h"
#include "time.h"
#define CAKENUMBER 40
#define SIZE 10000

using namespace std;
	

int main()
{
	cout << SIZE << endl;
	cout << CAKENUMBER << endl;
	srand(time(NULL));
	for (int i = 0; i < CAKENUMBER; i++)
	{
		cout << (rand() + 2234124)%100 << " " << (rand() + 2301374)%100 << endl;
	}
}
