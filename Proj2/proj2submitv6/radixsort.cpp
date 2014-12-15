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
	vector<vector<string> > bucket(100);
//	cout<<(' '-31)<<endl;
//	int i=299;
	for(int i=maxlength;i>=0;i--)
	{
//		i=294;
//		cout<<i<<endl;
//		cout<<data.size()<<endl;;
		for(int j=1;j<data.size();j++)
		{
//			cout<<j<<endl;
			if(data[j].size()-1<i)
			{	
				bucket[0].push_back(data[j]);
			}
			else
			{
				bucket[data[j][i]-31].push_back(data[j]);
			}
			
			
		}
//		cout<<i<<endl;
		int key=1;
		for(int j=0;j<100;j++)
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

