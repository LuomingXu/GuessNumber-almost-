#pragma once
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include"printmeau.h"
#include"scan.h"

//定义struct
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

//主游戏程序
int MainGame()
{
	int Number = 0;//用户输入的数 
	int count = 0;//记录用户猜了几次的数 

	int TheNumber = 0;//系统随机出一个数 
	srand((unsigned)time(NULL));//定义时间种子，不能定义在for循环之中，若如此，就为伪随机
	TheNumber = rand() % 101;
	TheNumber = 10;//测试用猜数数字
	printf("********************游戏开始********************\n");
	printf("请输入您猜的数\n");

	while (Number <1 || Number >100)//确保用户输入的是1-100的数 
	{
		PrintError(2);
		Number = ScanfNums();
	}

	count++;

	while (Number != TheNumber)
	{
		if (Number > TheNumber)
			printf("第%d次猜数;大了\n", count);
		else if (Number < TheNumber)
			printf("第%d次猜数;小了\n", count);

		if (count == 10)
		{
			return count + 1;
		}
		printf("********************************\n");
		printf("******请输入您第%d次新猜的数******\n", count + 1);
		Number = ScanfNums();

		while (Number <1 || Number >100)//确保用户输入的是1-100的数 
		{
			PrintError(2);
			Number = ScanfNums();
		}

		count++;
	}

	return count;
}
//打印排行榜
void PrintRankList(GuessNumber Game[])
{
	printf("\n");
	printf("\n");
	printf("%6s%10s%9s%9s\n", "名次", "用户", "最高分", "总分数");
	for (int i = 0; i < 10; i++)
	{
		printf("%6d%10s%9d%9d\n", i + 1, Game[i].GamerName, Game[i].grade, Game[i].totalGrade);
	}
}
//对struct排序
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
//更新struct
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
		printf("成绩太差上不了榜单\n最差分数:%d\n", worstGrade);
		return;
	}

	for (int i = 0; i < 10; i++)
	{
		if (strcmp(Game[i].GamerName, GameName) == 0)
		{
			if (Game[i].grade < grade)//如果新分数比原来的高, 就替换
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
//初始化struct
void InitializeStruct(GuessNumber Game[])
{
	for (int i = 0; i < 11; i++)
	{
		//初始化
		strcpy_s(Game[i].GamerName, 20, "无");
		Game[i].grade = 0;
		Game[i].totalGrade = 0;
	}
}
//读取保存的排行榜数据
void ReadRankList(GuessNumber Game[])
{
	FILE *fp = NULL;

	int choice = 1;
	while (1)
	{
		errno_t err = fopen_s(&fp, "c:\\RankList.txt", "r");
		if (err == 0)
		{
			printf("成功打开排行榜文件\n");
			break;
		}
		else
		{
			printf("打开排行榜文件失败\n");
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
		fscanf_s(fp, "%d%s%d%d", &temp, Game[i].GamerName, 10, //因为是fscanf_s函数, 所以这个20是用来确保只读取10的字符进入Game[i].GamerName
			&Game[i].grade, &Game[i].totalGrade);
		count++;
	}
	
	if (count == 10)
	{
		printf("读取排行榜完成\n");
	}

	fclose(fp);
	return;
}
//向文件保存排行榜数据
void SaveRankList(GuessNumber Game[])
{
	FILE *fpTemp = NULL, *fp= NULL;

	int choice = 1;
	while (1)
	{
		errno_t err = fopen_s(&fp, "c:\\RankList.txt", "w");
		if (err == 0)
		{
			printf("成功打开文件\n");
			break;
		}
		else
		{
			printf("打开文件失败\n");
			printf("正在创建文件\n");
			errno_t errTemp = fopen_s(&fpTemp, "c:\\RankList.txt", "a+");
			if (errTemp == 0)
			{
				printf("成功创建文件\n");
			}
			else
			{
				printf("创建文件失败\n");
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
		printf("保存排行榜完成\n");
	}

	fclose(fp);
	system("attrib +h c:\\RankList.txt");
	return;
}
//初始菜单选项
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
