#include <iostream>
#include <sstream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <cstring>
#pragma execution_character_set("utf-8")

using namespace std;

//定义全局变量
const int MAX = 0x3f3f3f;
char filename[50];
int fd; //打开文件时系统返回的文件标识符
bool opened = false;
char *pargv[4] = {"ls", "-l", NULL, NULL};

void create_open_file(char *filename)
{
	//建立新文件时的权限遮罩
	umask(0000);
	//以读写方式 | 如果文件不存在则创建该文件，若存在则忽略
	fd = open(filename, O_RDWR | O_CREAT, 0666); //真实权限:mode-umask
	//当打开的文件不存在时使用 3 个参数的格式
	if (fd < 0)
	{
		printf("文件创建失败\n");
	}
	else
	{
		printf("文件创建成功\n");
	}
	close(fd);
}

void write_file(char *buffer, char *filename)
{
	//只写打开
	fd = open(filename, O_WRONLY);
	if (fd < 0)
	{
		printf("文件打开失败\n");
		return;
	}
	int returnnum = write(fd, buffer, strlen(buffer));
	if (returnnum != -1)
	{
		printf("写入成功！\n");
	}
	else
	{
		printf("写入失败！\n");
	}
}

void mode_file(int mode, char *filename)
{
	//以any方式打开
	fd = open(filename, O_RDONLY, 0666);
	if (fd < 0)
	{
		printf("文件打开失败\n");
		return;
	}
	// 10-base number-> 8-base number
	int mode_u = mode / 100;						 // user
	int mode_g = mode / 10 % 10;					 // group
	int mode_o = mode % 10;							 // others
	mode = (mode_u * 8 * 8) + (mode_g * 8) + mode_o; //八进制转换
	int returnnum = chmod(filename, mode);
	if (returnnum == -1)
	{
		printf("修改权限失败\n");
	}
	else
	{
		printf("修改权限成功\n");
	}
}

void read_file(char *filename)
{
	//只读打开
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("文件打开失败\n");
		return;
	}
	char buffer[1 << 15]; // 2的15次方
	memset(buffer, 0, sizeof(buffer));
	// lseek定位一个已经打开的文件
	//第2 3参数将读写位置移到文件开头
	lseek(fd, 0, SEEK_SET);
	int returnnum = read(fd, buffer, 1 << 15);
	if (returnnum != -1)
	{
		printf("文件内容为：\n");
		printf("%s\n", buffer);
	}
	else
	{
		printf("文件读取失败\n");
	}
	close(fd);
}

void view_mode(char *filename)
{
	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("文件打开失败\n");
		return;
	}
	pargv[2] = (char *)malloc(50);
	// pargv的第三参数是文件名
	strcpy(pargv[2], filename);
	printf("文件权限为");
	int returnnum = execv("/bin/ls", pargv); //执行文件函数
	if (returnnum == -1)
	{
		printf("查看失败\n");
	}
	else
	{
		printf("文件权限为：\n");
	}
}

void shell()
{
	// system("chcp 65001");
	system("clear");
	do
	{
		cout << "Welcome to Zerin's Filetool\n";
		cout << "Usage:\n";
		cout << "touch a.cpp\n";
		cout << "cat a.cpp\n";
		cout << "echo \"hello\" >> a.cpp\n";
		cout << "chmod 777 a.cpp\n";
		cout << "ll a.cpp\n\n";
		string to = "touch", ca = "cat", ch = "chmod", ec = "echo", ll = "ll";
		string cmd;
		char *name = new char[20];
		getline(cin, cmd);
		istringstream str(cmd);
		// touch命令
		// find查找失败返回的值比max大
		if (cmd.find(to) < MAX)
		{
			str >> cmd;
			str >> cmd; //覆盖前一次>>中的touch,得到name
			strcpy(name, cmd.c_str());
			create_open_file(name);
		}
		// cat命令
		else if (cmd.find(ca) < MAX)
		{
			str >> name; //此处也可>>cmd
			// str >> cmd;//覆盖前一次>> 得到name
			// strcpy(name, cmd.c_str());
			str >> name; //更好的方法 不需复制
			read_file(name);
		} // echo
		else if (cmd.find(ec) < MAX)
		{
			string buffer_raw;
			char *buffer = new char[1 << 10];
			str >> buffer_raw;
			str >> buffer_raw; //覆盖前一次>> 得到buffer
			str >> name;
			str >> name; //覆盖前一次>> 得到name
			//去除""
			buffer_raw = buffer_raw.substr(1, buffer_raw.length() - 2);
			strcpy(buffer, buffer_raw.c_str());
			write_file(buffer, name);
		} // chmod
		else if (cmd.find(ch) < MAX)
		{
			int mode;
			str >> cmd;
			str >> mode;
			str >> name;
			mode_file(mode, name);
		} // ll
		else if (cmd.find(ll) < MAX)
		{
			str >> cmd;
			str >> name;
			view_mode(name);
		}
		else
		{
			cout << cmd << ": command not found\n";
		}
		cin.get();
		system("clear");
	} while (1);
}

int main()
{
	shell();
	return 0;
}
