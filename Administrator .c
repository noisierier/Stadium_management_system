#include <stdio.h>
#include <stdlib.h>
#include "Administrator.h"
#include"delay.h"
#include"menu.h"
#include"rank.h"
#include"site_search.h"
#include"addsite.h"



void administrator_menu(void)//管理员主菜单界面
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" _________________体育馆管理系统___________________\n");
	printf(" __________________________________________管理员版\n");
	printf("\t\t 请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.预定管理                                    |\n");
	printf("|                                                  |\n");
	printf("|    2.场地管理                                    |\n");
	printf("|                                                  |\n");
	printf("|    3.个人信息                                    |\n");
	printf("|                                                  |\n");
	printf("|    4.使用手册                                    |\n");
	printf("|                                                  |\n");
	printf("|    5.返回主界面                                  |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	administrator_choose_1();
}

void administrator_choose_1(void)//管理员主界面选择系统
{
	char flag;
	printf("请输入您的选项：");
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5')
	{
		printf("\n请根据提示，输入'1'或'2'或'3'或'4'或'5'：");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case '1':Scheduled_anagement();//预定管理
		break;
	case '2':site_management();//场地管理
		break;
	case '3':administerator_personal_information();//管理员个人信息
		break;
	case '4':administerator_service_manual();//管理员使用手册
		break;
	case '5':printf("\n正在返回······");
		delay(500);
		menu();
	default:
		break;
	}
}

void administrator_return_1(void)//返回管理员主菜单界面
{
	printf("按任意键返回管理员主界面：");
	char a;
	a = getch();
	printf("%c", a);
	delay(100);
	if (a != NULL)
	{
		printf("\n正在返回······");
		delay(400);
		administrator_menu();
	}
}

void Scheduled_anagement(void)//查看场地预定函数界面
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" ________________体育馆预定及管理系统______________\n");
	printf(" __________________________________________管理员版\n");
	printf("\t\t 请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.查看预定情况                                |\n");
	printf("|                                                  |\n");
	printf("|    2.统计预定情况                                |\n");
	printf("|                                                  |\n");
	printf("|    3.返回管理员主界面                            |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	administrator_choose_2();
}

void administrator_choose_2(void)//查看场地预定函数界面选择函数
{
	char flag;
	printf("请输入您的选项：");
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3')
	{
		printf("\n请根据提示，输入'1'或'2'或'3'：");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case '1':inquiry_menu();//调出场地预定查询函数界面
		break;
	case '2':administrator_menu_rank();//统计用户预定信息函数
		break;
	case '3':printf("\n正在返回······");
		delay(500);
		administrator_menu();
		break;
	default:
		break;
	}
}

void rank_site(void)//管理员统计用户预定信息函数
{
	system("cls");
	printf("查看预定情况统计相关函数\n");
	administrator_return_2();
}

void administrator_return_2(void)//返回预定管理函数界面
{
	printf("按任意键返回预定管理界面：");
	char a;
	a = getch();
	printf("%c", a);
	delay(100);
	if (a != NULL)
	{
		printf("\n正在返回······");
		delay(400);
		Scheduled_anagement();
	}
}

void site_management(void)//场地管理函数界面
{   /*查询所有场地
	添加一个新场地*/
	system("cls");
	printf(" __________________________________________________\n");
	printf(" ________________体育馆场地及管理系统______________\n");
	printf(" __________________________________________管理员版\n");
	printf("\t\t 请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.查看所有场地                                |\n");
	printf("|                                                  |\n");
	printf("|    2.添加新的场地                                |\n");
	printf("|                                                  |\n");
	printf("|    3.返回管理员主界面                            |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	administrator_choose_3();
}

void administrator_choose_3(void)//场地管理界面选择函数
{
	char flag;
	printf("请输入您的选项：");
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3')
	{
		printf("\n请根据提示，输入'1'或'2'或'3'：");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case '1':read_site_menu_ad();//查看场地函数
		break;
	case '2':add_site();//添加场地函数
		break;
	case '3':printf("\n正在返回······");
		delay(500);
		administrator_menu();
		break;
	default:
		break;
	}
}

void add_site(void)//添加场地函数
{
	system("cls");
	circulateInsertCourtData();
	administrator_return_3();
}

void administrator_return_3(void)//返回场地管理函数界面
{
	printf("按任意键返回场地管理界面：");
	char a;
	a = getch();
	printf("%c", a);
	delay(100);
	if (a != NULL)
	{
		printf("\n正在返回······");
		delay(400);
		site_management();
	}
}

void administerator_personal_information(void)//管理员个人信息函数界面
{
	/*对个人信息中的密码、邮箱、电话等信息进行修改*/
	system("cls");
	printf(" __________________________________________________\n");
	printf(" ______________体育馆个人信息管理系统______________\n");
	printf(" __________________________________________管理员版\n");
	printf("\t\t 请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.查看信息                                    |\n");
	printf("|                                                  |\n");
	printf("|    2.修改信息                                    |\n");
	printf("|                                                  |\n");
	printf("|    3.用户信息管理系统                            |\n");
	printf("|                                                  |\n");
	printf("|    4.返回管理员主界面                            |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	administerator_choose_4();
}

void administerator_choose_4(void)//管理员个人信息管理操作系统
{
	char flag;
	printf("请输入您的选项：");
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3' &&flag!='4')
	{
		printf("\n请根据提示，输入'1'或'2'或'3'或'4'：");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case '1'://查看管理员信息函数
		ad_read_info();
		break;
	case '2'://修改管理员信息函数
		ad_modify_menu();
		break;
	case '3':user_information_management_system_menu();
		break;
	case '4':printf("\n正在返回······");
		delay(500);
		administrator_menu();
		break;
	default:
		break;
	}
}

void administrator_return_4(void)//返回个人信息管理函数界面
{
	printf("按任意键返回个人信息管理界面：");
	char a;
	a = getch();
	printf("%c", a);
	delay(100);
	if (a != NULL)
	{
		printf("\n正在返回······");
		delay(400);
		administerator_personal_information();
	}
}

void administerator_service_manual(void)//管理员使用手册函数
{
	
	system("cls"); 
	printf("——————————————————————————————————————————————\n");
	printf("在管理员系统中，您可以查看用户的预定信息，并对体育馆所有场地的预定统计及营业额情况进行查看\n");
	delay(500);
	administrator_return_1();
}