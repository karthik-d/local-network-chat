#ifndef EXP_HEADER
#define EXP_HEADER

#include<string>
#include<stack.h>
#include<math.h>

char operators[] = {'(',')','+','-','/','*','^'};

int preference(char op){
	switch(op){
		case('^'): return 3;
		case('/'): return 2;
		case('*'): return 2;
		case('+'): return 1;
		case('-'): return 1;
		default: return 0;
	}
}

int brackets(char exp[]){
	int len = strlen(exp);
	int ctr = 0;
	for(int i=0;i<len;i++){
		if(exp[i]==40){
			ctr++;
		}
		else if(exp[i]==41){
			ctr--;
		}
	}
	return ctr;
}

int search(char ch, char arr[]){
	int len = strlen(arr);
	for(int i=0;i<len;i++){
		if(arr[i]==ch){
			return i;
		}
	}
	return -1;
}

int in_to_post(char exp[],char post[]){
	stack buff;
	strcpy(post," ");
	int j = 0;
	int pref,pref_;
	char elem,elem_,popped;
	int check = brackets(exp);
	if(check<0){
		return -1;			//Unbalanced Braces
	}
	else if(check>0){
		return 1;
	}
	int len = strlen(exp);
	for(int i=0;i<len;i++){
		if(search(exp[i],operators)==-1){
			post[j] = exp[i];
			j++;
		}
		else if(exp[i]==40){
			elem = exp[i];
			buff.push(elem);
		}
		else if(exp[i]==41){
			buff.pop(popped);
			while(popped!=40){
				post[j] = popped;
				j++;
				buff.pop(popped);
			}
		}
		else{
			elem = exp[i];
			pref = preference(elem);
			buff.peek(elem_);
			pref_ = preference(elem_);
			
			if(pref>pref_){
				buff.push(elem);
			}
			else{
				while(pref<=pref_){
					if(elem==64){
						break;
					}
					else{
						buff.pop(popped);
						buff.peek(elem_);
						post[j] = popped;
						j++;
						pref_ = preference(elem_);
					}
				}
				buff.push(elem);
			}
		}
	}
	buff.pop(popped);
	while(popped!=64){
		post[j] = popped;
		j++;
		buff.pop(popped);
	}
	post[j] = '\0';
	return 0;                 	//Successful
}
	
void final_val(char exp[],float val[], char key[],float &ans){
	stack buff;        //buffer for variables 
	stack num_buff;   // for numbers
	bool prev;            //true if has to be checked
	int result,ind;
	char oper,op1,op2;
	float n_op1,n_op2,res;
	int len = strlen(exp);
	for(int i=0;i<len;i++){
		if(search(exp[i],operators)!=-1){   //not an operator
			oper = exp[i];        
			buff.pop(op2);    
			if(op2==64){           // @ meaning underflow
				num_buff.pop(n_op2);
				num_buff.pop(n_op1);
				op1 = '@';              
			}
			else{
				buff.pop(op1);
				if(op1==64){
					num_buff.pop(n_op1);
				}
			}
			if(op2!=64){
				if(op1==64){
					;
				}
				else{
					if(isdigit(op1)){
						n_op1 = (int)op1-48;   //ASCII to integer i.e. ASCII of '9' is 57, etc.
					}
					else{
						ind = search(op1,key);
						n_op1 = val[ind];
					}
				}
				if(isdigit(op2)){
					n_op2 = (int)op2-48;
				}
				else{
					ind = search(op2,key);
					n_op2 = val[ind];
				}
			}
			else{
				;
			}
			if(oper==43){
				res = n_op1+n_op2;
			}
			else if(oper==45){
				res = n_op1-n_op2;
			}
			else if(oper==47){
				res = n_op1/n_op2;
			}
			else if(oper==42){
				res = n_op1*n_op2;
			}
			else if(oper==94){
				res = pow(n_op1,n_op2);
			}		
			num_buff.push(res);
		}
		else if(isalpha(exp[i])||isdigit(exp[i])){
			buff.push(exp[i]);
		}
		else{
			;
		}
	}
	num_buff.pop(ans);
}	

bool in_arr(char arr[], char ch){
	int len = strlen(arr);
	for(int i=0;i<len;i++){
		if(arr[i]==ch){
			return true;
		}
	}
	return false;	
}

void create_legend(char exp[],float val[], char key[]){
	int ctr=0;
	int len = strlen(exp);
	for(int i=0;i<len;i++){
		if(isalpha(exp[i])){
			if (not in_arr(key,exp[i])){
				cout << endl << "Enter Value for '" << exp[i] << "': ";
				cin >> val[ctr];
				key[ctr] = exp[i];
				ctr++;
			}
		}
	}	
}

void evaluate(char exp[],char post[],float &ans){
	int res = in_to_post(exp,post);
	if(res==-1){
		cout << endl << "Unequal Brackets. More closing brackets." << endl;
		return;
	}
	else if(res==1){
		cout << endl << "Unequal Brackets. More opening brackets." << endl;
		return;
	}
	else{
		char key[100];
		float val[100];
		create_legend(post,val,key);
		final_val(post,val,key,ans);
	}
}

#endif

