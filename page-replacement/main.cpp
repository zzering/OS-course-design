#include<iostream>
#include<algorithm>
#include<list>
#include<vector>
#include<iomanip>
#include<climits>
#include<time.h>
#include<stdio.h>

using namespace std;

const int minn = 8;
const int maxx = 32;
const int N = 320;//指令执行次数
int ins[2 * N];
double hit_num = 0;
const int max_add = 32766;//32k-2

struct node {
	int id;
	int num;
};

void get_input()
{
	int cnt = 0;
	srand(time(0));
	while (cnt < N) {
		//在[1，32k - 2]间选取一起点
		int m = rand() % max_add + 1;
		ins[cnt++] = m;
		if (cnt >= N)break;
		ins[cnt++] = m + 1;
		if (cnt >= N)break;
		//在[0，M-1]间选取一起点
		int m1 = rand() % m;
		ins[cnt++] = m1;
		if (cnt >= N)break;
		ins[cnt++] = m1 + 1;
		if (cnt >= N)break;
		//在[M1 + 2，32k - 2]中选取一起点
		//(max_add +1 - 2 - m1) + (m1 + 2);
		int m2 = rand() % (max_add - 1 - m1) + (m1 + 2);
		ins[cnt++] = m2;
		if (cnt >= N)break;
		ins[cnt++] = m2 + 1;
		if (cnt >= N)break;
	}
	for (int i = 0; i < N; i++) {
		//产生的为地址，除以1024得到所在的页号
		ins[i] = ins[i] / 1024;
	}
}

double FIFO(int page)
{
	hit_num = 0;
	list<int>temp;//双向循环链表
	//用-1初始化
	for (int i = 0; i < page; i++) {
		temp.push_back(-1);
	}
	for (int i = 0; i < N; i++) {
		list<int>::iterator it = find(temp.begin(), temp.end(), ins[i]);
		//检查队列中存在对应的页号
		if (it == temp.end()) {
			//不存在时，删除队列中第一个页号，插入当前页号
			temp.pop_front();
			temp.push_back(ins[i]);
		}
		else {
			hit_num++;
		}
	}
	hit_num = hit_num / N;
	hit_num *= 100;
	return hit_num;
}

//最近最久未使用算法
double LRU(int page)
{
	hit_num = 0;
	list<node>temp;
	for (int i = 0; i < page; i++) {
		temp.push_back(node{ -1,0 });
	}
	list<node>::iterator it;
	for (int i = 0; i < N; i++) {
		for (it = temp.begin(); it != temp.end(); it++) {
			//每轮循环使num增大,最大的是最久未使用
			it->num++;
		}
		bool flag = false;
		//查找分页是否存在
		for (it = temp.begin(); it != temp.end(); it++) {
			//分页存在时
			if (it->id == ins[i]) {
				flag = true;
				it->num = 0;//设置为最近使用过
				hit_num++;
				break;
			}
		}
		//分页不存在时
		if (!flag) {
			//找一个最大的
			list<node>::iterator max_it = temp.begin();
			for (it = temp.begin(); it != temp.end(); it++) {
				if (it->num > max_it->num) {
					max_it = it;
				}
			}
			temp.erase(max_it);//淘汰最久未使用的分页
			temp.push_back(node{ ins[i],0 });
		}
	}
	hit_num = hit_num / N;
	hit_num *= 100;
	return hit_num;
}

//最佳页面置换算法
double OPT(int page)
{
	list<int>temp;
	hit_num = 0;
	for (int i = 0; i < page; i++) {
		temp.push_back(-1);
	}
	for (int i = 0; i < N; i++) {
		list<int>::iterator it = find(temp.begin(), temp.end(), ins[i]);
		if (it == temp.end()) {
			int max_id = -1;
			list<int>::iterator ans;
			for (it = temp.begin(); it != temp.end(); it++) {
				int cur = 0x3f3f3f3f;//若未查找到下标为无穷大
				//从当前页面之后开始查找
				for (int j = i + 1; j < N; j++) {
					if (ins[j] == *it) {
						cur = j;//记录下标
						break;
					}
				}
				//更新最大下标对应的页面
				if (cur > max_id) {
					max_id = cur;
					ans = it;
				}
			}
			temp.erase(ans);//淘汰最长时间不需要访问的页面
			temp.push_back(ins[i]);
		}
		else {
			hit_num++;
		}
	}
	hit_num = hit_num / N;
	hit_num *= 100;
	return hit_num;
}

int main()
{
	get_input();
	cout << "\t\t\t\t命中率结果" << endl;
	cout << "内存页块\t\tFIFO(%)\t\t\tLRU(%)\t\t\tOPT(%)" << endl;
	for (int i = minn; i <= maxx; i++) {
		printf("%d\t\t\t%.2f\t\t\t%.2f\t\t\t%.2f\n", i, FIFO(i), LRU(i), OPT(i));
	}
	return 0;
}
