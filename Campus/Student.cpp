#include "Student.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PRINT(str) printf("%s\n",str);
//========================================链表数据操作===========================================

//==============================被回调函数=====================================
int StudentAge(Node* node) { return node->stu.age; }
int StudentNum(Node* node) { return node->stu.num; }
StuDataFunc FunctionArr[] = { StudentAge, StudentNum };

//================================复合函数=====================================
Node* CreatNode()
{
	Node* head = (Node*)calloc(sizeof(Node), 1);
	if (!head)
	{
		printf("内存分配失败！\n");
		return NULL;
	}
	return head;
}

void AddStudents(Node* head)
{
	int i = 1;
	do
	{
		printf("第%d个数据录入：\n",i);
		AddStudent(head);
		i++;
	} while (CheckContinue());
}

void PrintAll(Node* head)
{
	for (Node* node = head->next; node; node = node->next)
		PrintStudent(node);
}

void SortInOption(Node* head)
{
	//获取选择
	int option = 1;
	//拼接法排序
	Node* temp_head = CreatNode(), *node = temp_head;	//head的副本
	for (Node* cur = head; cur->next; cur = cur->next)	//最后一次是cur -> node -> NULL	
	{													
		node->next = FindStudent(cur,option);	
		node = node->next;
	}
	printf("完成排序\n");
}

void DeleteAll(Node* head)
{
	//while (head->next)
	//	DeleteNextStudent(head);
	for (int i = 1; head->next; i++)
	{
		DeleteNextStudent(head);
		printf("删除了第%d个数据\n",i);
	}
	printf("成功删除所有数据!\n");
}


int CheckContinue()
{
	printf("输入【q】退出，【其他键】继续 =>");
	char respone;
	while ('\n' != getchar());
	scanf("%c",&respone);
	if (respone == 'q')	return 0;
	return 1;
}

//=================================基本函数====================================
void AddStudent(Node* head)
{
	//写入
	Node* node = (Node*)calloc(sizeof(Node), 1);
	if (!node)
	{
		printf("内存分配失败！");
		return;
	}
	 printf("学号：");
	 scanf("%d",&node->stu.num);
	 printf("姓名：");
	 scanf("%s", node->stu.name);
	 printf("年龄：");
	 scanf("%d",&node->stu.age);
	 Node* cur = (Node*)head;
	 while (cur->next)
	 {
		 cur = cur->next;
	 }
	 cur->next = node;
	 printf("写入完成！\n");
}

Node* FindStudent(Node* head, size_t option)	//找出head后面除了本身的最大值的node
{
	//获取选项对应的函数
	if (option < 1 || option > 2)
	{
		printf("没有此选项");
		return nullptr;
	}
	StuDataFunc GetStuData = FunctionArr[option-1];
	//找出列表最大值
	if (head == nullptr || head->next == nullptr) {
		// printf("链表为空，无法查找\n");
		return nullptr;
	}
	int max = GetStuData(head->next);	//初始化为第一个
	Node* target_node = head->next;		//初始化为第一个
	//遍历链表
	for (Node* cur = head->next; cur; cur->next)
	{
		int temp = GetStuData(cur);
		if (temp > max)
		{
			max = temp;
			target_node = cur;
		}
	}
	return target_node;
}

void PrintStudent(Node* node)
{
	printf("%s(%d岁) %d号\n", node->stu.name, node->stu.age, node->stu.num);
}

void DeleteNextStudent(Node* node)
{
	//尾节点
	if (!node->next)
	{
		printf("不存在此数据\n");
		return;
	}
	//首和中间的删除
	node->next = node->next->next;
}

//====================================链表文件操作===================================
void SaveData(Node* head)
{
	//进入文件
	FILE* fp01 = fopen("D:/My_Code/ForTest/StudentData.txt","wb");
	if (!fp01)
	{
		printf("文件打开失败!01\n");
		return;
	}
	//写入操作
	for (Node* cur = head->next; cur; cur = cur->next)
	{
		fwrite(&cur->stu, sizeof(Student), 1, fp01);
	}
	//写入记录标记
	Student stu_00 = { 0 };
	fwrite(&stu_00, sizeof(Student), 1, fp01);
	printf("数据保存完成\n");
	//退出文件
	fclose(fp01);
}

void LoadData(Node* head)
{
	//进入文件
	FILE* fp01 = fopen("D:/My_Code/ForTest/StudentData.txt", "rb");
	if (!fp01)
	{
		printf("暂时没有数据\n");
		return;
	}
	//更新链表  (首节点cur)
	printf("开始更新数据\n");
	int i = 0, read_respone = 1;
	for(Node* cur = (Node*)head; read_respone;cur = cur->next)
	{
		//读入到node
		Node* node = (Node*)calloc(sizeof(Node), 1);
		if (!node)
		{
			printf("内存分配失败！");
			return;
		}
		fread(&node->stu, sizeof(Student), 1, fp01);
		//连接有效节点node到list尾部
		if (node->stu.age && node->stu.name && node->stu.num)
		{
			cur->next = node;
			i++;
		}
		else
			break;
		//展示
		printf("%s(%d岁) %d号\n", node->stu.name, node->stu.age, node->stu.num);
	}
	printf("成功更新了%d个数据\n", i);
	//退出文件
	fclose(fp01);
}
