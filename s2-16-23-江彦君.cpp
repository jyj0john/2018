#include <iostream>
#include<string>
using namespace std;

//全局变量定义
int Available[100]; 	//可利用资源数组
int Max[50][100];   	//最大需求矩阵
int Allocation[50][100];  //分配矩阵
int Need[50][100];        //需求矩阵
int Request[50][100];     //M个进程还需要N类资源的资源量
int Finish[50];			//标记
string p[50];			//保存安全序列
int m, n;   //M个进程,N类资源


struct pcb {
	bool flag = 1;		//分配安全性标识
	int claim[3];		//进程需要的总资源数
	int allocated[3];	//已经分配的资源数
						//char status = 'R';	//进程状态，R为安全，W为死锁
	string name;
	int Need[3];		//运行结束还需要的资源
	bool ex = 0;		//已经分配标识
};

//安全性算法
int Safe(pcb* pro)
{
	int j;
	int  l = 0;
	int Work[100]; //可利用资源数组
	for (int i = 0; i<n; i++)
		Work[i] = Available[i];
	for (int i = 0; i<m; i++)
		Finish[i] = 0;
	for (int i = 0; i<m; i++)
	{
		if (Finish[i] == 1)
			continue;
		else
		{
			for ( j = 0; j<n; j++)
			{
				if (Need[i][j]>Work[j])
					break;
			}
			if (j == n)
			{
				Finish[i] = 1;
				for (int k = 0; k<n; k++)
					Work[k] += Allocation[i][k];
				p[l++] = pro[i].name;
				i = -1;
			}
			else continue;
		}
		if (l == m)
		{
			cout << "系统是安全的" << '\n';
			cout << "系统安全序列是:\n";
			for (i = 0; i<l; i++)
			{
				cout << p[i];
				if (i != l - 1)
					cout << "-->";
			}
			cout << '\n';
			return 1;
		}
	}
	return 0;
}
void initialize(pcb* a, int n,int m) {
	for (int i = 0; i < n; i++) {
		cout << "请输入第" << i + 1 << "个程序块:" << endl;
		cout << "进程名：";
		cin >> a[i].name;
		cout << "三种资源的需求量：" << endl;
		for (int j = 0; j < m; j++) {
			cin >> a[i].claim[j];
		}
		cout << "三种资源的已分配量：" << endl;
		for (int k = 0; k < m; k++) {
			cin >> a[i].allocated[k];
			a[i].Need[k] = a[i].claim[k] - a[i].allocated[k];
		}
	}
}
void display(pcb*a, int n,int m) {
	cout << "进程名：" << '\t' << "Claim/需要的总资源：" << '\t' << "Allocated/已经分配的资源:" << '\t' << "Claim-Allocated:" << endl;
	for (int i = 0; i < n; i++) {
		cout << a[i].name << '\t' << '\t';
		for (int j = 0; j < m; j++) {
			cout << a[i].claim[j] << '\t';
		}

		for (int k = 0; k < m; k++) {
			cout << a[i].allocated[k] << '\t';
		}
		cout << '\t';
		for (int p = 0; p < m; p++) {
			cout << a[i].Need[p] << '\t';
		}
		cout << endl;
	}
}
void showAvail() {
	for (int i = 0; i < 3; i++)
		cout << Available[i]<<" ";
	cout << endl;
}
int main()
{
	string na;
	int i, j, mi;
	cout << "输入进程的数目:\n";
	cin >> m;
	cout << "输入资源的种类数:\n";
	cin >> n;
	pcb* a = new pcb[m];
	initialize(a, m, n);
	for (i = 0; i<m; i++)
		for (j = 0; j<n; j++)
			 Max[i][j] = a[i].claim[j];
	for (i = 0; i<m; i++)
	{
		for (j = 0; j<n; j++)
		{
			Allocation[i][j] = a[i].allocated[j];
			Need[i][j] = Max[i][j] - Allocation[i][j];
			if (Need[i][j]<0)
			{
				cout << "你输入的第" << i + 1 << "个进程所拥有的第" << j + 1 << "个资源错误，请重新输入:\n";
				j--;
				continue;
			}
		}
	}
	cout << "请输入各个资源现有的数目:\n";
	for (i = 0; i<n; i++)
		cin >> Available[i];
	display(a, m, n);
	Safe(a);
	while (1)
	{
		cout << "输入要申请的资源的进程名：\n";
		cin >> na;
		for(int i = 0; i < m; i++)
			if(a[i].name == na)
				mi = i;
		cout << "输入进程所请求的各个资源的数量\n";
		for (i = 0; i<n; i++)
			cin >> Request[mi][i];
		for (i = 0; i<n; i++)
		{
			/*可行性检测*/
			if (Request[mi][i]>Need[mi][i])
			{
				cout << "所请求资源数超过进程的需求量！\n";
				system("pause");
				return 0;
			}
			if (Request[mi][i]>Available[i])
			{
				cout << "所请求资源数超过系统所有的资源数！\n";
				system("pause");
				return 0;
			}
		}
		/*试分配*/
		for (i = 0; i<n; i++)
		{
			Available[i] -= Request[mi][i];
			Allocation[mi][i] += Request[mi][i];
			Need[mi][i] -= Request[mi][i];
		}
		if (Safe(a) == 1)
			cout << "同意分配请求\n";
		else
		{
			cout << "死锁！"<<endl;
			for (i = 0; i<n; i++)		//回溯
			{
				Available[i] += Request[mi][i];
				Allocation[mi][i] -= Request[mi][i];
				Need[mi][i] += Request[mi][i];
			}
		}



		for (i = 0; i<m; i++)
			Finish[i] = 0;	//	归零标记
		char Flag;       //标志位
		cout << "是否再次请求分配？是请按y，否请按n"<<endl;
		while (1)
		{
			cin >> Flag;
			if (Flag == 'y' || Flag == 'n')
				break;
			else
			{
				cout << "请按要求重新输入:\n";
				continue;
			}
		}
		if (Flag == 'y')
			continue;
		else break;
	}
}