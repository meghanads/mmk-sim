/***************************
 * color macros
 * ************************/

#include<iostream>
#include<stdio.h>


using namespace std;

#define red   "\033[0;31m"        /* 0 -> normal ;  31 -> red */
#define cyan  "\033[1;36m"        /* 1 -> bold ;  36 -> cyan */
#define green "\033[0;32m"        /* 4 -> underline ;  32 -> green */
#define blue  "\033[0;34m"        /* 9 -> strike ;  34 -> blue */
#define black  "\033[0;30m"
#define brown  "\033[0;33m"
#define magenta  "\033[0;35m"
#define gray  "\033[0;37m"
#define white "\033[01;37m"

/***********************
 * clear function:
 * ********************/

void Myclear()
{
	system("clear");
	cout<<blue<<"====================================="<<endl
		<<"       M/M/K Queue Simulation        "<<endl
		<<"====================================="<<endl<<endl<<brown;
}


