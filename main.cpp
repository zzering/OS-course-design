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

void show(int num, int next[], int length[])
{
	int i;
	cout << endl << "��һ���ŵ�"<<"\t\t\t" << "�ƶ�����" << endl;
	for (i = 0; i < num; i++) {
		cout << next[i] << "\t\t\t\t" << length[i] << endl;
	}
	cout << "ƽ��Ѱ������:";
	printf("%.2f\n\n", average(length, num));//�����λfloat���С��
}

//�����ȷ����㷨
void first_come_first_server(int* a, int n, int now) {
	int i, j = 0;
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
				length[j] = abs(a[i] - now);//abs����ֵ
				next[j++] = a[i];
				visit[i] = 1;
				now = a[i];//����nowֵ
			}
		}
	}
	show(n, next, length);
}
//���Ѱ��ʱ�������㷨
void shortest_seek_time_first(int* a, int n, int now) {
	int i, min, j = 0;
	int flag;//��ǰ���·�����±�
	int t = n;
	int next[MAX], length[MAX];
	int visit[MAX] = { 0 };//�������飬�Ѿ����ʹ���Ϊ1
	//Ѱ��n��
	while (t--) {
		min = 999999;//ÿ��ѭ����min����
		//��û�з��ʹ����������
		for (i = 0; i < n; i++) {
			if (visit[i])
				continue;
			if (abs(a[i] - now) < min) {
				flag = i;
				min = abs(a[i] - now);
			}
		}
		length[j] = min;//�ƶ��ľ���
		next[j++] = a[flag];//��һ�������ʵĴŵ���
		visit[flag] = 1;//���ʹ�����1
		now = a[flag];//�ŵ��ƶ�����ǰλ��
	}
	show(n, next, length);
}

//ɨ���㷨
void scan(int* a, int n, int now) {
	int i, flag = 0, j = 0;//flag�ǵ�ǰ�ŵ��±�
	//����ı�ԭʼ����,Ӱ�������㷨
	int temp_a[MAX];
	for (int j = 0; j < n; j++) {
		temp_a[j] = a[j];
	}
	int next[MAX], length[MAX];
	sort(temp_a, temp_a + n);//��С��������
	//Ѱ�ҿ�ʼ�ŵ�
	for (i = 0; i < n; i++) {
		if (temp_a[i] >= now) {
			flag = i;
			break;
		}
	}
	//�������������
	for (i = flag; i < n; i++) {
		next[j] = temp_a[i];
		length[j++] = abs(temp_a[i] - now);
		now = temp_a[i];//�ŵ��ƶ�����ǰλ��
	}
	//�������ݼ��������
	for (i = flag - 1; i >= 0; i--) {
		next[j] = temp_a[i];
		length[j++] = abs(temp_a[i] - now);
		now = temp_a[i];//�ŵ��ƶ�����ǰλ��
	}
	show(n, next, length);
}

void circle_scan(int* a, int n, int now) {
	int i, flag = 0, j = 0;
	//����ı�ԭʼ����,Ӱ�������㷨
	int temp_a[MAX];
	for (int j = 0; j < n; j++) {
		temp_a[j] = a[j];
	}
	int next[MAX], length[MAX];
	sort(temp_a, temp_a + n);//��С��������
	for (i = 0; i < n; i++) {
		if (temp_a[i] >= now) {
			flag = i;
			break;
		}
	}
	//�������������
	for (i = flag; i < n; i++) {
		next[j] = temp_a[i];
		length[j++] = abs(temp_a[i] - now);
		now = temp_a[i];
	}
	//ѭ���������������
	for (i = 0; i < flag; i++) {
		next[j] = temp_a[i];
		length[j++] = abs(temp_a[i] - now);
		now = temp_a[i];
	}
	show(n, next, length);
}

//���������������뺯��
void lazyDogInput(int a[],int &num)
{
	int i,order;
	cout << "��ѡ������ŵ��������з�ʽ:\n";
	cout << "1.�������:\n";
	cout << "2.����ָ������:\n";
	cout << "3.�ֶ���������:\n";
	cin >> order;
	switch (order) {
	case 1:
		cout << "������ŵ�����" << endl;
		cin >> num;
		cout << "��������ŵ���" << endl;
		srand((int)time(0));
		for (i = 0; i < num; i++) {
			a[i] = rand() % 100;
			cout << a[i] << "  ";
		}
		break;
	case 2:
		num = 14;
		a[0] = 30; a[1] = 50; a[2] = 100; a[3] = 180; a[4] = 20; a[5] = 90; a[6] = 150;
		a[7] = 70; a[8] = 80; a[9] = 10; a[10] = 160; a[11] = 120; a[12] = 40; a[13] = 110;
		cout << "�ŵ�����Ϊ��" << endl;
		for (i = 0; i < num; i++) {
			cout << a[i] << "  ";
		}
		break;
	case 3:
		cout << "������ŵ�����" << endl;
		cin >> num;
		cout << "����������ŵ����У�" << endl;
		for (i = 0; i < num; i++) {
			cin>>a[i];
		}
		cout << "�ŵ�����Ϊ��" << endl;
		for (i = 0; i < num; i++) {
			cout << a[i] << "  ";
		}
		break;
	}
}

int main() {
	do {
		system("cls");
		int a[MAX];//���Ҫ�õ��Ĵŵ���
		int start;//��ʼ�Ĵŵ�
		int n, i, flag = 1;
		lazyDogInput(a, n);
		cout << endl << "��ʼ�Ĵŵ���" << endl;
		cin >> start;
		//���̵���Ŀ¼
		while (flag) {
			system("cls");
			cout << "��ѡһ�ִ��̵����㷨��" << endl;;
			cout << "1.�����ȷ���Ѱ���㷨" << endl;
			cout << "2.���Ѱ��ʱ������" << endl;
			cout << "3.ɨ���㷨" << endl;
			cout << "4.ѭ��ɨ���㷨" << endl;
			cout << "0.����" << endl;
			cin >> flag;
			cout << "�ŵ�����:\n";
			if (flag) {
				for (i = 0; i < n; i++) {
					cout << a[i] << "  ";
				}
				cout << "\n��ʼ�Ĵŵ���" << start << endl;
			}
			switch (flag) {
			case 1:
				first_come_first_server(a, n, start);
				system("pause");
				break;
			case 2:
				shortest_seek_time_first(a, n, start);
				system("pause");
				break;
			case 3:
				scan(a, n, start);
				system("pause");
				break;
			case 4:
				circle_scan(a, n, start);
				system("pause");
				break;
			case 0:break;
			}
		}
	} while (true);
	return 0;
}