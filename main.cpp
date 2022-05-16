#include <iostream>
#include <algorithm>
#include <cstdio>

#define MAX 100
using namespace std;

//求平均寻道长度
double average(int *length, int n)
{
	double sum = 0;
	int i;
	for (i = 0; i < n; i++)
		sum += length[i];
	return sum / n;
}

void show(int num, int next[], int length[])
{
	int i;
	cout << endl
		 << "下一个磁道"
		 << "\t\t\t"
		 << "移动距离" << endl;
	for (i = 0; i < num; i++)
	{
		cout << next[i] << "\t\t\t\t" << length[i] << endl;
	}
	cout << "平均寻道长度:";
	printf("%.2f\n\n", average(length, num)); //输出两位float后的小数
}

//先来先服务算法
void first_come_first_server(int *a, int n, int now)
{
	int i, j = 0;
	int num = n; //调度请求数目
	int next[MAX], length[MAX];
	int visit[MAX] = {0};
	while (num--)
	{
		for (i = 0; i < n; i++)
		{
			//省略已处理的请求
			if (visit[i])
			{
				continue;
			}
			else
			{
				length[j] = abs(a[i] - now); // abs绝对值
				next[j++] = a[i];
				visit[i] = 1;
				now = a[i]; //更新now值
			}
		}
	}
	show(n, next, length);
}
//最短寻道时间优先算法
void shortest_seek_time_first(int *a, int n, int now)
{
	int i, min, j = 0;
	int flag; //当前最短路径的下标
	int t = n;
	int next[MAX], length[MAX];
	int visit[MAX] = {0}; //访问数组，已经访问过的为1
	//寻道n次
	while (t--)
	{
		min = 9999999; //每次循环将min重置
		//找没有访问过的中最近的
		for (i = 0; i < n; i++)
		{
			if (visit[i])
				continue;
			if (abs(a[i] - now) < min)
			{
				flag = i;
				min = abs(a[i] - now);
			}
		}
		length[j] = min;	 //移动的距离
		next[j++] = a[flag]; //下一个被访问的磁道号
		visit[flag] = 1;	 //访问过的置1
		now = a[flag];		 //磁道移动到当前位置
	}
	show(n, next, length);
}

//扫描算法
void scan(int *a, int n, int now)
{
	int i, flag = 0, j = 0; // flag是当前磁道下标
	//避免改变原始序列,影响后面的算法
	int temp_a[MAX];
	for (int j = 0; j < n; j++)
	{
		temp_a[j] = a[j];
	}
	int next[MAX], length[MAX];
	sort(temp_a, temp_a + n); //从小到大排序
	//寻找开始磁道
	for (i = 0; i < n; i++)
	{
		if (temp_a[i] >= now)
		{
			flag = i;
			break;
		}
	}
	//往递增方向访问
	for (i = flag; i < n; i++)
	{
		next[j] = temp_a[i];
		length[j++] = abs(temp_a[i] - now);
		now = temp_a[i]; //磁道移动到当前位置
	}
	//回来往递减方向访问
	for (i = flag - 1; i >= 0; i--)
	{
		next[j] = temp_a[i];
		length[j++] = abs(temp_a[i] - now);
		now = temp_a[i]; //磁道移动到当前位置
	}
	show(n, next, length);
}

void circle_scan(int *a, int n, int now)
{
	int i, flag = 0, j = 0;
	//避免改变原始序列,影响后面的算法
	int temp_a[MAX];
	for (int j = 0; j < n; j++)
	{
		temp_a[j] = a[j];
	}
	int next[MAX], length[MAX];
	sort(temp_a, temp_a + n); //从小到大排序
	for (i = 0; i < n; i++)
	{
		if (temp_a[i] >= now)
		{
			flag = i;
			break;
		}
	}
	//往递增方向访问
	for (i = flag; i < n; i++)
	{
		next[j] = temp_a[i];
		length[j++] = abs(temp_a[i] - now);
		now = temp_a[i];
	}
	//循环往递增方向访问
	for (i = 0; i < flag; i++)
	{
		next[j] = temp_a[i];
		length[j++] = abs(temp_a[i] - now);
		now = temp_a[i];
	}
	show(n, next, length);
}

//适用于懒狗的输入函数
void lazyDogInput(int a[], int &num)
{
	int i, order;
	cout << "请选择输出磁道请求序列方式:\n";
	cout << "1.随机生成:\n";
	cout << "2.生成指定序列:\n";
	cout << "3.手动输入序列:\n";
	cin >> order;
	switch (order)
	{
	case 1:
		cout << "请输入磁道数：" << endl;
		cin >> num;
		cout << "生成随机磁道：" << endl;
		srand((int)time(0));
		for (i = 0; i < num; i++)
		{
			a[i] = rand() % 100;
			cout << a[i] << "  ";
		}
		break;
	case 2:
		num = 14;
		a[0] = 30;
		a[1] = 50;
		a[2] = 100;
		a[3] = 180;
		a[4] = 20;
		a[5] = 90;
		a[6] = 150;
		a[7] = 70;
		a[8] = 80;
		a[9] = 10;
		a[10] = 160;
		a[11] = 120;
		a[12] = 40;
		a[13] = 110;
		cout << "磁道序列为：" << endl;
		for (i = 0; i < num; i++)
		{
			cout << a[i] << "  ";
		}
		break;
	case 3:
		cout << "请输入磁道数：" << endl;
		cin >> num;
		cout << "请依次输入磁道序列：" << endl;
		for (i = 0; i < num; i++)
		{
			cin >> a[i];
		}
		cout << "磁道序列为：" << endl;
		for (i = 0; i < num; i++)
		{
			cout << a[i] << "  ";
		}
		break;
	}
}

int main()
{
	do
	{
		int a[MAX]; //存放要用到的磁道号
		int start;	//开始的磁道
		int n, i, flag = 1;
		lazyDogInput(a, n);
		cout << endl
			 << "开始的磁道：" << endl;
		cin >> start;
		//磁盘调度目录
		while (flag)
		{
			system("clear");
			cout << "请选一种磁盘调度算法：" << endl;
			cout << "1.先来先服务寻道算法" << endl;
			cout << "2.最短寻道时间优先" << endl;
			cout << "3.扫描算法" << endl;
			cout << "4.循环扫描算法" << endl;
			cout << "0.返回" << endl;
			cin >> flag;
			if (flag)
			{
				cout << "磁道序列:\n";
				for (i = 0; i < n; i++)
				{
					cout << a[i] << "  ";
				}
				cout << "\n开始的磁道：" << start << endl;
			}
			switch (flag)
			{
			case 1:
				first_come_first_server(a, n, start);
				cin.get();
				cin.get();
				break;
			case 2:
				shortest_seek_time_first(a, n, start);
				cin.get();
				cin.get();
				break;
			case 3:
				scan(a, n, start);
				cin.get();
				cin.get();
				break;
			case 4:
				circle_scan(a, n, start);
				cin.get();
				cin.get();
				break;
			case 0:
				system("clear");
				break;
			}
		}
	} while (true);
	return 0;
}