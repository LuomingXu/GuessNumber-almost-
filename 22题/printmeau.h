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

//���˵���ӡ
void PrintMeau()
{
	printf("\n");
	printf("********��ӭ����������Ϸ********\n");
	printf("1.�����������\n");
	printf("2.��ʾ���а�\n");
	printf("3.�������а�\"C:\\\\RankList.txt\"\n");
	printf(".�����Ա���10���û�����\n");
	printf(".����\"0\"�˳�\n");
}
//�β˵���ӡ
void PrintSmallMeau()
{
	printf("\n");
	printf("********����������Ϸ��********\n");
	printf("1.�����������\n");
	printf("2.��ʾ���а�\n");
	printf("3.�������а�\"C:\\\\RankList.txt\"\n");
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
//��ӡ�˳��˵�
void PrintExitMeau()
{
	printf("\n");
	printf("********ȷ���˳��밴\"0\"********\n");
	printf("*******ȡ��������������*********\n");
}
//�ļ�ϵͳ�Ĳ˵�ѡ��
void PrintFileChoice()
{
	printf("\n");
	printf("*********�˳��밴\"0\"********\n");
	printf("****���������밴������������****\n");
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

#endif // !__PRINTMEAU_H__
