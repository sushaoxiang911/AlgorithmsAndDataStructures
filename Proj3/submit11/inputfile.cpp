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
	        entry *tempdata=new entry;
	        tempdata->id=idtemp;
	        int start=0;
	        int i;
	        for(i=start;i<templine.length();i++)
	        {
	            if(templine[i]=='|')
	            {
	                break;
	            }    
	        }
	        tempdata->timestamp=templine.substr(start,i-start);
	        start=i+1;
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
	        tempdata->message=templine.substr(start,templine.length()-start);

		timestampdata.push_back(tempdata);
		categorydata.push_back(tempdata);
		data.push_back(tempdata);
	        idtemp++;
	        
	}
	infile.close();
}

