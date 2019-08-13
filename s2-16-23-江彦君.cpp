#include <iostream>
#include<string>
using namespace std;

//ȫ�ֱ�������
int Available[100]; 	//��������Դ����
int Max[50][100];   	//����������
int Allocation[50][100];  //�������
int Need[50][100];        //�������
int Request[50][100];     //M�����̻���ҪN����Դ����Դ��
int Finish[50];			//���
string p[50];			//���氲ȫ����
int m, n;   //M������,N����Դ


struct pcb {
	bool flag = 1;		//���䰲ȫ�Ա�ʶ
	int claim[3];		//������Ҫ������Դ��
	int allocated[3];	//�Ѿ��������Դ��
						//char status = 'R';	//����״̬��RΪ��ȫ��WΪ����
	string name;
	int Need[3];		//���н�������Ҫ����Դ
	bool ex = 0;		//�Ѿ������ʶ
};

//��ȫ���㷨
int Safe(pcb* pro)
{
	int j;
	int  l = 0;
	int Work[100]; //��������Դ����
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
			cout << "ϵͳ�ǰ�ȫ��" << '\n';
			cout << "ϵͳ��ȫ������:\n";
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
		cout << "�������" << i + 1 << "�������:" << endl;
		cout << "��������";
		cin >> a[i].name;
		cout << "������Դ����������" << endl;
		for (int j = 0; j < m; j++) {
			cin >> a[i].claim[j];
		}
		cout << "������Դ���ѷ�������" << endl;
		for (int k = 0; k < m; k++) {
			cin >> a[i].allocated[k];
			a[i].Need[k] = a[i].claim[k] - a[i].allocated[k];
		}
	}
}
void display(pcb*a, int n,int m) {
	cout << "��������" << '\t' << "Claim/��Ҫ������Դ��" << '\t' << "Allocated/�Ѿ��������Դ:" << '\t' << "Claim-Allocated:" << endl;
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
	cout << "������̵���Ŀ:\n";
	cin >> m;
	cout << "������Դ��������:\n";
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
				cout << "������ĵ�" << i + 1 << "��������ӵ�еĵ�" << j + 1 << "����Դ��������������:\n";
				j--;
				continue;
			}
		}
	}
	cout << "�����������Դ���е���Ŀ:\n";
	for (i = 0; i<n; i++)
		cin >> Available[i];
	display(a, m, n);
	Safe(a);
	while (1)
	{
		cout << "����Ҫ�������Դ�Ľ�������\n";
		cin >> na;
		for(int i = 0; i < m; i++)
			if(a[i].name == na)
				mi = i;
		cout << "�������������ĸ�����Դ������\n";
		for (i = 0; i<n; i++)
			cin >> Request[mi][i];
		for (i = 0; i<n; i++)
		{
			/*�����Լ��*/
			if (Request[mi][i]>Need[mi][i])
			{
				cout << "��������Դ���������̵���������\n";
				system("pause");
				return 0;
			}
			if (Request[mi][i]>Available[i])
			{
				cout << "��������Դ������ϵͳ���е���Դ����\n";
				system("pause");
				return 0;
			}
		}
		/*�Է���*/
		for (i = 0; i<n; i++)
		{
			Available[i] -= Request[mi][i];
			Allocation[mi][i] += Request[mi][i];
			Need[mi][i] -= Request[mi][i];
		}
		if (Safe(a) == 1)
			cout << "ͬ���������\n";
		else
		{
			cout << "������"<<endl;
			for (i = 0; i<n; i++)		//����
			{
				Available[i] += Request[mi][i];
				Allocation[mi][i] -= Request[mi][i];
				Need[mi][i] += Request[mi][i];
			}
		}



		for (i = 0; i<m; i++)
			Finish[i] = 0;	//	������
		char Flag;       //��־λ
		cout << "�Ƿ��ٴ�������䣿���밴y�����밴n"<<endl;
		while (1)
		{
			cin >> Flag;
			if (Flag == 'y' || Flag == 'n')
				break;
			else
			{
				cout << "�밴Ҫ����������:\n";
				continue;
			}
		}
		if (Flag == 'y')
			continue;
		else break;
	}
}