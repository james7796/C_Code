//���� ť - ���� ���� �ڵ����� �Ҵ�, ���� ������ ����

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NEXT(index,QSIZE)   ((index+1)%QSIZE)  //���� ť���� �ε����� �����ϴ� ��ũ�� �Լ�

typedef void * Element; //void * ������ Element ���� ������ ����
typedef struct Queue //Queue ����ü ����
{
    Element *buf;//�����
    int qsize;
    int front; //���� �ε���(���� �������� ������ �����Ͱ� �ִ� �ε���)
    int rear;//������ �ε���
    int count;//���� ����

}Queue;

Queue *NewQueue();//������
void DeleteQueue(Queue *queue);//�Ҹ���
int IsEmpty(Queue *queue); //ť�� ������� Ȯ��
void Enqueue(Queue *queue, Element data); //ť�� ����
Element Dequeue(Queue *queue); //ť���� ����


typedef struct Data
{
    int num;
    char *name;
}Data;

Data *NewData(int num, const char *name)
{
    Data *data = (Data *)malloc(sizeof(Data));
    data->num = num;
    data->name = (char *)malloc(strlen(name) + 1);
    strcpy_s(data->name, strlen(name) + 1, name);
    return data;
}
void DeleteData(Data *data)
{
    free(data->name);
    free(data);
}
void ViewData(Data *data)
{
    printf("%-5d %-10s\n", data->num, data->name);
}


int main(void)
{
    Data *data;
    Queue *queue = NewQueue();//���� ����

    Enqueue(queue, NewData(3, "ȫ�浿"));//data ���� �� ť�� ����
    Enqueue(queue, NewData(5, "������")); //data ���� �� ť�� ����
    Enqueue(queue, NewData(2, "��������")); //data ���� �� ť�� ����
    Enqueue(queue, NewData(4, "�̼���")); //data ���� �� ť�� ����

    printf("%-5s %-10s\n", "��ȣ", "�̸�");
    while (!IsEmpty(queue))//ť�� ������� �ʴٸ� �ݺ�
    {
        data = (Data *)Dequeue(queue);//ť���� ����
        ViewData(data);//���� ������ ���
        DeleteData(data);//������ �Ҹ�       
    }
    printf("\n");

    DeleteQueue(queue);//�Ҹ�
    return 0;
}

void InitQueue(Queue *queue, int qsize);//ť �ʱ�ȭ
Queue *NewQueue()
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));//���� �޸� �Ҵ�
    InitQueue(queue, 1);//ť �ʱ�ȭ
    return queue;
}
void InitQueue(Queue *queue, int qsize)
{
    queue->buf = (Element *)malloc(sizeof(Element)*qsize);//���۸� ���� �޸� �Ҵ�
    queue->qsize = qsize;
    queue->front = queue->rear = 0; //front�� rear�� 0���� ����
    queue->count = 0;//���� ������ 0���� ����
}

void DisposeQueue(Queue *queue);//ť ����ȭ
void DeleteQueue(Queue *queue)
{
    DisposeQueue(queue);//���� �޸� ����
    free(queue);//ť �޸� ����
}
void DisposeQueue(Queue *queue)
{
    free(queue->buf);//���� �޸� ����
}

int IsFull(Queue *queue)
{
    return queue->count == queue->qsize;//���� ������ qsize�� ������ �� �� ����
}
int IsEmpty(Queue *queue)
{
    return queue->count == 0;    //���� ������ 0�̸� �� ����
}
void Expand(Queue *queue);//���� Ȯ��
void Enqueue(Queue *queue, Element data)
{
    if (IsFull(queue))//ť�� �� á�� ��
    {
        Expand(queue);//���� Ȯ��
    }
    queue->buf[queue->rear] = data;//rear �ε����� ������ ����
    queue->rear = NEXT(queue->rear, queue->qsize); //rear�� ���� ��ġ�� ����
    queue->count++;//���� ������ 1 ����
}
void Expand(Queue *queue)
{
    int i = 0;
    int count;
    Element *buf = (Element *)malloc(sizeof(Element)*queue->qsize);//�ӽ� ����� �޸� �Ҵ�
    count = queue->count;//���� ���� ���
    for (i = 0; i<count; i++)//ť�� �ִ� ������ buf�� ����(������ �������)
    {
        buf[i] = Dequeue(queue);
    }
    queue->qsize *= 2;//ť ũ�� 2��� Ȯ��
    queue->buf = (Element *)realloc(queue->buf, sizeof(Element)*queue->qsize);//���� Ȯ��
    for (i = 0; i<count; i++)//�ӽ� ����ҿ� ������ ������ �ٽ� ť�� ����
    {
        Enqueue(queue, buf[i]);
    }
    free(buf);//�ӽ� ����� �޸� ����

}
Element Dequeue(Queue *queue)
{
    Element re = 0;
    if (IsEmpty(queue))//ť�� ����� ��
    {
        printf("ť�� �����\n");
        return re;
    }
    re = queue->buf[queue->front];//front �ε����� ������ ���� re�� ����
    queue->front = NEXT(queue->front, queue->qsize);//front�� ���� ��ġ�� ����
    queue->count--;//���� ������ 1 ����
    return re;
}