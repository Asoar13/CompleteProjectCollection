#ifndef STUDENT
#define STUDENT
#define LENGTH 20

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

///链表数据操作
// 回调函数的函数指针
int StudentAge(Node* node);
int StudentNum(Node* node);
//函数指针数组
typedef int (*StuDataFunc) (Node*);
extern StuDataFunc FunctionArr[];
extern const int DataFuncCount;

//基本函数
int CheckContinue();
void PrintError(const char* promot);
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
void ;

///链表文件操作
void SaveData(Node* head);
void LoadData(Node* head);
#endif 