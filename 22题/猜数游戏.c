#include<stdio.h>
#include"printmeau.h"
#include"function.h"
#include"scan.h"

int main()
{
	int RandomNum = 0;
	int MeauSelectedNumber = 10;//菜单选择的数字
	char GamerName[20];//暂存用户姓名
	GuessNumber Game[11];//用户信息的struct
	InitializeStruct(Game);

	ReadRankList(Game);
	MeauSelectedNumber = SelectNum();

	while (MeauSelectedNumber != 0)
	{
		switch (MeauSelectedNumber)
		{
			case 1:
				//把一个姓名保存到char的数组里面
				printf("请输入玩家姓名\n");
				gets_s(GamerName, 20);

				//这边插入游戏的主程序
				int count = MainGame(&RandomNum);
				
				//计算分数
				int grade = 0;
				if (count <= 10)
				{
					grade = 100 / count;
					printf("\n恭喜您猜对了\n");
					printf("系统的随机数是: %d\n", RandomNum);
					printf("您总共猜了\"%d\"次\n", count);
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
				PrintRankList(Game,GamerName);
				break;
			case 3:
				SaveRankList(Game);
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
