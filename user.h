#ifndef USER_HEAD
#define USER_HEAD

#include<iostream>
#include<string>
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<comm_func.h>

#define LEN 200

using namespace std;

int diff_em_mob(char uid[],long long int &mob);

void charr_to_mob(char uid[],long long int &num){
	char inter[10];
	int ctr = 0;
	num = 0;
	cout << num << num;
	for(int i=0;i<10;i++){
		inter[ctr] = uid[i];
		ctr++;
		if(i==4){
			int ret;
			charr_to_num(inter,ret);
			long long int val = ret*pow(10,5);
			num += val;
			ctr = 0;
		}
		else if(i==9){
			int ret;
			charr_to_num(inter,ret);
			num += ret;
		}
	}
}


class person{
	char name[100];
	date dob;
	
	public:
		void get_name(){
			while(true){
				cout << "Enter Name: ";
				gets(name);
				trim(name,100);
				capitalise(name);
				int len = strlen(name);
				if(len>25 or len<3){
					cout << endl << "Name should be between 3 and 25 characters. \nYou entered " << strlen(name) << " characters"<< endl;
					continue;
				}
				else{
					break;
				}
			}
		}
		void get_dob(){
			char date_entry[10];
			while(true){
				cout << "Date Of Birth " << endl;
				cout << "Day(dd): ";
				memset(date_entry,0,sizeof(date_entry));
				gets(date_entry);
				if(!all_digit(date_entry)){
					cout << "Invalid Day. Enter only numbers\n" << endl;
					continue;
				}
				charr_to_num(date_entry,dob.day);
				cout << "Month(mm): ";
				memset(date_entry,0,sizeof(date_entry));
				gets(date_entry);
				if(!all_digit(date_entry)){
					cout << "Invalid Month. Enter only numbers\n" << endl;
					continue;
				}
				charr_to_num(date_entry,dob.month);
				cout << "Year(yyyy): ";
				memset(date_entry,0,sizeof(date_entry));
				gets(date_entry);
				if(!all_digit(date_entry)){
					cout << "Invalid Year. Enter only numbers\n" << endl;
					continue;
				}
				charr_to_num(date_entry,dob.year);
				if(not date_cmp_curr(dob.day,dob.month,dob.year)){
					cout << endl << "Invalid Date" << endl;
					continue;
				}
				break;
			}
		}
		
		void display(){
			cout << endl << "Name: " << name;
			cout << endl << "Date Of Birth: " << dob.day << " " << dob.month << " " << dob.year;
		}
		
		void fetch_name(char ret[]){
			strcpy(ret,name);
		}
};
class user : public person{
	char email[250];
	char pwd[20];
	long long int mobno = 0;
	int secret_key;
	
	public:
		void get_pwd(){
			memset(pwd,0,20);
			while(true){
				cout << "Choose Password(must contain atleast one alphabet and one numeral): ";
				gets(pwd);
				int len = strlen(pwd);
				if(len>15 or len<6){
					cout << endl << "Password must be between 6 and 15 characters.\nYou have entered " << len << " characters" << endl;
					continue;
				}
				else if(not pwd_qual(pwd)){
					cout << endl << "Password does not match specified criteria" << endl;
					continue;
				}
				else{
					char repwd[20];
					cout << "Re-Enter Password: ";
					gets(repwd); 
					if(strcmp(repwd,pwd)!=0){
						cout << endl << "Entered passwords do not match. Retry!" << endl;
						continue;
					}
					else{
						break;
					}
				}
				break; 
			}
		}
		void getdata(){
			cout << endl << "Please Enter Your Details" << endl;
			cin.ignore();
			get_name();
			while(true){
				cout << "Enter Email Address: ";
				cin >> email;
				int len = strlen(email);
				if (len>250 or len<5){
					cout << endl << "Email Address should be between 5 and 250 characters.\nYou have entered " << len << " characters" << endl;
					continue;
				}
				else if(not email_ver(email)){
					cout << endl << "Please enter a Valid Email Address\n" << endl;
				}
				else{
					break;
				}
			}
			char mob_entry[10];
			cin.ignore();
			while(true){
				cout << "Enter Mobile No.(10 digits only): ";
				gets(mob_entry);
				if(!all_digit(mob_entry)){
					cout << "Invalid Mobile Number. Enter only numbers\n" << endl;
					continue;
				}
				charr_to_mob(mob_entry,mobno);
				if(mobno<1000000000 or mobno>9999999999){
					cout << "Invalid Mobile Number!\nEnter only 10 digits. Exclude country code (if any)\n " << endl;
					continue;
				}
				else{
					break;
				}
			}
			cout << "\b" << "\b";
			get_pwd();
			get_dob();
			char sk_entry[10];
			while(true){
				memset(sk_entry,0,sizeof(sk_entry));
				cout << "Choose 6-digit Secret-Key (for password recovery): ";
				gets(sk_entry);
				int len = strlen(sk_entry);
				if(len!=6){
					cout << "Invalid Secret-Code. Enter exactly 6 digits\n" << endl;
					continue;
				}
				bool flag = true;
				if(!all_digit(sk_entry)){
					cout << "Invalid Secret Code. Enter only numbers\n" << endl;
					continue;
				}
				else{
					charr_to_num(sk_entry,secret_key);
					break;
				}
			}
		}
		bool write_to_file(user curr){
			user temp, temp1, temp2;
			if(find_user(curr.email,temp) || find_user(curr.mobno,temp)){
				return false;
			}
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
					if(fin1){                                 //To Avoid One Repitition
						if(!flag1){
							if(strcmp(temp1.email,curr.email)==-1){         //lexicographical ordering check
								fout1.write((char*)&temp1,sizeof(temp1));
							}
							else{
								fout1.write((char*)&curr,sizeof(curr));
								fout1.write((char*)&temp1,sizeof(temp1));
								flag1 = true;
							}
						}
						else{
							fout1.write((char*)&temp1,sizeof(temp1));
						}
					}
				}
				if(fin2){
					fin2.read((char*)&temp2,sizeof(temp2));
					if(fin2){
						if(!flag2){
							if(temp2.mobno<curr.mobno){
								fout2.write((char*)&temp2,sizeof(temp2));
							}
							else{
								fout2.write((char*)&curr,sizeof(curr));
								fout2.write((char*)&temp2,sizeof(temp2));
								flag2 = true;
							}
						}
						else{
							fout2.write((char*)&temp2,sizeof(temp2));
						}
					}
				}
			}
			if(!flag1){
				fout1.write((char*)&curr,sizeof(curr));
			}
			if(!flag2){
				fout2.write((char*)&curr,sizeof(curr));
			}
			fin1.close();
			fin2.close();
			fout1.close();
			fout2.close();
			remove("user_em.dat");
			remove("user_mob.dat");
			rename("temp1.dat","user_em.dat");
			rename("temp2.dat","user_mob.dat");
			create_dir();
			return true;
		}
		bool find_user(long long int mobn,user &ret){
			ifstream fin;
			fin.open("user_mob.dat",ios::in);
			user arr[1000];
			user curr;
			int ctr = 0;
			while(fin){
				fin.read((char*)&curr,sizeof(curr));
				arr[ctr] = curr;
				ctr++;
			}
			fin.close();
			
			int beg,mid,end;
			beg = 0;
			end = ctr;
			while(beg<=end){
				mid = (beg+end)/2;
				if(arr[mid].mobno==mobn){
					ret = arr[mid];
					return true;
				}
				else if(arr[mid].mobno>mobn){
					end = mid-1;
				}
				else{
					beg = mid+1;
				}
			}
			return false;
		}
		bool find_user(char email[],user &ret){
			ifstream fin;
			fin.open("user_em.dat",ios::in);
			user arr[1000];
			user curr;
			int ctr = 0;
			while(fin){
				fin.read((char*)&curr,sizeof(curr));
				arr[ctr] = curr;
				ctr++;
			}
			fin.close();
			
			int beg,mid,end;
			beg = 0;
			end = ctr;
			while(beg<=end){
				mid = (beg+end)/2;
				if(strcmp(arr[mid].email,email)==0){
					ret = arr[mid];
					return true;
				}
				else if(strcmp(arr[mid].email,email)==1){
					end = mid-1;
				}
				else{
					beg = mid+1;
				}
			}
			return false;
		}		
		void create_dir(){
			char curr[LEN];
			getcwd(curr,LEN);
			char new_[LEN];
			char cha[LEN];
			char mem[LEN];
			strcpy(new_,curr);
			strcat(new_,"\\users\\");
			strcat(new_,email);
			mkdir(new_);
			if(GetLastError()!=0){
				cout << endl << "Unknown Error Occurred! Please Restart Program";
			}
			else{
				strcpy(cha,new_);
				strcat(cha,"\\chats");
				mkdir(cha);
				strcpy(mem,new_);
				strcat(mem,"\\memos");
				mkdir(mem);
			}
		}
		bool login_attempt(long long int mobn, char pass[], user &ret){
			user curr;
			bool res = find_user(mobn,curr);
			if(!res){
				return false;
			}
			else{
				if(strcmp(curr.pwd,pass)==0){
					ret = curr;
					return true;
				}
				else{
					return false;
				}
			}
		}
		bool login_attempt(char email[], char pass[], user &ret){
			user curr;
			bool res = find_user(email,curr);
			if(!res){
				return false;
			}
			else{
				if(strcmp(curr.pwd,pass)==0){
					ret = curr;
					return true;
				}
				else{
					return false;
				}
			}
		}
		void display(){
			cout << "PERSON DETAILS" << endl;
			person::display();
			cout << endl << "Email: " << email;
			cout << endl << "Phone: " << mobno;
			cout << endl << "Pass: " << pwd;
		}
		
		void fetch_mob(long long int &ret){
			ret = mobno;
		}
		
		void fetch_email(char ret[]){
			strcpy(ret,email);
		}
		
		void fetch_pwd(char ret[]){
			strcpy(ret,pwd);
		}
		
		int fetch_sk(){
			return secret_key;
		}
};

int diff_em_mob(char uid[],long long int &mob){
	bool result = email_ver(uid);	
	user temp;		
	if(result){
		bool fnd = temp.find_user(uid,temp);
		if(not fnd){
			return 0;
		}
		else{
			return 1;
		}
	}
	else{
		int len = strlen(uid);
		if(len!=10){
			return 0;
		}
		else{
			bool flag = false;
			for(int i=0;i<10;i++){
				if(not isdigit(uid[i])){
					flag = true;
					break;
				}
			}
			if(flag){
				return 0;
			}
			else{
				charr_to_mob(uid,mob);
				bool fnd = temp.find_user(mob,temp);
				if(!fnd){
					return 0;
				}
				else{
					return 2;
				}
			}
		}
	}
}

#endif	
	
