#include<iostream>
#include<iomanip>
#include<thread>
#include<conio.h>
#include<math.h>
#include<server.h>
#include<client.h>
#include<windows.h>
#include<ip_finder.h>
#include<stdlib.h>
#include<user.h>
#include<comm_func.h>
#include<operations.h>
#include<calendar.h>
#include<tictactoe.h>
#include<calculator.h>
#include<converter.h>

void beginSession(user curr){
	bool logout = false;
	char currdir[LEN];
	char userdir[LEN];
	getcwd(currdir,LEN);
	strcpy(userdir,currdir);
	strcat(userdir,"\\users\\");
	char u_em[250];
	curr.fetch_email(u_em);
	strcat(userdir,u_em);
	
	while(true&&!logout){
		char curr_ip[15];
		char peer_ip[15];
		
		char main_ch;
		char u_name[20];
		curr.fetch_name(u_name);
		system("cls");
		cout << endl << "Current User: " << u_name << "!";
		cout << endl << "1-Local Chat\n2-Evaluate Expressions\n3-Unit Converter\n4-Year Calender\n5-Tic-Tac-Toe Game\n6-Notes/Memos\n7-Scientific Calculator\n8-Manage Account\n9-Log Out\nEnter Choice: ";
		cin >> main_ch;
		
		if(main_ch=='1'){
			char chat_ch;
			cout << endl << "______________________________LOCAL CHAT______________________________" << endl;
			while(true){
				cout << endl << "1-Initiate Request\n2-Accept Request\n3-Chat History\n4-Main Menu\nEnter Choice: ";
				cin >> chat_ch;
				
				if(chat_ch=='1'){
					char chs;
					my_ip(curr_ip);
					SOCKET Listen;
					cout << endl << "Target must use this IP Address to Accept your request\n" << curr_ip << endl;
					Listen = InitServer(curr_ip);
					
					if(Listen==INVALID_SOCKET){
						cout << endl << "Server Error Occurred!\nPlease retry shortly..." << endl;
						continue;
					}
					else{
						SOCKET Client;
						Client = EngageServer(Listen,curr_ip);
						
						if (Client==INVALID_SOCKET){
							cout << endl << "Couldn't Connect to Client.\nEnsure that client entered the correct IP..." << endl;
						}
						else{
							struct sockaddr_in detail;
							socklen_t det_len = sizeof(detail);
							getpeername(Client,(struct sockaddr*)&detail,&det_len);
							strcpy(peer_ip,inet_ntoa(detail.sin_addr));
							
							cout << endl << "Connected to " << peer_ip << " successfully! " << endl;
							
							ofstream sfout;
							char now[200];
							strcpy(now,userdir);
							strcat(now,"\\chats\\");
							char store_t[30];
							date_time_now(store_t);
							strcat(now,store_t);
							strcat(now,".txt");
							char now_[200];
							corr_fname(now,now_);
							sfout.open(now_,ios::out);
							sfout << curr_ip << endl << peer_ip;
							
							thread ReceiveProcessServer(ReceiveDataServer,Client, peer_ip, std::ref(sfout));
							int res_ser;
							while(true){
								cout << endl << "1-Send Text\n2-Terminate Connection\nEnter Choice: ";
								cin >> chs;
								if(chs=='1'){
									res_ser = SendDataServer(Client,std::ref(sfout));    //(std::ref)Creating a reference_wrapper that will be later unpacked in the function
									if(res_ser==1){
										;
									}
									else if(res_ser==10053 or res_ser==10054){
										cout << endl << "Target closed the connection! Exiting chat... " << endl;
										closesocket(Client);
										WSACleanup();
										break;
									}
								}
								else if(chs=='2'){
									closesocket(Client);
									WSACleanup();
									break;
								}
								else{
									cout << endl << "Invalid Choice!" << endl;
									continue;
								}
							}
							ReceiveProcessServer.join();
							sfout.close();
							
							ifstream check;
							trim(now_,strlen(now_));
							check.open(now_,ios::in);
							char data[100];
							int ctr = 0;
							while(check){
								check.getline(data,100);
								ctr++;
							}
							check.close();
							if (ctr<=3){
								remove(now_);
							}
						}
					}
				}
				
				else if(chat_ch=='2'){
					char acip[15];
					bool chat_entry = false;
					SOCKET Conn;
					
					
					cin.ignore();
					while(true){
						cout << endl << "Enter IP Address to connect to (X to go back): ";
						gets(acip);
						
						if(strlen(acip)==1){
							if(acip[0]=='X' or acip[0]=='x'){
								break;
							}
						}
						
						cout << endl << "Attempting Connection..." << endl;
						
						Conn = ConnectServer(acip);
						if(Conn==INVALID_SOCKET){
							cout << endl << "Connection Failed!\nPlease Re-Enter the correct IP or press X to exit\nMake sure your peer has started the request" << endl;
							continue;
						}
						else{
							chat_entry = true;
							break;
						}
					}
					
					if(chat_entry){
						cout << endl << "Connected to " << acip << " successfully! " << endl;
						
						ofstream cfout;
						char now[200];
						strcpy(now,userdir);
						strcat(now,"\\chats\\");
						char store_t[30];
						date_time_now(store_t);
						strcat(now,store_t);
						strcat(now,".txt");
						char now_[200];
						corr_fname(now,now_);
						cfout.open(now_,ios::out);
						my_ip(curr_ip);
						cfout << curr_ip << endl << acip;
						
						thread ReceiveProcessClient(ReceiveDataClient,Conn,acip,std::ref(cfout));
						int res_cl;
						char chc;
						while(true){
							cout << endl << "1-Send Text\n2-Terminate Connection\nEnter Choice: ";
							cin >> chc;
							if(chc=='1'){
								res_cl = SendDataClient(Conn,std::ref(cfout));
								if(res_cl==1){
									;
								}
								else if(res_cl==10053 or res_cl==10054){
									cout << endl << "Target closed the Connection! Exiting... " << endl;
									break;
								}
							}
							else if(chc=='2'){
								closesocket(Conn);
								break;
							}
							else{
								cout << endl << "Invalid Choice!" << endl;
								continue;
							}
						}
						ReceiveProcessClient.join();
						cfout.close();
						
						ifstream check;
						trim(now_,strlen(now_));
						check.open(now_,ios::in);
						char data[100];
						int ctr = 0;
						while(check){
							check.getline(data,100);
							ctr++;
						}
						check.close();
						if (ctr<=3){
							remove(now_);
						}
					}
				}
				else if(chat_ch=='3'){
					char cd[200];
					memset(cd,0,sizeof(cd));
					strcpy(cd,userdir);
					strcat(cd,"\\chats");
					char ind[100][10];
					char cont[100][100];
					int ctr = 0;
					DIR *dir;
					dir = opendir(cd);
					struct dirent *file;
					char ctr_ch[10];
					cout << endl << "YOUR CHAT HISTORY" << endl;
					while (file=readdir(dir)){
						if(file->d_name[0]!='.'){
							num_to_charr(ctr+1,ctr_ch);
							strcpy(ind[ctr],ctr_ch);
							strcpy(cont[ctr],file->d_name);
							cout << endl << ctr+1 << " - " << file->d_name;
							ctr++;
						}
					}
					closedir(dir);					
					
					if(ctr==0){
						cout << endl << "No chat history available!" << endl;
						continue;
					}
					
					char f_ch[10];
					cout << endl << "\nChoose file to open (1 to " << ctr << ")\nNOTE: Enter 'X' to exit: ";
					cin.ignore();
					gets(f_ch);
					int retval = search_in(ind,ctr,f_ch);
					if(retval==-1){
						f_ch[0] = tolower(f_ch[0]);
						if(strcmp(f_ch,"x")==0){
							cout << endl << "Exiting..." << endl;
							break;
						}
						else{
							cout << endl << "Invalid Choice!" << endl;
							continue;
						}
					}
					else{
						strcat(cd,"\\");
						strcat(cd,cont[retval]);
						ifstream fin;
						fin.open(cd,ios::in);
						char data[1000];
						fin.getline(data,1000);
						cout << endl << "\t\t" << endl << "__________________________________________________________________";
						cout << endl << "Your IP Was: " << data;
						fin.getline(data,1000);
						cout << endl << "Peer IP Was: " << data << endl;
						while(fin){
							fin.getline(data,1000);
							cout << endl << data;
						}
						cout << endl << "\t\tEND OF CHAT" << endl << "__________________________________________________________________" << endl;
					}
				}
				else if(chat_ch=='4'){
					break;
				}
				else{
					cout << endl << "Invalid Choice!" << endl;
				}
			}
		}
		
		else if(main_ch=='2'){
			cout << endl << "_________________________EXPRESSION EVALUATOR__________________________" << endl;
			char exp_ch;
			
			while(true){
				cout << endl << "1-Evaluate One-Line Expression\n2-Only Convert to Postfix\n3-Previous Menu\nEnter Choice: ";
				cin >> exp_ch;
				if(exp_ch=='1'){
					char exp[200];
					char post[200];
					float ans;
					cout << endl << "Enter Expression (with brackets) \nNOTE: For multi-digit constants, enter variable and provide value at prompt\n      For single-digit constants, values can be entered directly\nEg: For 2+(3*24.87) ---> 2+(3*A), where A=24.87 " << endl;
					cin.ignore();
					gets(exp);
					evaluate(exp,post,ans);
					cout << endl << "Final Answer: " << ans << endl;
				}
				else if(exp_ch=='2'){
					char exp[200];
					char post[200];
					cout << endl << "Enter Expression (with brackets)\nNOTE: Only single-character constants or variables" << endl;
					cin.ignore();
					gets(exp);
					in_to_post(exp,post);
					cout << endl << "Postfix Expression: " << post << endl;
				}
				else if(exp_ch=='3'){
					break;
				}
				else{
					cout << endl << "Invalid Choice!" << endl;
					continue;
				}
			}
		}
		
		else if(main_ch=='3'){
			cout << endl << "____________________________UNIT CONVERTER____________________________" << endl;
			init_converter();
		}
		else if(main_ch=='4'){
			cout << endl << "_______________________________CALENDAR_______________________________" << endl;
			init_calendar();
		}
		
		else if(main_ch=='5'){
			cout << endl << "______________________________TIC-TAC-TOE______________________________" << endl;
			tictac obj;
		 	obj.starting_window();
			cout<<"The Player's Battleground: \n";
			obj. background_graphics();
			obj.input_values();
			cout << endl << "Exiting..." << endl;
		}
		
		else if(main_ch=='6'){
			cout << endl << "_________________________________MEMOS________________________________" << endl;
			bool add_e;
			char mem_ch;
			char here[200];
			char name[20];
			while(true){
				cout << endl << "1-Add Memo\n2-Read memo\n3-Delete Memo\n4-Previous Menu\nEnter Choice: ";
				cin >> mem_ch;
				cin.ignore();
				if(mem_ch=='1'){
					ifstream fin;
					ofstream fout;
					memset(here,0,sizeof(here));
					strcpy(here,userdir);
					strcat(here,"\\memos\\");
					add_e = true;
					while(add_e){
						memset(name,0,sizeof(name));
						cout << endl << "Enter Memo Name('X' to go back): ";
						gets(name);
						int len = strlen(name);
						if(len==1){
							if(name[0]=='x' or name[0]=='X'){
								add_e = false;
								break;
							}
						}
						trim(name,100);
						if(len>25 or len<3){
							cout << endl << "Name should be between 3 and 25 characters. \nYou entered " << strlen(name) << " characters"<< endl;
							continue;
						}
						else{
							strcat(here,name);
							strcat(here,".txt");
							fin.open(here,ios::in);
							if(fin){
								cout << endl << "Memo with that name already exists!" << endl;
								continue;
							}
							fin.close();
							break;
						}
					}
					if(!add_e){
						continue;
					}
					fout.open(here);
					char data[100];
					char ch;
					while(true){
						cout << endl << "Enter Data" << endl;
						gets(data);
						fout << data << '\n';
						cout << endl << "More data to enter(y/n)?: ";
						cin >> ch;
						cin.ignore();
						if(ch=='n'){
							break;
						}
					}
					fout.close();
					cout << endl << "Memo Stored" << endl;
				}
				else if(mem_ch=='2'){
					char f_ch[10];
					memset(f_ch,0,sizeof(f_ch));
					char cd[200];
					strcpy(cd,userdir);
					strcat(cd,"\\memos");
					char ind[100][10];
					char cont[100][100];
					int ctr = 0;
					DIR *dir;
					dir = opendir(cd);
					struct dirent *file;
					char ctr_ch[10];
					cout << endl << "YOUR MEMOS" << endl;
					while (file=readdir(dir)){
						if(file->d_name[0]!='.'){
							num_to_charr(ctr+1,ctr_ch);
							strcpy(ind[ctr],ctr_ch);
							strcpy(cont[ctr],file->d_name);
							cout << endl << ctr+1 << " - " << file->d_name;
							ctr++;
						}
					}
					closedir(dir);
					
					if(ctr==0){
						cout << endl << "No memos available!" << endl;
						continue;
					}
					
					cout << endl << "\nChoose file to open (1 to " << ctr << ")\nNOTE: Enter 'X' to exit: ";
					gets(f_ch);
					int retval = search_in(ind,ctr,f_ch);
					if(retval==-1){
						f_ch[0] = tolower(f_ch[0]);
						if(strcmp(f_ch,"x")==0){
							cout << endl << "Exiting..." << endl;
							break;
						}
						else{
							cout << endl << "Invalid Choice!" << endl;
							continue;
						}
					}
					else{
						strcat(cd,"\\");
						strcat(cd,cont[retval]);
						ifstream fin;
						fin.open(cd,ios::in);
						char ch;
						cout << endl << "CONTENTS OF '" << cont[retval] << "'\n" << endl;
						cout << "________________________________________________________" << endl;
						while(fin){
							fin.get(ch);
							cout << ch;
						}
						cout << endl << "________________________________________________________" << endl;
					}
				}
				else if(mem_ch=='3'){
					char ch;
					char f_ch[10];
					memset(f_ch,0,sizeof(f_ch));
					char cd[200];
					strcpy(cd,userdir);
					strcat(cd,"\\memos");
					char ind[100][10];
					char cont[100][100];
					int ctr = 0;
					DIR *dir;
					dir = opendir(cd);
					struct dirent *file;
					char ctr_ch[10];
					cout << endl << "YOUR MEMOS" << endl;
					while (file=readdir(dir)){
						if(file->d_name[0]!='.'){
							num_to_charr(ctr+1,ctr_ch);
							strcpy(ind[ctr],ctr_ch);
							strcpy(cont[ctr],file->d_name);
							cout << endl << ctr+1 << " - " << file->d_name;
							ctr++;
						}
					}
					closedir(dir);
					
					if(ctr==0){
						cout << endl << "No memos available!" << endl;
						continue;
					}
					
					cout << endl << "\nChoose file to delete (1 to " << ctr << ")\nNOTE: Enter 'X' to exit: ";
					gets(f_ch);
					int retval = search_in(ind,ctr,f_ch);
					if(retval==-1){
						f_ch[0] = tolower(f_ch[0]);
						if(strcmp(f_ch,"x")==0){
							cout << endl << "Exiting..." << endl;
							break;
						}
						else{
							cout << endl << "Invalid Choice!" << endl;
							continue;
						}
					}
					else{
						strcat(cd,"\\");
						strcat(cd,cont[retval]);
						cout << endl << "Delete '" << cont[retval] << "' ? (y/n): ";
						cin >> ch;
						if(ch=='y'){
							remove(cd);
							cout << endl << "Deleted!" << endl;
						}
						else{
							cout << endl << "Deletion Aborted!" << endl;
						}
					}
				}
				else if(mem_ch=='4'){
					break;
				}
				else{
					cout << endl << "Invalid Choice";
					continue;
				}
			}
		}
		
		else if(main_ch=='7'){
			cout << endl << "_________________________SCIENTIFIC CALCULATOR_________________________" << endl;
			init_calculator();
		}
		
		else if(main_ch=='8'){
			cout << endl << "______________________________YOUR ACCOUNT______________________________" << endl;
			char man_ch;
			logout = false;
			while(true&&!logout){
				cout << endl << "1-Change Password\n2-Delete Account\n3-Reset Account\n4-Forgot Password\n5-Previous Menu\nEnter Choice: ";
				cin >> man_ch;
				if(man_ch=='1'){
					int tries = 3;
					cin.ignore();
					while(tries>0){
						char pass[20];
						cout << endl << "Enter Password: ";
						gets(pass);
						tries--;
						char comp[20];
						curr.fetch_pwd(comp);
						if(strcmp(comp,pass)){
							cout << "Incorrect Password! Tries Left: " << tries << endl << endl;
						}
						else{
							tries = 3;
							curr.get_pwd();
							user temp1, temp2;
							ofstream fout1,fout2;
							ifstream fin1,fin2;
							fin1.open("user_em.dat",ios::in);
							fin2.open("user_mob.dat",ios::in);
							fout1.open("temp1.dat",ios::out);
							fout2.open("temp2.dat",ios::out);
							bool flag1 = false;
							bool flag2 = false;
							while(fin1||fin2){
								if(fin1){
									fin1.read((char*)&temp1,sizeof(temp1));
								}
								if(fin2){
									fin2.read((char*)&temp2,sizeof(temp2));					
								}
								if(fin1){
									char comp[250];
									temp1.fetch_email(comp);
									char here[250];
									curr.fetch_email(here);
									if(strcmp(comp,here)==0){         //lexicographical ordering check
										fout1.write((char*)&curr,sizeof(curr));
									}
									else{
										fout1.write((char*)&temp1,sizeof(temp1));
									}
								}
								if(fin2){
									long long int comp;
									temp2.fetch_mob(comp);
									long long int here;
									curr.fetch_mob(here);
									if(comp==here){
										fout2.write((char*)&curr,sizeof(curr));
									}
									else{
										fout2.write((char*)&temp2,sizeof(temp2));
									}
								}
							}
							fin1.close();
							fin2.close();
							fout1.close();
							fout2.close();
							remove("user_em.dat");
							remove("user_mob.dat");
							rename("temp1.dat","user_em.dat");
							rename("temp2.dat","user_mob.dat");
							cout << endl << "Password Changed Successfully!" << endl;
							logout = true;
							break;
						}
					}
					if(tries<=0){
						cout << endl << "Too many incorrect login attempts. Make sure its the correct User ID" << endl;
						cin.ignore();
						logout = true;
						break;
					}
				}
				else if(man_ch=='2'){
					int tries = 3;
					cin.ignore();
					while(tries>0){
						char pass[20];
						cout << endl << "Enter Password: ";
						gets(pass);
						tries--;
						char comp[20];
						curr.fetch_pwd(comp);
						if(strcmp(comp,pass)){
							cout << "Incorrect Password! Tries Left: " << tries << endl << endl;
						}
						else{
							char ch;
							cout << endl << "Are you sure you want to delete the account?(y/n): ";
							ch = tolower(ch);
							cin >> ch;
							if(ch=='n'){
								cout << endl << "Aborting..." << endl;
								tries = 3;
								break;
							}
							else if(ch=='y'){
								user temp1, temp2;
								ofstream fout1,fout2;
								ifstream fin1,fin2;
								fin1.open("user_em.dat",ios::in);
								fin2.open("user_mob.dat",ios::in);
								fout1.open("temp1.dat",ios::out);
								fout2.open("temp2.dat",ios::out);
								while(fin1||fin2){
									if(fin1){
										fin1.read((char*)&temp1,sizeof(temp1));
									}
									if(fin2){
										fin2.read((char*)&temp2,sizeof(temp2));					
									}
									if(fin1){
										char comp[250];
										temp1.fetch_email(comp);
										char here[250];
										curr.fetch_email(here);
										if(strcmp(comp,here)==0){         //lexicographical ordering check
											;
										}
										else{
											fout1.write((char*)&temp1,sizeof(temp1));
										}
									}
									if(fin2){
										long long int comp;
										temp2.fetch_mob(comp);
										long long int here;
										curr.fetch_mob(here);
										if(comp==here){
											;
										}
										else{
											fout2.write((char*)&temp2,sizeof(temp2));
										}
									}
								}
								fin1.close();
								fin2.close();
								fout1.close();
								fout2.close();
								remove("user_em.dat");
								remove("user_mob.dat");
								rename("temp1.dat","user_em.dat");
								rename("temp2.dat","user_mob.dat");
								fin1.open("user_em.dat",ios::out);
								fin1.close();
								fin1.open("user_em.dat",ios::out);
								fin1.close();
								del_dir(userdir);
								cout << endl << "Account Deletion Initiated! Please Close and Re-Open the program to complete the process" << endl;
								logout = true;
								break;
							}
						}
					}
					if(tries<=0){
						cout << endl << "Too many incorrect login attempts. Make sure its the correct User ID" << endl;
						logout = true;
						break;
					}
				}
				else if(man_ch=='3'){
					int tries = 3;
					cin.ignore();
					while(tries>0){
						char pass[20];
						cout << endl << "Enter Password: ";
						gets(pass);
						tries--;
						char comp[20];
						curr.fetch_pwd(comp);
						if(strcmp(comp,pass)){
							cout << "Incorrect Password! Tries Left: " << tries << endl << endl;
						}
						else{
							char ch;
							cout << endl << "Are you sure you want to reset the account?(y/n): ";
							ch = tolower(ch);
							cin >> ch;
							if(ch=='n'){
								cout << endl << "Aborting..." << endl;
								tries = 3;
								break;
							}
							else if(ch=='y'){
								char rem[200];
								strcpy(rem,userdir);
								strcmp(rem,"\\chats");
								del_dir(userdir);
								cout << endl << "Account Reset Complete!" << endl;
								logout = true;
								break;
							}
						}
					}
					if(tries<=0){
						cout << endl << "Too many incorrect login attempts. Make sure its the correct User ID" << endl;
						logout = true;
						break;
					}
				}
				else if(man_ch=='4'){
					char sk_entry[10];
					cin.ignore();
					cout << endl << "Enter Secret-Key: ";
					gets(sk_entry);
					if(!all_digit(sk_entry)){
						cout << endl << "Incorrect Secret-Key" << endl;
						continue;
					}
					if(strlen(sk_entry)!=6){
						cout << endl << "Incorrect Secret-Key" << endl;
						continue;
					}
					int sk;
					charr_to_num(sk_entry,sk);
					if(sk!=curr.fetch_sk()){
						cout << endl << "Incorrect Secret-Key" << endl;
						continue;
					}
					curr.get_pwd();
					user temp1, temp2;
					ofstream fout1,fout2;
					ifstream fin1,fin2;
					fin1.open("user_em.dat",ios::in);
					fin2.open("user_mob.dat",ios::in);
					fout1.open("temp1.dat",ios::out);
					fout2.open("temp2.dat",ios::out);
					bool flag1 = false;
					bool flag2 = false;
					while(fin1||fin2){
						if(fin1){
							fin1.read((char*)&temp1,sizeof(temp1));
						}
						if(fin2){
							fin2.read((char*)&temp2,sizeof(temp2));					
						}
						if(fin1){
							char comp[250];
							temp1.fetch_email(comp);
							char here[250];
							curr.fetch_email(here);
							if(strcmp(comp,here)==0){         //lexicographical ordering check
								fout1.write((char*)&curr,sizeof(curr));
							}
							else{
								fout1.write((char*)&temp1,sizeof(temp1));
							}
						}
						if(fin2){
							long long int comp;
							temp2.fetch_mob(comp);
							long long int here;
							curr.fetch_mob(here);
							if(comp==here){
								fout2.write((char*)&curr,sizeof(curr));
							}
							else{
								fout2.write((char*)&temp2,sizeof(temp2));
							}
						}
					}
					fin1.close();
					fin2.close();
					fout1.close();
					fout2.close();
					remove("user_em.dat");
					remove("user_mob.dat");
					rename("temp1.dat","user_em.dat");
					rename("temp2.dat","user_mob.dat");
					cout << endl << "New Password Set Successfully!" << endl;
					logout = true;
					break;
				}
				else if(man_ch=='5'){
					break;
				}
				else{
					cout << endl << "Invalid Choice!" << endl;
					continue;
				}
			}
			if(logout){
				cout << endl << "Saved Changes\nLogging Out..." << endl;
				Sleep(500);
				system("cls");
			}
		}
		
		else if(main_ch=='9'){
			cout << endl << "Logging Out..." << endl << endl;
			Sleep(500);
			system("cls");
			break;
		}
		
		else{
			cout << endl << main_ch;
			cout << endl << "Invalid Choice!" << endl;
		}
	}
}

int main(){	
	initial_check();
	system("CLS");
	
	/*user obj;
	ifstream fin;
	fin.open("user_em.dat",ios::in);
	while(fin){
		fin.read((char*)&obj,sizeof(obj));
		obj.display();
	}
	fin.close();
	cout << endl;
	fin.open("user_mob.dat",ios::in);
	while(fin){
		fin.read((char*)&obj,sizeof(obj));
		obj.display();
	}
	fin.close();*/
	
	char log_ch;
	user temp;
	bool logout;
	
	while(true){
		//system("CLS");
		logout = false;
		cout << endl << "_________________INFINITY-OS Welcomes You!_________________" << endl;
		cout << endl << "1-Login\n2-Register New Account\n3-Forgot Password\n4-Exit\nEnter Choice: ";
		cin >> log_ch;
		if(log_ch=='1'){
			char uid[250];
			long long int mob = 0;
			while(true&&!logout){
				memset(uid,0,250);
				cout << endl << "LOGIN";
				cout << endl << "Enter Mobile No./Email ID: ";
				cin.ignore();
				gets(uid);
				long long int mob = 0;
				int result = diff_em_mob(uid,mob);
				if(result==0){
					cout << endl << "Invalid or Unregistered User ID" << endl;
					break;
				}
				
				int tries = 3;
				while(tries>0){
					char pass[20];
					cout << "Enter Password: ";
					gets(pass);
					tries--;
					bool ses;
					user present;
					if(result==1){
						ses = temp.login_attempt(uid,pass,present);
					}
					else if(result==2){
						ses = temp.login_attempt(mob,pass,present);
					}
					if(!ses){
						cout << "Incorrect Password! Tries Left: " << tries << endl << endl;
					}
					else{
						tries = 3;
						cout << endl << "Logging In..." << endl;
						Sleep(500);
						beginSession(present);
						logout = true;
						break;
					}
				}
				if(tries<=0){
					cout << endl << "Too many incorrect login attempts. Make sure its the correct USER ID" << endl;
					logout = true;
				}
			}
		}
		else if(log_ch=='2'){
			user new_;
			new_.getdata();
			bool res = new_.write_to_file(new_);
			if(!res){
				cout << endl << "User Already Registered! Please try logging in" << endl;
				continue;
			}
			else{
				cout << endl << "User Registered Successfully!" << endl;
			}
		}
		else if(log_ch=='3'){
			char uid[250];
			long long int mob = 0;
			cout << endl << "Enter Mobile No./Email ID: ";
			cin.ignore();
			gets(uid);
			long long int mobi = 0;
			int result = diff_em_mob(uid,mobi);
			if(result==0){
				cout << endl << "Invalid or Unregistered User ID" << endl;
				break;
			}
			user ch;
			if(result==1){
				temp.find_user(uid,ch);
			}
			else if(result==2){
				temp.find_user(mobi,ch);
			}
			char sk_entry[10];
			cout << endl << "Enter Secret-Key: ";
			gets(sk_entry);
			if(!all_digit(sk_entry)){
				cout << endl << "Incorrect Secret-Key" << endl;
				continue;
			}
			if(strlen(sk_entry)!=6){
				cout << endl << "Incorrect Secret-Key" << endl;
				continue;
			}
			int sk;
			charr_to_num(sk_entry,sk);
			if(sk!=ch.fetch_sk()){
				cout << endl << "Incorrect Secret-Key" << endl;
				continue;
			}
			ch.get_pwd();
			user temp1, temp2;
			ofstream fout1,fout2;
			ifstream fin1,fin2;
			fin1.open("user_em.dat",ios::in);
			fin2.open("user_mob.dat",ios::in);
			fout1.open("temp1.dat",ios::out);
			fout2.open("temp2.dat",ios::out);
			bool flag1 = false;
			bool flag2 = false;
			while(fin1||fin2){
				if(fin1){
					fin1.read((char*)&temp1,sizeof(temp1));
				}
				if(fin2){
					fin2.read((char*)&temp2,sizeof(temp2));					
				}
				if(fin1){
					char comp[250];
					temp1.fetch_email(comp);
					char here[250];
					ch.fetch_email(here);
					if(strcmp(comp,here)==0){         //lexicographical ordering check
						fout1.write((char*)&ch,sizeof(ch));
					}
					else{
						fout1.write((char*)&temp1,sizeof(temp1));
					}
				}
				if(fin2){
					long long int comp;
					temp2.fetch_mob(comp);
					long long int here;
					ch.fetch_mob(here);
					if(comp==here){
						fout2.write((char*)&ch,sizeof(ch));
					}
					else{
						fout2.write((char*)&temp2,sizeof(temp2));
					}
				}
			}
			fin1.close();
			fin2.close();
			fout1.close();
			fout2.close();
			remove("user_em.dat");
			remove("user_mob.dat");
			rename("temp1.dat","user_em.dat");
			rename("temp2.dat","user_mob.dat");
			cout << endl << "New Password Set Successfully!" << endl;
			continue;
		}
		else if(log_ch=='4'){
			break;
		}
		else{
			cout << endl << "Invalid Choice!" << endl;
			continue;
		}
	}
}
	
