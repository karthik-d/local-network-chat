#ifndef STACK_HEAD
#define STACK_HEAD

class stack{
	struct node{
		char data;
		float numb;
		node* next;
	};
	node* top = NULL;
	
	public:
		node* CreateNewNode(char ch){
			node* ptr = new node;
			ptr->data = ch;
			ptr->next = NULL;
			return ptr;
		}
		node* CreateNewNode(float num){
			node* ptr = new node;
			ptr->numb = num;
			ptr->next = NULL;
			return ptr;
		}
		
		void push(char ch){
			node* elem = CreateNewNode(ch);
			if(top==NULL){
				top = elem;
			}
			else{
				elem->next = top;
				top = elem;
			}
		}
		void push(float num){
			node* elem = CreateNewNode(num);
			if(top==NULL){
				top = elem;
			}
			else{
				elem->next = top;
				top = elem;
			}
		}
		
		int pop(char &ch){
			if(top==NULL){
				ch = '@';       //Underflow
				return 0;
			}
			else{
				node* temp;
				ch = top->data;
				temp = top;
				top = top->next;
				delete temp;
				return 1;
			}
		}
		int pop(float &num){
			if(top==NULL){
				num = '@';       //Underflow
				return 0;
			}
			else{
				node* temp;
				num = top->numb;
				temp = top;
				top = top->next;
				delete temp;
				return 1;
			}
		}
		
		void peek(char &ch){
			if(top==NULL){
				ch = '@';
			}
			else{
				ch = top->data;
			}
		}
		void peek(float &num){
			if(top==NULL){
				num = '@';
			}
			else{
				num = top->numb;
			}
		}
		
		void display(){
			node* ptr = top;
			cout << "__________________________________" << endl;
			while(ptr!=NULL){
				cout << ptr->data << " ";
				cout << ptr->numb;
				ptr = ptr->next;
			}
			cout << endl <<  "__________________________________" << endl;
		}
};



#endif
