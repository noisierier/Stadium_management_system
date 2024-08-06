#include "info_management.h"
#include<stdio.h>
#include"Administrator.h"
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include"delay.h"
#include <math.h>
#include"menu.h"
#include"user.h"

char uesr_id_[30];
char ad_id_[30];	
extern const char* venue_names[] ;

																											
void user_login(void)//用户登录
{
	Node* head = (Node*)malloc(sizeof(Node));//创建头结点
	head->next = NULL;
	loadList(head, "Customer.txt");
	system("cls");
	char free_key;
	printf("\n请输入您的的用户账号（不得小于6字符，不得大于10字符）:");
	char search[30];
	scanf("%s", search);
	while (!determine_id_passward(search))
	{
		printf("\n格式不对，请重新输入用户账号：");
		scanf("%s", search);
	}
	Node* move = head;
	while (move->next != NULL)
	{
		
		if (strcmp(move->next->cus.id, search) == 0)
		{
			printf("\n成功匹配到您的账号！");
			printf("\n\n请输入您的的用户密码（不得小于6字符，不得大于10字符）:");
			char search_p[30];
			scanf("%s", search_p);
			while (!determine_id_passward(search_p))
			{
				printf("\n格式不对，请重新输入您的用户密码：");
				scanf("%s", search_p);
			}
			if (strcmp(move->next->cus.cus_password, search_p) == 0)
			{
				printf("\n密码输入正确，已成功进入系统，请稍后······");
				strcpy(uesr_id_, search);
				delay(500);
				user_menu();
			}
			else
			{
				printf("\n密码输入错误，请按任意键返回上一级界面：");
				free_key = getch();
				printf("%c", free_key);
				printf("\n正在返回······");
				delay(500);
				menu();
			}
		}
		move = move->next;
	}
	printf("\n未找到用户信息,请按任意键返回上一级界面：");
	free_key = getch();
	printf("%c", free_key);
	printf("\n正在返回······");
	delay(500);
	menu();
}

void user_register(void)//用户注册函数
{
	Node* head = (Node*)malloc(sizeof(Node));//创建头结点
	head->next = NULL;
	loadList(head, "Customer.txt");
	Node* fresh = (Node*)malloc(sizeof(Node));
	fresh->next = NULL;
	system("cls");
	char free_key;
	printf("请根据提示，输入需要录入的用户信息：");

	printf("\n请输入需要注册的用户账号（不得小于6字符，不得大于10字符）:");//fflush(stdin);
	gets_s(fresh->cus.id, 30);
	while (!determine_id_passward(fresh->cus.id))
	{
		printf("\n格式不对，请重新输入用户账号：");
		gets_s(fresh->cus.id, 30);
	}

	Node* move = head;
	while (move->next != NULL)
	{
		if (strcmp(move->next->cus.id, fresh->cus.id) == 0)
		{
			printf("\n库中已经有此账号，请重新输入用户账号：");
			fflush(stdin);
			gets_s(fresh->cus.id, 30);
			while (!determine_id_passward(fresh->cus.id))
			{
				printf("\n格式不对，请重新输入用户账号：");
				fflush(stdin);
				gets_s(fresh->cus.id, 30);
			}
			move = head;
		}
		else
		{
			move = move->next;
		}
	}

	fresh->cus.appointmentNum[0] = '0'; fresh->cus.appointmentNum[1] = '\0'; fresh->cus.appointmentNum[2] = '\0'; fresh->cus.appointmentNum[3] = '\0'; fresh->cus.appointmentNum[4] = '\0';
	fresh->cus.book_num[0] = 0;fresh->cus.book_num[1] = 0;fresh->cus.book_num[2] = 0;fresh->cus.book_num[3] = 0;fresh->cus.book_num[4] = 0;fresh->cus.book_num[5] = 0;


	printf("\n请输入用户密码（不得小于6字符，不得大于10字符）：");
	gets_s(fresh->cus.cus_password, 30);
	while (!determine_id_passward(fresh->cus.cus_password))
	{
		printf("\n格式不对，请重新输入用户密码：");
		gets_s(fresh->cus.cus_password, 30);
	}

	printf("\n请输入用户姓名（不得小于2字符，不得大于20字符）:");
	gets_s(fresh->cus.name, 20);
	while (!determine_name(fresh->cus.name))
	{
		printf("\n格式不对，请重新输入用户姓名：");
		gets_s(fresh->cus.name, 20);
	}

	printf("\n请输入用户性别（'1'代表男，'0'代表女)：");
	char gender;
	gender = getchar();
	clearInputBuffer();
	while (gender != '0' && gender != '1')
	{
		printf("\n请输入'0'或'1'：");
		gender = getchar();
		clearInputBuffer();
	}
	if (gender == '0')
	{
		fresh->cus.gender[0] = '0';
		for (int i = 1; i < 10; i++)
		{
			fresh->cus.gender[i] = '\0';
		}
	}
	else if (gender == '1')
	{
		fresh->cus.gender[0] = '1';
		for (int i = 1; i < 10; i++)
		{
			fresh->cus.gender[i] = '\0';
		}
	}


	printf("\n请输入用户手机号（11位数字）：");
	gets_s(fresh->cus.phone, 30);
	while (!determine_phone(fresh->cus.phone))
	{
		printf("\n格式不对，请重新输入用户手机号：");
		gets_s(fresh->cus.phone, 30);
	}
	

	printf("\n请输入用户年龄:");
	gets_s(fresh->cus.age, 5);
	while (!determine_age(fresh->cus.age))
	{
		printf("\n格式不对，请重新输入用户年龄：");
		gets_s(fresh->cus.age, 20);
	}

	for (int i = 0; i < 30; i++)
	{
		fresh->cus.cus_balance[i] = '\0';//新用户注册，余额等于0
	}
	fresh->cus.cus_balance[0] = '0';
	

	printf("\n请输入用户住址:");
	scanf("%s", &fresh->cus.address);

	printf("\n请输入用户邮箱:");
	clearInputBuffer();
	gets_s(fresh->cus.email, 30);
	while (!determine_email(fresh->cus.email))
	{
		printf("\n格式不对，请重新输入用户邮箱：");
		gets_s(fresh->cus.email, 30);
	}


	for (int i = 0; i < 5; i++)
	{
		fresh->cus.noShowCount[i] = '\0';//新用户注册，爽约次数等于0
	}
	fresh->cus.noShowCount[0] = '0';

	move = head;
	while (move->next != NULL)
	{
		move = move->next;
	}
	move->next = fresh;
	saveList(head,"Customer.txt");
	printf("\n成功注册用户信息，按任意键返回上一级界面：");
	free_key = getch();
	printf("%c", free_key);
	delay(500);
	menu();

}

void user_information_management_system_menu(void)//管理员版本用户信息管理系统菜单界面
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" ______________体育馆用户信息管理系统______________\n");
	printf(" __________________________________________管理员版\n");
	printf("\t\t 请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.录入用户信息                                |\n");
	printf("|                                                  |\n");
	printf("|    2.打印用户信息                                |\n");
	printf("|                                                  |\n");
	printf("|    3.统计用户人数                                |\n");
	printf("|                                                  |\n");
	printf("|    4.查找用户信息                                |\n");
	printf("|                                                  |\n");
	printf("|    5.修改用户信息                                |\n");
	printf("|                                                  |\n");
	printf("|    6.删除用户信息                                |\n");
	printf("|                                                  |\n");
	printf("|    7.返回信息管理界面                            |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	management_system_choose();
}

void management_system_choose(void) //管理员版本用户信息管理系统选择函数
{
	Node* head = (Node*)malloc(sizeof(Node));//创建头结点
	head->next = NULL;
	loadList(head, "Customer.txt");
	char flag;
	printf("请输入您的选项：");
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7')
	{
		printf("\n请根据提示，输入'1'或'2'或'3'或'4'或'5'或'6'或'7'：");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case '1': additem(head); //录入用户信息
		break;
	case '2': showallitem(head); //打印用户信息
		break;
	case '3': count(head);//统计用户人数
		break;
	case '4': seatchitem(head);//查找用户信息
		break;
	case '5':modify_menu_pre(head);//修改用户信息		
		break;
	case '6': deletecustomer(head);//删除用户信息		
		break;
	case '7': system("cls"); //返回信息管理界面		
		printf("正在返回······");
		delay(500);
		administerator_personal_information();
		break;
	default:
		break;
	}
}

void additem(Node* head) //管理员添加用户信息
{
	Node* fresh = (Node*)malloc(sizeof(Node));
	fresh->next = NULL;
	system("cls");
	char free_key;
	printf("请根据提示，输入需要录入的用户信息：");

	printf("\n请输入用户账号（不得小于6字符，不得大于10字符）:");											//
	clearInputBuffer();
	gets_s(fresh->cus.id, 30);
	while (!determine_id_passward(fresh->cus.id))
	{
		printf("\n格式不对，请重新输入用户账号：");
		gets_s(fresh->cus.id, 30);
	}

	Node* move = head;
	while (move->next != NULL)
	{
		if (strcmp(move->next->cus.id, fresh->cus.id) == 0)
		{
			printf("\n库中已经有此账号，请重新输入用户账号：");
			fflush(stdin);
			gets_s(fresh->cus.id, 30);
			while (!determine_id_passward(fresh->cus.id))
			{
				printf("\n格式不对，请重新输入用户账号：");
				fflush(stdin);
				gets_s(fresh->cus.id, 30);
			}
			move = head;
		}
		else
		{
			move = move->next;
		}
	}

	fresh->cus.appointmentNum[0] = '0'; fresh->cus.appointmentNum[1] = '\0'; fresh->cus.appointmentNum[2] = '\0'; fresh->cus.appointmentNum[3] = '\0'; fresh->cus.appointmentNum[4] = '\0';
	fresh->cus.book_num[0] = 0; fresh->cus.book_num[1] = 0; fresh->cus.book_num[2] = 0; fresh->cus.book_num[3] = 0; fresh->cus.book_num[4] = 0; fresh->cus.book_num[5] = 0;

	printf("\n请输入用户密码（不得小于6字符，不得大于10字符）：");
	gets_s(fresh->cus.cus_password, 30);
	while (!determine_id_passward(fresh->cus.cus_password))
	{
		printf("\n格式不对，请重新输入用户密码：");
		gets_s(fresh->cus.cus_password, 30);
	}

	printf("\n请输入用户姓名（不得小于2字符，不得大于20字符）:");
	gets_s(fresh->cus.name, 20);
	while (!determine_name(fresh->cus.name))
	{
		printf("\n格式不对，请重新输入用户姓名：");
		gets_s(fresh->cus.name, 20);
	}

	printf("\n请输入用户性别（'1'代表男，'0'代表女)：");
	char gender;
	gender = getchar();
	clearInputBuffer();
	while (gender != '0' && gender != '1')
	{
		printf("\n请输入'0'或'1'：");
		gender = getchar();
		clearInputBuffer();
	}
	if (gender == '0')
	{
		fresh->cus.gender[0] = '0';
		for (int i = 1; i < 10; i++)
		{
			fresh->cus.gender[i] = '\0';
		}
	}
	else if (gender == '1')
	{
		fresh->cus.gender[0] = '1';
		for (int i = 1; i < 10; i++)
		{
			fresh->cus.gender[i] = '\0';
		}
	}

	printf("\n请输入用户手机号（11位数字）：");
	gets_s(fresh->cus.phone, 30);
	while (!determine_phone(fresh->cus.phone))
	{
		printf("\n格式不对，请重新输入用户手机号：");
		gets_s(fresh->cus.phone, 30);
	}

	printf("\n请输入用户年龄:");
	gets_s(fresh->cus.age, 5);
	while (!determine_age(fresh->cus.age))
	{
		printf("\n格式不对，请重新输入用户年龄：");
		gets_s(fresh->cus.age, 20);
	}

	printf("\n请输入用户余额(小写数字，两位小数):");
	gets_s(fresh->cus.cus_balance, 30);
	while ((!is_valid_number(fresh->cus.cus_balance)) || (!(str_to_double(fresh->cus.cus_balance) >= 0)))
	{
		printf("\n格式不对，请重新输入用户余额：");
		gets_s(fresh->cus.cus_balance, 30);
	}

	printf("\n请输入用户住址:");
	scanf("%s", &fresh->cus.address);

	printf("\n请输入用户邮箱:");
	clearInputBuffer();
	gets_s(fresh->cus.email, 30);
	while (!determine_email(fresh->cus.email))
	{
		printf("\n格式不对，请重新输入用户邮箱：");
		gets_s(fresh->cus.email, 30);
	}

	printf("\n请输入用户爽约次数（小写数字）:");
	gets_s(fresh->cus.noShowCount, 5);
	int noShowCount_key = atoi(fresh->cus.noShowCount);
	while (strlen(fresh->cus.noShowCount) == 0 || !all_digits(fresh->cus.noShowCount) || noShowCount_key < 0 || noShowCount_key > 7)
	{
		printf("\n格式不对或者超出爽约限制，请重新输入用户爽约次数：");
		gets_s(fresh->cus.noShowCount, 5);
		noShowCount_key = atoi(fresh->cus.noShowCount);
	}

	move = head;
	while (move->next != NULL)
	{
		move = move->next;
	}
	move->next = fresh;
	saveList(head, "Customer.txt");	
	printf("\n成功添加用户信息，按任意键返回上一级界面：");
	free_key = getch();
	printf("%c", free_key);
	delay(500);
	user_information_management_system_menu();
}

void showallitem(Node* head)//打印所有用户的信息
{
	system("cls");
	char free_key;
	Node* move = head->next;
	while (move != NULL) 
	{
		printf("账号：%s \n密码：%s \n姓名：%s \n性别（0代表女，1代表男）：%d  \n年龄：%s \n手机号：%s \n余额：%.2f \n住址：%s \n邮箱：%s \n爽约次数:%d  \n总预定次数：%d", move->cus.id, move->cus.cus_password, move->cus.name, atoi(move->cus.gender), move->cus.age, move->cus.phone, str_to_double(move->cus.cus_balance), move->cus.address, move->cus.email, atoi(move->cus.noShowCount), atoi(move->cus.appointmentNum));
		for (int i = 0; i < 6; i++)
		{
			printf("\n%s 预约次数: %d", venue_names[i], move->cus.book_num[i]);
		}
		printf("\n\n\n");
		move = move->next;
	}

	printf("\n用户信息打印完毕，按任意键返回上一级界面：");
	free_key = getch();
	printf("%c", free_key);
	delay(500);
	user_information_management_system_menu();
}

void count(Node* head) //统计所有用户的人数
{
	system("cls");
	char free_key;
	int count = 0;
	Node* move = head->next;
	while (move != NULL) 
	{
		count++;
		move = move->next;
	}
	printf("用户的总人数为:%d\n", count);
	printf("\n用户人数统计完毕，按任意键返回上一级界面：");
	free_key = getch();
	printf("%c", free_key);
	delay(500);
	user_information_management_system_menu();
}

void seatchitem(Node* head)//查找用户信息
{
	system("cls");
	char free_key;
	printf("\n请输入需要查询的用户账号（不得小于6字符，不得大于10字符）:");
	char search[30];
	scanf("%s", search);
	while (!determine_id_passward(search))
	{
		printf("\n格式不对，请重新输入需要查询的用户账号：");
		scanf("%s", search);
	}
	Node* move = head;
	while (move->next != NULL) 
	{
		if (strcmp(move->next->cus.id, search) == 0) 
		{
			printf("账号：%s \n密码：%s \n姓名：%s \n性别（0代表女，1代表男）：%d\n年龄：%s\n手机号：%s\n账号余额：%.2f\n住址：%s\n电子邮箱：%s\n爽约次数：%d \n", move->next->cus.id, move->next->cus.cus_password, move->next->cus.name, atoi(move->next->cus.gender), move->next->cus.age, move->next->cus.phone, str_to_double(move->next->cus.cus_balance), move->next->cus.address, move->next->cus.email, atoi(move->next->cus.noShowCount));
			printf("已经打印完毕，请按任意键返回上一级界面：");
			free_key = getch();
			printf("%c",free_key);
			printf("\n正在返回······");
			delay(500);
			user_information_management_system_menu();
		}
		move = move->next;
	}
	printf("\n未找到用户信息,请按任意键返回上一级界面：");
	free_key = getch();
	printf("%c", free_key);
	printf("\n正在返回······");
	delay(500);
	user_information_management_system_menu();
}

void modify_menu_pre(Node* head)//修改用户信息界面_判断用户输入账号
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" ______________体育馆用户信息管理系统______________\n");
	printf(" __________________________________________管理员版\n");
	printf("\t\t 请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.输入需要修改的用户账号                      |\n");
	printf("|                                                  |\n");
	printf("|    2.使用手册                                    |\n");
	printf("|                                                  |\n");
	printf("|    3.返回上一级界面                              |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	modify_choose_pre(head);//pre版本信息修改选择
}

void modify_choose_pre(Node* head)//pre版本信息修改选择————负责判断用户账号的存在性
{
	Node* move = head;
	char key, free_key;
	printf("请根据您需要选择的信息，选择相关的选项：");
	char flag;
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
	case '1':
		system("cls");
		printf("请先输入用户账号，然后输入您的选项\n");
		printf("\n请输入需要修改的用户账号（不得小于6字符，不得大于10字符）:");
		char search[30];
		scanf("%s", search);
		while (!determine_id_passward(search))
		{
			printf("\n格式不对，退出修改系统，还是继续输入用户账号？");
			printf("\n退出修改系统请按'P',继续输入用户账号请按'1'：");
			key = getch();
			printf("%c", key);
			while (key != '1' && key != 'p' && key != 'P')
			{
				printf("\n请输入'1'或'P': ");
				key = getch();
				printf("%c", key);
				delay(100);
			}
			switch (key)
			{
			case'p':printf("\n正在返回······");
				delay(500);
				modify_menu_pre(head);
				break;
			case'P':printf("\n正在返回······");
				delay(500);
				modify_menu_pre(head);
				break;
			case'1':
				break;
			default:
				break;
			}
			printf("\n请输入需要修改信息的用户账号（不得小于6字符，不得大于10字符）：");
			scanf("%s", search);
		}
		while (strcmp(move->next->cus.id, search) != 0)
		{
			if (move->next == NULL)
			{
				printf("\n库中没有您的账号,请按任意键退出修改系统：");
				free_key = getch();
				printf("%c", free_key);
				delay(500);
				modify_menu_pre(head);
			}
			move = move->next;
		}
		system("cls");
		printf("已找到用户账号，正在为您跳转至用户详细信息修改界面，请稍后······");
		delay(500);
		modify_choose_real(head, search);
		break;
	case '2':system("cls");
		printf("打印修改用户信息使用手册");
		printf("\n按任意键返回修改系统：");
		free_key = getch();
		printf("%c", free_key);
		delay(500);
		modify_menu_pre(head);
		break;
	case '3':system("cls");
		printf("正在返回，请稍后······");
		delay(500);
		user_information_management_system_menu();
		break;
	default:
		break;
	}
}

void modify_menu_real(char* id)//已有用户账号
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" ______________体育馆用户信息管理系统______________\n");
	printf(" __________________________________________管理员版\n");
	printf(" 当前正在修改的用户账号：%s\n",id);
	printf(" __________________________________________________\n");
	printf("\t\t 请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.修改用户密码                                |\n");
	printf("|                                                  |\n");
	printf("|    2.修改用户姓名                                |\n");
	printf("|                                                  |\n");
	printf("|    3.修改用户年龄                                |\n");
	printf("|                                                  |\n");
	printf("|    4.修改用户余额                                |\n");
	printf("|                                                  |\n");
	printf("|    5.修改用户住址                                |\n");
	printf("|                                                  |\n");
	printf("|    6.修改用户邮箱                                |\n");
	printf("|                                                  |\n");
	printf("|    7.修改用户爽约次数                            |\n");
	printf("|                                                  |\n");
	printf("|    8.修改用户性别                                |\n");
	printf("|                                                  |\n");
	printf("|    9.修改用户手机号                              |\n");
	printf("|                                                  |\n");
	printf("|    x.返回信息修改界面                            |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
}

void modify_choose_real(Node* head, char* id)//已经判定用户信息存在，进入用户信息详细修改界面
{
	Node* move = head;
	while (strcmp(move->cus.id, id) != 0)
	{
		move = move->next;
	}
	while (1)
	{
		modify_menu_real(id);//显示选择界面
		printf("请根据您需要选择的信息，选择相关的选项：");
		char flag;
		char age[30];
		flag = getch();
		printf("%c", flag);
		delay(100);
		while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7' && flag != '8' && flag != '9' && flag != 'x'&&flag!='X')
		{
			printf("\n请根据提示，输入'1'或'2'或'3'或'4'或'5'或'6'或'7'或'8'或'9'或'x'：");
			flag = getch();
			printf("%c", flag);
			delay(100);
		}
		switch (flag)
		{
		case '1':
			system("cls");
			printf("\n请输入用户密码（不得小于6字符，不得大于10字符）：");
			clearInputBuffer();
			gets_s(move->cus.cus_password, 30);
			while (!determine_id_passward(move->cus.cus_password))
			{
				printf("\n格式不对，请重新输入用户密码：");
				gets_s(move->cus.cus_password, 30);
			}
			return_modify_choose_real(head,id);

			break;
		case '2':
			system("cls");
			printf("\n请输入用户姓名（不得小于2字符，不得大于20字符）:");
			gets_s(move->cus.name, 20);
			while (!determine_name(move->cus.name))
			{
				printf("\n格式不对，请重新输入用户姓名：");
				gets_s(move->cus.name, 20);
			}
			return_modify_choose_real(head, id);

			break;
		case '3':
			system("cls");
			printf("\n请输入用户年龄:");
			scanf("%s",age);
			while (!determine_age(age))
			{
				printf("\n格式不对，请重新输入用户年龄：");
				scanf("%s", age);
			}
			strcpy(move->cus.age,age);
			return_modify_choose_real(head, id);

			break;
		case '4':
			system("cls");
			printf("\n请输入用户余额(小写数字，两位小数):"); 
			clearInputBuffer();
			gets_s(move->cus.cus_balance, 30);
			while ((!is_valid_number(move->cus.cus_balance))|| !(str_to_double(move->cus.cus_balance)>=0))
			{
				printf("\n格式不对，请重新输入用户余额：");
				gets_s(move->cus.cus_balance, 30);
			}
			return_modify_choose_real(head, id);

			break;
		case '5':
			system("cls");
			printf("\n请输入用户住址:");
			scanf("%s", move->cus.address);
			return_modify_choose_real(head, id);

			break;
		case '6':
			system("cls");
			printf("\n请输入用户邮箱:");																				
			clearInputBuffer();
			gets_s(move->cus.email, 30);
			while (!determine_email(move->cus.email))
			{
				printf("\n格式不对，请重新输入用户邮箱：");
				gets_s(move->cus.email, 30);
			}
			return_modify_choose_real(head, id);

			break;
		case'7':

			system("cls");
			printf("\n请输入用户爽约次数（小写数字）:");																	
			gets_s(move->cus.noShowCount, 5);
			int noShowCount_key = atoi(move->cus.noShowCount);
			while (strlen(move->cus.noShowCount) == 0 || !all_digits(move->cus.noShowCount) || noShowCount_key < 0 || noShowCount_key > 7)
			{
				printf("\n格式不对或者超出爽约限制，请重新输入用户爽约次数：");
				gets_s(move->cus.noShowCount, 5);
				noShowCount_key = atoi(move->cus.noShowCount);
			}
			return_modify_choose_real(head, id);

			break;

		case'8:':
			system("cls");
			printf("\n请输入用户性别（'1'代表男，'0'代表女)：");
			char gender;
			gender = getchar();
			clearInputBuffer();
			while (gender != '0' && gender != '1')
			{
				printf("\n请输入'0'或'1'：");
				gender = getchar();
				clearInputBuffer();
			}
			if (gender == '0')
			{
				move->cus.gender[0] = '0';
				for (int i = 1; i < 10; i++)
				{
					move->cus.gender[i] = '\0';
				}
			}
			else if (gender == '1')
			{
				move->cus.gender[0] = '1';
				for (int i = 1; i < 10; i++)
				{
					move->cus.gender[i] = '\0';
				}
			}
			break;
		
		case'9':
			system("cls");
			printf("\n请输入用户手机号（11位数字）：");
			gets_s(move->cus.phone, 30);
			while (!determine_phone(move->cus.phone))
			{
				printf("\n格式不对，请重新输入用户手机号：");
				gets_s(move->cus.phone, 30);
			}
			break;


		case 'x': system("cls"); //返回信息管理界面		
			printf("正在返回······");
			delay(500);
			modify_menu_pre(head);
			break;
	
		case 'X': system("cls"); //返回信息管理界面		
			printf("正在返回······");
			delay(500);
			modify_menu_pre(head);
			break;
		default:
			break;
		}
	}
}

void return_modify_choose_real(Node* head, char* id)//修改信息完毕，返回界面
{
	system("cls");
	printf("信息修改完毕，正在返回修改选择界面，请稍后······");
	delay(500);
	saveList(head, "Customer.txt");
	modify_choose_real(head, id);
}

void deletecustomer(Node* head) //删除用户信息
{
	char key, free_key;
	Node* move = head;
	system("cls");
	printf("请输入需要删除用户信息的用户账号（不得小于6字符，不得大于10字符）：");
	char search[30];
	scanf("%s", search);
	while (!determine_id_passward(search))
	{
		printf("\n格式不对，退出删除系统，还是继续输入用户账号？");
		printf("退出删除系统请按'P',继续输入用户账号请按'1'：\n");
		key = getch();
		printf("%c", key);
		while (key != '1' && key != 'p' && key != 'P')
		{
			printf("\n请输入'1'或'P': ");
			key = getch();
			printf("%c", key);
			delay(100);
		}
		switch (key)
		{
		case 'p':
			printf("\n正在返回······");
			delay(500);
			user_information_management_system_menu();
			break;
		case 'P':
			printf("\n正在返回······");
			delay(500);
			user_information_management_system_menu();
			break;
		case '1':
			break;
		default:
			break;
		}
		printf("\n请输入需要删除信息的用户账号（不得小于6字符，不得大于10字符）：");
		scanf_s("%s", search);
	}
	
	while (move->next != NULL && strcmp(move->next->cus.id, search) != 0)
	{
		move = move->next;
	}
	if (move->next == NULL)
	{
		printf("\n库中没有您的账号,请按任意键退出删除系统：");
		free_key = getch();
		printf("%c", free_key);
		delay(500);
		user_information_management_system_menu();
	}
	else
	{
		printf("已找到用户账号，正在为您删除用户信息，请稍后······");
		Node* tmp = move->next;
		move->next = tmp->next;
		free(tmp);
		saveList(head, "Customer.txt");
		delay(200);
		printf("\n成功删除用户信息！正在返回上一级界面······");

		delay(300);
		user_information_management_system_menu();
	}
}

void saveList(Node* head, const char* filename)//保存链表至文件中
{
	FILE* file = fopen(filename, "wb");
	if (file == NULL)
	{
		printf("无法打开文件 %s\n", filename);
		return;
	}
	Node* p = head->next;
	while (p != NULL)
	{
		fwrite(&p->cus, sizeof(Customer), 1, file);
		p = p->next;
	}
	fclose(file);
	saveListToFile(head, "customerInfo.txt");
}

void saveList_ad(Node* head, const char* filename)//保存链表至文件中
{
	FILE* file = fopen(filename, "wb");
	if (file == NULL)
	{
		printf("无法打开文件 %s\n", filename);
		return;
	}
	Node* p = head->next;
	while (p != NULL)
	{
		fwrite(&p->cus, sizeof(Customer), 1, file);
		p = p->next;
	}
	fclose(file);
}

void loadList(Node* head, const char* filename)//从文件中读取链表
{
	FILE* file = fopen(filename, "rb");
	if (file == NULL)
	{
		printf("无法打开文件 %s\n", filename);
		return;
	}
	Node* p = head;
	Customer cus;
	while (fread(&cus, sizeof(Customer), 1, file) == 1)
	{
		Node* newNode = (Node*)malloc(sizeof(Node));
		newNode->cus = cus;
		newNode->next = NULL;
		p->next = newNode;
		p = newNode;
	}
	fclose(file);
}

void user_modify_menu(void)//用户个人登录后的信息修改界面
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" _______________用户个人信息修改系统_______________\n");
	printf(" __________________________________________用户版本\n");
	printf(" 当前正在修改的用户账号：%s\n", uesr_id_);		
	printf(" __________________________________________________\n");
	printf("\t\t 请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.修改用户密码                                |\n");
	printf("|                                                  |\n");
	printf("|    2.修改用户姓名                                |\n");
	printf("|                                                  |\n");
	printf("|    3.修改用户年龄                                |\n");
	printf("|                                                  |\n");
	printf("|    4.修改用户住址                                |\n");
	printf("|                                                  |\n");
	printf("|    5.修改用户邮箱                                |\n");
	printf("|                                                  |\n");
	printf("|    6.修改用户性别                                |\n");
	printf("|                                                  |\n");
	printf("|    7.修改用户手机号                              |\n");
	printf("|                                                  |\n");
	printf("|    8.返回上一级界面                              |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	user_modify_menu_choose();
}

void user_modify_menu_choose(void)//用户个人信息修改界面选择函数
{
		printf("请根据您需要选择的信息，选择相关的选项：");
		Node* head = (Node*)malloc(sizeof(Node));//创建头结点
		head->next = NULL;
		loadList(head, "Customer.txt");
		Node* move = head;
		char flag;
		char age[30];
		while (strcmp(move->cus.id, uesr_id_) != 0)
		{
			move = move->next;
		}
		flag = getch();
		printf("%c", flag);
		delay(100);
		while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7' && flag != '8')
		{
			printf("\n请根据提示，输入'1'或'2'或'3'或'4'或'5'或'6'或'7'或'8'：");
			flag = getch();
			printf("%c", flag);
			delay(100);
		}
		switch (flag)
		{
		case '1':
	
			system("cls");
			printf("\n请输入修改后的用户密码（不得小于6字符，不得大于10字符）：");
			clearInputBuffer();
			gets_s(move->cus.cus_password, 30);
			while (!determine_id_passward(move->cus.cus_password))
			{
				printf("\n格式不对，请重新输入用户密码：");
				gets_s(move->cus.cus_password, 30);
			}
			printf("修改完成，即将返回上一级界面。");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();

	
			break;
		case '2':
	
			system("cls");
			printf("\n请输入修改后的用户姓名（不得小于2字符，不得大于20字符）:");
			gets_s(move->cus.name, 20);
			while (!determine_name(move->cus.name))
			{
				printf("\n格式不对，请重新输入用户姓名：");
				gets_s(move->cus.name, 20);
			}
			printf("修改完成，即将返回上一级界面。");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();
			
	
			break;
		case '3':
	
			system("cls");
			printf("\n请输入修改后的用户年龄:");
			scanf("%s", age);
			while (!determine_age(age))
			{
				printf("\n格式不对，请重新输入用户年龄：");
				scanf("%s", age);
			}
			strcpy(move->cus.age, age);
			printf("修改完成，即将返回上一级界面。");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();
			
	
			break;
		
		case '4':
	
			system("cls");
			printf("\n请输入修改后的用户住址:");
			scanf("%s", move->cus.address);
			printf("修改完成，即将返回上一级界面。");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();
			
	
			break;
		case '5':
	
			system("cls");
			printf("\n请输入修改后的用户邮箱:");
			clearInputBuffer();
			gets_s(move->cus.email, 30);
			while (!determine_email(move->cus.email))
			{
				printf("\n格式不对，请重新输入用户邮箱：");
				
				gets_s(move->cus.email, 30);
			}
			printf("修改完成，即将返回上一级界面。");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();
			
	
			break;
		
		case'6':system("cls");
			printf("\n请输入修改后的用户性别（'1'代表男，'0'代表女)：");
			char gender;
			gender = getchar();
			clearInputBuffer();
			while (gender != '0' && gender != '1')
			{
				printf("\n请输入'0'或'1'：");
				gender = getchar();
				clearInputBuffer();
			}
			if (gender == '0')
			{
				move->cus.gender[0] = '0';
				for (int i = 1; i < 10; i++)
				{
					move->cus.gender[i] = '\0';
				}
			}
			else if (gender == '1')
			{
				move->cus.gender[0] = '1';
				for (int i = 1; i < 10; i++)
				{
					move->cus.gender[i] = '\0';
				}
			}
			printf("修改完成，即将返回上一级界面。");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();
			break;
		
		
		case '7':system("cls");
			printf("\n请输入修改后的用户手机号（11位数字）：");
			gets_s(move->cus.phone, 30);
			while (!determine_phone(move->cus.phone))
			{
				printf("\n格式不对，请重新输入用户手机号：");
				gets_s(move->cus.phone, 30);
			}
			printf("修改完成，即将返回上一级界面。");
			saveList(head, "Customer.txt");
			delay(500);
			user_modify_menu();
			break;



		case '8': system("cls"); //返回信息修改前界面		
			printf("正在返回······");
			delay(500);
			user_personal_information();
			
			break;
		default:
			break;
		}
}

void ad_login(void)//管理员登录
{
	Node* head = (Node*)malloc(sizeof(Node));//创建头结点
	head->next = NULL;
	loadList(head, "administrator.txt");
	system("cls");
	char free_key;
	printf("\n请输入您的的管理员账号（不得小于6字符，不得大于10字符）:");
	char search[30];
	scanf("%s", search);
	while (!determine_id_passward(search))
	{
		printf("\n格式不对，请重新输入管理员账号：");
		scanf("%s", search);
	}
	Node* move = head;
	while (move->next != NULL)
	{

		if (strcmp(move->next->cus.id, search) == 0)
		{
			printf("\n成功匹配到您的账号！");
			printf("\n\n请输入您的的管理员密码（不得小于6字符，不得大于10字符）:");
			char search_p[30];
			scanf("%s", search_p);
			while (!determine_id_passward(search_p))
			{
				printf("\n格式不对，请重新输入您的管理员密码：");
				scanf("%s", search_p);
			}
			if (strcmp(move->next->cus.cus_password, search_p) == 0)
			{
				printf("\n密码输入正确，已成功进入系统，请稍后······");
				strcpy(ad_id_, search);
				delay(500);
				administrator_menu();
			}
			else
			{
				printf("\n密码输入错误，请按任意键返回上一级界面：");
				free_key = getch();
				printf("%c", free_key);
				printf("\n正在返回······");
				delay(500);
				menu();
			}
		}
		move = move->next;
	}
	printf("\n未找到管理员信息,请按任意键返回上一级界面：");
	free_key = getch();
	printf("%c", free_key);
	printf("\n正在返回······");
	delay(500);
	menu();
}

void ad_modify_menu(void)//管理员个人登录后的信息修改界面
{
	system("cls");
	printf(" __________________________________________________\n");
	printf(" ______________体育馆个人信息管理系统______________\n");
	printf(" __________________________________________管理员版\n");
	printf(" 当前正在修改的管理员账号：%s\n", ad_id_);
	printf(" __________________________________________________\n");
	printf("\t\t 请选择您的需求\t\t\t\n");
	printf(" __________________________________________________\n");
	printf("|                                                  |\n");
	printf("|    1.修改管理员密码                              |\n");
	printf("|                                                  |\n");
	printf("|    2.修改管理员姓名                              |\n");
	printf("|                                                  |\n");
	printf("|    3.修改管理员年龄                              |\n");
	printf("|                                                  |\n");
	printf("|    4.修改管理员住址                              |\n");
	printf("|                                                  |\n");
	printf("|    5.修改管理员邮箱                              |\n");
	printf("|                                                  |\n");
	printf("|    6.修改管理员手机号                            |\n");
	printf("|                                                  |\n");
	printf("|    7.返回上一级界面                              |\n");
	printf("|                                                  |\n");
	printf("|__________________________________________________|\n");
	ad_modify_menu_choose();
}

void ad_modify_menu_choose(void)//管理员个人信息修改界面选择函数
{
	printf("请根据您需要选择的信息，选择相关的选项：");
	Node* head = (Node*)malloc(sizeof(Node));//创建头结点
	head->next = NULL;
	loadList(head, "administrator.txt");
	Node* move = head;
	char flag;
	char age[30];
	while (strcmp(move->cus.id, ad_id_) != 0)
	{
		move = move->next;
	}
	flag = getch();
	printf("%c", flag);
	delay(100);
	while (flag != '1' && flag != '2' && flag != '3' && flag != '4' && flag != '5' && flag != '6' && flag != '7' )
	{
		printf("\n请根据提示，输入'1'或'2'或'3'或'4'或'5'或'6'或'7'：");
		flag = getch();
		printf("%c", flag);
		delay(100);
	}
	switch (flag)
	{
	case '1':

		system("cls");
		printf("\n请输入修改后的管理员密码（不得小于6字符，不得大于10字符）：");
		clearInputBuffer();
		gets_s(move->cus.cus_password, 30);
		while (!determine_id_passward(move->cus.cus_password))
		{
			printf("\n格式不对，请重新输入管理员密码：");
			gets_s(move->cus.cus_password, 30);
		}
		printf("修改完成，即将返回上一级界面。");
		saveList_ad(head, "administrator.txt");
		delay(500);
		ad_modify_menu();


		break;
	case '2':

		system("cls");
		printf("\n请输入修改后的管理员姓名（不得小于2字符，不得大于20字符）:");
		gets_s(move->cus.name, 20);
		while (!determine_name(move->cus.name))
		{
			printf("\n格式不对，请重新输入管理员姓名：");
			gets_s(move->cus.name, 20);
		}
		printf("修改完成，即将返回上一级界面。");
		saveList_ad(head, "administrator.txt");
		delay(500);
		ad_modify_menu();


		break;
	case '3':

		system("cls");
		printf("\n请输入修改后的管理员年龄:");
		scanf("%s", age);
		while (!determine_age(age))
		{
			printf("\n格式不对，请重新输入管理员年龄：");
			scanf("%s", age);
		}
		strcpy(move->cus.age, age);
		printf("修改完成，即将返回上一级界面。");
		saveList_ad(head, "administrator.txt");
		delay(500);
		ad_modify_menu();


		break;

	case '4':

		system("cls");
		printf("\n请输入修改后的管理员住址:");
		scanf("%s", move->cus.address);
		printf("修改完成，即将返回上一级界面。");
		saveList_ad(head, "administrator.txt");
		delay(500);
		ad_modify_menu();


		break;
	case '5':

		system("cls");
		printf("\n请输入修改后的管理员邮箱:");
		clearInputBuffer();
		gets_s(move->cus.email, 30);
		while (!determine_email(move->cus.email))
		{
			printf("\n格式输入错误，请重新输入管理员邮箱：");
			gets_s(move->cus.email, 30);
		}
		printf("修改完成，即将返回上一级界面。");
		saveList_ad(head, "administrator.txt");
		delay(500);
		ad_modify_menu();


		break;
	case'6':system("cls");
		printf("\n请输入修改后的管理员手机号（11位数字）：");
		gets_s(move->cus.phone, 30);
		while (!determine_phone(move->cus.phone))
		{
			printf("\n格式不对，请重新输入管理员手机号：");
			gets_s(move->cus.phone, 30);
		}
		printf("修改完成，即将返回上一级界面。");
		saveList_ad(head, "administrator.txt");
		delay(500);
		ad_modify_menu();
		break;


	case '7': system("cls"); //返回信息修改前界面		
		printf("正在返回······");
		delay(500);
		administerator_personal_information();

		break;
	default:
		break;
	}
}

void user_read_info(void)//用户查看个人信息
{
	Node* head = (Node*)malloc(sizeof(Node));//创建头结点
	head->next = NULL;
	loadList(head, "Customer.txt");
	Node* move = head;
	char key;
	system("cls");
	while (strcmp(move->cus.id, uesr_id_) != 0)
	{
		move = move->next;
	}
	printf("账号：%s \n密码：%s \n姓名：%s  \n性别(0代表女，1代表男)：%d \n手机号：%s \n年龄：%s\n账号余额：%.2f\n住址：%s\n电子邮箱：%s\n爽约次数：%d \n总预约次数：%d", move->cus.id, move->cus.cus_password, move->cus.name, atoi(move->cus.gender), move->cus.phone, move->cus.age, str_to_double(move->cus.cus_balance), move->cus.address, move->cus.email, atoi(move->cus.noShowCount), atoi(move->cus.appointmentNum));
	for (int i = 0; i < 6; i++)
	{
		printf("\n%s 预约次数: %d", venue_names[i], move->cus.book_num[i]);
	}
	printf("\n\n已经打印完毕，请按任意键返回上一级界面：");
	key = getch();
	printf("%c",key);
	delay(500);
	user_personal_information();
}

void ad_read_info(void)//管理员查看个人信息														
{
	Node* head = (Node*)malloc(sizeof(Node));//创建头结点
	head->next = NULL;
	loadList(head, "administrator.txt");
	Node* move = head;
	char key;
	while (strcmp(move->cus.id, ad_id_) != 0)
	{
		move = move->next;
	}
	system("cls");
	printf("账号：%s \n密码：%s \n姓名：%s \n手机号：%s \n年龄：%s\n住址：%s\n电子邮箱：%s\n", move->cus.id, move->cus.cus_password, move->cus.name, move->cus.phone, move->cus.age, move->cus.address, move->cus.email);
	if (strcmp(move->cus.id, "11111111") == 0)
	{
		printf("所属场馆：场馆 1");
	}
	if (strcmp(move->cus.id, "22222222") == 0)
	{
		printf("所属场馆：场馆 2");
	}
	if (strcmp(move->cus.id, "33333333") == 0)
	{
		printf("所属场馆：场馆 3");
	}
	printf("\n已经打印完毕，请按任意键返回上一级界面：");
	key = getch();
	printf("%c", key);
	delay(500);
	administerator_personal_information();
}

bool is_valid_number(char* str) //判断字符串数组输出的值为整数或者小数
{
	int dot_count = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
			{
				return false;
			}
		}
		else if (!isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

bool all_digits(char* str) //判断数组内存储的字符全都是数字
{
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

int count_strings(char* strings) //返回数组元素个数
{
	int count = 0;
	while (strings[count] != NULL)
	{
		count++;
	}
	return count;
}

int determine_id_passward(char* strings)//判定用户名和密码格式函数
{
		int length = strlen(strings);
		if (length < 6 || length > 10)
		{
			return 0;
		}
		for (int i = 0; i < length; i++)
		{
			if (!isalnum(strings[i]))
			{
				return 0;
			}
		}
		return 1;
}

int determine_name(char* strings)//判定用户名字格式函数
{
	int key = count_strings(strings);
	if (key <= 20 && key >= 2)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int  determine_age(char* strings)//判断用户年龄格式函数
{
	int age = atoi(strings);
	if (!all_digits(strings))
	{
		return 0;
	}
	else if (age > 150 || age < 0)
	{
		return 0;
	}
	return 1;
}

bool determine_email(char* email) //判断邮箱格式函数
{
	int at = -1;
	int dot = -1;
	int len = strlen(email);
	for (int i = 0; i < len; i++)
	{
		if (email[i] == '@')
		{
			at = i;
		}
		else if (email[i] == '.')
		{
			dot = i;
		}
	}
	if (at == -1 || dot == -1)
	{
		return false;
	}
	if (at > dot)
	{
		return false;
	}
	if (at != 3 || dot - at != 4 || len - dot != 4)
	{
		return false;
	}
	for (int i = 0; i < at; i++)
	{
		if (!isalnum(email[i]))
		{
			return false;
		}
	}
	for (int i = at + 1; i < dot; i++)
	{
		if (!isalnum(email[i]))
		{
			return false;
		}
	}
	for (int i = dot + 1; i < len; i++)
	{
		if (!isalnum(email[i]))
		{
			return false;
		}
	}
	return true;
}

bool determine_phone(char* str)
{
	int len = strlen(str);
	if (len != 11)
	{
		return false;
	}
	for (int i = 0; i < len; i++)
	{
		if (!isdigit(str[i]))
		{
			return false;
		}
	}
	return true;
}

void clearInputBuffer() //清理gets_s()留下的换行符
{
	char c;
	while ((c = getchar()) != '\n' && c != EOF);
}

double str_to_double(char* str)//将余额转化成双精度小数
{
	double num;
	sscanf(str, "%lf", &num);
	return (double)((int)(num * 100 + 0.5)) / 100;
}

void saveListToFile(Node* head, const char* filename) //将链表数据存储在数组数组文件中
{
	int numCustomers = 0;
	Node* move = head;
	FILE* file = fopen(filename, "w");
	if (file == NULL)
	{
		printf("\n文件打开失败！");
	}
	while (move->next != NULL)
	{
		move = move->next;
		fprintf(file, "%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%d,%d,%d,%d,%d,%d\n",
			move->cus.age, move->cus.id, move->cus.cus_password,
			move->cus.name, move->cus.gender,
			move->cus.phone, move->cus.email,
			move->cus.cus_balance, move->cus.address,
			move->cus.noShowCount, move->cus.appointmentNum,
			move->cus.book_num[0], move->cus.book_num[1],
			move->cus.book_num[2], move->cus.book_num[3],
			move->cus.book_num[4], move->cus.book_num[5]);
	}
	fclose(file);
}