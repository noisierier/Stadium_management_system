#ifndef BOOK_SITE_H
#define BOOK_SITE_H
#include"info_management.h"


struct Order
{
	char ID[20];
	char name[20];
	int age;     // 使用整数来存储年龄
	int gender;  // 使用整数来存储性别
	char orderNumber[30];     //订单编号
	char location[50];   //具体的场馆、场地、日期、时间段
};

struct order_info {
    char username[50];
    char fullName[50];
    int age;     // 使用整数来存储年龄
    int gender;  // 使用整数来存储性别
    char orderNumber[50];
    char venue[50];
    char venueNumber[50];
    char date[20];
    char time[20];
};

void book_f();//预定场地验证加进入函数

void bookCourt(Customer* customer);//预定场地

void saveOrderToFile(const char* ID, const char* name, const char* age, const char* gender, const char* orderNumber, const char* location);  //保存订单信息

void calculateDates(); //关于时间

int isInteger(const char* input);//验证整数

int authenticateUser(const char* username, Customer* customer);//匹配用户账号，存储数组信息，验证爽约次数小于三

int checkAppointmentLimit(const Customer* customer);//验证总预约次数小于三，可以正常进行预约

int authenticateUser_history(const char* username, Customer* customer);//匹配用户账号，存储数组信息，不验证爽约次数,打印用户订单使用

void showOrders(char username[], Customer* customer);//打印历史预约订单和取消预定

void showOrders_menu();//打印历史订单并进行取消预定预处理

void saveOrder();//将order数据存进文件

int readOrder();//阅读订单文档并返回总订单数量

int filter_digits(const char* input); //从字符串中过滤出数字并返回整数

void signIn_pre(void);//签到预处理

void signIn(char username[], Customer* customer);//用户签到

int calculateDateDifferenceFromToday(const char* cancellationTimeRange);//获取场馆信息，用于取消预定改变信息存入文件


#endif