#include <getopt.h>
#include <iostream>
#include <cstdlib>

using namespace std;

char *MODE;
char *ALGOR;
int report;
int t;
int mode;
struct option longopts[]={
{"algorithm",required_argument,NULL,'a'},
{"mode",required_argument,NULL,'m'},
{"report",no_argument,NULL,'r'},
{"help",no_argument,NULL,'h'},
{"timing",no_argument,NULL,'t'},
{0,0,0,0},
};

int main(int argc,char *argv[])
{
	opterr=0;
	int c;
	while((c=getopt_long(argc,argv,":a:m:rht",longopts,NULL))!=-1)
	{
		switch(c){
		case 0:
		break;
		case 'a':
		ALGOR=optarg;
		break;
		case 'm':
		MODE=optarg;
		mode=1;
		break;
		case 'r':
		report=1;
		break;
		case 't':
		t=1;
		break;
		case 'h':
		cout<<"help information:"<<endl;
		exit(0);
		break;
		case ':':
		cout<<"abc"<<endl;
		exit(0);
		case '?':
		cout<<"cde"<<endl;
		exit(0);
		
		}
	}
	if(ALGOR!=NULL)
	{
		cout<<ALGOR<<endl;
	}
	if(MODE!=NULL)
	{
		cout<<mode<<" "<<MODE<<endl;
	}
	cout<<report<<" "<<t<<endl;
	if (optind < argc)
         {
           cout<<"non-option ARGV-elements: ";
           while (optind < argc)
             cout<<argv[optind++];
         }
	cout<<endl;
     

}



