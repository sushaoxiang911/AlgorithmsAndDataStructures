#include<iostream>
#include<vector>
#include<string>

using namespace std;


void R_sort(vector<string> &data)
{
//	cout<<data.size()<<endl;
	int maxlength=0;
	for(int i=1;i<data.size();i++)
	{
		if(data[i].length()>maxlength)
			maxlength=data[i].length();
	}
//	cout<<maxlength<<endl;
//	cout<<data[2].length()<<endl;
	vector<vector<string> > bucket(96);
	for(int i=maxlength-1;i>=0;i--)
	{
		for(int j=1;j<data.size();j++)
		{
//			cout<<data[j].size()<<" "<<(data[j].size()-1<i)<<endl;
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
		for(int j=0;j<96;j++)
		{
			//cout<<"a"<<endl;
			for(int k=0;k<bucket[j].size();k++)
			{
//				cout<<"b"<<endl;
				data[key]=bucket[j][k];
				key++;
			}
				bucket[j].clear();

		}
//		for(int i=0;i<data.size();i++)
//		{
//			cout<<data[i]<<endl;
//		}
//	cout<<i<<endl;
	}
	

//	cout<<"a"<<endl;

}

