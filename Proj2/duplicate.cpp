#include<iostream>
#include<vector>
#include<algorithm>
#include"duplicate.h"
#include <sys/resource.h>
#include <sys/time.h>
#include <iostream>

using namespace std;

void  my_unique(vector<string> &data)
{
	Timer timetemp;
	vector<string>::iterator ptr1=data.begin()+1;
	vector<string>::iterator ptr2=ptr1+1;
	while(ptr2<data.end())
	{
		if(*ptr1==*ptr2)
		{
			ptr2=data.erase(ptr2);
		}
		else
		{
			ptr1++;
			ptr2++;
		}
	}
	
	timetemp.recordTime();
	unique_time=unique_time+timetemp.getTime();
}

void stl_unique(vector<string> &data)
{
	vector<string> temp;

	Timer timetemp;	

	vector<string>::iterator pos=unique(data.begin()+1,data.end());

	timetemp.recordTime();
	unique_time=unique_time+timetemp.getTime();
	

	vector<string>::iterator start;
	for(start=data.begin();start<pos;start++)
	{
		temp.push_back(*start);
	}
	data=temp;
	
	timetemp.recordTime();
	unique_time=unique_time+timetemp.getTime();
}


vector<string> my_intersection(vector<string> &data1, vector<string> &data2)
{
	Timer timetemp;	

	vector<string> result;
	result.push_back(" ");
	vector<string>::iterator ptr1=data1.begin()+1;
	vector<string>::iterator ptr2=data2.begin()+1;
	while(ptr1!=data1.end()&&ptr2!=data2.end())
	{
		if (*ptr1>*ptr2)
		{
			ptr2++;
		}
		else if(*ptr1<*ptr2)
		{
			ptr1++;
		}
		else
		{
			result.push_back(*ptr1);
			ptr1++;
			ptr2++;
		}
	}
	
	timetemp.recordTime();
	intersection_time=intersection_time+timetemp.getTime();
	
	return result;
}

vector<string> stl_intersection(vector<string> &data1, vector<string> &data2)
{
	Timer timetemp;
	int size=(data1.size()>data2.size())?data1.size():data2.size();
	vector<string> temp (size);
	vector<string> result;
	vector<string>::iterator pos;
	vector<string>::iterator ptr;
	pos=set_intersection(data1.begin()+1,data1.end(),
				data2.begin()+1,data2.end(),
					temp.begin());

	result.push_back(" ");
	for(ptr=temp.begin();ptr!=pos;ptr++)
	{
		result.push_back(*ptr);
	}

	timetemp.recordTime();
	intersection_time=intersection_time+timetemp.getTime();
	return result;
}


int my_union(vector<string> &data1, vector<string> &data2)
{
	Timer timetemp;
	
	int result=0;
	vector<string>::iterator ptr1=data1.begin()+1;
	vector<string>::iterator ptr2=data2.begin()+1;
	while(ptr1!=data1.end()&&ptr2!=data2.end())
	{
		if (*ptr1>*ptr2)
		{
			result++;
			ptr2++;
		}
		else if(*ptr1<*ptr2)
		{
			result++;
			ptr1++;
		}
		else
		{
			result++;
			ptr1++;
			ptr2++;
		}
	}
	if(ptr1!=data1.end())
	{
		while(ptr1!=data1.end())
		{
			result++;
			ptr1++;
		}
	}
	if(ptr2!=data2.end())
	{
		while(ptr2!=data2.end())
		{
			result++;
			ptr2++;
		}
	}	
	timetemp.recordTime();
	union_time=union_time+timetemp.getTime();

	return result;
}

int stl_union(vector<string> &data1, vector<string> &data2)
{
	Timer timetemp;

	vector<string> temp(data1.size()+data2.size());
	vector<string>::iterator pos;

	
	pos=set_union(data1.begin()+1,data1.end(),data2.begin()+1,data2.end(),temp.begin());

	timetemp.recordTime();
	union_time=union_time+timetemp.getTime();

	return (pos-temp.begin());
}

int my_diff(vector<string> &data1, vector<string> &data2)
{
	Timer timetemp;

	int result=0;
	vector<string>::iterator ptr1=data1.begin()+1;
	vector<string>::iterator ptr2=data2.begin()+1;
	while(ptr1!=data1.end()&&ptr2!=data2.end())
	{
		if (*ptr1>*ptr2)
		{
			ptr2++;
		}
		else if(*ptr1<*ptr2)
		{
			result++;
			ptr1++;
		}
		else
		{
			ptr1++;
			ptr2++;
		}
	}
	if(ptr1!=data1.end())
	{
		while(ptr1!=data1.end())
		{
			result++;
			ptr1++;
		}
	}	

	timetemp.recordTime();
	diff_time=diff_time+timetemp.getTime();


	return result;
}
int stl_diff(vector<string> &data1, vector<string> &data2)
{
	Timer timetemp;
	vector<string> temp(data1.size()+data2.size());
	vector<string>::iterator pos;

	
	
	pos=set_difference(data1.begin()+1,data1.end(),data2.begin()+1,data2.end(),temp.begin());

	timetemp.recordTime();
	diff_time=diff_time+timetemp.getTime();


	return (pos-temp.begin());
}

vector<string> my_merge(vector<string> &data1, vector<string> &data2)
{
	Timer timetemp;

	vector<string>::iterator ptr1=data1.begin()+1;
	vector<string>::iterator ptr2=data2.begin()+1;
	vector<string> result;
	result.push_back(" ");
	while(ptr1!=data1.end()&&ptr2!=data2.end())
	{
		if(*ptr1<=*ptr2)
		{
			result.push_back(*ptr1);
			ptr1++;
		}
		else
		{
			result.push_back(*ptr2);
			ptr2++;
		}
	}
	if(ptr1!=data1.end())
	{
		while(ptr1!=data1.end())
		{
			result.push_back(*ptr1);
			ptr1++;
		}
	}
	if(ptr2!=data2.end())
	{	
		while(ptr2!=data2.end())
		{
			result.push_back(*ptr2);
			ptr2++;
		}
	}

	timetemp.recordTime();
	merge_time=merge_time+timetemp.getTime();

	return result;
	
}

vector<string> stl_merge(vector<string> &data1, vector<string> &data2)
{
	Timer timetemp;
	vector<string>::iterator pos;
	vector<string>::iterator ptr;
	vector<string> temp(data1.size()+data2.size());
	vector<string> result;
	result.push_back(" ");

	

	pos=merge(data1.begin()+1,data1.end(),data2.begin()+1,data2.end(),temp.begin());

	

	for(ptr=temp.begin();ptr!=pos;ptr++)
	{
		result.push_back(*ptr);
	}
	timetemp.recordTime();
	merge_time=merge_time+timetemp.getTime();
	return result;
}



void professor_giving(vector <string>&same, vector<string>& data)
{
	vector<string>::iterator pos=data.begin()+1;
	vector<string>::iterator start;
	for(int i=1;i<same.size();i++)
	{
		for(start=pos;start!=data.end();start++)
		{
			if(*start==same[i])
			{
				pos=data.erase(start);
				break;
			}
		}
	}
}


void g_get(vector<g_line> &result,vector<string> &data,int submissions,int threshold)
{
	vector<string>::iterator ptr1=data.begin()+1;
	vector<string>::iterator ptr2=ptr1;
	int counter=0;
	g_line temp;
	while(ptr2!=data.end())
	{
		for(ptr2=ptr1;ptr2!=data.end();ptr2++)
		{
			if(*ptr2!=*ptr1)
			{
				break;
			}
		}
		counter=ptr2-ptr1;
		if(counter*100/submissions>=threshold)
		{
			temp.line=*ptr1;
			temp.percent=counter*100/submissions;
			result.push_back(temp);
		}
		ptr1=ptr2;
		
	}
}
bool g_comp(const g_line &s1, const g_line &s2)
{
	if(s1.percent>s2.percent)
	{
		return 1;
	}
	else if(s1.percent<s2.percent)
	{
		return 0;
	}
	else
	{
		if(s1.line<s2.line)
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}
}

void my_s_get(vector<s_name> &result, vector<vector<string> > &data, int threshold)
{
	vector<vector<string> >::iterator ptr1=data.begin();
	vector<vector<string> >::iterator ptr2;
	while(ptr1!=data.end()-1)
	{
		for(ptr2=ptr1+1;ptr2!=data.end();ptr2++)
		{
			int per;
			if(my_union(*ptr1,*ptr2)==0)
			{
				per=100;
			}
			else
			{
				per=(my_intersection(*ptr1,*ptr2).size()-1)*100/my_union(*ptr1,*ptr2);
			}
			if(per>=threshold)
			{
				s_name temp;
				if(*(ptr1->begin())>*(ptr2->begin()))
				{
					temp.name1=*(ptr2->begin());
					temp.name2=*(ptr1->begin());
				}
				else
				{
					temp.name1=*(ptr1->begin());
					temp.name2=*(ptr2->begin());
				}
				temp.percent=per;
				result.push_back(temp);
			}
		}
		ptr1++;
	}
}


void stl_s_get(vector<s_name> &result, vector<vector<string> > &data, int threshold)
{
	vector<vector<string> >::iterator ptr1=data.begin();
	vector<vector<string> >::iterator ptr2;
	while(ptr1!=data.end()-1)
	{
		for(ptr2=ptr1+1;ptr2!=data.end();ptr2++)
		{
			int per;
			if(stl_union(*ptr1,*ptr2)==0)
			{
				per=100;
			}	
			else
			{
				per=(stl_intersection(*ptr1,*ptr2).size()-1)*100/stl_union(*ptr1,*ptr2);
			}
			if(per>=threshold)
			{
				s_name temp;
				if(*(ptr1->begin())>*(ptr2->begin()))
				{
					temp.name1=*(ptr2->begin());
					temp.name2=*(ptr1->begin());
				}
				else
				{
					temp.name1=*(ptr1->begin());
					temp.name2=*(ptr2->begin());
				}
				temp.percent=per;
				result.push_back(temp);
			}
		}
		ptr1++;
	}
}

bool s_comp(const s_name &s1,const s_name &s2)
{
	if(s1.percent>s2.percent)
	{
		return 1;
	}
	else if(s1.percent<s2.percent)
	{
		return 0;
	}
	else
	{
		if(s1.name1<s2.name1)
		{
			return 1;
		}
		else if(s1.name1>s2.name1)
		{
			return 0;
		}
		else
		{
			if(s1.name2<=s2.name2)
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







