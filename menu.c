#include <stdio.h>
#include "menu.h"
#include"user.h"
#include"Administrator.h"
#include"delay.h"
#include "info_management.h"

void menu(void)//主菜单
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" _________________体育馆管理系统___________________\n");
	printf(" __________________________________________________\n");
	printf("\t\t  请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.用户登陆                                    |\n");
	printf("|                                                  |\n");
	printf("|    2.用户注册                                    |\n");
	printf("|                                                  |\n");
	printf("|    3.管理员登录                                  |\n");
	printf("|                                                  |\n");
	printf("|    4.使用手册                                    |\n");
	printf("|                                                  |\n");
	printf("|    5.退出程序                                    |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	choose();
}

void choose(void)//主菜单选择函数
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
	case '1':user_login();//用户登录函数
		break;
	case '2':user_register();//用户注册函数
		break;
	case '3':
		ad_login();//管理员登录函数
		break;
	case '4':service_manual();//使用手册
		break;
	case '5':exit(0);
		break;
	default:
		break;
	}
}

void service_manual(void)//主菜单用户使用手册
{ 
	char flag;
	system("cls");
	delay(100);
	printf("根据选项提示进入各个系统\n！");
	printf("该体育馆管理项目已有注册好的四个用户账号和已经储存好的三个不同场馆的管理员账号，\n用户账号可以在管理员系统内进行查看，所以此处只给出一个用户账号和所有管理员的账号：");
	printf("\n用户账号：11111111    用户密码：11111111（都是8个1）");
	printf("\n管理员账号：11111111    管理员密码：11111111（都是8个1）");
	printf("\n管理员账号：22222222    管理员密码：22222222（都是8个2）");
	printf("\n管理员账号：33333333    管理员密码：33333333（都是8个3）");
	printf("\n为了照顾用户体验，大部分输入时都不需要输入回车（字符串输入除外）");
	
	delay(500);
	printf("\n请按任意键退出用户手册，返回主界面:");
	if (flag = getch() != NULL)
	{
		printf("%c", flag);
		printf("\n正在返回主界面······");
		delay(500);
		menu();
	}
}

void _return(void)//按任意键返回主菜单界面函数
{
	char flag;
	printf("按任意键返回主界面：");
	if (flag = getch() != NULL)
	{
		printf("%c", flag);
		printf("\n正在返回······");
		delay(500);
		menu();
	}
}

		