#include<stdio.h>
#include<stdlib.h>
#include"printmeau.h"
#include"function.h"
#include"scan.h"

int main()
{
	int MeauSelectedNumber = 10;//�˵�ѡ�������
	char GamerName[20];//�ݴ��û�����
	GuessNumber Game[11];//�û���Ϣ��struct
	InitializeStruct(Game);

	ReadRankList(Game);
	MeauSelectedNumber = SelectNum();

	while (MeauSelectedNumber != 0)
	{
		switch (MeauSelectedNumber)
		{
			case 1:
				//��һ���������浽char����������
				printf("�������������\n");
				gets_s(GamerName, 20);

				//��߲�����Ϸ��������
				int count = MainGame();
				
				//�������
				int grade = 0;
				if (count <= 10)
				{
					grade = 100 / count;
					printf("\n��ϲ���¶���\n");
					printf("���ܹ�����\"%d\"��\n", count);
					//�����û������а��ڵ��û��Ƚ�, ���Ǹ������а����û��򽫴˸�ֵ��struct��
					UpdateUserInfo(Game, GamerName, grade);
					printf("***��������***\n");
					Rank(Game);//�������µ�����, ��Ҫ��������
					printf("***�������***\n");
				}
				else
				{
					printf("********ʧ��********\n");
					printf("�������Ĵ�������, ������\n");
				}
				break;
			case 2:
				PrintRankList(Game);
				break;
			case 3:
				SaveRankList(Game);
				break;
			default:
				printf("�����ڴ�ѡ��!\n");
				break;
		}

		PrintSmallMeau();
		MeauSelectedNumber = ScanfNum();
	}
	
	PrintExit();

	system("pause");
	return 0;
}
