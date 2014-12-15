#ifndef FUNCTION_H
#define	FUNCTION_H

#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cassert>
#include <iomanip>
#include <vector>
#include <stack>
#include <queue>
#include "function.h"
#include <getopt.h>

using namespace std;

char *l_opt_arg;
int do_stack,do_queue;
struct option longopts[]={
{"stack",no_argument,&do_stack,1},
{"queue",no_argument,&do_queue,1},
{"output",required_argument,NULL,'o'},
{"help",no_argument,NULL,'h'},
{0,0,0,0},
};

struct point
	{
		char sign;
		int origin;
		int location; 
	};
//	A STRUCTURE ABOUT THE STATES AND THE SIGN OF A CERTAIN POINT
//	CHAR TYPE SIGN: THE LABEL OF THE POINT('W','.','^','v','S','H','P')
//	INT TYPE ORIGIN: NOTICE THE LAST POINT COME TO HERE
//	0:NO POINT COMING HERE
//	1:FROM SOUtH
//	2:FROM WEST
//	3:FROM NORTH
//	4:FROM EAST
//	5:FROM DOWNSTAIR
//	6:FROM UPSTAIR


int sizeGet(int,int);
void initbuilding(vector<point>&,char,int,int&,int,int);
int convtovec(int,int,int,int,int);
void ignorecomm();


#endif
