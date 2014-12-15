#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <iomanip>
#include <vector>
#include <fstream>
#include"headfile.h"

using namespace std;

void parse(entry &tempdata);

void input(vector<entry> &timestampdata,vector<entry> &categorydata, vector<entry> &data,string filename)
{

        ifstream infile;
	infile.open(filename.c_str());
	if(!infile.is_open())
	{
		cerr<<"open error!"<<endl;
		exit(1);
	}
	string templine;
	int idtemp=0;
	while(getline(infile,templine))
	{
		if(templine=="")
		{
			break;
		}
		//cout<<"a"<<endl;
	        entry tempdata;
	        tempdata.id=idtemp;
	        int start=0;
	        int i;
	        for(i=start;i<templine.length();i++)
	        {
	            if(templine[i]=='|')
	            {
	                break;
	            }    
	        }
	        tempdata.timestamp=templine.substr(start,i-start);
	        start=i+1;
	        for(i=start;i<templine.length();i++)
	        {
	            if(templine[i]=='|')
	            {
	                break;
	            }    
	        }
	        tempdata.category=templine.substr(start,i-start);
	        start=i+1;
	        tempdata.message=templine.substr(start,templine.length()-start);
	        parse(tempdata);
//	        cout<<tempdata.keyword.size()<<endl;
//	        for(i=0;i<tempdata.keyword.size();i++)
//	        {
//	        	cout<<tempdata.keyword[i]<<endl;
//	        }
		timestampdata.push_back(tempdata);
		categorydata.push_back(tempdata);
		data.push_back(tempdata);
	        idtemp++;
	        
	}
	infile.close();
}
void parse(entry &tempdata)
{
        string keyp1=tempdata.category;
        string keyp2=tempdata.message;
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
//       cout<<keyp1<<" "<<keyp2<<endl;
        int start=0;
        int i;
        while(start<keyp1.length())
        {
        	
                for(i=start;i<keyp1.length();i++)
                {
                        if((keyp1[i]<=122&&keyp1[i]>=97)||(keyp1[i]<=57&&keyp1[i]>=48))
                        {
                                start=i;
                                break;
                        }
                }
                for(i=start;i<keyp1.length();i++)
                {
                        if((keyp1[i]>57&&keyp1[i]<97)||keyp1[i]<48||keyp1[i]>122)
                        {
                                break;
                        }
                }
//                cout<<start<<" "<<i<<endl;
                if(i-start>0)
                {
                	tempdata.keyword.push_back(keyp1.substr(start,i-start));
                }
                start=i+1;   
        }
//        cout<<keyp2<<endl;
        start=0;
        while(start<keyp2.length())
        {
                for(i=start;i<keyp2.length();i++)
                {
                        if((keyp2[i]<=122&&keyp2[i]>=97)||(keyp2[i]<=57&&keyp2[i]>=48))
                        {
                                start=i;
                                break;
                        }
                }
                for(i=start;i<keyp2.length();i++)
                {
                        if((keyp2[i]>57&&keyp2[i]<97)||keyp2[i]<48||keyp2[i]>122)
                        {
                                break;
                        }
                }
                if(i-start>0)
                {
                	tempdata.keyword.push_back(keyp2.substr(start,i-start));
                }
                start=i+1;   
        }
}
