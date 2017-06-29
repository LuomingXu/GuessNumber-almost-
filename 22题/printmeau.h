#pragma once
#ifndef __PRINTMEAU_H__
#define __PRINTMEAU_H__

#include <stdio.h>

void PrintMeau();
void PrintMeauNum();
void PrintSmallMeau();
void PrintExit();
void PrintExitMeau();
void PrintFileChoice();
void PrintError(int i);

//主菜单打印
void PrintMeau()
{
	printf("\n");
	printf("********欢迎来到猜数游戏********\n");
	printf("1.输入玩家姓名\n");
	printf("2.显示排行榜\n");
	printf("3.保存排行榜到\"C:\\\\RankList.txt\"\n");
	printf("P.S. 最多可以保存10组用户数据\n");
	printf("     输入\"0\"退出\n");
	printf("Copyright @  2017 Xu Luoming.All Right Reserved\n");//C语言似乎不能显示©, 那就只能退而求其次了...
}
//次菜单打印
void PrintSmallMeau()
{
	printf("\n");
	printf("********继续猜数游戏吗********\n");
	printf("1.输入玩家姓名\n");
	printf("2.显示排行榜\n");
	printf("3.保存排行榜到\"C:\\\\RankList.txt\"\n");
	printf("P.S. 最多可以保存10组用户数据\n");
	printf("     输入\"0\"退出\n");
}
//打印输入数字的菜单
void PrintMeauNum()
{
	printf("\n");
	printf("********确认选用此数字的菜单********\n");
	printf("重新输入请按 1\n");
	printf("确认此数请按 2\n");
}
//退出信息打印
void PrintExit()
{
	printf("\n");
	printf("\n");
	printf("********************欢迎使用*******************\n");
	printf("**********************再见!********************\n");
	printf("Copyright @  2017 Xu Luoming.All Right Reserved\n");
}
//打印退出菜单
void PrintExitMeau()
{
	printf("\n");
	printf("********确认退出请按\"0\"********\n");
	printf("*******取消其他单个数字*********\n");
}
//文件系统的菜单选择
void PrintFileChoice()
{
	printf("\n");
	printf("**************退出请按\"0\"************\n");
	printf("****继续尝试打开\/保存请按其他单个数字****\n");
}
//错误信息警告
void PrintError(int i)
{
	switch (i)
	{
	case 1:
		printf("请首先输入玩家姓名(选择\"1\"选项)\n");
		break;
	case 2:
		printf("请输入1-100的数\n");
		break;
	case 3:
		printf("请输入\"单个\"数字\n");
		break;
	case 4:
		printf("第一个字符必须为不为\"0\"数字\n");
		break;
	default:
		printf("不存在此错误代码\n");
		break;
	}
}

#endif // !__PRINTMEAU_H__
