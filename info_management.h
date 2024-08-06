#ifndef INFO_MANAGEMENT_H
#define INFO_MANAGEMENT_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Customer 
{
    char age[5];           // 年龄
    char id[30];            // 账号
    char cus_password[30];  // 密码
    char name[20];     // 姓名
    char gender[10];           //性别
    char phone[30];         //电话
    char email[30];    // 邮箱
    char cus_balance[30] ; // 余额
    char address[30];  // 住址
    char noShowCount[5];   // 爽约次数
    char appointmentNum[5]; //总预约次数
    int book_num[6];//各个场馆的预约次数
} Customer;//用户信息


typedef struct _Node
{
	Customer cus;
	struct _Node* next;
}Node;//结点信息

bool is_valid_number(char* str); //判断字符串数组输出的值为整数或者小数

bool all_digits(char* str); //判断数组内存储的字符全都是数字

int count_strings(char* strings); //返回数组元素个数

int determine_id_passward(char* strings);//判定用户名和密码格式函数

int determine_name(char* strings);//判定用户名字格式函数

int  determine_age(char* strings);//判断用户年龄格式函数

bool determine_email(char* email);//判断邮箱格式函数

void management_system_choose(void); //管理员版本用户信息管理系统选择函数

void additem(Node* head); //添加用户信息

void showallitem(Node* head);//打印所有用户的信息

void count(Node* head); //统计所有用户的人数

void seatchitem(Node* head);//查找用户信息

void modify_menu_pre(Node* head);//修改用户信息界面_判断用户输入账号

void modify_choose_pre(Node* head);//pre版本信息修改选择————负责判断用户账号的存在性

void modify_menu_real(char* id);//已有用户账号

void modify_choose_real(Node* head, char* id);//已经判定用户信息存在，进入用户信息详细修改界面

void return_modify_choose_real(Node* head, char* id);//修改信息完毕，返回界面

void deletecustomer(Node* head); //删除用户信息

void saveList(Node* head, const char* filename);//保存链表至文件中

void saveList_ad(Node* head, const char* filename);//保存链表至管理员文件中

void loadList(Node* head, const char* filename);//从文件中读取链表

void clearInputBuffer(); //清理gets_s()留下的换行符

double str_to_double(char* str);//将余额转化成双精度小数

void user_login(void);//用户登录

void user_register(void);//用户注册函数

void user_modify_menu(void);//用户个人登录后的信息修改界面

void user_modify_menu_choose(void);//用户个人信息修改界面选择函数

void ad_modify_menu_choose(void);//管理员个人信息修改界面选择函数

void ad_modify_menu(void);//用户个人登录后的信息修改界面

void user_read_info(void);//用户查看个人信息

void ad_read_info(void);//管理员查看个人信息

bool determine_phone(char* str);//判定手机号格式

void saveListToFile(Node* head, const char* filename);//将链表数据存储在数组数据文件中

#endif