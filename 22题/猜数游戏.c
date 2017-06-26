#include<stdio.h>
#include<string.h>
#include<time.h>
#include<stdlib.h>
#include<ctype.h>

typedef struct MyStruct
{
	char GamerName[20];
	int grade;
	int totalGrade;
}GuessNumber;

int MainGame();
int ScanfNum();
int ScanfNums();
void PrintError(int i);
void PrintExit();
void PrintMeau();
void PrintSmallMeau();
void PrintMeauNum();
void Rank(GuessNumber Game[]);
void PrintRankList(GuessNumber Game[]);
void InitializeStruct(GuessNumber Game[]);
void UpdateUserInfo(GuessNumber Game[], char GameName[], int grade);

int main()
{
	int MeauSelectedNumber = 10;	//菜单选择的数字
	char GamerName[20];	//暂存用户姓名
	GuessNumber Game[11];	//用户信息的struct

	InitializeStruct(Game);

	PrintMeau();
	MeauSelectedNumber = ScanfNum();

	while (MeauSelectedNumber != 1)
	{
		PrintError(1);
		MeauSelectedNumber = ScanfNum();
	}

	while (MeauSelectedNumber != 0)
	{
		switch (MeauSelectedNumber)
		{
			case 1:
				//把一个姓名保存到char的数组里面
				printf("请输入玩家姓名\n");
				gets_s(GamerName, 20);
				//这边插入游戏的主程序
				int count = MainGame();
				printf("%d\n", count);
				//计算分数
				int grade = 0;
				if (count <= 10)
				{
					grade = 100 / count;
					printf("恭喜您猜对了\n");
					//将此用户与排行榜内的用户比较, 若是高于排行榜内用户则将此赋值进struct内
					UpdateUserInfo(Game, GamerName, grade);
					printf("***进行排序***\n");
					Rank(Game);//输入了新的数据, 需要进行排序
					printf("***排序完成***\n");
				}
				else
				{
					printf("********失败********\n");
					printf("您猜数的次数过多, 获得零分\n");
				}
				break;
			case 2:
				PrintRankList(Game);
				break;
			default:
				printf("不存在此选项!\n");
				break;
		}

		PrintSmallMeau();
		MeauSelectedNumber = ScanfNum();
	}
	
	PrintExit();

	system("pause");
	return 0;
}
//确保输入的是单个数字
int ScanfNum()
{
	char temp[CHAR_MAX];

	gets_s(temp, CHAR_MAX);

	while ( isdigit(temp[0]) == 0 || strlen(temp) > 1)
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
				printf("请输入\n");
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
//主游戏程序
int MainGame()
{
	int Number = 0;//用户输入的数 
	int count = 0;//记录用户猜了几次的数 

	int TheNumber = 0;//系统随机出一个数 
	srand((unsigned)time(NULL));//定义时间种子，不能定义在for循环之中，若如此，就为伪随机
	TheNumber = rand() % 101;
	//TheNumber = 10;//测试用猜数数字
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

		printf("请输入您第%d次新猜的数\n", count + 1);
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
	printf("%6s%6s%9s%9s\n","名次","用户","最高分","总分数");
	for (int i = 0; i < 10; i++)
	{
		printf("%6d%6s%9d%9d\n", i + 1, Game[i].GamerName, Game[i].grade, Game[i].totalGrade);
	}
}
//对struct排序
void Rank(GuessNumber Game[])
{
	int k = 0, l = 0, change;
	char temp[20];

	for (k = 0; k < 10; k++)
	{
		for (l = 0; l < 10 - k; l++)
		{
			if (Game[l].grade < Game[l + 1].grade)
			{
				change = Game[l].grade;
				Game[l].grade = Game[l + 1].grade;
				Game[l + 1].grade = change;
				change = Game[l].totalGrade;
				Game[l].totalGrade = Game[l + 1].totalGrade;
				Game[l + 1].totalGrade = change;
				strcpy_s(temp, 20, Game[l].GamerName);
				strcpy_s(Game[l].GamerName, 20, Game[l + 1].GamerName);
				strcpy_s(Game[l + 1].GamerName, 20, temp);
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
		printf("成绩太差上不了榜单\n", worstGrade);
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
//主菜单打印
void PrintMeau()
{
	printf("\n");
	printf("********欢迎来到猜数游戏********\n");
	printf("1.输入玩家姓名\n");
	printf("2.打印排行榜\n");
	printf(".最多可以保存10组用户数据\n");
	printf(".输入\"0\"退出\n");
}
//次菜单打印
void PrintSmallMeau()
{
	printf("\n");
	printf("********继续猜数游戏吗********\n");
	printf("1.输入玩家姓名\n");
	printf("2.打印排行榜\n");
	printf(".最多可以保存10组用户数据\n");
	printf(".输入\"0\"退出\n");
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
	printf("********欢迎使用********\n");
	printf("**********再见!*********\n");
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
			printf("第一个字符必须为不为\"零\"数字\n");
			break;
		default:
			printf("不存在此错误代码\n");
			break;
	}
}