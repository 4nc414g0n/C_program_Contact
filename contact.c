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
//��ʼ��
void InitContact(Contact* pc)
{
	pc->data = (PeoInfo*)malloc(sizeof(PeoInfo)*DEFAULT_SZ);
	pc->sz = 0;
	pc->capicity = DEFAULT_SZ;
}
//�洢����
void SaveContact(Contact* pc)
{
	FILE *pf = fopen("contact.dat", "w");
	if (pf != NULL)
	{
		for (size_t i = 0; i < pc->sz; i++)
		{
			fwrite(pc->data + i, sizeof(PeoInfo), 1, pf);
		}
		printf("����ɹ�");
	}
	else
	{
		perror("SaveContact");
		return;
	}
	fclose(pf);
	pf = NULL;
}

//��ȡ����
void ReadContact(Contact* pc)
{
	FILE *pf = fopen("contact.dat", "r");
	PeoInfo a = { 0 };
	if (pf != NULL)
	{
		while (fread(&a, sizeof(PeoInfo), 1, pf))//����fread����ֵ�Ǳ���������ȡ�������ݸ���������ֵ<Ҫ��ȡ�����ݸ����ͱ�ʾ������Ҳ����0<1��
		{	//�ж��Ƿ�����
			if (pc->sz == pc->capicity)
			{
				PeoInfo* ptr = (PeoInfo*)realloc(pc->data, sizeof(PeoInfo)*(pc->capicity + INC_SZ));
				if (ptr != NULL)
				{
					pc->data = ptr;
					pc->capicity += INC_SZ;
					printf("���ݳɹ�");
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
		printf("��ȡ�ɹ�");
	}
	else
	{
		perror("ReadContact");
		return;
	}
	fclose(pf);
	pf = NULL;
}

//����ͨѶ¼
void DestoryContact(Contact* pc)
{
	free(pc->data);
	pc->data = NULL;
	pc->sz = 0;
	pc->capicity = 0;
}

//������ϵ��
void AddContact(Contact* pc)
{
	if (pc->sz == pc->capicity)
	{
		PeoInfo* ptr = (PeoInfo*)realloc(pc->data, sizeof(PeoInfo)*(pc->capicity + INC_SZ));
		if (ptr != NULL)
		{
			pc->data = ptr;
			pc->capicity += INC_SZ;
			printf("���ݳɹ�");
		}
		else
		{
			perror("AddContact");
			return;
		}

	}
	printf("��������:>");
	scanf("%s", pc->data[pc->sz].name);//�ַ����������൱���൱�ڵ�ַ
	printf("\n");
	printf("�����Ա�:>");
	scanf("%s", pc->data[pc->sz].sex);
	printf("\n");
	printf("��������:>");
	scanf("%d", &pc->data[pc->sz].age);//������Ҫ����&
	printf("\n");
	printf("����绰:>");
	scanf("%s", pc->data[pc->sz].tele);
	printf("\n");
	printf("�����ַ:>");
	scanf("%s", pc->data[pc->sz].addr);
	printf("\n");
	pc->sz++;
}

//��ӡ��ϵ����Ϣ
void PrintContact(const Contact* pc)
{
	for (int i = 0; i < pc->sz; i++)
	{
		printf("%5s %5s %5s %5s %5s\n", "name", "age", "sex", "tele", "addr");
		printf("%5s %5d %5s %5s %5s\n", pc->data[i].name, pc->data[i].age, pc->data[i].sex, pc->data[i].tele, pc->data[i].addr);
	}
}

//ɾ����ϵ�˵���Ϣ
void DelContact(Contact* pc)
{
	char del_name[MAX_NAME];
	printf("����������:>");
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
			printf("ɾ���ɹ�");
			return;
		}

	}
	printf("�޴���");
}

//����ָ����ϵ��
void SearchContact(Contact* pc)
{
	char del_name[MAX_NAME];
	printf("����������:>");
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
	printf("���޴���");
}

//�޸�ָ����ϵ��
void ModifyContact(Contact* pc)
{
	char del_name[MAX_NAME];
	printf("����������:>");
	scanf("%s", del_name);
	for (int i = 0; i < pc->sz; i++)
	{
		if (strcmp(pc->data[i].name, del_name) == 0)
		{
			printf("��������:>");
			scanf("%s", pc->data[i].name);//�ַ����������൱���൱�ڵ�ַ
			printf("\n");
			printf("�����Ա�:>");
			scanf("%s", pc->data[i].sex);
			printf("\n");
			printf("��������:>");
			scanf("%d", &pc->data[i].age);//������Ҫ����&
			printf("\n");
			printf("����绰:>");
			scanf("%s", pc->data[i].tele);
			printf("\n");
			printf("�����ַ:>");
			scanf("%s", pc->data[i].addr);
			printf("\n");
			return;
		}

	}
	printf("�޴���");
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
		printf("��ѡ��>");
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
			printf("����������������룺>");
		}

	} while (input);
	return 0;
}