

// Contains fuctions for traffic generation:



#include<math.h>
#include<fstream>
#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<time.h>

using namespace std;

/*******************************************
 * function: double expntl(double MN)
 * Input: MN, mean of exp RV
 * output: exp RV
 * ****************************************/


double expntl(double MN)
{
	double z;	//Uniform RV


	do
	{
		z=((double)rand()/RAND_MAX);
	}
	while((z==0) || (z==1));

	return(-(MN*log(z)));
}



/***********************************************************************
 * function: void GenTraffic( double MN, double TM)
 * Input: MN, mean of exp RV; TM time up to which we have to generate RV; TS time slot dutation
 * output: 'Traffic' file containig arrival instants of packets
 *
 * **********************************************************************/


void GenTraffic(double MN , double TM, double TS)
{
	int i=1, temp=0, temp1=0;
	long int thist=0, prevt=0;

	ofstream out1 ("Traffic", ios::out);
	ofstream out2 ("TrafficNorm", ios::out);
	ofstream out3 ("TrafficCum", ios::out);

	double tm, ctm=0;

	if(!out1)
	{
		cerr << "error in opening Traffic file"
			 << endl;
		exit(1);
	}


	do	
	{
		tm=expntl(MN);
		ctm = ctm + tm;
		if(ctm <= TM)
		{
			out1<<ctm;
			out1<<endl;

			out2<<ceil(ctm/TS);
			out2<<endl;
			
			thist=ceil(ctm/TS);

			if(prevt==thist || !temp)
			{
				i++;
				prevt=thist;
				temp=1;
			}
			else
			{
				if(!temp1)
				{
					out3<<(i-1);
					temp1=1;
				}
				else
				{
					out3<<i;
				}
				out3<<endl;
				i=1;
				prevt=thist;
			}



		}
	}
	while(ctm < TM);


}

