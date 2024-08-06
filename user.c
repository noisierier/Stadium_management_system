#include<stdio.h>
#include <stdlib.h>
#include"user.h"
#include"delay.h"
#include"menu.h"
#include"site_search.h"
#include"book_site.h"



void user_menu(void)//用户主菜单界面
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" _________________体育馆管理系统___________________\n");
	printf(" __________________________________________用户版本\n");
	printf("\t\t 请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.查询场地信息                                |\n");
	printf("|                                                  |\n");
	printf("|    2.预定信息                                    |\n");
	printf("|                                                  |\n");
	printf("|    3.个人信息                                    |\n");
	printf("|                                                  |\n");
	printf("|    4.使用手册                                    |\n");
	printf("|                                                  |\n");
	printf("|    5.返回主界面                                  |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	user_choose_1();
}

void user_return_1(void)//返回用户主菜单界面
{
	printf("按任意键返回用户界面：");
	char a;
	a = getch();
	printf("%c", a);
	delay(100);
	if (a != NULL)
	{
		printf("\n正在返回······");
		delay(400);
		user_menu();
	}	      
}

void user_choose_1(void)//用户主菜单界面选择函数
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
	case '1':read_site_menu_user();//查询场地信息函数
		break;
	case '2':reserve_message();//预定信息
		break;
	case '3':user_personal_information();//用户个人信息
		break;
	case '4':user_service_manual();//用户使用手册
		delay(500);
		user_return_1();
		break;
	case '5':
		printf("\n正在返回······");
		delay(500); 
		menu();
		break;
	default:
		break;
	}
}

void reserve_message(void)//预定场地及信息介绍界面
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" _________________体育馆预定系统___________________\n");
	printf(" __________________________________________用户版本\n");
	printf("\t\t 请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.场地预定查询                                |\n");
	printf("|                                                  |\n");
	printf("|    2.预定场地                                    |\n");
	printf("|                                                  |\n");
	printf("|    3.历史预定订单和取消预约                      |\n");
	printf("|                                                  |\n");
	printf("|    4.预定情况统计                                |\n");
	printf("|                                                  |\n");
	printf("|    5.预定签到                                    |\n");
	printf("|                                                  |\n");
	printf("|    6.使用手册                                    |\n");
	printf("|                                                  |\n");
	printf("|    7.返回界面                                    |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	user_choose_2();
}

void user_choose_2() //预定场地及信息介绍界面选择函数
{
	char flag;
	printf("请输入您的选项：");
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7')
	{
		printf("\n请根据提示，输入'1'或'2'或'3'或'4'或'5'或'6'或'7':");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case'1':inquiry_menu_user();//查看场地预定情况函数
		break;
	case '2':book_f();//预定场地函数
		break;
	case '3'://预定历史查询函数
		showOrders_menu();
		break;
	case'4':user_menu_rank();//预定情况统计
		break;
	case'5':signIn_pre();//签到预处理及主函数
		break;
	case '6':
		system("cls");
		printf("————————————————————————————————————————————————\n");
		printf("根据提示进行预定场地或查询预定历史记录。\n");
		delay(500);
		user_return_2();
		break;
	case '7':
		printf("\n正在返回······");
		delay(500); 
		user_menu();
		break;
	default:
		break;
	}
}

void user_return_2(void)//返回预定信息界面
{
	printf("按任意键返回预定信息界面：");
	char a;
	a = getch();
	printf("%c", a);
	delay(100);
	if (a != NULL)
	{
		printf("\n正在返回······");
		delay(400);
		reserve_message();
	}
}

void user_personal_information(void)//用户个人信息
{
	delay(100);
	system("cls");
	printf(" __________________________________________________\n");
	printf(" _______________用户个人信息管理系统_______________\n");
	printf(" __________________________________________用户版本\n");
	printf("\t\t 请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.查看信息                                    |\n");
	printf("|                                                  |\n");
	printf("|    2.修改信息                                    |\n");
	printf("|                                                  |\n");
	printf("|    3.返回界面                                    |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	user_choose_3();
}

void user_choose_3(void)//用户个人信息管理操作系统
{
	char flag;
	printf("请输入您的选项：");
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3' )
	{
		printf("\n请根据提示，输入'1'或'2'或'3'：");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case '1'://查看用户信息函数
		user_read_info();
		break;
	case '2'://修改用户信息函数
		user_modify_menu();
		break;
	case '3':printf("\n正在返回······");
		delay(500);
		user_menu();	
		break;
	default:
		break;
	}
}

void user_return_3(void)//返回用户个人信息管理界面
{
	printf("按任意键返回个人信息界面：");
	char a;
	a = getch();
	printf("%c", a);
	delay(100);
	if (a != NULL)
	{
		printf("\n正在返回······");
		delay(400);
		user_personal_information();
	}
}

void user_service_manual(void)//用户使用手册
{
	delay(100);
	system("cls");
	printf("————————————————————————————————————————————————\n");
	printf("在体育馆用户系统中，您可以根据提示进行了解场地信息，进行场馆预定，管理个人用户信息，并查看预定情况\n");
}