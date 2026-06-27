#ifndef TICTACTOE_HEAD
#define TICTACTOE_HEAD

struct prevent_repeatetion
{
		int a=0,b=0,c=0,d=0,e=0,f=0,g=0,h=0,l=0;
}; 
class tictac
{
	
	int che=0;
	char a='1';
	char b='2';
	char c='3';
	char d='4';
	char e='5';
	char f='6';
	char g='7';
	char h='8';
	char l='9';
	char sub=' ';
	char name1[20],name2[20];
	prevent_repeatetion box;
	

	int i,pos,j,k;
	char zz;
	public:
             
        void input_values()
        {
        	cout<<"Enter X And O Correspondingly\n";
        	system("cls");
        	while(che==0)
        	{
        		background_graphics();
        		cout<<endl<<endl<<endl<<endl;
        		cout<<"Enter the Position that you want to Attack: \n";
        		cin>>pos;
        		cout<<endl;
        		
        		if(pos==1)
        		{
        		if(box.a==0)
        		{
        			cout<<"Enter the Weapon you want to Deploy: ";
        			cin.ignore();
        			cin>>sub;
        		if((sub=='x')||(sub=='X')||(sub=='O')||(sub=='o'))
        		{
        			a=sub;
        			box.a+=1;
				}
				else 
				{
					cout<<"Enter a valid Response!!\nPress any key to continue...";
					getch();
					//goto cur;
				}
			}
			else{
				cout<<"Enter a valid Response!!\nPress any key to continue...";
				getch();
			}
			}
		
		else if(pos==2)
        		{
        		if(box.b==0)
        		{
        			cout<<"Enter the Weapon you want to Deploy: ";
        		//	cin.ignore();
        			cin>>sub;
        		if((sub=='x')||(sub=='X')||(sub=='O')||(sub=='o'))
        		{
        			b=sub;
        			box.b+=1;
				}
				else 
				{
					cout<<"Enter a valid Response!!\nPress any key to continue...";
					cin >> zz;
					//goto cur;
				}
		}
		else{
				cout<<"Enter a valid Response!!\nPress any key to continue...";
				getch();
			}
		    }
		   // system("pause");
	
		    	if(pos==3)
        		{
        		if(box.c==0)
        		{
        			cout<<"Enter the Weapon you want to Deploy: ";
        			cin>>sub;
        		if((sub=='x')||(sub=='X')||(sub=='O')||(sub=='o'))
        		{
        			c=sub;
        			box.c+=1;
				}
			
				else
				{
					cout<<"Enter a valid Response!!\nPress any key to continue...";
					getch();
					//goto cur;
				}
		}
		else{
				cout<<"Enter a valid Response!!\nPress any key to continue...";
				getch();
			}
		    }
		    
			
		  else  if(pos==4)
        		{
        		if(box.d==0)
        		{
        			cout<<"Enter the Weapon you want to Deploy: ";
        			cin.ignore();
        			cin>>sub;
        		if((sub=='x')||(sub=='X')||(sub=='O')||(sub=='o'))
        		{
        			d=sub;
        			box.d += 1;
				}
		    	else
				{
					cout<<"Enter a valid Response!!\nPress any key to continue...";
					getch();
					//goto cur;
				
		}
		    }
		    else{
				cout<<"Enter a valid Response!!\nPress any key to continue...";
				getch();
			}
		}
		    
			
		    
		  else  if(pos==5)
        		{
        		if(box.e==0)
        		{
        			cout<<"Enter the Weapon you want to Deploy: ";
        			cin>>sub;
        		if((sub=='x')||(sub=='X')||(sub=='O')||(sub=='o'))
        		{
        			e=sub;
        			box.e+=1;
				}
				else
				{
					cout<<"Enter a valid Response!!\nPress any key to continue...";
					getch();
					//goto cur;
				}
			}
			else{
				cout<<"Enter a valid Response!!\nPress any key to continue...";
				getch();
			}
		}
		   
		    
		else if(pos==6)	
        		{
        			
        		if(box.f==0)
        		{
        			cout<<"Enter the Weapon you want to Deploy: ";
        			cin>>sub;
        		if((sub=='x')||(sub=='X')||(sub=='O')||(sub=='o'))
        		{
        			f=sub;
        			box.f+=1;
				}
				else
				{
					cout<<"Enter a valid Response!!\nPress any key to continue...";
					getch();
					//goto cur;
				}
			}
			else{
				cout<<"Enter a valid Response!!\nPress any key to continue...";
				getch();
			}
			
			}
		    
		    
		  else  	if(pos==7)
        		{
        	if(box.g==0)
        		{
        			cout<<"Enter the Weapon you want to Deploy: ";
        			cin>>sub;
        		if((sub=='x')||(sub=='X')||(sub=='O')||(sub=='o'))
        		{
        			g=sub;
        			box.g+=1;
				}
			
				else
				{
					cout<<"Enter a valid Response!!\nPress any key to continue...";
					getch();
					//goto cur;
				}
			}
			else{
				cout<<"Enter a valid Response!!\nPress any key to continue...";
				getch();
			}
		    }
		    
		    
		  else if(pos==8)
        		{
        		 if(box.h==0)
        		{
        			cout<<"Enter the Weapon you want to Deploy: ";
        			cin>>sub;
        		if((sub=='x')||(sub=='X')||(sub=='O')||(sub=='o'))
        		{
        			h=sub;
        			box.h+=1;
				}
			
				else
				{
					cout<<"Enter a valid Response!!\nPress any key to continue...";
					getch();
					//goto cur;
				}
			}
			else{
				cout<<"Enter a valid Response!!\nPress any key to continue...";
				getch();
			}
		    }
		    
			
		else if(pos==9)
        		{
        			if(box.l==0)
        		{
        			cout<<"Enter the Weapon you want to Deploy: ";
        			cin>>sub;
        		if((sub=='x')||(sub=='X')||(sub=='O')||(sub=='o'))
        		{
        			l=sub;
        			box.l+=1;
				}
			
				else
				{
					cout<<"Enter a valid Response!!\nPress any key to continue...";
					getch();
					//goto cur;
				}
			}
			else{
				cout<<"Enter a valid Response!!\nPress any key to continue...";
				getch();
			}
			}
		    
		    
			system("cls");
			check();
	}
	}
		void starting_window()
		{		
			memset(name1,0,sizeof(name1));
			memset(name2,0,sizeof(name2));
			for(i=0;i<14;i++)
			{
			   cout<<endl;
			}
			cout<<"                      ....WELCOME TO YOUR XOX GAME....\n";
			for(i=0;i<3;i++)
			{
				cout<<endl;
			}
			cout<<"                        Enter Your Name (Player one): ";
			cin>>name1;
			cout<<endl;
			cout<<"                        Enter Your Name (Player two): ";
			cin>>name2; cout<<endl<<endl<<endl;
			cout<<"                      ALL THE  BEST FELLOW COMRADES!!!\n\n\n\n";
			system("pause");
			system("cls");
			cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
			cout<<"                 Your Game is Being Loaded\n";
			for(i=0;i<10000000;i++);
			cout<<endl<<endl<<endl<<endl<<endl;
			system("pause");
		}
        void check()
        {
        	if((((a=='X')||(a=='x'))&&((b=='X')||(b=='x'))&&((c=='X')||(c=='x')))||(((d=='X')||(d=='x'))&&((e=='X')||(e=='x'))&&((f=='X')||(f=='x')))||(((g=='X')||(g=='x'))&&((h=='X')||(h=='x'))&&((l=='X')||(l=='x')))||(((a=='X')||(a=='x'))&&((d=='X')||(d=='x'))&&((g=='X')||(g=='x')))||(((e=='X')||(e=='x'))&&((b=='X')||(b=='x'))&&((h=='X')||(h=='x')))||(((l=='X')||(l=='x'))&&((f=='X')||(f=='x'))&&((c=='X')||(c=='x')))||(((a=='X')||(a=='x'))&&((e=='X')||(e=='x'))&&((l=='X')||(l=='x')))||(((g=='X')||(g=='x'))&&((e=='X')||(e=='x'))&&((c=='X')||(c=='x'))))
        	{
        		player1_won();
			}
			else if((((a=='O')||(a=='o'))&&((b=='O')||(b=='o'))&&((c=='O')||(c=='o')))||(((d=='O')||(d=='o'))&&((e=='O')||(e=='o'))&&((f=='O')||(f=='o')))||(((g=='O')||(g=='o'))&&((h=='O')||(h=='o'))&&((l=='O')||(l=='o')))||(((a=='O')||(a=='o'))&&((d=='O')||(d=='o'))&&((g=='O')||(g=='o')))||(((e=='O')||(e=='o'))&&((b=='O')||(b=='o'))&&((h=='O')||(h=='o')))||(((l=='O')||(l=='o'))&&((f=='O')||(f=='o'))&&((c=='O')||(c=='o')))||(((a=='O')||(a=='o'))&&((e=='O')||(e=='o'))&&((l=='O')||(l=='o')))||(((g=='O')||(g=='o'))&&((e=='O')||(e=='o'))&&((c=='O')||(c=='o'))))
		{
			player2_won();
		}
		else{
			if(box.a && box.b && box.c && box.d && box.e && box.f && box.g && box.h && box.l){
				draw_match();
			}
		}
		}
		void player1_won()
		{
			system("cls");
			background_graphics();
			cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
			cout<<"                      .....Congratulations....\n";
			cout<<endl<<endl;
			cout<<"                      "<<name1<<" Has Won Over "<<name2;
			cout<<endl<<endl<<endl<<endl<<endl;
			system("pause");
			che++;
			
		}
		void player2_won()
		{
			system("cls");
			background_graphics();
			cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
			cout<<"                      .....Congratulations....\n";
			cout<<endl<<endl;
			cout<<"                      "<<name2<<" Has Won Over "<<name1;
			cout<<endl<<endl<<endl<<endl<<endl;
			system("pause");
		    che++;
		}
		void draw_match(){
			system("cls");
			background_graphics();
			cout<<endl<<endl<<endl<<endl<<endl<<endl<<endl<<endl;
			cout << endl << "This Game Was a DRAW!";
			cout<<endl<<endl<<endl<<endl<<endl;
			system("pause");
		    che++;
		}
		
        void background_graphics()
		{
			cout<<endl<<endl<<endl<<endl<<endl;
			cout<<"                                |              |                 \n";
			cout<<"                                |              |                 \n";
			cout<<"                        "<<a<<"       |       "<<b<<"      |      "<<c<<"          \n";
			cout<<"                                |              |                 \n";
			cout<<"                  ______________|______________|______________  \n";
			cout<<"                                |              |                 \n";
			cout<<"                                |              |                 \n";
			cout<<"                        "<<d<<"       |       "<<e<<"      |       "<<f<<"          \n";
			cout<<"                                |              |                 \n";
			cout<<"                  ______________|______________|______________  \n";
			cout<<"                                |              |                 \n";
			cout<<"                                |              |                 \n";
			cout<<"                        "<<g<<"       |       "<<h<<"      |       "<<l<<"          \n";
			cout<<"                                |              |                 \n";
			cout<<"                                |              |                 \n";
			cout<<endl<<endl<<endl<<endl;		
			
		}
};

#endif
