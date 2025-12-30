#include<stdio.h>
#include"Student.h"
#define LINE(string) printf("\n=========================%s=======================\n",string);

void StudentTable();

int main()
{
	StudentTable();
	return 0;
}

void StudentTable()
{
	LINE("创建")
		Node* head = CreatNode();
	LoadData(head);

	//LINE("写入")
	//	AddStudents(head);

	//LINE("找到")
	//	PrintStudent(FindPrevStudent(head,1));

	//LINE("排序")
	//	SortInOption(head);

	LINE("全部")
		PrintAll(head);

	LINE("删除目标")
		DeleteByName(head);

	//LINE("测试")
	//	printf("%d",strcmp("11231", "22321"));

	LINE("全部")
		PrintAll(head);

	//LINE("删除")
	//DeleteAll(head);

	LINE("结束")
		SaveData(head);
}
