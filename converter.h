#ifndef CONVERTER_HEAD
#define CONVERTER_HEAD

#include<iostream>
using namespace std;

void init_converter(){
	int a = 1;
	curr:	while(a)
	{
	cout<<"Welcome to conversions..\n";
	cout<<endl;
	cout<<"MENU DRIVEN\n";
	cout<<"1. Length\n";
	cout<<"2. Weight\n";
	cout<<"3. Area\n";
	cout<<"4. Power\n";
	cout<<"5. Temperature\n";
	cout<<"6. Main Menu\n";
	cout<<endl;
	cout<<"Enter your Choice: ";
	int n,m;cin>>n;
	float val;
	switch(n)
	{
		case 1:
		        while(1)
		        {
		        cout<<"1. Centimeters -   Inches \n";
		        cout<<"2. Feet        -   Centimeters\n";
		        cout<<"3. Meter       -   Yards\n";
		        cout<<"4. Meter       -   Feet\n";
		        cout<<"5. Kilometer   -   Miles\n";
		        cout<<"6. Previous Menu\n";
		        cout<<"Enter your Choice: ";
		        cin>>m;
		        cout<<endl;
		        switch(m)
		        {
		        	case 1: 
		        	cout<<endl;
		        	cout<<"Enter in cm: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*0.3937<<" inches";
		        	break;
		        	
		        	case 2: 
		        	cout<<endl;
		        	cout<<"Enter in Feet: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*30.4801<<" centimeters";
		        	break;
		        	
		        	case 3:
		        	cout<<endl;
		        	cout<<"Enter in Meter: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*1.0936<<" yards";
		        	break;
		        	
		        	case 4:
		        	cout<<endl;
		        	cout<<"Enter in Meter: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*3.3<<" feets";
		        	break;
		        	
		        	case 5:
		        	cout<<endl;
		        	cout<<"Enter in Kilometer: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*0.6214<<" Miles";
		        	break;
		        	
		        	case 6:
		        cout<<endl<<endl;
		        		goto curr;
		        		
		        		default: cout<<"Wrong Option.\n";
		        		
		        	
				}
				cout<<endl<<endl;
			}
			break;
		
		case 2:  
		while(1)
		{
		      	cout<<"1. Pound       -   Kilograms \n";
		        cout<<"2. Kilograms   -   Pounds\n";
		        cout<<"3. Ounce       -   Grams\n";
		        cout<<"4. Grams       -   Ounce\n";
		        cout<<"5. Go to Main Menu\n";
		        cout<<"Enter your Choice: ";
		        cin>>m;
		        cout<<endl;
		        switch(m)
		        {
		        	case 1:
		        	cout<<endl;
		        	cout<<"Enter in Pounds: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*0.4536<<" Kilograms";
		        	break;
		        	
		        	case 2:
		        	cout<<endl;
		        	cout<<"Enter in Kilograms: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*2.205<<" Pounds";
		        	break;
		        	
		        	case 3:
		        	cout<<endl;
		        	cout<<"Enter in Ounce: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*28.3495<<" Grams";
		        	break;
		        	
		        	case 4:
		        	cout<<endl;
		        	cout<<"Enter in Grams: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*0.03527<<" Ounces";
		        	break;
		        	
		        	case 5:
		       	cout<<endl<<endl;
		        		goto curr;
		        		break;
		        		
		        		default: cout<<"Wrong Choice\n";
				}
				cout<<endl<<endl;
				system("pause");
		}
		break;
		
		case 3:
				while(1)
		{
		      	cout<<"1. Sq.Inch       - Sq.Centimters \n";
		        cout<<"2. Sq.foot       - Sq.Centimeters\n";
		        cout<<"3. Hectare       - Sq.Meters\n";
		        cout<<"4. Go to Main Menu\n";
		        cout<<"Enter your Choice: ";
		        cin>>m;
		        cout<<endl;
		        switch(m)
		        {
		        	case 1: 
					cout<<endl;
		        	cout<<"Enter in Sq.Inch: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*6.4516<<" Sq.Centimeters";
		        	break;
		        	
		        	case 2:
		        	cout<<endl;
		        	cout<<"Enter in Sq.Feet: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*929<<" Sq.Centimeters";
		        	break;
		        	
		        	case 3:
		        	cout<<endl;
		        	cout<<"Enter in Hectares: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*1000.0<<" Sq.Meters";
		        	break;
		        	
		        	case 4:
		       	cout<<endl<<endl;
		        		goto curr;
		        		break;
		        		
		        		default: cout<<"Wrong Choice.\n";
			}
	         	cout<<endl<<endl;
	}
	break;
	
	case 4:
			while(1)
		{
		      	cout<<"1. Whatts        - Horse Power  \n";
		        cout<<"2. Horse Power   - Whatts\n";
		        cout<<"3. Go to Main Menu\n";
		        cout<<"Enter your Choice: ";
		        cin>>m;
		        cout<<endl;
		        switch(m)
		        { 
		        case 1: cout<<endl;
		        	cout<<"Enter in Watt: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val/745.7<<" Horse Power";
		        	break;
		        	
		        case 2: 
		            cout<<endl;
		        	cout<<"Enter in Horse Power: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*746.5<<" Whatts";
		        	break;
		        	
		        case 3:
		        cout<<endl<<endl;
		        	goto curr;
		        		break;
		        		
		        		default: cout<<"Wrong Choice.\n";
			}
			    cout<<endl<<endl;
	}
	break;
	case 5: 
	
	while(1)
		{
		      	cout<<"1. Celcius       - Kelvin  \n";
		        cout<<"2. Kelvin        - Celcius\n";
		        cout<<"3. Celcius       - Fahrenheit\n";
		        cout<<"4. Go to Main Menu\n";
		        cout<<"Enter your Choice: ";
		        cin>>m;
		        cout<<endl;
		        switch(m)
		        { 
		        case 1:
		            cout<<endl;
		        	cout<<"Enter in Celcius: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val+273<<" Kelvin";
		        	break;
		        	
		        	case 2:
		        		cout<<endl;
		        	cout<<"Enter in Kelvin: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val-273<<" Celcius";
		        	break;
		        	
		        	case 3:
		        		cout<<endl;
		        	cout<<"Enter in Celcius: ";
		        	cin>>val;
		        	cout<<endl;
		        	cout<<"Result : "<<val*9/5+32<<" Fahrenheit";
		        	break;
		        	
		        	case 4:
		       	cout<<endl<<endl;
				system("pause");
		        		goto curr;
		        		break;
		        		
		        		
		        		default: cout<<"Wrong Choice.\n";
			}
			    cout<<endl<<endl;
				system("pause");
		}
	case 6:
		a = 0;		
	}
	}
}

#endif
