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
			
	12/05	All done. 
		Using Depth first search to make Part B. 
		
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
#include <time.h>

using namespace std;



char *MODE;
int mode;
struct option longopts[]={
{"mode",required_argument,NULL,'m'},
{"help",no_argument,NULL,'h'},
{0,0,0,0},
};
void ManualPage();
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
		ManualPage();
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
	if(!strcmp(MODE,"OPTTSP"))
	{
		int sidelength;
		int cakenumber;
		cin >> sidelength >> cakenumber;
		int **matrix = new int*[cakenumber];
		for(int i = 0; i<cakenumber; i++)
		{
			matrix[i] = new int[cakenumber]; 
		}
		vector<point> cakepoint (cakenumber);
		for (int i=0;i<cakenumber;i++)
		{
			cin >> cakepoint[i].x >> cakepoint[i].y ;
			cakepoint[i].leastdistance = -1;
			cakepoint[i].isinset = 0;
		}
		for(int i = 0;i < cakenumber; i++)
		{
			matrix[i][i] = -1;
			for (int j = i+1; j < cakenumber; j++)
			{
				matrix[i][j] = abs(cakepoint[i].x - cakepoint[j].x) + abs(cakepoint[i].y - cakepoint[j].y);
				matrix[j][i] = matrix[i][j];
			}
		}
		
	
		vector<int> Minimum(cakenumber);
		vector<int> SecondMinimum(cakenumber);
	
	
		for(int i = 0; i < cakenumber; i++)
		{
			int tempMini = -1;
			int tempSecondMini = -1;
			for(int j = 0; j < cakenumber; j++)
			{
				if(j != i)
				{
					if(tempMini == -1)
					{
						tempMini = matrix[i][j];
						continue;
					}
					if(tempSecondMini == -1 && tempMini !=-1 && tempMini < matrix[i][j])
					{
						tempSecondMini = matrix[i][j];
						continue;
					}
					if(tempSecondMini ==-1 && tempMini !=-1 && tempMini >=matrix[i][j])
					{
						tempSecondMini = tempMini;
						tempMini = matrix[i][j];
						continue;
					}
					if (tempMini >= matrix[i][j])
					{
						tempSecondMini = tempMini;
						tempMini = matrix[i][j];
						continue;
					}
					if(tempMini < matrix[i][j] && tempSecondMini >= matrix[i][j])
					{
						tempSecondMini = matrix[i][j];
						continue;
					}
				}
			}
			Minimum[i] = tempMini;
			SecondMinimum[i] = tempSecondMini;
		
		}
	
	
		OPTTSP(cakepoint, cakenumber, matrix,Minimum, SecondMinimum);
	}


/*************************** Part C ****************************************/

	if(!strcmp(MODE,"FASTTSP"))
	{
		clock_t start = clock();
		int sidelength;
		int cakenumber;
		cin >> sidelength >> cakenumber;
		int **matrix = new int*[cakenumber];
		for(int i = 0; i<cakenumber; i++)
		{
			matrix[i] = new int[cakenumber]; 
		}
		vector<point> cakepoint (cakenumber);
		for (int i=0;i<cakenumber;i++)
		{
			cin >> cakepoint[i].x >> cakepoint[i].y ;
			cakepoint[i].leastdistance = -1;
			cakepoint[i].isinset = 0;
		}
		for(int i = 0;i < cakenumber; i++)
		{
			matrix[i][i] = -1;
			for (int j = i+1; j < cakenumber; j++)
			{
				matrix[i][j] = abs(cakepoint[i].x - cakepoint[j].x) + abs(cakepoint[i].y - cakepoint[j].y);
				matrix[j][i] = matrix[i][j];
			}
		}
		
	
		vector<int> Minimum(cakenumber);
		vector<int> SecondMinimum(cakenumber);
	
	
		for(int i = 0; i < cakenumber; i++)
		{
			int tempMini = -1;
			int tempSecondMini = -1;
			for(int j = 0; j < cakenumber; j++)
			{
				if(j != i)
				{
					if(tempMini == -1)
					{
						tempMini = matrix[i][j];
						continue;
					}
					if(tempSecondMini == -1 && tempMini !=-1 && tempMini < matrix[i][j])
					{
						tempSecondMini = matrix[i][j];
						continue;
					}
					if(tempSecondMini ==-1 && tempMini !=-1 && tempMini >=matrix[i][j])
					{
						tempSecondMini = tempMini;
						tempMini = matrix[i][j];
						continue;
					}
					if (tempMini >= matrix[i][j])
					{
						tempSecondMini = tempMini;
						tempMini = matrix[i][j];
						continue;
					}
					if(tempMini < matrix[i][j] && tempSecondMini >= matrix[i][j])
					{
						tempSecondMini = matrix[i][j];
						continue;
					}
				}
			}
			Minimum[i] = tempMini;
			SecondMinimum[i] = tempSecondMini;
		
		}
	
	
		FASTTSP(cakepoint, cakenumber, matrix,Minimum, SecondMinimum, start);
	}


/************************** test panel *****************************************/
/*	
	for (int i=0;i<cakenumber;i++)
	{
		cout << " x coordinate: " << cakepoint[i].x << " y coordinate: " << 
		cakepoint[i].y << " leastdistance: " << cakepoint[i].leastdistance << " isinset: " << cakepoint[i].isinset << endl;  
	}


*/
/*
	for(int i = 0; i < cakenumber; i++)
	{
		for(int j = 0; j < cakenumber; j++)
		{
			cout << matrix[i][j] << " "; 
		}
		cout << endl;
	}
	for(int i = 0; i < cakenumber; i++)
	{
		cout << Minimum[i] << " " << SecondMinimum[i] << endl;
	}
*/
	return 0;
}


void ManualPage()
{
	cout << "NAME" << endl;
	cout << "      cakequest -a command line 'cake retrieval operations' planning program." << endl;
	cout << "SYNOPSIS" << endl;
	cout << "      cakequest --mode|-m MODE [OPTION] ..." << endl;
	cout << "DESCRIPTION" << endl;
	cout << "      cakequest takes map input from standard input that describes the" << endl;
	cout << "      positions of all the cakes in the world around Kirby. If running" << endl;
	cout << "      in MST mode, it will then produce anMST for the graph in which the" << endl;
	cout << "      vertices are cakes. If running in OPTTSP mode, cakequest will solve" << endl;
	cout << "      the Traveling Salesman Problem by generating a tour that describes" << endl;
	cout << "      how Kirby retrieves all cakes while traveling the minimum possible" << endl;
	cout << "      manhattan distance. If running in FASTTSP mode, cakequest will solve" << endl;
	cout << "      the Traveling Salesman Problem using a heuristic that yields a faster" << endl;
	cout << "      solution than OPTTSP that is close to optimal (the minimum required" << endl;
	cout << "      manhattan distance), but is not required to be perfectly optimal." << endl;
	cout << "OPTIONS" << endl;
	cout << "      -h, --help" << endl;
	cout << "            Print this help screen and exit." << endl;
	cout << "      -m, --mode" << endl;
	cout << "            Required option that states run mode. MODE must be one of MST," << endl;
	cout << "            OPTTSP, or FASTTSP." << endl;  
}
