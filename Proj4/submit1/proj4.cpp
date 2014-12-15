/*
	11/27	Using Prim to do the part one.
		Graph structure:the vertices(coordinates)
				the smallest distance from the points out of the set to the constructed tree
				if it is in the set
		Everytime compare the all the small edges, choosing the smallest one. Put it into the set and 
		renew every small edge(compare)
		Cin 	
		
	12/03	Using greedy to do the part three.
		three methods:
			Everytime find the minimize distance and put it into the set, until all the points are in set
			Using MST in first part, preorder it
			Using Kruskal to solve, two check conditions: No loop before final state, no branch
		
*/

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <fstream>
#include <getopt.h>
#include <algorithm>
#include <utility>
#include "headfile.h"

using namespace std;

char *MODE;
int mode;
struct option longopts[]={
{"mode",required_argument,NULL,'m'},
{"help",no_argument,NULL,'h'},
{0,0,0,0},
};

int main(int argc,char *argv[])
{
	bool algor_choice;
	opterr=0;
	int c;
	while((c=getopt_long(argc,argv,":a:m:rht",longopts,NULL))!=-1)
	{
		switch(c){
		case 0:
		break;
		case 'm':
		MODE=optarg;
		if(strcmp(MODE,"MST")&&strcmp(MODE,"OPTTSP")&&strcmp(MODE,"FASTTSP"))
		{
			cerr<<"Unvalid mode"<<endl;
			exit(1);
		}
		mode=1;
		break;
		case 'h':
		exit(0);
		break;
		case ':':
		cerr<<"Undefine argument"<<endl;
		exit(1);
		case '?':
		cerr<<"Unrecognized option"<<endl;
		exit(1);
		
		}
	}
	if(mode==0)
	{
		cerr<<"No specific mode"<<endl;
		exit(1);
	}
	


/**************************** Part A *************************************/

	if(!strcmp(MODE,"MST"))
	{	
		int sidelength;
		int cakenumber;
		cin >> sidelength >> cakenumber;
		vector<point> cakepoint (cakenumber);
		for (int i=0;i<cakenumber;i++)
		{
			cin >> cakepoint[i].x >> cakepoint[i].y ;
			cakepoint[i].leastdistance = -1;
			cakepoint[i].isinset = 0;
		}
		getMST(cakepoint, cakenumber);
		exit(0);
	}

/*************************** Part B ****************************************/



/*************************** Part C ****************************************/

	if(!strcmp(MODE,"FASTTSP"))
	{
		int sidelength;
		int cakenumber;
		cin >> sidelength >> cakenumber;
		vector<point> cakepoint (cakenumber);
		for (int i=0;i<cakenumber;i++)
		{
			cin >> cakepoint[i].x >> cakepoint[i].y ;
			cakepoint[i].leastdistance = -1;
			cakepoint[i].isinset = 0;
		}
		FASTTSP(cakepoint, cakenumber);
		exit(0);
	}


/************************** test panel *****************************************/
/*	
	for (int i=0;i<cakenumber;i++)
	{
		cout << " x coordinate: " << cakepoint[i].x << " y coordinate: " << 
		cakepoint[i].y << " leastdistance: " << cakepoint[i].leastdistance << " isinset: " << cakepoint[i].isinset << endl;  
	}


*/
	return 0;
}
