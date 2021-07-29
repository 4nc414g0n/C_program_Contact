#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NAME 20
#define MAX_SEX 10
#define MAX_TELE 12
#define MAX_ADDR 30
#define MAX 1000
#define DEFAULT_SZ 3
#define INC_SZ 2
typedef struct PeoInfo
{
	char name[MAX_NAME];
	char sex[MAX_SEX];
	int age;
	char tele[MAX_TELE];
	char addr[MAX_ADDR];
}PeoInfo;
typedef struct Contact
{
	PeoInfo *data;
	int sz;
	int capicity;
}Contact;
//��ʼ��ͨѶ¼
void InitContact(Contact* pc);

//������ϵ��
void AddContact(Contact* pc);

//��ӡ��ϵ����Ϣ
void PrintContact(const Contact* pc);

//ɾ����ϵ�˵���Ϣ
void DelContact(Contact* pc);

//����ָ����ϵ��
void SearchContact(Contact* pc);

//�޸�ָ����ϵ��
void ModifyContact(Contact* pc);

//����ͨѶ¼
void SortContact(Contact* pc);

//����ͨѶ¼
void DestoryContact(Contact* pc);

//�洢����
void SaveContact(Contact* pc);

//��ȡ����
void ReadContact(Contact* pc);