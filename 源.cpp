/*
#include<iostream>
#include<string>
using namespace std;
int maxn = 16;	//��������ڴ�ռ�
int tim = 2;	//����ϵͳ����ʱ��

struct occup_sect {	//�ѷ�������
	occup_sect* next;
	int begin, end;		//��β��ǩ
	int size;
	bool state;
};
struct free_sect {	//��������������
	free_sect* next;
	int begin, end;
	int size;
	bool state;
};
struct pcb {
	int size;
	int arr_time;
	string name;
	int due_time;
	int front;
	int rear;
	bool wait = false;
};
void initialize(pcb* p, int size);	//������̱�
void distibute(free_sect* h, occup_sect* H, pcb p);
void recycle(free_sect* h, occup_sect* H, pcb p);
void display(free_sect* h, occup_sect* H);

int main() {
	int size = 3;	//���ý�����Ŀ
	free_sect* h = new free_sect;
	occup_sect* H =NULL;
	h->begin = 0;
	h->end = 15;
	h->size = 16;
	pcb* p = new pcb[8];
	int *a = new int[maxn];
	initialize(p,size);
	//ʱ������ģ��
	for (int i = 0; i <= tim; i++) {
		for(int j = 0; j < size; j++)
			if (p[j].arr_time == i) {
				distibute(h, H, p[i]);
			}
		display(h, H);
		for (int j = 0; j < size; j++) {
			if (p[j].wait == false) {
				if (p[j].due_time == i)
					recycle(h, H, p[j]);
			}
		}
	}
	system("pause");
	return 0;
}
void initialize(pcb* p, int size) {
	for (int i = 0; i < size; i++) {
		cout << "�����������" << "\t" << "������̴�С��" << "\t" << "���������ֹʱ��" << "\t" << "���̵���ʱ��" << endl;
		cin >> p[i].name >> p[i].size >> p[i].due_time >> p[i].arr_time;
	}
}

void distibute(free_sect* h, occup_sect* H, pcb p)
{
	free_sect* q = h;
	occup_sect*Q = H;	//����ָ��

	if (H == NULL) {
		H = new occup_sect;
		H->begin = 0;
		H->end = p.size;
		H->size = p.size;
		p.front = 0;
		p.rear = p.front + p.size;

		h->begin = p.rear+1;	//��ǰֻ��һ��������
		h->next = new free_sect;
	}
	else {
		int mincost = maxn;
		while (Q->next != NULL) {
			Q = Q->next;
		}		//��Qָ���ѷ����β
		while (q != NULL) {
			if (q->size > p.size) {
				if (mincost > q->size - p.size) {
					mincost = q->size - p.size;
				}
			}
			q = q->next;
		}
		q = h;	//��ԭq
		while (q != NULL)
		{
			if (q->size - p.size == mincost) {
				p.front = q->begin;
				p.rear = q->end;
				Q->begin = p.front;
				Q->end = p.rear;
				Q->next = new occup_sect;
			}
			q = q->next;
		}
	}
}

void recycle(free_sect * h, occup_sect * H, pcb p)
{
	
}

//debug����
void display(free_sect * h, occup_sect * H)
{
	free_sect* p = h;
	occup_sect* P = H;
	int count = 1;
	if (h == NULL)
		cout << "������Ϊ�գ�ȫ��ռ�ã�"<<endl;
	if (H == NULL)
		cout << "��ռ�ý��̣�"<<endl;
	cout << "չʾ��������" << endl;
	while (p->next)
	{
		cout << "��" << count << "�����п��׵�ַΪ:" << h->begin << "\t" << "β��ַΪ��" << h->end << endl;
		count++;
		p = p->next;
	}
	count = 1;
	cout << "չʾ��ռ������" << endl;
	while (P->next)
	{
		cout << "��" << count << "�����̿��׵�ַΪ:" << H->begin << "\t" << "β��ַΪ��" << H->end << endl;
		count++;
		P = P->next;
	}
}
*/
#include<iostream>
#include<string>
#include<list>
#include<iomanip>
#define MemSize  16  //�����ڴ��С
#define MemBassaddr 0  //�����ڴ���ʼ��ַ
using namespace std;
struct free_sect//���з����ṹ����
{
	int base_address;//���з�������ʼ��ַ
	int sect_len;//���з����ĳ���
};
struct used_sect//�ѷ�����ڴ�����ṹ����
{
	string jobname;//��ҵ��
	int base_address;  //��ҵ��ռ��������ʼ��ַ
	int sect_len;//��ҵ��ռ�����ĳ���
};
list<free_sect>freetable;//���з�����
list<used_sect>usedtable;//�ѷ��������
void AllocateMem(string &jobname, int &joblen)//����������Ӧ�����㷨Ϊ��ҵjobname����joblen��С�Ŀռ�
{
	//Ҫ�������ҵ������Ϊ�Ѵ��ڵ���ҵ��
	list<used_sect>::iterator used = usedtable.begin();
	while (used != usedtable.end())
	{
		if (used->jobname == jobname)
		{
			cout << "��ҵ�Ѵ���,�����ٷ���һ����ͬ������ҵ��" << endl;
			return;
		}
		else
		{
			used++;
		}
	}
	//������Ӧ�����㷨
	list<free_sect>::iterator it = freetable.begin();	//����ָ��
	if (it == freetable.end())
	{
		cout << "���з��������꣡" << endl;
		return;
	}
	list<free_sect>::iterator select_node = it;			//���Žڵ�

	while (it != freetable.end())
	{
		if (it->sect_len >= joblen)
		{
			if (select_node->sect_len > it->sect_len)
			{
				select_node = it;
				it++;
				continue;
			}
			else if (select_node->sect_len < joblen)	//����ʼ�ڵ㲻����������ʱ����
			{
				select_node = it;	
				it++;
				continue;
			}
			else
			{
				it++;
				continue;
			}
		}
		else
		{
			it++;
		}
	}//while

	if (select_node->sect_len >= joblen)
	{
		//�޸��ѷ��������
		used_sect tempuse;
		tempuse.base_address = select_node->base_address;
		tempuse.jobname = jobname;
		tempuse.sect_len = joblen;
		usedtable.push_back(tempuse);

		//�ӿ���������ռ�
		if (select_node->sect_len == joblen)
		{
			freetable.erase(select_node);
		}
		else
		{
			select_node->base_address = select_node->base_address + joblen;
			select_node->sect_len = select_node->sect_len - joblen;
		}
		cout << "Ϊ��ҵ" << jobname << "�����ڴ�ɹ���" << endl;
		return;
	}
	else
	{
		cout << "�ڴ治�㣬Ϊ��ҵ�����ڴ�ʧ�ܣ�" << endl;
		return;
	}
}
void ReclaimMem(string jobname)//������ҵjobname��ռ���ڴ�
{
	list<used_sect>::iterator itused = usedtable.begin();
	list<free_sect>::iterator itfree = freetable.begin();	//����ָ��
	free_sect free;
	while (itused != usedtable.end())
	{
		if (itused->jobname == jobname)//�ҵ�Ҫ���յ���ҵ
		{
			free.base_address = itused->base_address;
			free.sect_len = itused->sect_len;
			usedtable.erase(itused);
			if (itfree != freetable.end())
			{
				list<free_sect>::iterator it_down = itfree;
				list<free_sect>::iterator it_up = ++itfree;
				while (it_up != freetable.end())
				{
					if (free.base_address == (it_down->base_address + it_down->sect_len))//���ڿ�����
					{
						if (free.base_address + free.sect_len == it_up->base_address)//���ڿ�����,���ڿ�����
						{
							it_down->sect_len = it_down->sect_len + free.sect_len + it_up->sect_len;
							freetable.erase(it_up);//ɾ�����ڿ�����
							cout << "������ҵ��ռ���ڴ�ɹ���" << endl;
							return;

						}
						else//���ڿ�����,�������ڿ�����
						{
							it_down->sect_len = it_down->sect_len + free.sect_len;
							cout << "������ҵ��ռ���ڴ�ɹ���" << endl;
							return;

						}

					}
					else if (free.base_address + free.sect_len == it_up->base_address)//���ڿ�����,�������ڿ�����
					{
						it_up->base_address = free.base_address;
						it_up->sect_len = free.sect_len + it_up->sect_len;
						cout << "������ҵ��ռ���ڴ�ɹ���" << endl;
						return;

					}
					else//�Ȳ����ڿ������ֲ����ڿ�����
					{
						if ((free.base_address<it_up->base_address) && (free.base_address>it_down->base_address))//λ�ڿ������м�
						{
							freetable.insert(it_up, free);
							cout << "������ҵ��ռ���ڴ�ɹ���" << endl;
							return;

						}
						else
						{
							if (free.base_address<it_down->base_address)//С�ڿ���������
							{
								freetable.insert(it_down, free);
								cout << "������ҵ��ռ���ڴ�ɹ���" << endl;
								return;
							}
							else//���ڿ���������
							{
								it_down = it_up;
								itfree++;
								it_up = itfree;
								continue;
							}
						}//
					}//else�Ȳ����ڿ������ֲ����ڿ�����

				}//while
				if (it_up == freetable.end())
				{
					if (it_down->base_address > free.base_address)
					{
						if (free.base_address + free.sect_len == it_down->base_address)//���ڿ�����
						{
							it_down->base_address = free.base_address;
							it_down->sect_len = it_down->sect_len + free.sect_len;
							cout << "������ҵ��ռ���ڴ�ɹ���" << endl;
							return;
						}
						else//�����ڿ�����
						{
							freetable.insert(it_down, free);
							cout << "������ҵ��ռ���ڴ�ɹ���" << endl;
							return;
						}
					}
					else
					{
						if (it_down->base_address + it_down->sect_len == free.base_address)//���ڿ�����
						{
							it_down->sect_len = it_down->sect_len + free.sect_len;
							cout << "������ҵ��ռ���ڴ�ɹ���" << endl;
							return;
						}
						else
						{
							freetable.push_back(free);
							cout << "������ҵ��ռ���ڴ�ɹ���" << endl;
							return;
						}
					}

				}//if(it_up==freetable.end())
				 /*else//û�б��������������ĩβ���Ѹ��±�
				 {
				 cout<<"������ҵ��ռ���ڴ�ɹ���"<<endl;
				 return;
				 }*/

			}//if(itfree!=NULL)
			else//���з�����Ϊ��
			{
				freetable.push_back(free);
				cout << "������ҵ��ռ���ڴ�ɹ���" << endl;
				return;
			}

		}//if(itused...)
		else //δ�ҵ�Ҫ���յ���ҵ
		{
			itused++;
		}
	}//while
	if (itused == usedtable.end())
	{
		cout << "δ�ҵ�Ҫ���յ���ҵ,��ȷ�����������ҵ���Ƿ���ȷ��" << endl;
	}
}

//������
int main()
{
	//��ʼ�����з�����
	free_sect tempfree;
	tempfree.base_address = MemBassaddr;
	tempfree.sect_len = MemSize;
	freetable.push_back(tempfree);
	//���ڴ���й���
	int number(5);//������������(������ʾ)
	while (1)
	{

		if (number == 5)
		{
			cout << "�ڴ���������������Ӧ�����㷨����" << endl;
			cout << "---------------------------" << endl;
			cout << "��0���˳�����" << endl;
			cout << "��1��Ϊ��ҵ�����ڴ�" << endl;
			cout << "��2��������ҵ��ռ���ڴ�" << endl;
			cout << "��3����ʾ���з��������ѷ��������" << endl;
			//cout << "��4����ʾ" << endl;
			//cout << "��5�����ع����������" << endl;
			cout << "---------------------------" << endl;
		}
		cout << "��ѡ��һ����ȷ�Ĺ�����Ų�����";
		cin >> number;
		if (cin.fail())
		{
			system("cls");
			cout << "�������,����������֣�" << endl;
			cin.clear(); //���std::cin�Ĵ���״̬
			cin.sync(); //������뻺����
			continue;
		}
		string jobname;
		int joblen;
		list<free_sect>::iterator itfree = freetable.begin();
		list<used_sect>::iterator itused = usedtable.begin();
		int i = 0;//�����Ŵ��㿪ʼ
		int j = 0;//�ѷ��������ķ����Ŵ��㿪ʼ
		switch (number)
		{

		case 0:exit(0); break;
		case 1:
			cout << "������ҵ������ҵ���賤�ȣ� ";

			cin >> jobname >> joblen;
			if (cin.fail())
			{
				cout << "�������,��������ȷ���룡" << endl;
				break;
			}
			if (joblen<-0)
			{
				cout << "��ҵ����С�ڻ�����㣡" << endl;
				break;
			}
			AllocateMem(jobname, joblen);
			break;
		case 2:
			cout << "����Ҫ���յ���ҵ����";
			cin >> jobname;
			ReclaimMem(jobname);
			break;
		case 3:
			cout << endl << "���з�����״̬����:"<<"\n"<<"���з�����"<<"\t"<<"��ʼ��ַ"<<"\t"<<"��������"<<"\n";
			while (itfree != freetable.end())
			{
				cout << setw(5) << i << '\t' << '\t' << setw(5) << itfree->base_address << '\t' << '\t' << setw(5) << itfree->sect_len << '\t' << endl;
				i++;
				itfree++;
			}

			cout << endl << "�ѷ��������״̬����:"<<"\n"<<"��ҵ��"<<"\t"<<"��ʼ��ַ"<<"\t"<<"��������"<<"\n";
			while (itused != usedtable.end())
			{
				cout << setw(5) << itused->jobname << '\t' << itused->base_address << '\t' << '\t' << itused->sect_len << endl;
				j++;
				itused++;
			}
			break;
	/*	case 4:
			
			break;
		case 5:
			system("cls");
			break;
			*/
		default:
			cout << "�������,û�����ѡ��" << endl;

			break;
		}//swich
		cin.clear(); //���std::cin�Ĵ���״̬
		cin.sync(); //������뻺����
	}//while(1)

	return EXIT_SUCCESS;
}