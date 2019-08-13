#include<iostream>
#include<cstring>
#include<string>
#include<string.h>
using namespace std;
int compare(int a, int b) {
	if (a > b)
		return 1;
	else 
		return 0;
}
class process {
public:	
	string name ;
	char status = 'R';
	int arr_time;
	//int rest_time;
	int run_time;
	//process* p;
	process* next;
	process(int m,int n, string Name) {
		//cin >> m >> n;
		//cin >> Name;
		name = Name;
		arr_time = m;
		run_time = n;
	}
	/*
	int showarr() {
		return arr_time;
	}
	int showrun() {
		return run_time;
	}
	*/
	void print_run() {
		run_time--;
		status = 'C';
		cout << name << " is runnning!" << '\n' << "已经运行时间：" << run_time << " 还剩时间: " << 1;
		if (next != NULL)
			cout << " 就绪进程名：" << next->name << endl;
		else
			cout << " 无后续进程！" << endl;
	}

};
process* manage(process& a, process& b, process& c) {
	if (compare(a.arr_time, b.arr_time) == 1) {
		b.next = &a;
		if (compare(b.arr_time, c.arr_time) == 1) {
			c.next = &b;
			return &c;
		}
		else {
			if (compare(a.arr_time, c.arr_time) == 1) {
				b.next = &c;
				c.next = &a;
			}
			else
				a.next = &c;
			return &b;
		}
	}
	else {
		a.next = &b;
		if (compare(a.arr_time, c.arr_time) == 1) {
			c.next = &a;
			return &c;
		}
		else {
			if (compare(b.arr_time, c.arr_time) == 1){
				a.next = &c;
				c.next = &b;
		}
			else
				b.next = &c;	
			return &a;
		}
	}
}
int main() {
	process* head = NULL;
	double s = 0;
	int sum[10] = { 0 };
	process a(2,10,"A"), b(1,5,"B"), c(3,20,"C");
	head = manage(a, b, c);
	process* p = head;
	/*模拟进程运行*/
	for (int i = 1; i <= 3; i++) {
		head->print_run();
		//sum[j] += head->run_time+1;
		head = head->next;
	}
	/*求周转时间*/
	for (int i = 1; i <= 3; i++) {
		head = p;
		
			sum[i] = head->run_time + 1 + sum[i-1];
			if(head->next != NULL)
			head = head->next;
		
			cout << p->name << "周转时间为：" << sum[i]<< endl;
			s += sum[i];
			p = p->next;
	}
	cout << "平均周转时间为：" << s / 3 << endl;
	system("pause");
	return 0;
}
