#ifndef WIN32_LEAN_AND_MEAN          //To exclude Cryptography, DDE, RPC, Shell and other unnecessary APIs from windows.h
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef SERVER_HEAD
#define SERVER_HEAD

#define DEFAULT_PORT "5555"

#include<fstream>
#include<iostream>
#include<string.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <thread>
#include<ctime>
#include <stdio.h>

using namespace std;

SOCKET InitServer(char* ip_host){ 
 	
	WSADATA sample_obj;
	int retval1 = WSAStartup(MAKEWORD(2,2),&sample_obj);  // To start the winsock2 dll file //specifying version 2.2. as WORD data-type
	if (retval1){
		cout << endl << "Unknown Error Occurred! Please Retry Later..." << endl;     //Startup Winsock Failed
	}
	else{
		     //Startup Winsock Success
		
		//Socket Initialization
		struct addrinfo *result=NULL, *ptr=NULL, props;     //To hold host address information
		ZeroMemory(&props,sizeof(props));   //To assign NULL to every member of the structure
		props.ai_family = AF_INET;    //Normal IP Address family i.e. IPv4
		props.ai_socktype = SOCK_STREAM;  //Default socket type for TCP/IP
		props.ai_protocol = IPPROTO_TCP;    //Assigning TCP/IP Protocol
		props.ai_flags = AI_PASSIVE;			//Configures output for socket binding
		
		int retval2 = getaddrinfo(ip_host,DEFAULT_PORT,&props,&result);   //Instead of NULL(i.e. INADDR_ANY), IP is specified to limit traffic
																		  // Gets address info from host name or IP and gives details to be used for client searching
		if (retval2){
			cout << endl << "Unknown Error Occurred! Please Retry Later..." << endl;   //Address Resolution Failed
			WSACleanup();
		}
		else{						//Address Resolution Success
			
			//Socket Creation
			SOCKET ListenSocket = INVALID_SOCKET;
			ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);  //Suitable socket created using details of result
			if (ListenSocket == INVALID_SOCKET){
				cout << endl << "Unknown Error Occurred! Please Retry Later..." << endl;   // Socket Creation Failed
				freeaddrinfo(result);
				WSACleanup();
			}
			else{					//Socket Created
				
				//Binding Socket
				int retval3 = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);  //ai_addr is the adress to bind the socket to
				if (retval3==SOCKET_ERROR){       // Socket Binding Failed
					cout << endl << "Unknown Error Occurred! Please Retry Later..." << endl;
					freeaddrinfo(result);
					closesocket(ListenSocket);
					WSACleanup();
				}
				else{									//Bound to socket
					freeaddrinfo(result); 						// Address Information is not required anymore
					return ListenSocket;                            
				}
			}
		}
	}
	return INVALID_SOCKET;
}

SOCKET PseudoClient(char* ip_host){
	//Winsock Initialisation	
	WSADATA sample_obj;
	int retval1 = WSAStartup(MAKEWORD(2,2),&sample_obj);
	if (retval1){			
		cout << endl << "Unknown Error Occurred! Please Retry Later..." << endl;		//Initialisation failed
	}
	else{
		;				//Startup Done
		
		//Socket Initialization
		struct addrinfo *result=NULL, *ptr=NULL, props;
		ZeroMemory(&props,sizeof(props));   //To assign NULL to every member of the structure
		props.ai_family = AF_INET;
		props.ai_socktype = SOCK_STREAM;
		props.ai_protocol = IPPROTO_TCP;
		int retval2 = getaddrinfo(ip_host,DEFAULT_PORT,&props,&result);
		if (retval2){       		//Address resoltion Failed
			cout << endl << "Unknown Error Occurred! Please Retry Later..." << endl;
			WSACleanup();
		}
		else{
			;					//Address Resolved
			
			//Create Connection Socket
			ptr = result;
			SOCKET ConnectSocket;
			ConnectSocket = socket(ptr->ai_family,ptr->ai_socktype,ptr->ai_protocol);
			if (ConnectSocket==INVALID_SOCKET){
				cout << endl << "Unknown Error Occurred! Please Retry Later..." << endl;
				freeaddrinfo(result);				//Couldn't make connect initialiser
				WSACleanup();
			}
			else{			//Connect Socket Madw
				
				//Connect to a Socket
				int retval3 = connect(ConnectSocket,ptr->ai_addr,(int)ptr->ai_addrlen);
				if (ConnectSocket==SOCKET_ERROR){
					cout << endl << "Unknown Error Occurred! Please Retry Later..." << endl;	//Connection failed
					closesocket(ConnectSocket);
				}
				else{
					if (ConnectSocket==INVALID_SOCKET){
						cout << endl << "Unknown Error Occurred! Please Retry Later..." << endl;	//Connection Failed
					}
					else{
						freeaddrinfo(result);
						return ConnectSocket;			//Connection Successful
					}
				}
			}
		}
	}
	return INVALID_SOCKET;
}

void ServerTimeout(bool &Destroy, char* curr_ip){
	time_t begin = time(NULL);
	while(true){
		if(Destroy){
			break;
		}
		else{
			if((time(NULL)-begin)>=15){
				PseudoClient(curr_ip);
				break;
			}
		}
	}
}

SOCKET EngageServer(SOCKET ListenSocket,char* curr_ip){
	//Listen on a Socket
	SOCKET ClientSocket;
	int retval1 = listen(ListenSocket,SOMAXCONN);
	if (retval1==SOCKET_ERROR){
		closesocket(ListenSocket);         //Client Socket Failed
		WSACleanup();
		return INVALID_SOCKET;
	}
	else{
		bool connected = false;
		
		while(!connected){
			cout << endl << "Waiting for target to accept request...\nNOTE : The target must enter your IP on his Device\nIf no client is found within 15 seconds, connection attempt will fail" << endl;
			bool t_reset = false;
			thread TimeoutProcess(ServerTimeout,std::ref(t_reset),curr_ip);   // creates a refermnce wrapper tht can be later unwrapped, because thread can't hold a refernce
			ClientSocket = accept(ListenSocket,NULL,NULL);
			
			t_reset = true;
			TimeoutProcess.join(); 
			
			char peer_ip[15];
			memset(peer_ip,0,15);
			struct sockaddr_in detail;
			socklen_t det_len = sizeof(detail);
			getpeername(ClientSocket,(struct sockaddr*)&detail,&det_len);
			strcpy(peer_ip,inet_ntoa(detail.sin_addr));
			
			if(strcmp(peer_ip,curr_ip)==0){
				cout << endl << "Server Timed Out! No Suitable Clients Found...";
				break;
			}
			else{
				char ch;
				while(true){
					cout << endl << "Do you want to connect to " << peer_ip << " ? (y/n): ";
					cin >> ch;
					ch = tolower(ch);
					if (ch=='y'){
						connected = true;     //Successful Connection
						return ClientSocket;
					}
					else if (ch=='n'){
						break;
					}
					else{
						cout << endl << "Invalid Choice!" << endl;
						continue;
					}
				}
				cout << endl << "Enter 'y' to attempt connection again and anything else to go back to previous menu: ";
				cin >> ch;
				ch = tolower(ch);
				if(ch=='y'){
					continue;
				}
				else{
					break;
				}
			}
		}
	}
	return INVALID_SOCKET;
}

void ReceiveDataServer(SOCKET ClientSocket, char peer[], ofstream &fout){
	
	char data[1000];
	int recvResult;
	char ch;

	do{
		memset(data,0,1000);
		recvResult = recv(ClientSocket,data,sizeof(data),0);
		if (recvResult>0){
			cout << endl << endl << peer << " Says : " << data << endl;
			char store[1000];
			memset(store,0,1000);
			strcpy(store,peer);
			strcat(store," Said : ");
			strcat(store,data);
			fout << endl << store;
			cout << endl << "1-Send Text\n2-Terminate Connection\nEnter Choice: ";
		}
		else if(recvResult==0){
			;
		}
		else{
			return;					//Connection Closing
		}
	}while(ch!='y');
	WSACleanup();
}

int SendDataServer(SOCKET ClientSocket, ofstream &fout){
	
	int sendResult;
	char data[1000];
	int err;
	memset(data,0,1000);
	cout << endl << "Enter Text To Send: ";
	cin.ignore();
	cin.getline(data,1000);
	char store[1000];
	memset(store,0,1000);
	strcpy(store,"You Said : ");
	strcat(store,data);
	fout << endl << store;
	sendResult = send(ClientSocket,data,strlen(data),0);
	
	if(sendResult==SOCKET_ERROR){
		err = WSAGetLastError();             	//Sending Failed
		return err;
	}
	else{            
		return 1;        						//Sending Success
	}
}

#endif


