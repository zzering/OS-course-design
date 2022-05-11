#include <iostream>
#include <algorithm>
#include <cstdio>

#define MAX 100
using namespace std;

//求平均寻道长度
double average(int* length, int n) {
	double sum = 0;
	int i;
	for (i = 0; i < n; i++)
		sum += length[i];
	return sum / n;
}

//先来先服务算法
void First_come_first_server(int* a, int n, int now) {
	int i, k = 0;
	int num = n;//调度请求数目
	int next[MAX], length[MAX];
	int visit[MAX] = { 0 };
	while (num--){
		for (i = 0; i < n; i++) {
			//省略已处理的请求
			if (visit[i]){
				continue;
			}
			else {
				length[k] = abs(a[i] - now);//abs绝对值
				next[k++] = a[i];
				visit[i] = 1;
				now = a[i];//更新now值
			}
		}
	}
	cout << endl << "下一个磁道  " << "移动距离" << endl;
	for (i = 0; i < n; i++) {
		cout << next[i] << "           " << length[i] << endl;
	}
	cout << "平均寻道长度:";
	printf("%.2f\n\n", average(length, n));//输出两位float后的小数
}
//最短寻道时间优先算法
void Shortest_seek_time_first(int* a, int n, int now) {
	int i, min, k = 0;
	int flag;//最短路径的下标
	int t = n;
	int next[MAX], length[MAX];
	int visit[MAX] = { 0 };//访问数组，已经访问过的为1
	//寻道n次
	while (t--) {
		min = 999999;
		//找没有访问过的中最近的
		for (i = 0; i < n; i++) {
			if (visit[i])
				continue;
			if (abs(a[i] - now) < min) {
				flag = i;
				min = abs(a[i] - now);
			}
		}
		length[k] = min;//移动的距离
		next[k++] = a[flag];//下一个被访问的磁道号
		visit[flag] = 1;//访问过的置1
		now = a[flag];//磁道移动到当前位置
	}
	cout << endl << "下一个磁道  " << "移动距离" << endl;
	for (i = 0; i < n; i++)
		cout << next[i] << "           " << length[i] << endl;
	cout << "平均寻道长度:";
	printf("%.2f\n\n", average(length, n));
}

//扫描算法
void Scan(int* a, int n, int now) {
	int i, flag = 0, k = 0;
	int next[MAX], length[MAX];
	sort(a, a + n);//从小到大排序
	//寻找开始磁道
	for (i = 0; i < n; i++) {
		if (a[i] >= now) {
			flag = i;
			break;
		}
	}

	//往递增方向访问
	for (i = flag; i < n; i++) {
		next[k] = a[i];
		length[k++] = abs(a[i] - now);
		now = a[i];
	}

	//回来往递减方向访问
	for (i = flag - 1; i >= 0; i--) {
		next[k] = a[i];
		length[k++] = abs(a[i] - now);
		now = a[i];
	}

	cout << endl << "下一个磁道  " << "移动距离" << endl;
	for (i = 0; i < n; i++)
		cout << next[i] << "           " << length[i] << endl;
	cout << "平均寻道长度:";
	printf("%.2f\n\n", average(length, n));
}

void Circle_scan(int* a, int n, int now) {
	int i, flag = 0, k = 0;
	int next[MAX], length[MAX];
	sort(a, a + n);//从小到大排序
	for (i = 0; i < n; i++) {
		if (a[i] >= now) {
			flag = i;
			break;
		}
	}

	//往递增方向访问
	for (i = flag; i < n; i++) {
		next[k] = a[i];
		length[k++] = abs(a[i] - now);
		now = a[i];
	}

	//循环往递增方向访问
	for (i = 0; i < flag; i++) {
		next[k] = a[i];
		length[k++] = abs(a[i] - now);
		now = a[i];
	}

	cout << endl << "下一个磁道  " << "移动距离" << endl;
	for (i = 0; i < n; i++)
		cout << next[i] << "           " << length[i] << endl;
	cout << "平均寻道长度:";
	printf("%.2f\n\n", average(length, n));
}

int main() {
	int a[MAX];//存放要用到的磁道号
	int start;//开始的磁道
	int n, i, flag = 1;
	cout << "一共要用到的磁道数：" << endl;
	cin >> n;
	cout << "随机的磁道：" << endl;
	srand((int)time(0));
	for (i = 0; i < n; i++) {
		a[i] = rand() % 100;
		cout << a[i] << "    ";
	}
	cout << endl << "开始的磁道：" << endl;
	cin >> start;

	//磁盘调度目录
	while (flag) {
		cout << "请选一种磁盘调度算法：" << endl;;
		cout << "1.先来先服务寻道算法" << endl;
		cout << "2.最短寻道时间优先" << endl;
		cout << "3.扫描算法" << endl;
		cout << "4.循环扫描算法" << endl;
		cout << "0.退出" << endl;
		cin >> flag;
		switch (flag) {
		case 1:
			First_come_first_server(a, n, start);break;
		case 2:
			Shortest_seek_time_first(a, n, start); break;
		case 3:
			Scan(a, n, start); break;
		case 4:
			Circle_scan(a, n, start); break;
		case 0:
			break;
		}
	}
	return 0;
}