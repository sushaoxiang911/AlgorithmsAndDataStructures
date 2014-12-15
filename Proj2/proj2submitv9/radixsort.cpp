#include<iostream>
#include<vector>
#include<string>

using namespace std;

void R_sort(vector<string> &data)
{
	int maxlength=0;
	for(int i=1;i<data.size();i++)
	{
		if(data[i].length()>maxlength)
		{
			maxlength=data[i].length();
		}
	}
	vector<vector<string> > bucket(100);
	for(int i=maxlength;i>=0;i--)
	{
		for(int j=1;j<data.size();j++)
		{
			if(data[j].size()-1<i)
			{	
				bucket[0].push_back(data[j]);
			}
			else
			{
				bucket[data[j][i]-31].push_back(data[j]);
			}
		}
		int key=1;
		for(int j=0;j<100;j++)
		{
			for(int k=0;k<bucket[j].size();k++)
			{
				data[key]=bucket[j][k];
				key++;
			}
			bucket[j].clear();
		}
	}
}

