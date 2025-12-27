#ifndef STUDENT
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

//链表数据操作
//基本函数
int CheckContinue();
void AddStudent(Node* head);
Node* FindPrevStudent(Node* head, size_t option);
void PrintStudent(Node* node);
void DeleteNextStudent(Node* node);
//复合函数
Node* CreatNode();
void AddStudents(Node* head);
void PrintAll(Node* head);
void SortInOption(Node* head);
void DeleteAll(Node* head);
void;

//链表文件操作
void SaveData(Node* head);
void LoadData(Node* head);
#endif 