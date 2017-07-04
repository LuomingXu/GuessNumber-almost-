#pragma once
#ifndef __FUNCTION_H__
#define __FUNCTION_H__

#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<time.h>//为了测试排序所用时间的include, 但由于数据太少, 使用时间极少, 有点鸡肋/抠鼻
#include"printmeau.h"
#include"scan.h"

//定义struct
typedef struct MyStruct
{
	char GamerName[20];
	int grade;
	int totalGrade;
}GuessNumber;

int MainGame(int* RandomNumber);
int SelectNum();
void Rank(GuessNumber Game[]);
void PrintRankList(GuessNumber Game[], char GameName[]);
void InitializeStruct(GuessNumber Game[]);
void UpdateUserInfo(GuessNumber Game[], char GameName[], int grade);
void ReadRankList(GuessNumber Game[]);
void SaveRankList(GuessNumber Game[]);

clock_t start, finish;
double duration;

//主游戏程序
int MainGame(int* RandomNumber)
{
	int Number = 0;//用户输入的数 
	int count = 0;//记录用户猜了几次的数 

	int TheNumber = 0;//系统随机出一个数 
	srand((unsigned)time(NULL));//定义时间种子，不能定义在for循环之中，若如此，就为伪随机
	TheNumber = rand() % 101;

	TheNumber = 10;//测试用猜数数字
	*RandomNumber = TheNumber;//将系统随机出的数传回main函数

	printf("********************游戏开始********************\n");
	printf("程序已随机出一个1-100的数\n");
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
void PrintRankList(GuessNumber Game[],char GamerName[])
{
	printf("\n");
	printf("\n");
	printf("%5s%10s%9s%9s\n", "名次", "用户", "最高分", "总分数");
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(Game[i].GamerName,GamerName) == 0)
		{
			printf("%3s%2d%10s%9d%9d\n", "你:", i + 1, Game[i].GamerName, Game[i].grade, Game[i].totalGrade);
			continue;
		}
		printf("%5d%10s%9d%9d\n", i + 1, Game[i].GamerName, Game[i].grade, Game[i].totalGrade);
	}
}
//对struct排序
void Rank(GuessNumber Game[])
{
	int k = 0, l = 0;
	GuessNumber temp[1];
	bool changed = true;//若是某一次的循环没有变化, 则表明数据已经成有序排列, 则直接break, 为了提高冒泡效率的变量

	start = clock();
	
	for (k = 1; k < 11 && changed == true; k++)
	{
		changed = false;
		for (l = 0; l < 11 - k; l++)
		{
			if (Game[l].grade < Game[l + 1].grade)
			{//排序时以最高分为最优先
				temp[0] = Game[l];
				Game[l] = Game[l + 1];
				Game[l + 1] = temp[0];
				changed = true;
			}
			else if (Game[l].grade == Game[l + 1].grade && Game[l].totalGrade < Game[l + 1].totalGrade)
			{//总分为亚级的排序
				temp[0] = Game[l];
				Game[l] = Game[l + 1];
				Game[l + 1] = temp[0];
				changed = true;
			}
			else if (Game[l].grade == Game[l + 1].grade && Game[l].totalGrade == Game[l + 1].totalGrade && strcmp(Game[l].GamerName,Game[l + 1].GamerName) > 0)
			{//名字为次级的排序
				temp[0] = Game[l];
				Game[l] = Game[l + 1];
				Game[l + 1] = temp[0];
				changed = true;
			}
		}//for-l
	}//for-k
	finish = clock();
	duration = (double)(finish - start) / CLOCKS_PER_SEC;
	printf(__FUNCTION__": Time: %5.3fms\n", duration * 10000);

}
//更新struct
void UpdateUserInfo(GuessNumber Game[], char GamerName[], int grade)
{
	int flag = 0;
	int worstGrade = Game[9].grade;

	for (int i = 0; i < 9; i++)
	{
		if (worstGrade > Game[i].grade)
			worstGrade = Game[i].grade;
	}

	if (grade < worstGrade)
	{
		printf("成绩太差上不了榜单\n最差分数:%d\n你的分数:%d\n", worstGrade, grade);
		return;
	}
	//找到如果原来就存在此用户的数据
	for (int i = 0; i < 10; i++)
	{
		if (strcmp(Game[i].GamerName, GamerName) == 0)
		{
			if (Game[i].grade < grade)//如果新分数比原来的高, 就替换
			{
				Game[i].grade = grade;
			}
			Game[i].totalGrade += grade;
			flag++;
		}
	}
	//如果没有找到, 就在[10]里面添加
	if (flag == 0)
	{
		strcpy_s(Game[10].GamerName, 20, GamerName);
		Game[10].grade = grade;
		Game[10].totalGrade = grade;
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
		errno_t err = fopen_s(&fp, CurrentText, "r");
		if (err == 0)
		{
			printf("成功打开排行榜文件\n");
			break;
		}
		else
		{
			printf("打开排行榜文件失败\n或许不存在此文件\n程序会在保存排行榜数据时创建此文件\n");
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
		fscanf_s(fp, "%d%s%d%d", &temp, Game[i].GamerName, 20, //因为是"_s"的函数, 所以这个20是用来确保只读取20的字符进入Game[i].GamerName
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
	FILE *fpTemp = NULL, *fptemp2, *fp= NULL;

	char cmd[160] = "attrib -r -h \"";//由于在保存的时候添加了隐藏属性, 所以在再次打开的时候需要去除, 当文件目录里面有空格时, 需要在目录外添加""
	strcat_s(cmd, 160, CurrentText);
	strcat_s(cmd, 160, "\"");
	printf("cmd:%s\n", cmd);
	errno_t err = fopen_s(&fptemp2, CurrentText, "r");//若存在此文件, 才会在写入之前去除隐藏属性
	if (err == 0)
	{
		system(cmd);
		fclose(fptemp2);//使用之后必须关闭才能再打开
	}
	
	int choice = 1;
	while (1)
	{
		errno_t err = fopen_s(&fp, CurrentText, "w");
		if (err == 0)
		{
			printf("成功打开/创建文件\n");
			break;
		}
		else
		{
			printf("打开文件失败\n");
			printf("正在创建文件\n");
			errno_t errTemp = fopen_s(&fpTemp, CurrentText, "a+");
			if (errTemp == 0)
			{
				printf("成功创建文件\n可尝试再次保存\n");
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
		//在打印时要为scanf考虑, 在之间一定要留空格, 因为你并不知道这6, 10个字符是否占满了, 若是占满了, 字符之间就没有空格了, 在后续读取时就会出现错误
		fprintf_s(fp, "%6d %10s %9d %9d\n", i + 1, Game[i].GamerName, Game[i].grade, Game[i].totalGrade);
		count++;
	}

	if (count == 10)
	{
		printf("保存排行榜完成\n");
	}

	fclose(fp);

	strcpy_s(cmd, 160, "attrib +r +h \"");//防止普通用户修改内部数据, 导致fscanf出错, 所以隐藏文件
	strcat_s(cmd, 160, CurrentText);
	strcat_s(cmd, 160, "\"");
	printf("cmd:%s\n", cmd);
	system(cmd);

	return;
}
//初始菜单选项
int SelectNum()
{
	int MeauSelectedNumber = 10;

	PrintMeau();
	MeauSelectedNumber = ScanfNum();

	while (MeauSelectedNumber == 0)
	{
		PrintExitMeau();
		MeauSelectedNumber = ScanfNum();
		if (MeauSelectedNumber == 0)
		{
			return 0;
		}
		else
		{
			PrintMeau();
			MeauSelectedNumber = ScanfNum();
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
