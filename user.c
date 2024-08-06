#include<stdio.h>
#include <stdlib.h>
#include"user.h"
#include"delay.h"
#include"menu.h"
#include"site_search.h"
#include"book_site.h"



void user_menu(void)//�û����˵�����
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" _________________�����ݹ���ϵͳ___________________\n");
	printf(" __________________________________________�û��汾\n");
	printf("\t\t ��ѡ����������\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.��ѯ������Ϣ                                |\n");
	printf("|                                                  |\n");
	printf("|    2.Ԥ����Ϣ                                    |\n");
	printf("|                                                  |\n");
	printf("|    3.������Ϣ                                    |\n");
	printf("|                                                  |\n");
	printf("|    4.ʹ���ֲ�                                    |\n");
	printf("|                                                  |\n");
	printf("|    5.����������                                  |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	user_choose_1();
}

void user_return_1(void)//�����û����˵�����
{
	printf("������������û����棺");
	char a;
	a = getch();
	printf("%c", a);
	delay(100);
	if (a != NULL)
	{
		printf("\n���ڷ��ء�����������");
		delay(400);
		user_menu();
	}	      
}

void user_choose_1(void)//�û����˵�����ѡ����
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
	case '1':read_site_menu_user();//��ѯ������Ϣ����
		break;
	case '2':reserve_message();//Ԥ����Ϣ
		break;
	case '3':user_personal_information();//�û�������Ϣ
		break;
	case '4':user_service_manual();//�û�ʹ���ֲ�
		delay(500);
		user_return_1();
		break;
	case '5':
		printf("\n���ڷ��ء�����������");
		delay(500); 
		menu();
		break;
	default:
		break;
	}
}

void reserve_message(void)//Ԥ�����ؼ���Ϣ���ܽ���
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" _________________������Ԥ��ϵͳ___________________\n");
	printf(" __________________________________________�û��汾\n");
	printf("\t\t ��ѡ����������\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.����Ԥ����ѯ                                |\n");
	printf("|                                                  |\n");
	printf("|    2.Ԥ������                                    |\n");
	printf("|                                                  |\n");
	printf("|    3.��ʷԤ��������ȡ��ԤԼ                      |\n");
	printf("|                                                  |\n");
	printf("|    4.Ԥ�����ͳ��                                |\n");
	printf("|                                                  |\n");
	printf("|    5.Ԥ��ǩ��                                    |\n");
	printf("|                                                  |\n");
	printf("|    6.ʹ���ֲ�                                    |\n");
	printf("|                                                  |\n");
	printf("|    7.���ؽ���                                    |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	user_choose_2();
}

void user_choose_2() //Ԥ�����ؼ���Ϣ���ܽ���ѡ����
{
	char flag;
	printf("����������ѡ�");
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7')
	{
		printf("\n�������ʾ������'1'��'2'��'3'��'4'��'5'��'6'��'7':");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case'1':inquiry_menu_user();//�鿴����Ԥ���������
		break;
	case '2':book_f();//Ԥ�����غ���
		break;
	case '3'://Ԥ����ʷ��ѯ����
		showOrders_menu();
		break;
	case'4':user_menu_rank();//Ԥ�����ͳ��
		break;
	case'5':signIn_pre();//ǩ��Ԥ����������
		break;
	case '6':
		system("cls");
		printf("������������������������������������������������������������������������������������������������\n");
		printf("������ʾ����Ԥ�����ػ��ѯԤ����ʷ��¼��\n");
		delay(500);
		user_return_2();
		break;
	case '7':
		printf("\n���ڷ��ء�����������");
		delay(500); 
		user_menu();
		break;
	default:
		break;
	}
}

void user_return_2(void)//����Ԥ����Ϣ����
{
	printf("�����������Ԥ����Ϣ���棺");
	char a;
	a = getch();
	printf("%c", a);
	delay(100);
	if (a != NULL)
	{
		printf("\n���ڷ��ء�����������");
		delay(400);
		reserve_message();
	}
}

void user_personal_information(void)//�û�������Ϣ
{
	delay(100);
	system("cls");
	printf(" __________________________________________________\n");
	printf(" _______________�û�������Ϣ����ϵͳ_______________\n");
	printf(" __________________________________________�û��汾\n");
	printf("\t\t ��ѡ����������\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.�鿴��Ϣ                                    |\n");
	printf("|                                                  |\n");
	printf("|    2.�޸���Ϣ                                    |\n");
	printf("|                                                  |\n");
	printf("|    3.���ؽ���                                    |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	user_choose_3();
}

void user_choose_3(void)//�û�������Ϣ�������ϵͳ
{
	char flag;
	printf("����������ѡ�");
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3' )
	{
		printf("\n�������ʾ������'1'��'2'��'3'��");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case '1'://�鿴�û���Ϣ����
		user_read_info();
		break;
	case '2'://�޸��û���Ϣ����
		user_modify_menu();
		break;
	case '3':printf("\n���ڷ��ء�����������");
		delay(500);
		user_menu();	
		break;
	default:
		break;
	}
}

void user_return_3(void)//�����û�������Ϣ�������
{
	printf("����������ظ�����Ϣ���棺");
	char a;
	a = getch();
	printf("%c", a);
	delay(100);
	if (a != NULL)
	{
		printf("\n���ڷ��ء�����������");
		delay(400);
		user_personal_information();
	}
}

void user_service_manual(void)//�û�ʹ���ֲ�
{
	delay(100);
	system("cls");
	printf("������������������������������������������������������������������������������������������������\n");
	printf("���������û�ϵͳ�У������Ը�����ʾ�����˽ⳡ����Ϣ�����г���Ԥ������������û���Ϣ�����鿴Ԥ�����\n");
}