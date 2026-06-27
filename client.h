#ifndef WIN32_LEAN_AND_MEAN          //To exclude Cryptography, DDE, RPC, Shell and other unnecessary APIs from windows.h
#define WIN32_LEAN_AND_MEAN
#endif

#ifndef CLIENT_HEAD
#define CLIENT_HEAD

#define DEFAULT_PORT "5555"

#include<iostream>
#include<string.h>
#include <winsock2.h>
#include <windows.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include<thread>
#include <stdio.h>

using namespace std;
//#pragma comment(lib, "Ws2_32.lib")

SOCKET ConnectServer(char* ip_host){
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
		props.ai_family = AF_INET;  //IPv4
		props.ai_socktype = SOCK_STREAM;
		props.ai_protocol = IPPROTO_TCP;
		int retval2 = getaddrinfo(ip_host,DEFAULT_PORT,&props,&result);   // Resolving and providing info about the address provided
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
						if(GetLastError()==10060){  //Timeout error
							cout << endl << "Connection Attempt Time Out! Ensure that your peer is accepting connections" << endl;
							
						}
						else{
							freeaddrinfo(result);
							return ConnectSocket;			//Connection Successful
						}
					}
				}
			}
		}
	}
	return INVALID_SOCKET;
}

void ReceiveDataClient(SOCKET ConnectSocket, char peer[], ofstream &fout){
	
	char data[1000];
	int recvResult;
	char ch;
	
	do{
		memset(data,0,1000);              //Cleaning the string buffer
		recvResult = recv(ConnectSocket,data,sizeof(data),0);
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
			break;
		}
	}while(ch!='y');
}

int SendDataClient(SOCKET ConnectSocket, ofstream &fout){
	
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
	sendResult = send(ConnectSocket,data,strlen(data),0);
	
	if(sendResult==SOCKET_ERROR){
		err = WSAGetLastError();
		return err;             								 //Sending Failed
	}
	else{                  
		return 1;			 //Sending Success
	}
}

#endif



