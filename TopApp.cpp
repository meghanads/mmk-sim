/*	Name: Meghanad Shingate
 *	Roll No.:09307608
 *	Topic: M/M/K Queue Simulation
 *	Date: 5 October 2010
 *	Subject: Advance computing For Electrical Engineers
 */


#include<iostream>
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<vector>
#include<fstream>


#include"MyColor.cpp"
#include"TrafficGen.cpp"

// NOTE: CHANGE SIMULATION PARAMETERS HERE

#define SIMU_TM	1				//Simulation Time in seconds
#define IAT 10e-6				//Inter Arrival Time of packets Distributed Exponentially with mean IATM
#define  ST 20e-6				//Average Service Time Mean( Exp distributed)
#define SERVERS 2				//Number of servers
#define ITER	50				// Iterations
#define BUFF 0				//Buffer present in system ( put ZERO for infinite buffer)





using namespace std;

int FreeServer(void);
int NxtDepart(void);
int FreeServers(void);
int BusyServers(void);
int NowDepart(double);

double SERVER[SERVERS];

int main()
{

	

	Myclear();
	
	
	double ThrPut=0.0;	//throughput rate
	double Nsys=0.0;	//Number of customers waiting
	double Tsys=0.0;	//Time in syst
	double DROP=0.0;	//Dropped
	double ThrPutAvg=0.0;	//if BUFF!=0 then only applicable

	cout<<endl<<"NOTE: TO CHANGE PARAMETERS CHANGE MACROS IN TopApp.cpp FILE"<<endl; 

	cout<<green"SUMMERY:"<<endl
		<<"Simulation Time: "<<SIMU_TM<<" Sec."<<endl
		<<"Inter Arrival Time: "<<IAT<<" Sec."<<endl
		<<"Service Time Dist.: "<<ST<<" Sec."<<endl
		<<"Servers: "<<SERVERS<<endl
		<<"Buffer: "<<BUFF<<" (PUT ZERO FOR INFINITE BUFFER)"<<endl<<endl;


	cout<<red"ITER"<<"\t"<<"ThrPutRate"<<"\t"<<"Nsysi"<<"\t"<<"Tsysi"<<"\t"<<"\t|  ThrPutAvg"<<"\t"<<"NsysAvg"<<"\t"<<"TsysAvg"<<"\t\t| DROP"<<"\t| ThrPut(if BUFF!=0)"brown<<endl<<endl;


	for(int iter=0 ; iter<ITER ; iter++)
	{
		double RealTm =0.0;		//Running Time
		double NxtArr =0.0;		//Next Arrival (event #1)
		double NxtDep = SIMU_TM;//Next Departure Time (event #2)
		long int NumCust = 0;	// Number of customers in system
		
		double Succ = 0.0;		// Successful service complitions
		double AreaCust = 0.0;		//Number of customers in system
		double LstEve = RealTm;	//Last event time;
		double ThrPuti;			//Throuput Rate
		double Nsysi;			//mean Number of customers in system
		double Tsysi;			//mean System time
		double DROPi=0.0;			//Dropped packets or customers not able to get in Queue

		long int Arr, ArrQ;
		Arr=0;
		ArrQ=0;
		AreaCust=0.0;

		

		int Free, Ndep=0;
		double Dtm=0.0;

		for(int i=0;i<SERVERS;i++)
			SERVER[i] = 0.0;


		while(RealTm < SIMU_TM)
		{
			if(NxtArr < NxtDep)
			{
				RealTm = NxtArr;
				
				AreaCust = AreaCust + NumCust * (RealTm - LstEve);	//( Area under 'NumCust' curve)

				if((NumCust < BUFF) || (BUFF == 0))
				{
					ArrQ++;
					NumCust++;
				}
				else
					DROPi++;

				Arr++;

				LstEve = RealTm;

				NxtArr = RealTm + expntl(IAT);

				if((FreeServer() < SERVERS) && (NumCust > (BusyServers())))
				{
					Free = FreeServer();
					SERVER[Free] = RealTm + expntl(ST);
					NxtDep = SERVER[NxtDepart()];
					
				}

//				cout<<"IN IF:"<<"\t"<< RealTm<<"\t"<<NxtArr<<"\t"<<NxtDep<<"\t"<<NumCust<<"\t"<<FreeServers()<<endl;
				
			}
			else
			{
				RealTm = NxtDep;
				
				AreaCust = AreaCust + NumCust * (RealTm - LstEve);	//( Area under 'NumCust' curve)

		
				if(NowDepart(RealTm) < SERVERS)
				{
					SERVER[NowDepart(RealTm)] = 0.0;
					Succ++;
					NumCust--;
				}

				if((FreeServer() < SERVERS) && (NumCust > BusyServers()))
				{
					Dtm = RealTm + expntl(ST);
					if(Dtm < SIMU_TM)
						SERVER[FreeServer()]= Dtm;
					else
						SERVER[FreeServer()]= SIMU_TM;

					NxtDep= SERVER[NxtDepart()];
				}

				
							
				LstEve = RealTm;

			

				if(NxtDepart() < SERVERS)
					NxtDep = SERVER[NxtDepart()];
				else
					NxtDep = SIMU_TM;

//				cout<<"IN ELSE:"<<"\t"<< RealTm<<"\t"<<NxtArr<<"\t"<<NxtDep<<"\t"<<NumCust<<"\t"<<FreeServers()<<endl;

			}

		}

		ThrPuti = Succ / RealTm;		// Throughput Rate

		Nsysi = ceil(AreaCust / RealTm);	// Avg Number of customers waiting

		Tsysi = RealTm / ArrQ;	// Avg Waiting time

		DROPi= ceil( DROPi/ RealTm);

		if( iter != 0)
		{
			ThrPut=(ThrPut+ThrPuti)/2;
			Nsys=ceil((Nsys+Nsysi)/2);
			Tsys= (Tsys+Tsysi)/2;
			DROP=ceil((DROP+DROPi)/2);
			ThrPutAvg=(ThrPutAvg+(Arr-DROP)/Arr)/2;
		}
		else
		{
			ThrPut=ThrPuti;
			Tsys= Tsysi;
			Nsys= Nsysi;
			DROP=DROPi;
			ThrPutAvg=(Arr-DROP)/Arr;
		}


		if(Nsysi >0)
		cout<<iter<<"\t"<<ThrPuti<<"\t"<<"\t"<<Nsysi<<"\t"<<Tsysi<<"\t|  "<<ThrPut<<"\t"<<Nsys<<"\t"<<Tsys;
		
		if(BUFF != 0)
			cout<<"\t| "<<DROPi<<"\t| "<<(Arr-DROP)/Arr;
		else
			cout<<"\t| NA"<<"\t| NA";
		cout<<endl;

	}
	cout<<endl<<endl
		<<white"SIMULATION SUMMERY:"<<endl
		<<red"Average Number of Customers Getting Served per unit time: "blue<< ThrPut<<endl
		<<red"Average Number of Customers waiting in Queue: "blue<<Nsys<<endl
		<<red"Average Waiting Time for Customers: "blue<<Tsys<<endl
		<<red"Average Number of Customers Dropped: ";
	if(BUFF!=0)
		cout<<blue<<DROP<<endl;
	else
		cout<<blue<<"NA"<<endl;
	cout<<red"Avarage Throughput: ";
	if(BUFF!=0)
		cout<<blue<<ThrPutAvg<<endl<<endl;
	else
		cout<<blue<<"NA"<<endl<<endl;


}





/*************
 * Functions:
 * **********/


// Returns index of free server if present else returns (SERVERS+10)
int FreeServer()
{
	int i;
	for(i=0 ; i < SERVERS ; i++)
	{
		if(SERVER[i] == double(0.0))
			break;
	}

	if(i < SERVERS)
		return i;
	else
		return (SERVERS + 10);
	
}



// Returns index of server who is going to depart next, if all servers are free returns (SERVERS+10)
int NxtDepart()
{
	int i=0, min_i=0;
	double TempMin;

	while((SERVER[i] == double(0.0)) && (i < SERVERS ))
		i++;


	if( i >= SERVERS)
		return (SERVERS + 10);
	else
	{
		TempMin = SERVER[i];
		for(;i<SERVERS ; i++)
		{
			if((SERVER[i]<= TempMin) && (SERVER[i]>double(0.0)))
			{
				TempMin=SERVER[i];
				min_i=i;
			}
		}
		return min_i;
	}
}




// Returns number of free servers

int FreeServers()
{
	int i=0;
	for(int j=0; j<SERVERS ;j++)
	{
		if(SERVER[j]== double(0.0))
			i++;
	}
	return i;
}





//returns number of busy servers

int BusyServers()
{
	return (SERVERS - FreeServers());
}




// returns index of server who is going to depart at time TM
	
int NowDepart(double TM)
{
	int i = (SERVERS + 10);
	for(int j=0; j<SERVERS; j++)
	{
		if(SERVER[j] == TM)
			i=j;
	}

	return i;
}



/*
 * *****END OF CODE*****
 */

