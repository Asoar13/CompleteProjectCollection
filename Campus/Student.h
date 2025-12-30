#ifndef STUDENT
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define STUDENT
#define LENGTH 10

typedef struct 
{
	int num;
	int age;
	char name[LENGTH];
}Student;
typedef struct node
{
	node* next;
	Student stu;
}Node;
typedef struct Nd_node
{
	Node* node;
	Nd_node* next;
}Nd_node;

///链表数据操作
// 回调函数的函数指针
bool UpperNum(int a, int b);
bool LowerNum(int a, int b);
int StudentAge(Node* node);
int StudentNum(Node* node);
//函数指针数组
typedef bool (*CompareFunc)(int, int);
typedef int (*StuDataFunc) (Node*);
extern StuDataFunc FunctionArr[];
extern const int DataFuncCount;

//基本函数
void AddStudent(Node* head);
Node* FindPrevStudent(Node* head, size_t option, size_t method);
void GetOption(int *option, int * sort_method);
void PrintStudent(Node* node);
void DeleteNextStudent(Node* node);

//辅助函数
int CheckContinue();
void ClearInputBuffer();
void PrintError(const char* promot);

//复合函数
Node* CreatNode();
void AddStudents(Node* head);
void PrintAll(Node* head);
void SortInOption(Node* head);
void DeleteAll(Node* head);
void DeleteByName(Node* head);
void DeleteByNum(Node* head , int tatget_num);

///链表文件操作
void SaveData(Node* head);
void LoadData(Node* head);
#endif 