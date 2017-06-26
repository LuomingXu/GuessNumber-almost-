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
	int MeauSelectedNumber = 10;	//�˵�ѡ�������
	char GamerName[20];	//�ݴ��û�����
	GuessNumber Game[11];	//�û���Ϣ��struct

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
				//��һ���������浽char����������
				printf("�������������\n");
				gets_s(GamerName, 20);
				//��߲�����Ϸ��������
				int count = MainGame();
				printf("%d\n", count);
				//�������
				int grade = 0;
				if (count <= 10)
				{
					grade = 100 / count;
					printf("��ϲ���¶���\n");
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
//ȷ��������ǵ�������
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
//ȷ�����������
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
				printf("������\n");
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
				printf("�����������: %d\n", nums);
				break;
			case 2:
				break;
			default:
				printf("û�д�ѡ��!\n");
			break;
		}
		PrintMeauNum();
		choice = ScanfNum();
		if (choice == 2)
			break;
	}

	return nums;
}
//����Ϸ����
int MainGame()
{
	int Number = 0;//�û�������� 
	int count = 0;//��¼�û����˼��ε��� 

	int TheNumber = 0;//ϵͳ�����һ���� 
	srand((unsigned)time(NULL));//����ʱ�����ӣ����ܶ�����forѭ��֮�У�����ˣ���Ϊα���
	TheNumber = rand() % 101;
	//TheNumber = 10;//�����ò�������
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

		printf("����������%d���²µ���\n", count + 1);
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
	printf("%6s%6s%9s%9s\n","����","�û�","��߷�","�ܷ���");
	for (int i = 0; i < 10; i++)
	{
		printf("%6d%6s%9d%9d\n", i + 1, Game[i].GamerName, Game[i].grade, Game[i].totalGrade);
	}
}
//��struct����
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
		printf("�ɼ�̫���ϲ��˰�\n", worstGrade);
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
//���˵���ӡ
void PrintMeau()
{
	printf("\n");
	printf("********��ӭ����������Ϸ********\n");
	printf("1.�����������\n");
	printf("2.��ӡ���а�\n");
	printf(".�����Ա���10���û�����\n");
	printf(".����\"0\"�˳�\n");
}
//�β˵���ӡ
void PrintSmallMeau()
{
	printf("\n");
	printf("********����������Ϸ��********\n");
	printf("1.�����������\n");
	printf("2.��ӡ���а�\n");
	printf(".�����Ա���10���û�����\n");
	printf(".����\"0\"�˳�\n");
}
//��ӡ�������ֵĲ˵�
void PrintMeauNum()
{
	printf("\n");
	printf("********ȷ��ѡ�ô����ֵĲ˵�********\n");
	printf("���������밴 1\n");
	printf("ȷ�ϴ����밴 2\n");
}
//�˳���Ϣ��ӡ
void PrintExit()
{
	printf("\n");
	printf("\n");
	printf("********��ӭʹ��********\n");
	printf("**********�ټ�!*********\n");
}
//������Ϣ����
void PrintError(int i)
{
	switch (i)
	{
		case 1:
			printf("�����������������(ѡ��\"1\"ѡ��)\n");
			break;
		case 2:
			printf("������1-100����\n");
			break;
		case 3:
			printf("������\"����\"����\n");
			break;
		case 4:
			printf("��һ���ַ�����Ϊ��Ϊ\"��\"����\n");
			break;
		default:
			printf("�����ڴ˴������\n");
			break;
	}
}