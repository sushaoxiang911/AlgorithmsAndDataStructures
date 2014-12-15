#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
#include<sstream>
#include"headfile.h"
#include<ctype.h>

using namespace std;



int hashstring(const string &s,int hash_size) 
{
  unsigned int key = 0;
  for(int i=0;i<s.length();i++) 
  {
    key = key*37 + s[i];
  }
  return key%hash_size;
}

bool comp_time (const entry* data1,const entry* data2)
{
	if(data1->timestamp != data2->timestamp)
	{
		return data1->timestamp < data2->timestamp;
	}
	else
	{
		if(data1->categorylower!=data2->categorylower)
		{
			return data1->categorylower < data2->categorylower;
		}
		else
		{
			if(data1->id<data2->id)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
}




void t_search(vector<entry*> &data,const string &timestamp1,const string &timestamp2,vector<entry*> &recent)
{
	ios::sync_with_stdio(false);
	recent.clear();
	entry* temp=new entry;
	temp->timestamp=timestamp1;
	temp->id=0;
	temp->category="";
	vector<entry*>::iterator pos=lower_bound(data.begin(),data.end(),temp,comp_time);
	vector<entry*>::iterator ptr;
	ostringstream tempstream;
	for(ptr=pos;ptr<data.end();ptr++)
	{
		if((*ptr)->timestamp <= timestamp2)
		{
			
			tempstream<<(*ptr)->id<<'|'<<(*ptr)->timestamp<<'|'<<(*ptr)->category<<'|'<<(*ptr)->message<<'\n';
			recent.push_back((*ptr));
		}
	}
	cout<<tempstream.str();
	delete temp;
}



string convertTolower(string str)
{
	for(int i=0;i<str.length();i++)
	{
		if(str[i]<=90&&str[i]>=65)
		{
			str[i]=str[i]+32;
		}
	}
	return str;
}

bool comp_category(const entry* data1,const entry* data2)
{
	if(data1->categorylower != data2->categorylower)
	{
		return data1->categorylower < data2->categorylower;
	}
	else
	{
		if(data1->timestamp != data2->timestamp)
		{
			return data1->timestamp < data2->timestamp;
		}
		else
		{
			if(data1->id<data2->id)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
}


void c_search(vector<entry*> &data,const string &category1,const string &category2,vector<entry*> &recent)
{
	ios::sync_with_stdio(false);
	recent.clear();
	string category2lower = convertTolower(category2);
	string category1lower = convertTolower(category1);
	entry* temp=new entry;
	temp->id=0;
	temp->category=category1;
	temp->timestamp="";
	temp->categorylower = category1lower;
	vector<entry*>::iterator pos=lower_bound(data.begin(),data.end(),temp,comp_category);
	vector<entry*>::iterator ptr;
	ostringstream tempstream;
	for(ptr=pos;ptr<data.end();ptr++)
	{
		if((*ptr)->categorylower <= category2lower)
		{
			tempstream<<(*ptr)->id<<'|'<<(*ptr)->timestamp<<'|'<<(*ptr)->category<<'|'<<(*ptr)->message<<'\n';
			recent.push_back((*ptr));
		}
	}
	cout<<tempstream.str();
}



void parse(entry* tempdata,vector<keywordarray*> hashtable[],int hashsize)
{
        string keyp1=tempdata->category;
        string keyp2=tempdata->message;
        for(int i=0;i<keyp1.length();i++)
        {
                if(keyp1[i]<=90&&keyp1[i]>=65)
                {
                        keyp1[i]=keyp1[i]+32;
                }
        }
        for(int i=0;i<keyp2.length();i++)
        {
                if(keyp2[i]<=90&&keyp2[i]>=65)
                {
                        keyp2[i]=keyp2[i]+32;
                }
        }
        int start=0;
        int i;
        while(start<keyp1.length())
        {
        	
                for(i=start;i<keyp1.length();i++)
                {
                        if(isalnum(keyp1[i]))
                        {
                                start=i;
                                break;
                        }
                }
                for(i=start;i<keyp1.length();i++)
                {
                        if(!isalnum(keyp1[i]))
                        {
                                break;
                        }
                }
                if(i-start>0)
                {
                	string temp=keyp1.substr(start,i-start);
                	put_in(temp,hashtable,hashsize,tempdata);
                }
                start=i+1;   
        }
        start=0;
        while(start<keyp2.length())
        {
                for(i=start;i<keyp2.length();i++)
                {
                        if(isalnum(keyp2[i]))
                        {
                                start=i;
                                break;
                        }
                }
                for(i=start;i<keyp2.length();i++)
                {
                        if(!isalnum(keyp2[i]))
                        {
                                break;
                        }
                }
                if(i-start>0)
                {
                	string temp=keyp2.substr(start,i-start);
                	put_in(temp,hashtable,hashsize,tempdata);
                }
                start=i+1;   
        }
}

void put_in(const string &keyword ,vector<keywordarray*> hashtable[],int hashsize,entry* data)
{
	int check=1;
	int hashindex=hashstring(keyword,hashsize);
	for(int i=0;i<hashtable[hashindex].size();i++)
	{
		if(keyword==hashtable[hashindex][i]->keyword)
		{
			(hashtable[hashindex][i]->indexarray).push_back(data);
			check=0;
		}
	}
	if (check)
	{
		keywordarray* temp=new keywordarray;
		temp->keyword=keyword;
		temp->issort=0;
		(temp->indexarray).push_back(data);
		hashtable[hashindex].push_back(temp);
	}
}

bool getTpair(pair<string, string> &temp, const string &input)
{
	int verticalindex;
	int barnum=0;
	for(int i=0;i<input.length();i++)
	{
		if(input[i]=='|')
		{
			barnum++;
			verticalindex=i;
			if(barnum>1)
			{
				return 0;
			}
		}
	}
	if(barnum==0)
	{
		return 0;
	}
	string time1=input.substr(0,verticalindex);
	string time2=input.substr(verticalindex+1);
	int coloncheck=0;
	for(int i=0;i<time1.length();i++)
	{
		if(time1[i]==':')
		{
			coloncheck++;
		}
	}
	if(coloncheck!=4)
	{
		return 0;
	}
	coloncheck=0;
	for(int i=0;i<time2.length();i++)
	{
		if(time2[i]==':')
		{
			coloncheck++;
		}
	}
	if(coloncheck!=4)
	{
		return 0;
	}
	if(time1[0]==':')
	{
		time1="00"+time1;
	}
	if(time1[time1.length()-1]==':')
	{
		time1=time1+"00";
	}
	if(time2[0]==':')
	{
		time2="00"+time2;
	}
	if(time2[time2.length()-1]==':')
	{
		time2=time2+"00";
	}
	int start=0;
	int i=0;
	while(i<time1.length())
	{
		for(i=start;i<time1.length();i++)
		{
			if(time1[i]==':')
			{
				break;
			}
		}
		if(time1[i+1]==':'&&i<time1.length())
		{
			time1.insert(i+1,"00");
		}
		start=i+1;
	}
	start=0;
	i=0;
	while(i<time2.length())
	{
		for(i=start;i<time2.length();i++)
		{
			if(time2[i]==':')
			{
				break;
			}
		}
		if(time2[i+1]==':'&&i<time1.length())
		{
			time2.insert(i+1,"00");
		}
		start=i+1;
	}
	if(time1<time2)
	{
		temp.first=time1;
		temp.second=time2;
	}
	else
	{
		temp.first=time2;
		temp.second=time1;
	}
	return 1;		
}

bool getCpair(pair<string, string> &temp, const string &input)
{
	int verticalindex;
	int barnum=0;
	for(int i=0;i<input.length();i++)
	{
		if(input[i]=='|')
		{
			barnum++;
			verticalindex=i;
			if(barnum>1)
			{
				return 0;
			}
		}
	}
	if(barnum==0)
	{
		return 0;
	}
	string category1=convertTolower(input.substr(0,verticalindex));
	string category2=convertTolower(input.substr(verticalindex+1));
	if(category1<category2)
	{
		temp.first=category1;
		temp.second=category2;
	}
	else
	{
		temp.first=category2;
		temp.second=category1;
	}
	return 1;
}


void parsekeyword(string &keysentence, vector<string> &result)
{	
	int i;
	int start=0;
	for(i=0;i<keysentence.length();i++)
	{
		if(keysentence[i]<=90&&keysentence[i]>=65)
                {
                        keysentence[i]=keysentence[i]+32;
                }
	}
	while(start<keysentence.length())
        {
        	
                for(i=start;i<keysentence.length();i++)
                {
                        if((keysentence[i]<=122&&keysentence[i]>=97)||(keysentence[i]<=57&&keysentence[i]>=48))
                        {
                                start=i;
                                break;
                        }
                }
                for(i=start;i<keysentence.length();i++)
                {
                        if((keysentence[i]>57&&keysentence[i]<97)||keysentence[i]<48||keysentence[i]>122)
                        {
                                break;
                        }
                }
                if(i-start>0)
                {
                	result.push_back(keysentence.substr(start,i-start));
                }
                start=i+1;   
        }
}

vector<entry*> stl_intersection(vector<entry*> &data1, vector<entry*> &data2)
{
	int size=(data1.size()>data2.size())?data1.size():data2.size();
	vector<entry*> temp (size);
	vector<entry*> result;
	vector<entry*>::iterator pos;
	vector<entry*>::iterator ptr;
	pos=set_intersection(data1.begin(),data1.end(),
				data2.begin(),data2.end(),
					temp.begin(),entryptreq);
	for(ptr=temp.begin();ptr!=pos;ptr++)
	{
		result.push_back(*ptr);
	}
	return result;
}

bool entryptrunique(const entry* data1,const entry* data2)
{
	return (data1->id==data2->id);
}

bool entryptreq(const entry* data1,const entry* data2)
{
	return (data1->id<data2->id);
}


