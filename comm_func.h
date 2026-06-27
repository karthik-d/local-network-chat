#ifndef GENERAL_HEAD
#define GENERAL_HEAD

#include<string>
#include<ctime>
#include<user.h>

struct date{								/*Structure for date*/
	int day = 0;
	int month = 0;
	int year = 0;
};

void trim(char str[],int max_size){						/*Function to remove leading and trailing whitespaces*/
	char temp[max_size];
	int len = strlen(str);
	int m = 0, n = 0;
	while (str[m]==' '){
		m++;
	}
	int i,j;
	for (i=m,j=0; i<(len);i++,j++){
		if (str[i] == ' ' & str[i+1] == ' '){			/* There shouldn't ne more than one gap between first/middle/last names*/
			break;
		}
		temp[j] = str[i];
		n++;
	}
	temp[n] = 0;
	strcpy(str,temp);
}

int first_day(int year){
	time_t now = time(0);
	tm *stru = localtime(&now);
	
	int yday = stru->tm_yday;   //Day of year
	int wday = stru->tm_wday;
	int cyear = 1900+stru->tm_year; //tm_year gives year since 1900
	
	for(int i=yday;i>0;i--){
		wday--;
		if(wday<0){
			wday = 6;
		}
	}
	for(int i=cyear;i>year;i--){
		if(((i-1)%4)==0){
			wday -= 2;
		}
		else{
			wday--;
		}
		if(wday==-1){
			wday = 6;
		}
		else if(wday==-2){
			wday = 5;
		}
	}
	return wday;
}

void num_to_charr(int num,char arr[]){
	memset(arr,0,sizeof(arr));
	int dig;
	int ctr = 0;
	int temp = num;
	while(temp>0){
		dig = temp%10;
		temp /= 10;
		ctr++;
	}
	while(ctr>0){
		ctr--;
		dig = num%10;
		num /= 10;
		arr[ctr] = (char)(dig+48);
	}
}

void charr_to_num(char arr[],int &num){
	int len = strlen(arr);
	int dig;
	num = 0;
	for(int i=0;i<len;i++){
		dig = arr[i];
		num += (dig-48)*pow(10,len-i-1);
	}
}

int search_in(char arr[][10],int N,char item[]){
	for(int i=0;i<N;i++){
		if(strcmp(arr[i],item)==0){
			return i;
		}
	}
	return -1;
}

bool all_digit(char str[]){
	int len = strlen(str);
	for(int i=0;i<len;i++){
		if(!isdigit(str[i])){
			return false;
		}
	}
	return true;
}

void capitalise(char str[]){
	int len = strlen(str);
	for (int i=0;i<len;i++){
		if (i==0){
			str[i] = toupper(str[i]);
		}
		else if (str[i-1]==' '){
			str[i] = toupper(str[i]);
		}
		else{
			str[i] = tolower(str[i]);
		}
	}
}

bool email_ver(char str[]){
	bool at = false;
	bool dot = false;
	bool af_dot = false;
	bool af_at = false;
	bool bef_dot = false;
	bool bef_at = false;
	bool ret_val;
	int len = strlen(str);
	for (int i=0;i<len;i++){
		char check = str[i];
		if (isalnum(check)){
			if (not at){
				bef_at = true;
			}
			else if (at & not dot){
				af_at = true;
				bef_dot = true;
			}
			else if (dot){
				af_dot = true;
			}
		}
		else if (check=='@'){
			if (not at){
				at = true;
			}
			else{
				return false;
			}
		}
		else if (check=='.'){
			if (at){
				dot = true;
			}
		}
	}
	ret_val = at&dot&af_dot&af_at&bef_dot&bef_at;
	return ret_val;
}

void del_dir(char path[]){
	char now[200];
	strcpy(now,path);
	DIR *dir;                       //Directory Stream
	dir = opendir(path);
	struct dirent *cont;     //Structure with file index and name
	while(cont = readdir(dir)){    //To empty the directory
		if(cont->d_name[0]!='.'){
			strcpy(now,path);
			strcat(now,"\\");
			strcat(now,cont->d_name);
			rmdir(now);
			int err = GetLastError();
			if(err==267){    //Directory name is invalid, meaning its a file
				remove(now);       
			}
			else if(err==145){
				del_dir(now);   //Directory is not empty   //recursion
				rmdir(now);
			}
		}
	}
	closedir(dir);
	rmdir(path);
}

bool date_check(int day,int month,int year){
	if(day<1){
		return false;
	}
	if(month>12||month<1){
		return false;
	}
	else if(month==4 or month==6 or month==9 or month==11){
		if(day>30){
			return false;
		}
	}
	else if(month==2){
		if((year%4==0 and day>29) or day>28){
			return false;
		}
	}
	else{
		if(day>31){
			return false;
		}
	}
	if(year<1){
		return false;
	}
	return true;
}

void initial_check(){
	char curr[LEN];
	char temp[LEN];
	getcwd(curr,LEN);
	strcpy(temp,curr);
	strcat(temp,"\\users");
	chdir(temp);
	if (GetLastError()==2){
		mkdir(temp);
		chdir(temp);
	}
	chdir(curr);
}

bool date_cmp_curr(int day, int mon, int year){
	if (year<1000){
		return false;
	}
	time_t now = time(0);
	tm *stru = localtime(&now);
	if(year>(1970+stru->tm_year)){
		return false;
	}
	else if(year==(1970+stru->tm_year)){
		if(mon>(1+stru->tm_mon)){
			return false;
		}
		else if(mon==(1+stru->tm_mon)){
			if(day>(1+stru->tm_mday)){
				return false;
			}
		}
	}
	return true;
}

void date_time_now(char arr[]){
	time_t now = time(0);
	struct tm *comp = localtime(&now);
	strcpy(arr,asctime(comp));
}

void corr_fname(char arr[],char temp[]){
	int len = strlen(arr);
	bool flag = false;
	int j = 0;
	for(int i=0;i<len;i++){
		if((int)arr[i]==58&&flag){
			temp[j] = (char)46;
			j++;
		}
		else if((int)arr[i]==58&&!flag){
			flag = true;
			temp[j] = arr[i];
			j++;
		}
		else if((int)arr[i]==10){
			;
		}
		else{
			temp[j] = arr[i];
			j++;
		}
	}
	temp[strlen(temp)] = '\0';
}

bool pwd_qual(char pwd[]){
	int len = strlen(pwd);
	bool num = false;
	bool alpha = false;
	for(int i=0;i<len;i++){
		if(isdigit(pwd[i])){
			num = true;
		}
		else if(isalpha(pwd[i])){
			alpha = true;
		}
		if(num&&alpha){
			break;
		}
	}
	bool ret = num&&alpha;
	return ret;
}

#endif
