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
        string categorylower;
//        vector<string> keyword;
};

struct keywordarray
{
	string keyword;
	vector<entry*> indexarray;
	bool issort;
};



void input(vector<entry*> &timestampdata,vector<entry*> &categorydata,vector<entry*> &data, string filename);

int hashstring(const string &s,int hash_size);

//bool comp_time(const entry* data1,const entry* data2);

void t_search(vector<entry*> &data,const string &timestamp1,const string &timestamp2,vector<entry*> &recent);

//bool comp_category(const entry* data1,const entry* data2);

string convertTolower(string str);

void c_search(vector<entry*> &data,const string &category1,const string &category2,vector<entry*> &recent);

void parse(entry* tempdata,vector<vector<keywordarray*> > &hashtable,int hashsize);

void put_in(const string &keyword,vector<vector<keywordarray*> > &hashtable,int hashsize,entry* data);

bool getTpair(pair<string, string> &temp, const string &input);

bool getCpair(pair<string, string> &temp, const string &input);

void parsekeyword(string &keysentence, vector<string> &result);

vector<entry*> stl_intersection(vector<entry*> &data1, vector<entry*> &data2);


//bool entryptrunique(const entry* data1,const entry* data2);

//bool entryptreq(const entry* data1,const entry* data2);


#endif
