//���� - ���� ũ�� �ڵ� Ȯ��, ���� ������ �ڷ� ����
 
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef void * Element; //void * ������ Element ���� ������ ����

typedef struct Stack //Stack ����ü ����
{
    Element *buf;//�����
    int ssize;//����� ũ��
    int top; //���� �ֱٿ� ������ �ε���
}Stack;

Stack *NewStack();//���� ������
void DeleteStack(Stack *stack);//���� �Ҹ���
int IsFull(Stack *stack); //������ �� á���� Ȯ��
int IsEmpty(Stack *stack); //������ ������� Ȯ��
void Push(Stack *stack, Element data); //���ÿ� ����
Element Pop(Stack *stack); //���ÿ��� ����


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
    Data *data = 0;
    Stack *stack = NewStack(); //���� ����

    Push(stack, NewData(3, "ȫ�浿"));//data ���� �� ���ÿ� ����
    Push(stack, NewData(5, "������")); //data ���� �� ���ÿ� ����
    Push(stack, NewData(2, "��������")); //data ���� �� ���ÿ� ����
    Push(stack, NewData(4, "�̼���")); //data ���� �� ���ÿ� ����

    printf("%-5s %-10s\n", "��ȣ", "�̸�");
    while (!IsEmpty(stack))//������ ������� �ʴٸ� �ݺ�
    {
        data = (Data *)Pop(stack);//���ÿ��� ����
        ViewData(data);//data ���
        DeleteData(data);//data �Ҹ�
    }
    DeleteStack(stack);//���� �Ҹ�
    return 0;
}

void InitStack(Stack *stack, int ssize);//���� �ʱ�ȭ
Stack *NewStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));//���� ���� �޸� �Ҵ�
    InitStack(stack, 1);//���� �ʱ�ȭ
    return stack;
}

void InitStack(Stack *stack, int ssize)
{
    stack->buf = (Element *)malloc(sizeof(Element)*ssize);
    stack->ssize = ssize;
    stack->top = -1; //���� �ʱ�ȭ������ top�� -1�� ����
}

void DisposeStack(Stack *stack);//���� ����ȭ
void DeleteStack(Stack *stack)
{
    DisposeStack(stack);//���� ����ȭ
    free(stack); //���� �޸� ����
}
void DisposeStack(Stack *stack)
{
    free(stack->buf);
}

int IsFull(Stack *stack)
{
    return (stack->top + 1) == stack->ssize;//top+1 �� ���� ũ��� ������ �� �� ����
}
int IsEmpty(Stack *stack)
{
    return stack->top == -1;    //top�� -1�̸� �� ����    
}
void Expand(Stack *stack);//���� ���� Ȯ��
void Push(Stack *stack, Element data)
{
    if (IsFull(stack))
    {
        Expand(stack);
    }
    stack->top++; //top�� 1 ����
    stack->buf[stack->top] = data;   //������ ����
}
void Expand(Stack *stack)
{
    stack->ssize *= 2;//���� ũ�⸦ 2�� ����
    stack->buf = (Element *)realloc(stack->buf, sizeof(Element)*stack->ssize);//���� 2��� Ȯ��
}
Element Pop(Stack *stack)
{
    Element re = 0;
    if (IsEmpty(stack))
    {
        printf("������ �����\n");
        return re;
    }
    re = stack->buf[stack->top];//top �ε����� ������ ���� re�� ����
    stack->top--;//top�� 1 ����
    return re;
}