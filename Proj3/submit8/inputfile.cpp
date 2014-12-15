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



void input(vector<entry*> &timestampdata,vector<entry*> &categorydata, vector<entry*> &data,string filename)
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
	        entry *tempdata=new entry;
	        tempdata->id=idtemp;
	        int start=0;
	        int i;
//	        for(i=start;i<templine.length();i++)
//	        {
//	            if(templine[i]=='|')
//	            {
//	                break;
//	            }    
//	        }//zhao bar de wen ti !!!!!!!!!!!!
	        tempdata->timestamp=templine.substr(0,14);
	        start=15;
	        for(i=start;i<templine.length();i++)
	        {
	            if(templine[i]=='|')
	            {
	                break;
	            }    
	        }
	        tempdata->category=templine.substr(start,i-start);
	        tempdata->categorylower=convertTolower(tempdata->category);
	        start=i+1;
	        tempdata->message=templine.substr(start);
//	        parse(tempdata);
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

