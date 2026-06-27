#ifndef CALENDAR_HEAD
#define CALENDAR_HEAD

#include<iostream>
#include<comm_func.h>

using namespace std;

int generate(int m,int startdate,int year)
{
	int flag = 0,k;
	int mdays[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	if(year%4==0){
		mdays[1] = 29;
	}
	cout<<"Su\tMo\tTu\tWe\tTh\tFr\tSa\n";
	for(int j=1;j<=mdays[m]+1;j++)
	{
		flag++;
		if(j==1)
		{
		for(k=0;k<startdate;k++)
		{
			cout<<"\t";
		}
	    }
	    if(j==8-startdate)	
		{
		cout<<endl;
		//chuma=j;
		flag=0;
		}
	    if(j==mdays[m]+1)
		{
			return (flag--);
			break;
		}
	    if(flag==7)
	    {
	    	cout<<endl;
	    	flag=0;
		}
		cout<<j<<"\t";
	}
}

void init_calendar(){
	char m_names[][12]={"January","February","March","April","May","June","July","August","September","October","November","December"};
	cout<<endl;
	char ch = 'y';
	do{
		cout<<"Enter the Year\n";
		int year; cin>>year;
		if(year<0)
		{
			cout<<"Please Enter greater than 0\n";
		}
		int j=0;
		int return_value;
		cout << endl << year;
		int starting_date;
		if (year<1900){
			cout << endl << "Enter Starting Date: ";
			cin >> starting_date;
			starting_date--;
		}
		else{
			starting_date = first_day(year);
		}
		int i,k;
		int month;
		for(month=0;month<12;month++)
		{
			cout<<endl<<endl;
			cout<<"Month: "<<m_names[month]<<endl<<endl<<endl;
			if(month==0)
			{
			return_value=generate(month,starting_date,year);
			}
			else
			{
			return_value=generate(month,return_value,year);
			}
			cout<<endl<<endl<<endl;
		}
		cout << endl << "More calendars to generate? (y/n): ";
		cin >> ch;
		ch = tolower(ch);
	}while(ch!='n');
}

#endif
