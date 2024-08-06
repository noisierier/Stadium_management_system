#ifndef SITE_SEARCH_H
#define SITE_SEARCH_H

struct Date // 结构体用于存储日期信息
{
    int year;
    int month;
    int day;
};

struct DateTime
{
    int year;
    int month;
    int day;
    int hour;
};

typedef struct //场地预订信息结构体   
{ 
    int courtNum; //场地编号
    int rentRerHour;//场地每小时的租金
    char courtId[10];
    int time[7][16];   // 某一天某个时间段的预约人数
    int maxPerson; //该场地容纳的最大人数
} Court;

typedef struct
{
    int hallNum;  //场馆编号
    int NumOfCourt;  //这个场馆的场地数量
    char name[10];//场馆编号
    char hallRegion[15];//场馆所属区域
    char sportType[15];//场馆运动类型
    int minAge;//准入最小年龄限制
    int maxAge;//准入最大年龄限制
    Court courts[2];
} Hall;

Hall halls[3];

void inquiry_menu(void);//场地预定查询菜单界面

void inquiry_choose(void);//场地预定查询菜单选择函数

void inquiry_menu_user(void);//用户查看场地预定函数界面

void inquiry_choose_user(void);//用户预定查询界面选择函数

void inquiry_menu_return_user(void);//用户返回预定查询界面

void inquiry_menu_return(void);//返回场地预定查询菜单界面函数

void redcol(const char* text);//红色字符

void greencol(const char* text);//绿色字符

void lightbluecol(const char* text);//蓝色字符

void printCourtStatusByCourt(int courtNum);//通过场地来打印预定情况

void printCourtStatusByHall(int hallNum); //通过场馆来打印预定情况

void saveToFile(); //保存文件

void readFromFile();//打开文件

struct Date getCurrentDate();//获取现在的时间

struct DateTime getCurrentDateTime(); //获取时间（更加精细）

void read_site_menu_user(void);

void read_site_choose_user(void);//查询场地信息选择——用户

void read_site_menu_ad(void);//场地查询界面——管理员

void read_site_choose_ad(void);//查询场地信息选择

void findHallbyName();//通过场馆名称查询

void findHallbyRegion(); //通过场馆所属区域查询

void findHallbyType();//通过场地运动类型查询

void findAvailableCourts();// 根据日期和时间段查询场地，实现过滤查询

void printHallInfoByIndex(int index); // 通过场馆名称查询并显示信息

void read_site_menu_return_ad(void);//管理员返回场馆查询界面

void read_site_menu_return_user(void);//用户返回场馆查询界面


#endif