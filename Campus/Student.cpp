#include "Student.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PRINT(str) printf("%s\n",str);
//==============================链表数据操作===================================
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
	int option = 1;
	//交换节点
	int i = 1;
	for(Node* cur = head->next, *prev = head; cur->next; i++)
	{
		//中间处理
		printf("开始第%d次\n", i);
		Node* temp = nullptr, * prev_ = FindPrevStudent(prev, option), * cur_ = prev_->next;
		//交换
		if (prev != prev_)
		{
		///交换prev的尾巴
		printf("完成第%d次prev交换\n", i);
		temp = prev->next;	prev->next = prev_->next;	prev_->next = temp;
		///交换cur的尾巴
		printf("完成第%d次cur交换\n", i);
		temp = cur->next;	cur->next = cur_->next;		cur_->next = temp;
		}
		//前进
		cur = prev->next->next;
		prev = prev->next;
		PRINT("下一个节点是")
		PrintStudent(cur);
		PRINT("\n当前链表")
			PrintAll(head);
		//if (cur->next) printf("下一个节点的尾是NULL\n");
		printf("完成第%d次\n", i);
	}
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
	printf("输入【q】退出，【其他键】继续\n");
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

Node* FindPrevStudent(Node* head, size_t option)
{
	size_t offset;
	//取得对应的偏移量
	switch (option)
	{
	case 1:		
		offset = offsetof(Student, num);
		break;
	case 2:
		offset = offsetof(Student, age);
		break;
	default:
		printf("操作有误！\n");
		return 0;
	}
	//找到最大数
	Node* move_node = head->next, * target_node = nullptr, *prev_node = head;
	for (int max = 1000; move_node; move_node = move_node->next)	//用for循环移动
	{
		int temp = *((int*) ((char*)&(move_node->stu) + offset) );	//原始化步长，加上偏移量再转回int型,并且解引用
		if( temp < max)
		{
			max = temp;
			printf("Max: %d\n",max);
			target_node = prev_node;
		}
		prev_node = move_node;
	}
	//返回前驱节点
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

//==============================链表文件操作===================================
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
