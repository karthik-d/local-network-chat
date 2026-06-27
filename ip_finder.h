#ifndef IPFINDER_HEAD
#define IPFINDER_HEAD
#define LEN 200

#include<stdlib.h>
#include<dirent.h>
#include<fstream>
#include<windows.h>
#include<string>
using namespace std;

void ipc_tofile(){
	char curr[LEN];
	char temp[LEN];
	getcwd(curr,LEN);
	strcpy(temp,curr);
	strcat(temp,"\\temp");
	chdir(temp);
	if (GetLastError()==2){
		mkdir(temp);
		chdir(temp);
	}
	
	ofstream fout;
	fout.open("extracts.txt",ios::out);
	fout.close();
	
	char prmt[LEN];
	strcpy(prmt,curr);
	strcat(prmt,"\\prompts");
	
	char prgm[LEN];
	char op[LEN];
	char inp[LEN];
	strcpy(prgm,prmt);
	strcat(prgm,"\\schedule.exe");
	strcpy(op,temp);
	strcat(op,"\\extracts.txt");
	strcpy(inp,prmt);
	strcat(inp,"\\ipconfig.txt");
	
	char cmnd[LEN];
	strcpy(cmnd,prgm);
	strcat(cmnd,"<");
	strcat(cmnd,inp);
	strcat(cmnd,">");
	strcat(cmnd,op);
	system(cmnd);    //exe file < input file(reading input) > output file(to which data is written)
	chdir(curr);
}

void my_ip(char ret_ip[]){
	ipc_tofile();
	char curr[LEN];
	char temp[LEN];
	getcwd(curr,LEN);
	strcpy(temp,curr);
	strcat(temp,"\\temp");
	chdir(temp);	
	ifstream fin;
	fin.open("extracts.txt",ios::in);
	char data[100];
	char ext[15];
	memset(ret_ip,0,sizeof(ret_ip));
	int leng,i;
	bool flag;
	while(fin){
		fin.getline(data,100);
		strncpy(ext,data,15);
		if(strcmp(ext,"   IPv4 Address")==0){
			leng = strlen(data);
			flag = false;
			for (int ctr=13,i=leng;i>=0;i--,ctr--){
				if(isdigit(data[i]) or data[i]==46){
					flag = true;
					ret_ip[ctr] = data[i];
				}
				else if(not flag){
					;
				}
				else{
					break;
				}
			}
			ret_ip[13] = 0;
		}
	}
	fin.close();
	chdir(curr);
}

bool valid_ip(char* ip){
	int len = strlen(ip);
	for (int i=0;i<len;i++){
		if(ip[i]=='.'||isdigit(ip[i])){
			;
		}
		else{
			return false;
		}
	}
	return true;
}

#endif

