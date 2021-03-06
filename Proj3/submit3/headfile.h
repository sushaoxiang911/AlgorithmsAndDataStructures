#ifndef HEADFILE_H
#define	HEADFILE_H

#include "headfile.h"
#include <string>
#include <vector>
#include <iostream>
#include <utility>


using namespace std;

struct entry
{
	int id;
        string timestamp;
        string category;
        string message;
//        vector<string> keyword;
};

struct keywordarray
{
	string keyword;
	vector<int> indexarray;
	bool issort;
};


/*
struct key_keyword
{
	int id;
	string keyword;
};

struct forsort
{
	int id;
        string timestamp;
        string category;
};
*/
void input(vector<entry*> &timestampdata,vector<entry*> &categorydata,vector<entry*> &data, string filename);

int hashstring(const string &s,int hash_size);

bool comp_time(const entry* data1,const entry* data2);


void t_search(vector<entry*> &data,const string &timestamp1,const string &timestamp2,vector<int> &recent);

bool comp_category(const entry* data1,const entry* data2);

string convertTolower(string str);

void c_search(vector<entry*> &data,const string &category1,const string &category2,vector<int> &recent);

void parse(const entry* tempdata,vector<keywordarray*> hashtable[],int hashsize,int index);

void put_in(const string &keyword,vector<keywordarray*> hashtable[],int hashsize,int index);


//bool comp_key_keyword(const key_keyword &data1, const key_keyword &data2);

//bool beq_key_keyword(const key_keyword &data1,const key_keyword &data2);

bool getTpair(pair<string, string> &temp, const string &input);

bool getCpair(pair<string, string> &temp, const string &input);

void parsekeyword(string &keysentence, vector<string> &result);

vector<int> stl_intersection(vector<int> &data1, vector<int> &data2);

//bool comp_forsort(const forsort &data1,const forsort &data2);


#endif
