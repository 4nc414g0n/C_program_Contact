#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include "contact.h"
enum MyEnum
{
	EXIT,//0
	ADD,//1
	DELETE,//2
	SEARCH,//3
	MODIFY,//4
	PRINT,//5
	SORT//6
};
void menu()
{
	printf("\n");
	printf("******************************************\n");
	printf("*********1:ADD         2:DELETE***********\n");
	printf("*********3:SEARCH      4:MODIFY***********\n");
	printf("*********5:PRINT       6:SORT  ***********\n");
	printf("*********0:EXIT                ***********\n");
	printf("******************************************\n");
}
int sort_by_name(const void*e1, const void*e2)
{
	return strcmp(((PeoInfo*)e1)->name, ((PeoInfo*)e2)->name);
}
//初始化
void InitContact(Contact* pc)
{
	pc->data = (PeoInfo*)malloc(sizeof(PeoInfo)*DEFAULT_SZ);
	pc->sz = 0;
	pc->capicity = DEFAULT_SZ;
}
//存储数据
void SaveContact(Contact* pc)
{
	FILE *pf = fopen("contact.dat", "w");
	if (pf != NULL)
	{
		for (size_t i = 0; i < pc->sz; i++)
		{
			fwrite(pc->data + i, sizeof(PeoInfo), 1, pf);
		}
		printf("保存成功");
	}
	else
	{
		perror("SaveContact");
		return;
	}
	fclose(pf);
	pf = NULL;
}

//读取数据
void ReadContact(Contact* pc)
{
	FILE *pf = fopen("contact.dat", "r");
	PeoInfo a = { 0 };
	if (pf != NULL)
	{
		while (fread(&a, sizeof(PeoInfo), 1, pf))//利用fread返回值是本次完整读取到的数据个数（返回值<要读取的数据个数就表示读完了也就是0<1）
		{	//判断是否增容
			if (pc->sz == pc->capicity)
			{
				PeoInfo* ptr = (PeoInfo*)realloc(pc->data, sizeof(PeoInfo)*(pc->capicity + INC_SZ));
				if (ptr != NULL)
				{
					pc->data = ptr;
					pc->capicity += INC_SZ;
					printf("增容成功");
				}
				else
				{
					perror("AddContact");
					return;
				}
			}
			pc->data[pc->sz] = a;
			pc->sz++;
		}
		printf("读取成功");
	}
	else
	{
		perror("ReadContact");
		return;
	}
	fclose(pf);
	pf = NULL;
}

//销毁通讯录
void DestoryContact(Contact* pc)
{
	free(pc->data);
	pc->data = NULL;
	pc->sz = 0;
	pc->capicity = 0;
}

//增加联系人
void AddContact(Contact* pc)
{
	if (pc->sz == pc->capicity)
	{
		PeoInfo* ptr = (PeoInfo*)realloc(pc->data, sizeof(PeoInfo)*(pc->capicity + INC_SZ));
		if (ptr != NULL)
		{
			pc->data = ptr;
			pc->capicity += INC_SZ;
			printf("增容成功");
		}
		else
		{
			perror("AddContact");
			return;
		}

	}
	printf("输入名字:>");
	scanf("%s", pc->data[pc->sz].name);//字符串数组名相当于相当于地址
	printf("\n");
	printf("输入性别:>");
	scanf("%s", pc->data[pc->sz].sex);
	printf("\n");
	printf("输入年龄:>");
	scanf("%d", &pc->data[pc->sz].age);//整形需要加上&
	printf("\n");
	printf("输入电话:>");
	scanf("%s", pc->data[pc->sz].tele);
	printf("\n");
	printf("输入地址:>");
	scanf("%s", pc->data[pc->sz].addr);
	printf("\n");
	pc->sz++;
}

//打印联系人信息
void PrintContact(const Contact* pc)
{
	for (int i = 0; i < pc->sz; i++)
	{
		printf("%5s %5s %5s %5s %5s\n", "name", "age", "sex", "tele", "addr");
		printf("%5s %5d %5s %5s %5s\n", pc->data[i].name, pc->data[i].age, pc->data[i].sex, pc->data[i].tele, pc->data[i].addr);
	}
}

//删除联系人的信息
void DelContact(Contact* pc)
{
	char del_name[MAX_NAME];
	printf("请输入名字:>");
	scanf("%s", del_name);
	for (int i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->data[i].name, del_name) == 0)
		{
			for (int j = i; j < pc->sz - 1; j++)
			{
				pc->data[j] = pc->data[j + 1];

			}
			pc->sz--;
			printf("删除成功");
			return;
		}

	}
	printf("无此人");
}

//查找指定联系人
void SearchContact(Contact* pc)
{
	char del_name[MAX_NAME];
	printf("请输入名字:>");
	scanf("%s", del_name);
	for (int i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->data[i].name, del_name) == 0)
		{
			printf("%5s %5s %5s %5s %5s\n", "name", "age", "sex", "tele", "addr");
			printf("%5s %5d %5s %5s %5s\n", pc->data[i].name, pc->data[i].age, pc->data[i].sex, pc->data[i].tele, pc->data[i].addr);
			return;
		}

	}
	printf("查无此人");
}

//修改指定联系人
void ModifyContact(Contact* pc)
{
	char del_name[MAX_NAME];
	printf("请输入名字:>");
	scanf("%s", del_name);
	for (int i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->data[i].name, del_name) == 0)
		{
			printf("输入名字:>");
			scanf("%s", pc->data[i].name);//字符串数组名相当于相当于地址
			printf("\n");
			printf("输入性别:>");
			scanf("%s", pc->data[i].sex);
			printf("\n");
			printf("输入年龄:>");
			scanf("%d", &pc->data[i].age);//整形需要加上&
			printf("\n");
			printf("输入电话:>");
			scanf("%s", pc->data[i].tele);
			printf("\n");
			printf("输入地址:>");
			scanf("%s", pc->data[i].addr);
			printf("\n");
			return;
		}

	}
	printf("无此人");
}
void SortContact(Contact* pc)
{
	qsort(pc->data, pc->sz, sizeof(PeoInfo), sort_by_name);
}

int main()
{
	int input = 0;

	Contact pc;
	InitContact(&pc);
	ReadContact(&pc);
	do
	{
		menu();
		printf("请选择：>");
		scanf("%d", &input);
		switch (input)
		{
		case ADD:
			AddContact(&pc);
			break;
		case DELETE:
			DelContact(&pc);
			break;
		case SEARCH:
			SearchContact(&pc);
			break;
		case MODIFY:
			ModifyContact(&pc);
			break;
		case PRINT:
			PrintContact(&pc);
			break;
		case SORT:
			SortContact(&pc);
			break;
		case EXIT:
			SaveContact(&pc);
			break;
		default:
			printf("输入错误请重新输入：>");
		}

	} while (input);
	return 0;
}