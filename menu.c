#include <stdio.h>
#include "menu.h"
#include"user.h"
#include"Administrator.h"
#include"delay.h"
#include "info_management.h"

void menu(void)//���˵�
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" _________________�����ݹ���ϵͳ___________________\n");
	printf(" __________________________________________________\n");
	printf("\t\t  ��ѡ����������\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.�û���½                                    |\n");
	printf("|                                                  |\n");
	printf("|    2.�û�ע��                                    |\n");
	printf("|                                                  |\n");
	printf("|    3.����Ա��¼                                  |\n");
	printf("|                                                  |\n");
	printf("|    4.ʹ���ֲ�                                    |\n");
	printf("|                                                  |\n");
	printf("|    5.�˳�����                                    |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	choose();
}

void choose(void)//���˵�ѡ����
{
    char flag;
	printf("����������ѡ�");
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5')
	{
		printf("\n�������ʾ������'1'��'2'��'3'��'4'��'5'��");
		flag = getch();		
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case '1':user_login();//�û���¼����
		break;
	case '2':user_register();//�û�ע�ắ��
		break;
	case '3':
		ad_login();//����Ա��¼����
		break;
	case '4':service_manual();//ʹ���ֲ�
		break;
	case '5':exit(0);
		break;
	default:
		break;
	}
}

void service_manual(void)//���˵��û�ʹ���ֲ�
{ 
	char flag;
	system("cls");
	delay(100);
	printf("����ѡ����ʾ�������ϵͳ\n��");
	printf("�������ݹ�����Ŀ����ע��õ��ĸ��û��˺ź��Ѿ�����õ�������ͬ���ݵĹ���Ա�˺ţ�\n�û��˺ſ����ڹ���Աϵͳ�ڽ��в鿴�����Դ˴�ֻ����һ���û��˺ź����й���Ա���˺ţ�");
	printf("\n�û��˺ţ�11111111    �û����룺11111111������8��1��");
	printf("\n����Ա�˺ţ�11111111    ����Ա���룺11111111������8��1��");
	printf("\n����Ա�˺ţ�22222222    ����Ա���룺22222222������8��2��");
	printf("\n����Ա�˺ţ�33333333    ����Ա���룺33333333������8��3��");
	printf("\nΪ���չ��û����飬�󲿷�����ʱ������Ҫ����س����ַ���������⣩");
	
	delay(500);
	printf("\n�밴������˳��û��ֲᣬ����������:");
	if (flag = getch() != NULL)
	{
		printf("%c", flag);
		printf("\n���ڷ��������桤����������");
		delay(500);
		menu();
	}
}

void _return(void)//��������������˵����溯��
{
	char flag;
	printf("����������������棺");
	if (flag = getch() != NULL)
	{
		printf("%c", flag);
		printf("\n���ڷ��ء�����������");
		delay(500);
		menu();
	}
}

		