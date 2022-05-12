#include <iostream>
#include <algorithm>
#include <cstdio>

#define MAX 100
using namespace std;

//��ƽ��Ѱ������
double average(int* length, int n) {
	double sum = 0;
	int i;
	for (i = 0; i < n; i++)
		sum += length[i];
	return sum / n;
}

//�����ȷ����㷨
void First_come_first_server(int* a, int n, int now) {
	int i, k = 0;
	int num = n;//����������Ŀ
	int next[MAX], length[MAX];
	int visit[MAX] = { 0 };
	while (num--){
		for (i = 0; i < n; i++) {
			//ʡ���Ѵ��������
			if (visit[i]){
				continue;
			}
			else {
				length[k] = abs(a[i] - now);//abs����ֵ
				next[k++] = a[i];
				visit[i] = 1;
				now = a[i];//����nowֵ
			}
		}
	}
	cout << endl << "��һ���ŵ�  " << "�ƶ�����" << endl;
	for (i = 0; i < n; i++) {
		cout << next[i] << "           " << length[i] << endl;
	}
	cout << "ƽ��Ѱ������:";
	printf("%.2f\n\n", average(length, n));//�����λfloat���С��
}
//���Ѱ��ʱ�������㷨
void Shortest_seek_time_first(int* a, int n, int now) {
	int i, min, k = 0;
	int flag;//���·�����±�
	int t = n;
	int next[MAX], length[MAX];
	int visit[MAX] = { 0 };//�������飬�Ѿ����ʹ���Ϊ1
	//Ѱ��n��
	while (t--) {
		min = 999999;
		//��û�з��ʹ����������
		for (i = 0; i < n; i++) {
			if (visit[i])
				continue;
			if (abs(a[i] - now) < min) {
				flag = i;
				min = abs(a[i] - now);
			}
		}
		length[k] = min;//�ƶ��ľ���
		next[k++] = a[flag];//��һ�������ʵĴŵ���
		visit[flag] = 1;//���ʹ�����1
		now = a[flag];//�ŵ��ƶ�����ǰλ��
	}
	cout << endl << "��һ���ŵ�  " << "�ƶ�����" << endl;
	for (i = 0; i < n; i++)
		cout << next[i] << "           " << length[i] << endl;
	cout << "ƽ��Ѱ������:";
	printf("%.2f\n\n", average(length, n));
}

//ɨ���㷨
void Scan(int* a, int n, int now) {
	int i, flag = 0, k = 0;
	int next[MAX], length[MAX];
	sort(a, a + n);//��С��������
	//Ѱ�ҿ�ʼ�ŵ�
	for (i = 0; i < n; i++) {
		if (a[i] >= now) {
			flag = i;
			break;
		}
	}

	//�������������
	for (i = flag; i < n; i++) {
		next[k] = a[i];
		length[k++] = abs(a[i] - now);
		now = a[i];
	}

	//�������ݼ��������
	for (i = flag - 1; i >= 0; i--) {
		next[k] = a[i];
		length[k++] = abs(a[i] - now);
		now = a[i];
	}

	cout << endl << "��һ���ŵ�  " << "�ƶ�����" << endl;
	for (i = 0; i < n; i++)
		cout << next[i] << "           " << length[i] << endl;
	cout << "ƽ��Ѱ������:";
	printf("%.2f\n\n", average(length, n));
}

void Circle_scan(int* a, int n, int now) {
	int i, flag = 0, k = 0;
	int next[MAX], length[MAX];
	sort(a, a + n);//��С��������
	for (i = 0; i < n; i++) {
		if (a[i] >= now) {
			flag = i;
			break;
		}
	}

	//�������������
	for (i = flag; i < n; i++) {
		next[k] = a[i];
		length[k++] = abs(a[i] - now);
		now = a[i];
	}

	//ѭ���������������
	for (i = 0; i < flag; i++) {
		next[k] = a[i];
		length[k++] = abs(a[i] - now);
		now = a[i];
	}

	cout << endl << "��һ���ŵ�  " << "�ƶ�����" << endl;
	for (i = 0; i < n; i++)
		cout << next[i] << "           " << length[i] << endl;
	cout << "ƽ��Ѱ������:";
	printf("%.2f\n\n", average(length, n));
}

int main() {
	int a[MAX];//���Ҫ�õ��Ĵŵ���
	int start;//��ʼ�Ĵŵ�
	int n, i, flag = 1;
	cout << "һ��Ҫ�õ��Ĵŵ�����" << endl;
	cin >> n;
	cout << "����Ĵŵ���" << endl;
	srand((int)time(0));
	for (i = 0; i < n; i++) {
		a[i] = rand() % 100;
		cout << a[i] << "    ";
	}
	cout << endl << "��ʼ�Ĵŵ���" << endl;
	cin >> start;

	//���̵���Ŀ¼
	while (flag) {
		cout << "��ѡһ�ִ��̵����㷨��" << endl;;
		cout << "1.�����ȷ���Ѱ���㷨" << endl;
		cout << "2.���Ѱ��ʱ������" << endl;
		cout << "3.ɨ���㷨" << endl;
		cout << "4.ѭ��ɨ���㷨" << endl;
		cout << "0.�˳�" << endl;
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