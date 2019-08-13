/*
#include<iostream>
#include<string>
using namespace std;
int maxn = 16;	//设置最大内存空间
int tim = 2;	//设置系统运行时间

struct occup_sect {	//已分配区表
	occup_sect* next;
	int begin, end;		//首尾标签
	int size;
	bool state;
};
struct free_sect {	//空闲区数据类型
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
void initialize(pcb* p, int size);	//输入进程表
void distibute(free_sect* h, occup_sect* H, pcb p);
void recycle(free_sect* h, occup_sect* H, pcb p);
void display(free_sect* h, occup_sect* H);

int main() {
	int size = 3;	//设置进程数目
	free_sect* h = new free_sect;
	occup_sect* H =NULL;
	h->begin = 0;
	h->end = 15;
	h->size = 16;
	pcb* p = new pcb[8];
	int *a = new int[maxn];
	initialize(p,size);
	//时间运行模拟
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
		cout << "输入进程名：" << "\t" << "输入进程大小：" << "\t" << "输入进程终止时间" << "\t" << "进程到达时间" << endl;
		cin >> p[i].name >> p[i].size >> p[i].due_time >> p[i].arr_time;
	}
}

void distibute(free_sect* h, occup_sect* H, pcb p)
{
	free_sect* q = h;
	occup_sect*Q = H;	//工作指针

	if (H == NULL) {
		H = new occup_sect;
		H->begin = 0;
		H->end = p.size;
		H->size = p.size;
		p.front = 0;
		p.rear = p.front + p.size;

		h->begin = p.rear+1;	//当前只有一个空闲区
		h->next = new free_sect;
	}
	else {
		int mincost = maxn;
		while (Q->next != NULL) {
			Q = Q->next;
		}		//把Q指向已分配表尾
		while (q != NULL) {
			if (q->size > p.size) {
				if (mincost > q->size - p.size) {
					mincost = q->size - p.size;
				}
			}
			q = q->next;
		}
		q = h;	//还原q
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

//debug函数
void display(free_sect * h, occup_sect * H)
{
	free_sect* p = h;
	occup_sect* P = H;
	int count = 1;
	if (h == NULL)
		cout << "空闲区为空！全部占用！"<<endl;
	if (H == NULL)
		cout << "无占用进程！"<<endl;
	cout << "展示空闲区：" << endl;
	while (p->next)
	{
		cout << "第" << count << "个空闲块首地址为:" << h->begin << "\t" << "尾地址为：" << h->end << endl;
		count++;
		p = p->next;
	}
	count = 1;
	cout << "展示已占用区：" << endl;
	while (P->next)
	{
		cout << "第" << count << "个进程块首地址为:" << H->begin << "\t" << "尾地址为：" << H->end << endl;
		count++;
		P = P->next;
	}
}
*/
#include<iostream>
#include<string>
#include<list>
#include<iomanip>
#define MemSize  16  //定义内存大小
#define MemBassaddr 0  //定义内存起始地址
using namespace std;
struct free_sect//空闲分区结构定义
{
	int base_address;//空闲分区的起始地址
	int sect_len;//空闲分区的长度
};
struct used_sect//已分配的内存分区结构定义
{
	string jobname;//作业名
	int base_address;  //作业所占分区的起始地址
	int sect_len;//作业所占分区的长度
};
list<free_sect>freetable;//空闲分区表
list<used_sect>usedtable;//已分配分区表
void AllocateMem(string &jobname, int &joblen)//采用最优适应分配算法为作业jobname分配joblen大小的空间
{
	//要分配的作业名不能为已存在的作业名
	list<used_sect>::iterator used = usedtable.begin();
	while (used != usedtable.end())
	{
		if (used->jobname == jobname)
		{
			cout << "作业已存在,不能再分配一个相同名的作业！" << endl;
			return;
		}
		else
		{
			used++;
		}
	}
	//最优适应分配算法
	list<free_sect>::iterator it = freetable.begin();	//工作指针
	if (it == freetable.end())
	{
		cout << "空闲分区已用完！" << endl;
		return;
	}
	list<free_sect>::iterator select_node = it;			//最优节点

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
			else if (select_node->sect_len < joblen)	//当初始节点不能满足条件时更新
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
		//修改已分配分区表
		used_sect tempuse;
		tempuse.base_address = select_node->base_address;
		tempuse.jobname = jobname;
		tempuse.sect_len = joblen;
		usedtable.push_back(tempuse);

		//从空闲区分配空间
		if (select_node->sect_len == joblen)
		{
			freetable.erase(select_node);
		}
		else
		{
			select_node->base_address = select_node->base_address + joblen;
			select_node->sect_len = select_node->sect_len - joblen;
		}
		cout << "为作业" << jobname << "分配内存成功！" << endl;
		return;
	}
	else
	{
		cout << "内存不足，为作业分配内存失败！" << endl;
		return;
	}
}
void ReclaimMem(string jobname)//回收作业jobname所占的内存
{
	list<used_sect>::iterator itused = usedtable.begin();
	list<free_sect>::iterator itfree = freetable.begin();	//工作指针
	free_sect free;
	while (itused != usedtable.end())
	{
		if (itused->jobname == jobname)//找到要回收的作业
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
					if (free.base_address == (it_down->base_address + it_down->sect_len))//下邻空闲区
					{
						if (free.base_address + free.sect_len == it_up->base_address)//下邻空闲区,上邻空闲区
						{
							it_down->sect_len = it_down->sect_len + free.sect_len + it_up->sect_len;
							freetable.erase(it_up);//删除上邻空闲区
							cout << "回收作业所占的内存成功！" << endl;
							return;

						}
						else//下邻空闲区,但不上邻空闲区
						{
							it_down->sect_len = it_down->sect_len + free.sect_len;
							cout << "回收作业所占的内存成功！" << endl;
							return;

						}

					}
					else if (free.base_address + free.sect_len == it_up->base_address)//上邻空闲区,但不下邻空闲区
					{
						it_up->base_address = free.base_address;
						it_up->sect_len = free.sect_len + it_up->sect_len;
						cout << "回收作业所占的内存成功！" << endl;
						return;

					}
					else//既不下邻空闲区又不上邻空闲区
					{
						if ((free.base_address<it_up->base_address) && (free.base_address>it_down->base_address))//位于空闲区中间
						{
							freetable.insert(it_up, free);
							cout << "回收作业所占的内存成功！" << endl;
							return;

						}
						else
						{
							if (free.base_address<it_down->base_address)//小于空闲区下限
							{
								freetable.insert(it_down, free);
								cout << "回收作业所占的内存成功！" << endl;
								return;
							}
							else//大于空闲区上限
							{
								it_down = it_up;
								itfree++;
								it_up = itfree;
								continue;
							}
						}//
					}//else既不下邻空闲区又不上邻空闲区

				}//while
				if (it_up == freetable.end())
				{
					if (it_down->base_address > free.base_address)
					{
						if (free.base_address + free.sect_len == it_down->base_address)//上邻空闲区
						{
							it_down->base_address = free.base_address;
							it_down->sect_len = it_down->sect_len + free.sect_len;
							cout << "回收作业所占的内存成功！" << endl;
							return;
						}
						else//不上邻空闲区
						{
							freetable.insert(it_down, free);
							cout << "回收作业所占的内存成功！" << endl;
							return;
						}
					}
					else
					{
						if (it_down->base_address + it_down->sect_len == free.base_address)//下邻空闲区
						{
							it_down->sect_len = it_down->sect_len + free.sect_len;
							cout << "回收作业所占的内存成功！" << endl;
							return;
						}
						else
						{
							freetable.push_back(free);
							cout << "回收作业所占的内存成功！" << endl;
							return;
						}
					}

				}//if(it_up==freetable.end())
				 /*else//没有遍历到空闲区表的末尾就已更新表
				 {
				 cout<<"回收作业所占的内存成功！"<<endl;
				 return;
				 }*/

			}//if(itfree!=NULL)
			else//空闲分区表为空
			{
				freetable.push_back(free);
				cout << "回收作业所占的内存成功！" << endl;
				return;
			}

		}//if(itused...)
		else //未找到要回收的作业
		{
			itused++;
		}
	}//while
	if (itused == usedtable.end())
	{
		cout << "未找到要回收的作业,请确定所输入的作业名是否正确！" << endl;
	}
}

//主函数
int main()
{
	//初始化空闲分区表
	free_sect tempfree;
	tempfree.base_address = MemBassaddr;
	tempfree.sect_len = MemSize;
	freetable.push_back(tempfree);
	//对内存进行管理
	int number(5);//管理操作的序号(如下所示)
	while (1)
	{

		if (number == 5)
		{
			cout << "内存管理操作（最优适应分配算法）：" << endl;
			cout << "---------------------------" << endl;
			cout << "【0】退出程序" << endl;
			cout << "【1】为作业分配内存" << endl;
			cout << "【2】回收作业所占的内存" << endl;
			cout << "【3】显示空闲分区表与已分配分区表" << endl;
			//cout << "【4】显示" << endl;
			//cout << "【5】返回管理操作界面" << endl;
			cout << "---------------------------" << endl;
		}
		cout << "请选择一个正确的管理序号操作：";
		cin >> number;
		if (cin.fail())
		{
			system("cls");
			cout << "输入错误,请仅输入数字！" << endl;
			cin.clear(); //清除std::cin的错误状态
			cin.sync(); //清空输入缓冲区
			continue;
		}
		string jobname;
		int joblen;
		list<free_sect>::iterator itfree = freetable.begin();
		list<used_sect>::iterator itused = usedtable.begin();
		int i = 0;//分区号从零开始
		int j = 0;//已分配分区表的分区号从零开始
		switch (number)
		{

		case 0:exit(0); break;
		case 1:
			cout << "输入作业名和作业所需长度： ";

			cin >> jobname >> joblen;
			if (cin.fail())
			{
				cout << "输入错误,请重新正确输入！" << endl;
				break;
			}
			if (joblen<-0)
			{
				cout << "作业长度小于或等于零！" << endl;
				break;
			}
			AllocateMem(jobname, joblen);
			break;
		case 2:
			cout << "输入要回收的作业名：";
			cin >> jobname;
			ReclaimMem(jobname);
			break;
		case 3:
			cout << endl << "空闲分区表状态如下:"<<"\n"<<"空闲分区号"<<"\t"<<"起始地址"<<"\t"<<"分区长度"<<"\n";
			while (itfree != freetable.end())
			{
				cout << setw(5) << i << '\t' << '\t' << setw(5) << itfree->base_address << '\t' << '\t' << setw(5) << itfree->sect_len << '\t' << endl;
				i++;
				itfree++;
			}

			cout << endl << "已分配分区表状态如下:"<<"\n"<<"作业名"<<"\t"<<"起始地址"<<"\t"<<"分区长度"<<"\n";
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
			cout << "输入错误,没有这个选项" << endl;

			break;
		}//swich
		cin.clear(); //清除std::cin的错误状态
		cin.sync(); //清空输入缓冲区
	}//while(1)

	return EXIT_SUCCESS;
}