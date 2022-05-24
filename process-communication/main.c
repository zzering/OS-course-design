#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

// const int SVKEY = 75;
#define SVKEY 75 //定义关键字SVKEY
#define REQ 1
const int SIZE = 1 << 8;

struct msgform
{
    long long mtype;
    char mtext[250];
} msg;

// for creating process
int i;
// for 通过共享缓存区通信
int shmid;
char *addr;

void pipeComm()
{
    pid_t pid;
    int fd[2]; // fd[0] 用于读取管道，fd[1] 用于写入管道
    char buf[SIZE];
    char msg[SIZE];
    memset(buf, 0, SIZE);
    memset(msg, 0, SIZE);
    if (pipe(fd) < 0)
    {
        perror("pipe");
        exit(1);
    }
    pid = fork();
    if (pid == 0) //子
    {
        close(fd[0]); // write only
        sprintf(msg, "%d is sending a message to parent %d by PIPE\n", getpid(), getppid());
        write(fd[1], msg, strlen(msg));
        exit(0);
    }
    else if (pid > 0)
    {
        close(fd[1]); // read only
        read(fd[0], buf, SIZE);
        printf("%s", buf);
    }
    else
    {
        perror("fork");
        exit(1);
    }
}

void qServer()
{
    int c_pid, s_pid, msgqid; // client的pid 和 消息队列识别码
    struct msgform msg;
    msgqid = msgget(SVKEY, 0777 | IPC_CREAT); //创建 75#消息队列
    while (1)
    {
        msgrcv(msgqid, &msg, 250, 1, 0); //接收client进程标识数消息
        c_pid = *(int *)msg.mtext;       //获得 cilent 进程标识数
        if (msg.mtype == REQ)
        {
            printf("(server):serving for client pid=%d\n", c_pid);
            break;
        }
    }
    msg.mtype = c_pid; //消息类型为 client 进程标识数
    s_pid = getpid();
    *(int *)msg.mtext = s_pid;            //获取 server 进程标识数
    msgsnd(msgqid, &msg, sizeof(int), 0); //发送消息
    exit(0);
}

void qClient()
{
    int pid, msgqid; // client的pid 和 消息队列识别码
    struct msgform msg;
    msgqid = msgget(SVKEY, 0777); //打开 75#消息队列

    pid = getpid();                       //获取client进程标识符
    *(int *)msg.mtext = pid;              // pint指针指向client进程标识符
    msg.mtype = REQ;                      //消息类型为 1
    msgsnd(msgqid, &msg, sizeof(int), 0); //发送消息msg入msgqid消息队列
    while (1)
    {
        msgrcv(msgqid, &msg, 250, pid, 0); //从队列msgqid接收消息msg
        if (msg.mtype != REQ)
        {
            printf("(client):receive reply from pid=%d\n", *(int *)msg.mtext); //显示 server进程标识数
            exit(0);
        }
    }
}

void msgQueueComm()
{
    i = fork(); //创建进程 1
    if (!i)     //子进程中 fork返回0
        qServer();
    i = fork(); //创建进程 2
    if (!i)
        qClient();
}

void sServer()
{
    shmid = shmget(SVKEY, 1024, 0777 | IPC_CREAT); /*创建共享存储区*/
    addr = shmat(shmid, 0, 0);                     /*获取首地址*/
    do
    {
        *addr = -1;
        while (*addr == -1)
            ; //阻塞，用于进程同步
        printf("(server) received\n");
    } while (*addr);
    shmctl(shmid, IPC_RMID, 0); /*撤消共享存储区，归还资源*/
    exit(0);
}

void sClient()
{
    int i;
    shmid = shmget(SVKEY, 1024, 0777); /*打开共享存储区*/
    addr = shmat(shmid, 0, 0);         /*获得共享存储区首地址*/
    for (i = 9; i >= 0; i--)
    {
        while (*addr != -1)
            ; //阻塞，用于进程同步
        printf("(client) sent\n");
        *addr = i;
    }
    exit(0);
}

void sharedMemComm()
{
    while ((i = fork()) == -1)
        ;
    if (!i)
        sServer();
    system("ipcs  -m");
    while ((i = fork()) == -1)
        ;
    if (!i)
        sClient();
    // wait(0);
    // wait(0);
}

int main()
{
    int choice;
    while (1)
    {
        system("clear");
        printf("        进程通信程序        ");
        printf("\n选择操作\n");
        printf("1.管道通信\n");
        printf("2.消息队列\n");
        printf("3.共享储存区\n");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            pipeComm();
            getchar();
            getchar();
            break;
        case 2:
            msgQueueComm();
            getchar();
            getchar();
            break;
        case 3:
            sharedMemComm();
            getchar();
            getchar();
            break;
        default:
            printf("INPUT ERROR!\n");
            break;
        }
    }
    return 0;
}