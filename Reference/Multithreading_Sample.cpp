#include<iostream>
#include<thread>
using namespace std;

void sample(int k){
	char ch;
	for (int i=0;i<10;i++){
		cout << endl << "Function: " << i*k;
		cin >> ch;
	}
}

void second(){
	int x=0;
	while(x<40){
		cout << endl << "Second: " << x;
		x++;
	}
}

int main(){
	
	thread t1(sample,7);
	thread t2(second);
	cout << endl << "In Main...";
	
	for (int m=0;m<50;m++){
			cout << endl << "Main: " << m;
	}
	
	t1.join();
	t2.join();
	return 0;
}
