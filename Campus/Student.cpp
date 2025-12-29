#include "Student.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define PRINT(str) printf("%s\n",str);
//========================================链表数据操作===========================================

//==============================被回调函数=====================================
int StudentAge(Node* node) { return node->stu.age; }
int StudentNum(Node* node) { return node->stu.num; }
extern StuDataFunc FunctionArr[] = { StudentNum, StudentAge };
extern const int DataFuncCount = sizeof(FunctionArr) / sizeof(FunctionArr[0]);
extern const char* option_str[] = { "学号","年龄" };

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
	int sort_object = 1, sort_method = 1;
	GetOption(&sort_object, &sort_method);
	//拼接法排序
	Node* temp_head = CreatNode(), * node = temp_head, * tail = node;	//head的副本
	Node* cur = head, * prev_cur;
	while (cur->next)		//最后一次执行是cur -> node -> NULL
	{
		prev_cur = FindPrevStudent(cur, sort_object, sort_method);
		node = prev_cur->next;		//记录最大节点
		prev_cur->next = prev_cur->next->next;	//删除最大节点
		node->next = nullptr;		//彻底从cur剔除node
		tail->next = node;
		tail = tail->next;		 //前进tail
	}
	const char* method_str[] = { "降序","升序" };
	printf("已完成<%s的%s>排序\n",option_str[sort_object -1], method_str[sort_method]);
	head->next = temp_head->next;
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

//=================================辅助函数====================================

bool UpperNum(int a, int b) { return (a > b); }
bool LowerNum(int a, int b) { return (a < b); }

int CheckContinue()
{
	printf("输入【q】退出，【其他键+回车】继续 => ");
	char respone;
	respone = getchar();
	while ('\n' != getchar());
	printf("\n");
	if (respone == 'q')	return 0;
	return 1;
}

void ClearInputBuffer()
{
	int ch;
	while((ch = getchar()) != '\n' && ch != EOF);
}

void PrintError(const char* promot)
{
	printf("格式错误！ or %s不合理！\n重新输入%s：",promot, promot);
	//废除错除输入
	while (getchar() != '\n');	
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
	while (!scanf(" %d", &node->stu.num) || node->stu.num < 0)	PrintError("学号");
	ClearInputBuffer();		//处理'\n'
	printf("姓名：");			
	while (!scanf("%s", node->stu.name))	PrintError("姓名");
	printf("年龄：");
	while (!scanf(" %d", &node->stu.age) || node->stu.age<0 || node->stu.age>99)	PrintError("年龄");
	ClearInputBuffer();		//处理'\n'
	Node* cur = (Node*)head;
	while (cur->next)
	{
	 cur = cur->next;
	}
	cur->next = node;
	printf("写入完成！\n");
}

Node* FindPrevStudent(Node* head, size_t sort_object, size_t method)	//找出head后面除了本身的最大值的node返回的是prev
{
	//获取选项对应的函数
	StuDataFunc GetStuData = FunctionArr[sort_object - 1];
	CompareFunc Compare = method ? UpperNum : LowerNum;
	//初始化
	if (head == nullptr || head->next == nullptr) {
		// printf("链表为空，无法查找\n");
		return nullptr;
	}
	int max = GetStuData(head->next);	//初始化为第一个
	Node* target_node = head;		//初始化为第一个
	//遍历链表,找出要求值
	Node* prev_node = head;
	for (Node* cur = head->next; cur; cur = cur->next)
	{
		int temp = GetStuData(cur);
		if (Compare(temp, max))
		{
			max = temp;
			target_node = prev_node;
		}
		prev_node = cur;	//最后更新，确保target_node是prev
	}
	return target_node;
}

void GetOption(int* sort_object, int* sort_method)
{
		//获取排序对象选择
	do {
		printf("\n请选择排序“对象”\n【1】 -> 学号\n【2】 -> 年龄\n输入选项(默认：1) => ");
		if (!scanf("%d", sort_object))
		{
			printf("格式错误！\n");
			ClearInputBuffer();
			continue;
		}
		if (*sort_object < 1 || *sort_object > DataFuncCount)
		{
			printf("没有此选项！\n");
			ClearInputBuffer();
			continue;
		}
		break;
	} while (CheckContinue());
		//获取排序方式选择
	do{
		printf("\n请选择排序“方式”\n【0】 -> 降序\n【1】 -> 升序\n输入选项(默认：1) => ");
		if (!scanf("%d", sort_method))
		{
			printf("格式错误！\n");
			continue;
		}
		if (*sort_method < 0 || *sort_method > 1)
		{
			printf("没有此选项！\n");
			ClearInputBuffer();
			continue;
		}
		break;
	}while (CheckContinue());
}

void PrintStudent(Node* node)
{
	printf("%10s(%-02d岁) %-d号\n", node->stu.name, node->stu.age, node->stu.num);
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
	Student stu_00 = { -1,0,-1 };
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
	int i = 0;
	for(Node* cur = (Node*)head; !feof(fp01);cur = cur->next)
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
		if (node->stu.age != -1 && node->stu.name != 0 && node->stu.num != -1)
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
