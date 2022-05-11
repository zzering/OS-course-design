#include"stdio.h"
#include"stdlib.h"
#define maxsize 1000 //�������������
#pragma warning(disable:4996)
//�Ƚ��ȳ������㷨
void FIFO(int array[], int m)
{
    int sum = 0, j, i, now;
    float avg;
    printf("\n �����뵱ǰ�Ĵŵ��ţ� ");
    scanf("%d", &now);
    printf("\n FIFO ���Ƚ��: ");
    printf("%d ", now);
    for (i = 0; i < m; i++) printf("%d ", array[i]);
    sum = abs(now - array[0]);
    for (j = 1; j < m; j++) sum += abs(array[j] - array[j - 1]); //�ۼ��ܵ��ƶ�����
    avg = (float)sum / m;//����ƽ��Ѱ������
    printf("\n �ƶ����ܵ����� %d \n", sum);
    printf(" ƽ��Ѱ�����ȣ� %f \n", avg);
}
//��̷���ʱ�����ȵ����㷨
void SSTF(int array[], int m)
{
    int temp;
    int k = 1;
    int now, l, r;
    int i, j, sum = 0;
    float avg;
    for (i = 0; i < m; i++)
    {
        for (j = i + 1; j < m; j++) //�Դŵ��Ž��д�С��������
        {
            if (array[i] > array[j])//���ŵ���֮��Ƚ�
            {
                temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
    for (i = 0; i < m; i++) //��������Ĵŵ�������
        printf("%d ", array[i]);
    printf("\n �����뵱ǰ�Ĵŵ��ţ� ");
    scanf("%d", &now);
    printf("\n SSTF ���Ƚ��: ");
    if (array[m - 1] <= now)//�ж���������������Ƿ�С�ڵ�ǰ�ŵ���
    {
        for (i = m - 1; i >= 0; i--) //������ŵ��ŴӴ�С���
            printf("%d ", array[i]);
        sum = now - array[0];//�����ƶ�����
    }
    else if (array[0] >= now)//�ж���������������Ƿ񶼴��ڵ�ǰ�ŵ���
    {
        for (i = 0; i < m; i++) //���ŵ��Ŵ�С�������
            printf("%d ", array[i]);
        sum = array[m - 1] - now;//�����ƶ�����
    }
    else
    {
        while (array[k] < now)//��һ�Ƚ���ȷ�� K ֵ
        {
            k++;
        }
        l = k - 1;
        r = k;
        //ȷ����ǰ�ŵ������ŵ������е�λ��
        while ((l >= 0) && (r < m))
        {
            if ((now - array[l]) <= (array[r] - now))//�ж���̾���
            {
                printf("%d ", array[l]);
                sum += now - array[l];//�����ƶ�����
                now = array[l];
                l = l - 1;
            }
            else
            {
                printf("%d ", array[r]);
                sum += array[r] - now;//�����ƶ�����
                now = array[r];
                r = r + 1;
            }
        }
        if (l = -1)
        {
            for (j = r; j < m; j++)
            {
                printf("%d ", array[j]);
            }
            sum += array[m - 1] - array[0];//�����ƶ�����
        }
        else
        {
            for (j = l; j >= 0; j--)
            {
                printf("%d ", array[j]);
            }
            sum += array[m - 1] - array[0];//�����ƶ�����
        }
    }
    avg = (float)sum / m;
    printf("\n �ƶ����ܵ����� %d \n", sum);
    printf(" ƽ��Ѱ�����ȣ� %f \n", avg);
}
///ɨ���㷨
void SCAN(int array[], int m)
{
    int sum = 0;
    for (int i = 0; i < m; i++)
    {
        for (int j = i + 1; j < m; j++) //�Դŵ��Ž��д�С��������
        {
            if (array[i] > array[j])//���ŵ���֮��Ƚ�
            {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
    for (int i = 0; i < m; i++)
    {
        printf("%d ", array[i]);
    }
    printf("\n �����뵱ǰ�Ĵŵ��ţ� ");
    int now;
    scanf("%d", &now);
    printf("\n SCAN ���Ƚ����");
    int pos;
    for (int i = 0; i < m; i++)
    {
        if (array[i] >= now)
        {
            pos = i;
            sum += abs(array[i] - now);
            break;
        }
    }
    for (int i = pos; i < m; i++)
    {
        if (i != pos)
            sum += abs(array[i] - array[i - 1]);
        printf("%d ", array[i]);
    }
    if (pos >= 1)
        sum += abs(array[m - 1] - array[pos - 1]);
    for (int i = pos - 1; i >= 0; i--)
    {
        if (i)
            sum += abs(array[i] - array[i - 1]);
        printf("%d ", array[i]);
    }
    printf("\n �ƶ����ܵ�����%d\n ƽ��Ѱ�����ȣ�%f\n", sum, 1.0 * sum / m);
}

void menu()
{
    int c;
    int count;
    int cidao[maxsize];//����ŵ�������
    int i = 0;
    int b;
    printf("���̵����㷨ģ��\n");
    printf("�����������������:\n");
    scanf("%d", &b);
    printf("��������������Ĵŵ�����:\n");
    for (i = 0; i < b; i++)
    {
        scanf("%d", &cidao[i]);
    }
    printf("�ŵ���ȡ���:\n");
    for (i = 0; i < b; i++)
    {
        printf("%d ", cidao[i]);//�����ȡ�Ĵŵ��Ĵŵ���
    }
    count = b;
    printf("\n ");
    while (1)
    {
        printf("�㷨ѡ�� \n");
        printf(" 1���Ƚ��ȳ��㷨�� FIFO�� \n");
        printf(" 2����̷���ʱ�������㷨�� SSTF�� \n");
        printf(" 3��ɨ���㷨�� SCAN�� \n");
        printf(" 4���˳� \n");
        printf("��������ţ� ");
        scanf("%d", &c);
        if (c > 5)
            break;
        switch (c)//�㷨ѡ��
        {
        case 1:
            FIFO(cidao, count);//�Ƚ��ȳ��㷨
            printf("\n");
            break;
        case 2:
            SSTF(cidao, count);//��̷���ʱ�������㷨
            printf("\n");
            break;
        case 3:
            SCAN(cidao, count);//ɨ���㷨
            printf("\n");
            break;
        case 4:
            exit(0);
        }
    }
}

int main()
{
    menu();
    return 0;
}

