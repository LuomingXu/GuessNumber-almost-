#pragma once
#ifndef __SCAN_H__
#define __SCAN_H__

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include"printmeau.h"

int ScanfNum();
int ScanfNums();

//确保输入的是单个数字
int ScanfNum()
{
	char temp[CHAR_MAX];

	gets_s(temp, CHAR_MAX);

	while (isdigit(temp[0]) == 0 || strlen(temp) > 1)
	{
		PrintError(3);
		gets_s(temp, CHAR_MAX);
	}

	return temp[0] - '0';
}
//确保输入的是数
int ScanfNums()
{
	int choice = 1;
	char temp[100];
	int nums = 0;

	while (1)
	{
		switch (choice)
		{
		case 1:
			printf("请输入: \n");
			gets_s(temp, 100);

			nums = temp[0] - '0';

			while (isdigit(temp[0]) == 0 || nums == 0)
			{
				PrintError(4);
				gets_s(temp, 100);
				nums = temp[0] - '0';
			}

			for (int i = 1; i < 100; i++)
			{
				if (isdigit(temp[i]) != 0)
				{
					nums = nums * 10 + (temp[i] - '0');
				}
				else
					break;
			}
			printf("您输入的数是: %d\n", nums);
			break;
		case 2:
			break;
		default:
			printf("没有此选项!\n");
			break;
		}
		PrintMeauNum();
		choice = ScanfNum();
		if (choice == 2)
			break;
	}

	return nums;
}

#endif // !__SCAN_H__

