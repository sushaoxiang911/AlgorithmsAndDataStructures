#include <iostream>
#include <getopt.h>

using namespace std;

char *l_opt_arg;
int do_stack,do_queue;
struct option longopts[]={
{"stack",no_argument,&do_stack,1},
{"queue",no_argument,&do_queue,1},
{"output",required_argument,NULL,'o'},
{"help",no_argument,NULL,'h'},
{0,0,0,0},
};

int main(int argc,char* argv[])
{
	int c;
	while((c=getopt_long(argc,argv,"sqo:h",longopts,NULL))!=-1)
	{
		switch(c){
		case 0:
		cout<<do_stack<<" "<<do_queue<<endl;
		break;
		case 's':
		do_stack=1;
		cout<<do_stack<<" "<<do_queue<<endl;
		break;
		case 'q':
		do_queue=1;
		cout<<do_stack<<" "<<do_queue<<endl;
		break;
		case 'o':
		l_opt_arg=optarg;
		cout<<l_opt_arg<<endl;
		break;
		case 'h':
		cout<<"help information"<<endl;
		break;
		
		}
	}
	return 0;
}
