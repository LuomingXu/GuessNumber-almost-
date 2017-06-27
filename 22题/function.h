#pragma once
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include"printmeau.h"
#include"scan.h"

//����struct
typedef struct MyStruct
{
	char GamerName[20];
	int grade;
	int totalGrade;
}GuessNumber;

int MainGame();
int SelectNum();
void Rank(GuessNumber Game[]);
void PrintRankList(GuessNumber Game[]);
void InitializeStruct(GuessNumber Game[]);
void UpdateUserInfo(GuessNumber Game[], char GameName[], int grade);
void ReadRankList(GuessNumber Game[]);
void SaveRankList(GuessNumber Game[]);

//����Ϸ����
int MainGame()
{
	int Number = 0;//�û�������� 
	int count = 0;//��¼�û����˼��ε��� 

	int TheNumber = 0;//ϵͳ�����һ���� 
	srand((unsigned)time(NULL));//����ʱ�����ӣ����ܶ�����forѭ��֮�У�����ˣ���Ϊα���
	TheNumber = rand() % 101;
	TheNumber = 10;//�����ò�������
	printf("********************��Ϸ��ʼ********************\n");
	printf("���������µ���\n");

	while (Number <1 || Number >100)//ȷ���û��������1-100���� 
	{
		PrintError(2);
		Number = ScanfNums();
	}

	count++;

	while (Number != TheNumber)
	{
		if (Number > TheNumber)
			printf("��%d�β���;����\n", count);
		else if (Number < TheNumber)
			printf("��%d�β���;С��\n", count);

		if (count == 10)
		{
			return count + 1;
		}
		printf("********************************\n");
		printf("******����������%d���²µ���******\n", count + 1);
		Number = ScanfNums();

		while (Number <1 || Number >100)//ȷ���û��������1-100���� 
		{
			PrintError(2);
			Number = ScanfNums();
		}

		count++;
	}

	return count;
}
//��ӡ���а�
void PrintRankList(GuessNumber Game[])
{
	printf("\n");
	printf("\n");
	printf("%6s%10s%9s%9s\n", "����", "�û�", "��߷�", "�ܷ���");
	for (int i = 0; i < 10; i++)
	{
		printf("%6d%10s%9d%9d\n", i + 1, Game[i].GamerName, Game[i].grade, Game[i].totalGrade);
	}
}
//��struct����
void Rank(GuessNumber Game[])
{
	int k = 0, l = 0;
	GuessNumber temp[1];

	for (k = 0; k < 10; k++)
	{
		for (l = 0; l < 10 - k; l++)
		{
			if (Game[l].grade < Game[l + 1].grade)
			{
				/*change = Game[l].grade;
				Game[l].grade = Game[l + 1].grade;
				Game[l + 1].grade = change;
				change = Game[l].totalGrade;
				Game[l].totalGrade = Game[l + 1].totalGrade;
				Game[l + 1].totalGrade = change;
				strcpy_s(temp, 20, Game[l].GamerName);
				strcpy_s(Game[l].GamerName, 20, Game[l + 1].GamerName);
				strcpy_s(Game[l + 1].GamerName, 20, temp);*/

				temp[0] = Game[l];
				Game[l] = Game[l + 1];
				Game[l + 1] = temp[0];
			}
		}
	}
}
//����struct
void UpdateUserInfo(GuessNumber Game[], char GameName[], int grade)
{
	int count = 0;
	int worstGrade = 0;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10 - i - 1; j++)
		{
			if (Game[i].grade < Game[i + 1].grade)
				worstGrade = Game[i].grade;
		}
	}

	if (grade <= worstGrade)
	{
		printf("�ɼ�̫���ϲ��˰�\n������:%d\n", worstGrade);
		return;
	}

	for (int i = 0; i < 10; i++)
	{
		if (strcmp(Game[i].GamerName, GameName) == 0)
		{
			if (Game[i].grade < grade)//����·�����ԭ���ĸ�, ���滻
			{
				Game[i].grade = grade;
			}
			Game[i].totalGrade += grade;
			count++;
		}
	}

	if (count == 0)
	{
		strcpy_s(Game[10].GamerName, 20, GameName);
		Game[10].grade = grade;
		Game[10].totalGrade += grade;
	}
}
//��ʼ��struct
void InitializeStruct(GuessNumber Game[])
{
	for (int i = 0; i < 11; i++)
	{
		//��ʼ��
		strcpy_s(Game[i].GamerName, 20, "��");
		Game[i].grade = 0;
		Game[i].totalGrade = 0;
	}
}
//��ȡ��������а�����
void ReadRankList(GuessNumber Game[])
{
	FILE *fp = NULL;

	int choice = 1;
	while (1)
	{
		errno_t err = fopen_s(&fp, "c:\\RankList.txt", "r");
		if (err == 0)
		{
			printf("�ɹ������а��ļ�\n");
			break;
		}
		else
		{
			printf("�����а��ļ�ʧ��\n");
		}

		PrintFileChoice();
		choice = ScanfNum();
		if (choice == 0)
		{
			return;
		}
	}

	int count = 0;
	int temp;
	for (int i = 0; i < 10; i++)
	{
		fscanf_s(fp, "%d%s%d%d", &temp, Game[i].GamerName, 10, //��Ϊ��fscanf_s����, �������20������ȷ��ֻ��ȡ10���ַ�����Game[i].GamerName
			&Game[i].grade, &Game[i].totalGrade);
		count++;
	}
	
	if (count == 10)
	{
		printf("��ȡ���а����\n");
	}

	fclose(fp);
	return;
}
//���ļ��������а�����
void SaveRankList(GuessNumber Game[])
{
	FILE *fpTemp = NULL, *fp= NULL;

	int choice = 1;
	while (1)
	{
		errno_t err = fopen_s(&fp, "c:\\RankList.txt", "w");
		if (err == 0)
		{
			printf("�ɹ����ļ�\n");
			break;
		}
		else
		{
			printf("���ļ�ʧ��\n");
			printf("���ڴ����ļ�\n");
			errno_t errTemp = fopen_s(&fpTemp, "c:\\RankList.txt", "a+");
			if (errTemp == 0)
			{
				printf("�ɹ������ļ�\n");
			}
			else
			{
				printf("�����ļ�ʧ��\n");
			}
			fclose(fpTemp);
		}

		PrintFileChoice();
		choice = ScanfNum();
		if (choice == 0)
		{
			return;
		}
	}

	int count = 0;
	for (int i = 0; i < 10; i++)
	{
		fprintf_s(fp, "%6d %10s %9d %9d\n", i + 1, Game[i].GamerName, Game[i].grade, Game[i].totalGrade);
		count++;
	}

	if (count == 10)
	{
		printf("�������а����\n");
	}

	fclose(fp);
	system("attrib +h c:\\RankList.txt");
	return;
}
//��ʼ�˵�ѡ��
int SelectNum()
{
	int MeauSelectedNumber = 10;

	PrintMeau();
	MeauSelectedNumber = ScanfNum();

	if (MeauSelectedNumber == 0)
	{
		PrintExitMeau();
		MeauSelectedNumber = ScanfNum();
		if (MeauSelectedNumber == 0)
		{
			return 0;
		}		
	}

	while (MeauSelectedNumber != 1)
	{
		PrintError(1);
		MeauSelectedNumber = ScanfNum();
	}

	return 1;
}

#endif // !__FUNCTION_H__
