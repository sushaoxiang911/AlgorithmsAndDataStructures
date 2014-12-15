#ifndef DUPLICATE_H
#define	DUPLICATE_H

#include"duplicate.h"
#include<string>
#include<vector>
#include <sys/resource.h>
#include <sys/time.h>
#include <iostream>

using namespace std;
class Timer{
	private:
		struct rusage startu;
		struct rusage endu;
		double duration;
	public:
		Timer(){ getrusage(RUSAGE_SELF, &startu); }
		void recordTime(){
			getrusage(RUSAGE_SELF, &endu);	
			double start_sec = startu.ru_utime.tv_sec + startu.ru_utime.tv_usec/1000000.0;	
			double end_sec = endu.ru_utime.tv_sec +endu.ru_utime.tv_usec/1000000.0;
			duration = end_sec - start_sec;
		}
		double getTime() { return duration; }
};

static double total_time=0;
static double intersection_time=0;
static double merge_time=0;
static double unique_time=0;
static double union_time=0;
static double diff_time=0;
static double sort_time=0;



struct g_line
{
	string line;
	int percent;
};

struct s_name
{
	string name1;
	string name2;
	int percent;
};

//bool identify(string &str);
//int datain(vector<string> &data, int check,string & _str);
//void norm(string &_str);

//input the document MODE file
void input_document(vector<vector<string> >&data, const string filename);

//input the code MODE file
void input_code(vector<vector<string> >&data, const string filename);

//radix sort
void R_sort(vector<string> &data);

//two unique
void my_unique(vector<string> &data);
void stl_unique(vector<string> &data);

//two intersection
vector<string> my_intersection(vector<string> &data1, vector<string> &data2);
vector<string> stl_intersection(vector<string> &data1,vector<string> &data2);

//delete common element
void professor_giving(vector <string>&same, vector<string>& data);

//two union
int my_union(vector<string> &data1, vector<string> &data2);
int stl_union(vector<string> &data1, vector<string> &data2);

//two difference
int my_diff(vector<string> &data1, vector<string> &data2);
int stl_diff(vector<string> &data1, vector<string> &data2);

//two merge
vector<string> my_merge(vector<string> &data1,vector<string> &data2);
vector<string> stl_merge(vector<string> &data1, vector<string> &data2);

//get the g_line type(LINE and PERCENT) from the merge result that the line appearance percent is higher than the threshold
vector<g_line> g_get(vector<string> &data,int submissions,int threshold); 
//the comparison of two g_line type
bool g_comp(const g_line &s1, const g_line &s2);

//get the s_name type(name1,name2,percent of similarity)from the whole data.
vector<s_name> my_s_get(vector<vector<string> > &data, int threshold);
vector<s_name> stl_s_get(vector<vector<string> > &data, int threshold);
//the comparison of two s_name type
bool s_comp(const s_name &s1,const s_name &s2);



//int max_g(vector<g_line> &data);
//void g_out(vector<g_line> &data);




#endif
