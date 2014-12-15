#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<utility>
#include"headfile.h"

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

bool comp_time(const entry &data1,const entry &data2)
{
	if(data1.timestamp<data2.timestamp)
	{
		return 1;
	}
	else if (data1.timestamp>data2.timestamp)
	{
		return 0;
	}
	else
	{
		if(data1.category<data2.category)
		{
			return 1;
		}
		else if(data1.category>data2.category)
		{
			return 0;
		}
		else
		{
			if(data1.id<data2.id)
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


void t_search(vector<entry> &data,const string &timestamp1,const string &timestamp2,vector<int> &recent)
{
	recent.clear();
	sort(data.begin(),data.end(),comp_time);
	entry temp;
	temp.timestamp=timestamp1;
	temp.id=0;
	temp.category="";
	vector<entry>::iterator pos=lower_bound(data.begin(),data.end(),temp,comp_time);
	vector<entry>::iterator ptr;
	for(ptr=pos;ptr<data.end();ptr++)
	{
		if(ptr->timestamp<=timestamp2)
		{
			cout<<ptr->id<<"|"<<ptr->timestamp<<"|"<<ptr->category<<"|"<<ptr->message<<endl;
			recent.push_back(ptr->id);
		}
	}
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

bool comp_category(const entry &data1,const entry &data2)
{
	if(convertTolower(data1.category)<convertTolower(data2.category))
	{
		return 1;
	}
	else if (convertTolower(data1.category)>convertTolower(data2.category))
	{
		return 0;
	}
	else
	{
		if(data1.timestamp<data2.timestamp)
		{
			return 1;
		}
		else if(data1.timestamp>data2.timestamp)
		{
			return 0;
		}
		else
		{
			if(data1.id<data2.id)
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
//!!!!!!!!!!!!!!
//Notice that if we c_search and t_search, everytime we use the function,it will need to resort for a time. IS THAT TIME CONSUMING??
//TWO COPIES FOR THE DATA.
void c_search(vector<entry> &data,const string &category1,const string &category2,vector<int> &recent)
{
	recent.clear();
//	sort(data.begin(),data.end(),comp_category);//HERE!!!!!!!!!!!!!!!!!!!
	entry temp;
	temp.id=0;
	temp.category=category1;
	temp.timestamp="";
	vector<entry>::iterator pos=lower_bound(data.begin(),data.end(),temp,comp_category);
	vector<entry>::iterator ptr;
	for(ptr=pos;ptr<data.end();ptr++)
	{
		if(convertTolower(ptr->category)<=convertTolower(category2))
		{
			cout<<ptr->id<<"|"<<ptr->category<<"|"<<ptr->message<<endl;
			recent.push_back(ptr->id);
		}
	}
}


bool comp_key_keyword(const key_keyword &data1, const key_keyword &data2)
{
	if(data1.id<data2.id)
	{
		return 1;
	}
	else if(data1.id>data2.id)
	{
		return 0;
	}
	else
	{
		if(data1.keyword<data2.keyword)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

bool beq_key_keyword(const key_keyword &data1,const key_keyword &data2)
{
	return ((data1.id==data2.id)&&(data1.keyword==data2.keyword));
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
	
	cout<<"return true"<<endl;
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
	cout<<"No head and back :"<<endl;
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
			cout<<time1<<endl;
		}
		start=i+1;
	}
	cout<<"time1 done"<<endl;
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
		if(time2[i+1]==':')
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
	string category1=input.substr(0,verticalindex);
	string category2=input.substr(verticalindex+1);
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

vector<int> stl_intersection(vector<int> &data1, vector<int> &data2)
{
	int size=(data1.size()>data2.size())?data1.size():data2.size();
	vector<int> temp (size);
	vector<int> result;
	vector<int>::iterator pos;
	vector<int>::iterator ptr;
	pos=set_intersection(data1.begin(),data1.end(),
				data2.begin(),data2.end(),
					temp.begin());
	for(ptr=temp.begin();ptr!=pos;ptr++)
	{
		result.push_back(*ptr);
	}
	return result;
}

bool comp_forsort(const forsort &data1,const forsort &data2)
{
	if(data1.timestamp<data2.timestamp)
	{
		return 1;
	}
	else if (data1.timestamp>data2.timestamp)
	{
		return 0;
	}
	else
	{
		if(data1.category<data2.category)
		{
			return 1;
		}
		else if(data1.category>data2.category)
		{
			return 0;
		}
		else
		{
			if(data1.id<data2.id)
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



