#ifndef DUPLICATE_H
#define	DUPLICATE_H

#include"duplicate.h"
#include<string>
#include<vector>
#include <sys/resource.h>
#include <sys/time.h>
#include <iostream>

using namespace std;
class Timer
{
	private:
		struct rusage startu;
		struct rusage endu;
		double duration;
	public:
		Timer()
		{
			getrusage(RUSAGE_SELF, &startu); 
		}
//CONSTRUCTOR
//START RECORDING TIME

		void recordTime()
		{
			getrusage(RUSAGE_SELF, &endu);	
			double start_sec = startu.ru_utime.tv_sec + startu.ru_utime.tv_usec/1000000.0;	
			double end_sec = endu.ru_utime.tv_sec +endu.ru_utime.tv_usec/1000000.0;
			duration = end_sec - start_sec;
		}
//EFFECT:	STOP THE TIMER

		double getTime() 
		{
			 return duration;
		}
//EFFECT:	RETURN THE TIME 
};


static double total_time=0;
static double intersection_time=0;
static double merge_time=0;
static double unique_time=0;
static double union_time=0;
static double diff_time=0;
static double sort_time=0;
//STATIC GLOBAL VARIABLES FOR THE TIME COUNTING FOR THE WHOLE PROGRAM


struct g_line
{
	string line;
	int percent;
};
//DISCRIPTION:	IT IS FOR G COMMAND.
//		RECORD A STRING TYPE LINE
//		RECORD A INTEGER TYPE PERCENT 

struct s_name
{
	string name1;
	string name2;
	int percent;
};
//DISCRIPTION:	IT IS FOR S COMMAND
//		RECORD A STRING TYPE NAME1
//		RECORD A STRING TYPE NAME2
//		RECORD A INTEGER TYPE SIMILARITY PERCEN


void input_document(vector<vector<string> >&data, const string filename);
//EFFECT:	INPUT A DOCUMENT MODE FILE INTO THE DATABASE
//REQUIRED:	VECTOR<VECTOR<STRING> > TYPE DATA
//		STRING TYPE FILE NAME
//MODIFY:	NONE

void input_code(vector<vector<string> >&data, const string filename);
//EFFECT:	INPUT A DOCUMENT MODE FILE INTO THE DATABASE
//REQUIRED:	VECTOR<VECTOR<STRING> > TYPE DATA
//		STRING TYPE FILE NAME
//MODIFY:	NONE

void R_sort(vector<string> &data);
//EFFECT:	SORT THE CURRENT VECTOR<STRING> TYPE DATA
//REQUIRED:	VECTOR<STRING> TYPE DATA
//MODIFY:	VECTOR<STRING> TYPE DATA

void my_unique(vector<string> &data);
//EFFECT:	DO UNIQUE OPERATION FOR THE CURRENT DATA
//REQUIRED:	VECTOR<STRING> TYPE DATA
//MODIFY:	VECTOR<STRING> TYPE DATA
void stl_unique(vector<string> &data);
//EFFECT:	DO UNIQUE OPERATION FOR THE CURRENT DATA
//REQUIRED:	VECTOR<STRING> TYPE DATA
//MODIFY:	VECTOR<STRING> TYPE DATA

vector<string> my_intersection(vector<string> &data1, vector<string> &data2);
//EFFECT:	DO INTERSECTION OPERATION OF TWO VECTOR<STRING> TYPE DATA
//		RETURN THE INTERSECTION ELEMENT OF THE TWO VECTORS
//REQUIRED:	TWO VECTOR<STRING> TYPE DATA
//MODIFY:	NONE
vector<string> stl_intersection(vector<string> &data1,vector<string> &data2);
//EFFECT:	DO INTERSECTION OPERATION OF TWO VECTOR<STRING> TYPE DATA
//		RETURN THE INTERSECTION ELEMENT OF THE TWO VECTORS
//REQUIRED:	TWO VECTOR<STRING> TYPE DATA
//MODIFY:	NONE

void professor_giving(vector <string>&same, vector<string>& data);
//EFFECT:	DELETE THE CONTENT LINES FROM EVERY PERSON'S DATA
//REQUIRED:	VECTOR<STRING> TYPE COMMON CONTENTLINES, VECTOR<STRING> TYPE DATA
//MODFIFY:	VECTOR<STRING> TYPE DATA

int my_union(vector<string> &data1, vector<string> &data2);
//EFFECT:	DO UNION OPERATION ON THE TWO VECTORS
//		RETURN AN INT OF THE LINE NUMBER OF THE UNION
//REQUIRED:	TWO VECTOR<STRING> TYPE DATA
//MODIFY:	NONE
int stl_union(vector<string> &data1, vector<string> &data2);
//EFFECT:	DO UNION OPERATION ON THE TWO VECTORS
//		RETURN AN INT OF THE LINE NUMBER OF THE UNION
//REQUIRED:	TWO VECTOR<STRING> TYPE DATA
//MODIFY:	NONE

int my_diff(vector<string> &data1, vector<string> &data2);
//EFFECT:	DO DIFFERENCE OPERATION ON THE TWO VECTORS
//		RETURN AN INT OF THE LINE NUMBER OF THE DIFFERENCE
//REQUIRED:	TWO VECTOR<STRING> TYPE DATA
//MODIFY:	NONE
int stl_diff(vector<string> &data1, vector<string> &data2);
//EFFECT:	DO DIFFERENCE OPERATION ON THE TWO VECTORS
//		RETURN AN INT OF THE LINE NUMBER OF THE DIFFERENCE
//REQUIRED:	TWO VECTOR<STRING> TYPE DATA
//MODIFY:	NONE

vector<string> my_merge(vector<string> &data1,vector<string> &data2);
//EFFECT:	DO MERGE OPERATION ON THE TWO VECTORS
//		RETURN AN VECTOR OF THE LINE NUMBER OF THE MERGE
//REQUIRED:	TWO VECTOR<STRING> TYPE DATA
//MODIFY:	NONE
vector<string> stl_merge(vector<string> &data1, vector<string> &data2);
//EFFECT:	DO MERGE OPERATION ON THE TWO VECTORS
//		RETURN AN VECTOR OF THE LINE NUMBER OF THE MERGE
//REQUIRED:	TWO VECTOR<STRING> TYPE DATA
//MODIFY:	NONE

void g_get(vector<g_line> &result, vector<string> &data,int submissions,int threshold); 
//EFFECT:	GET THE LINES ALONG WITH THE PERCENT SAVE IT INTO THE RESULT VECTOR
//REQUIRED:	VECTOR<G_LINE> RESULT, VECTOR<STRING> DATA, AN INT TYPE THE NUMBER OF SUBMISSIONS
//		AN INT TYPE NUMBER OF THE THRESHOLD
//MODIFY:	VECTOR<G_LINE> RESULT

bool g_comp(const g_line &s1, const g_line &s2);
//EFFECT:	METHOD OF COMPARE TWO G_LINE TYPE
//		RETURN 1 IF S1>=S2
//		RETURN 0 IF ELSE
//REQUIRED:	TWO G_LINE TYPE VARIABLES
//MODIFY:	NONE 

void my_s_get(vector<s_name> &result, vector<vector<string> > &data, int threshold);
//EFFECT:	GET THE TWO NAMES ALONG WITH THE PERCENT OF SIMILARITY SAVE IT INTO THE RESULT VECTOR
//REQUIRED:	THE RESULT CONTAINER, THE VECTOR<VECTOR<STRING> > DATABASE AND AN INT TYPE THRESHOLD
//MODIFY:	VECTOR<S_NAME> RESULT
void stl_s_get(vector<s_name> &result,vector<vector<string> > &data, int threshold);
//EFFECT:	GET THE TWO NAMES ALONG WITH THE PERCENT OF SIMILARITY SAVE IT INTO THE RESULT VECTOR
//REQUIRED:	THE RESULT CONTAINER, THE VECTOR<VECTOR<STRING> > DATABASE AND AN INT TYPE THRESHOLD
//MODIFY:	VECTOR<S_NAME> RESULT

bool s_comp(const s_name &s1,const s_name &s2);
//EFFECT:	METHOD OF COMPARE TWO S_NAME TYPE
//		RETURN 1 IF S1>=S2
//		RETURN 0 IF ELSE
//REQUIRED:	TWO S_NAME TYPE VARIABLES
//MODIFY:	NONE


#endif
